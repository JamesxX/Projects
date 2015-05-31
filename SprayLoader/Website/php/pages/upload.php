<?php

// Pages : Upload

require_once( "php/database.php" );
require_once('php/steamauth/steamauth.php');

class UploadPage extends BlogTheme{
	
	public $Title = "Upload Page";
	
	/* Something generic to display */
	private function BuildHeadText( $profile ){
		print( "<h5>Solarpower SprayLoader P.O.C</h5>" );
		print( '<div class="row"><div class="col s9">');
		print( "<p> Welcome back, " . $profile['personaname'] . ". Nullam sit amet lacus vel neque placerat aliquet et ac purus. Donec ac semper mi. Vestibulum imperdiet risus eget justo mollis, consequat consequat nunc ullamcorper. Proin lectus urna, faucibus sit amet egestas ut, fringilla non nisi. Sed ut iaculis neque, ullamcorper tincidunt justo. Donec at tincidunt risus. Duis vel velit porta ante ornare condimentum. Suspendisse fermentum hendrerit rutrum. Phasellus dignissim suscipit magna nec mattis. Aliquam hendrerit nisi turpis, sed pulvinar justo aliquet nec. Aliquam velit odio, congue sit amet ornare eu, auctor vitae dolor. In nisi magna, interdum sed lacus nec, cursus viverra est. Fusce quis bibendum neque. Nam vehicula rhoncus nibh, in facilisis dolor maximus ut. Sed pellentesque, augue ut sodales pulvinar, arcu est sagittis risus, sit amet pharetra sem lorem ac felis.</p>");
		print( '</div><div class="col s3">');
		print( '<img src="'.$profile['avatarfull'].'" title="" alt="" />');
		print( '</div></div>');
	}
	
	
	public function scale_image($src_image, $dst_image, $op = 'fit') {
		$src_width = imagesx($src_image);
		$src_height = imagesy($src_image);
	 
		$dst_width = imagesx($dst_image);
		$dst_height = imagesy($dst_image);
	 
		// Try to match destination image by width
		$new_width = $dst_width;
		$new_height = round($new_width*($src_height/$src_width));
		$new_x = 0;
		$new_y = round(($dst_height-$new_height)/2);
	 
		// FILL and FIT mode are mutually exclusive
		if ($op =='fill')
			$next = $new_height < $dst_height;
		 else
			$next = $new_height > $dst_height;
	 
		// If match by width failed and destination image does not fit, try by height 
		if ($next) {
			$new_height = $dst_height;
			$new_width = round($new_height*($src_width/$src_height));
			$new_x = round(($dst_width - $new_width)/2);
			$new_y = 0;
		}
	 
		// Copy image on right place
		imagecopyresampled($dst_image, $src_image , $new_x, $new_y, 0, 0, $new_width, $new_height, $src_width, $src_height);
	}
	
	/* Check the uploaded file */
	private function CheckFile($file){
		if (!is_file($file)) {
			echo '<p>Debug: ', $_FILES['fileToUpload']['tmp_name'], ' file not found', "<p/><br>";
			$message = '<p>There was an error while trying to upload your file';
			
			switch( $_FILES['fileToUpload']['error'] ) {
				case UPLOAD_ERR_OK:
					return true;
				case UPLOAD_ERR_INI_SIZE:
				case UPLOAD_ERR_FORM_SIZE:
					$message .= ' - file too large (limit of '.ini_get('upload_max_filesize').' bytes). </p>';
					return false;
				case UPLOAD_ERR_PARTIAL:
					$message .= ' - file upload was not completed. </p>';
					return false;
				case UPLOAD_ERR_NO_FILE:
					$message .= ' - zero-length file uploaded. </p>';
					return false;
				default:
					$message .= ' - internal error #'.$_FILES['fileToUpload']['error'].'. Please try again later</p>';
					return false;
			}
			print $message;
		}
		return true;
	}
	
	
	/* Clean the image : TODO! */
	private function CleanImage( $Image ){
		
		$imagehandle = imagecreatefromstring($Image);
		$img_base = imagecreatetruecolor(512, 512);
		imagecopyresized($img_base, $imagehandle, 0, 0, 0, 0, 512, 512, imagesx($imagehandle), imagesx($imagehandle));
		$this->scale_image($imagehandle, $img_base,'fill');
		ob_start();
		imagejpeg($img_base);
		
		$Return = ob_get_contents();
		ob_clean();
		imagedestroy($img_base);
		return $Return;
	}
	
	/* Logic for when someone uploads something */
	private function TackleForm( $profile = array() ){
		$this->StartCardPanel();
		$this->BuildHeadText( $profile );
		
		if ( $this->CheckFile($_FILES['fileToUpload']['tmp_name']) ) {
			$handle = fopen($_FILES['fileToUpload']['tmp_name'], "rb");
			$image_f = $this->CleanImage( fread( $handle, filesize($_FILES['fileToUpload']['tmp_name'])) );

			$mysqli = GetDatabaseObject();
			$img = $mysqli->real_escape_string( $image_f );
			$query = sprintf( "INSERT INTO Images (SteamID64, Approved, Image) Values('%s', 0, '%s' ) ON DUPLICATE KEY UPDATE Approved = 0, Image = '%s'", $profile["steamid"], $img, $img);
	
			$mysqli->query( $query);
			$mysqli->close();
			
			print( "<p>Thank you for your submission. Your image will be moderated shortly</p>");
			logoutbutton();
		}
		$this->EndCardPanel();

	}
	
	/* What is displayed when the user isn't logged in */
	private function NotAuthed( ){
		
		$this->StartCardPanel();
		
		echo "<h5>SolarPower SprayLoader P.O.C</h5>";
		echo "<p>Welcome! This page is used to upload sprays to use on the server. Simply select the image you wish to upload, and press submit. Please remember that these images are submitted to moderation, and must respect the guidelines. These include but are not limited to not uploading images of a pornographic nature, and other such images. Just use common sense and you'll be fine.</p>";
		echo "<p>To upload an image, you must first be logged in. Please do this by pressing the button below.</p>";
		echo "<center>";
		steamlogin(); //login button
		echo "</center>";
		
		$this->EndCardPanel();
	}
	
	/* What to display when the user is logged in */
	private function Authed( $profile = array() ){
		
		$this->StartCardPanel();
		$this->BuildHeadText( $profile );
		print( "<p>Please select the the image you want to upload. Each submission will be manually moderated before being available for use. Pornography and other such material is not allowed.</p>");
		
		print( '<form action="index.php?p=upload" method="post" enctype="multipart/form-data">
					<div class="file-field input-field">
						<input class="file-path validate" type="text"/>
						<div class="btn">
							<span>File</span>
							<input type="file" name="fileToUpload" id="fileToUpload">
						</div>
					</div>
					<input type="submit" value="Upload Picture" name="submit">
				</form>');
		
		$this->EndCardPanel();
	}
	
	/* Build the content for the page */
	public function BuildContent( ){
		if(!isset($_SESSION['steamid'])) {
			$this->NotAuthed();
		}else{
			include ('php/steamauth/userInfo.php');
			if (!isset($_POST["submit"])){
				$this->Authed($steamprofile);
			}else{
				$this->TackleForm($steamprofile);
			}
		}
	}
};

$Blog->PageSystem->AddPage( "upload", function( ){
	$Page = new UploadPage;
	if (isset($_SESSION['steamid'])){
		$Page->NavLinks["Logout"] = "php/steamauth/logout.php?p=".$_GET['p'];
	}else{
		$Page->NavLinks["Login"] = "?login&p=".$_GET['p'];
	}
	$Page->BuildPage();
})

?>