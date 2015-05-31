<?php
require_once( "php/database.php" );

$Blog->PageSystem->AddPage( "image", function( ){
	header("Content-Type: image/jpeg");

	/* Break if the corp isn't supplied in the URL */
	if ( !isset($_GET['s']) ){
		readfile ( "images/NoSteam.png" );
		exit();
	}

	ob_start(); 
	$mysqli = GetDatabaseObject();
	ob_clean();

	/* Break if there is a MySQL problem */
	if ($mysqli->connect_errno) {
		readfile ( "images/NoSQL.png" );
		exit();
	}

	/* Get image from MySQL */
	if ($result = $mysqli->query("SELECT * FROM images WHERE SteamID64='". $mysqli->real_escape_string( $_GET['s'] ) ."' LIMIT 1")) {

		while($obj = $result->fetch_object()){ 
			
			/* Check if the image is approved */
			if ( !( $obj->Approved or isset($_GET["override"])) ){
				readfile ( "images/NotApproved.png" );
				$result->close();
				exit();
			}
			
			/* Sanitize image */
			$image = imagecreatefromstring($obj->Image);
			$img_base = imagecreatetruecolor(512, 512);
			imagecopyresized($img_base, $image, 0, 0, 0, 0, 512, 512, imagesx($image), imagesx($image));
			imagejpeg($img_base);
			
			/* Output Corporation Image and break */
			imagedestroy($img_base);
			$result->close();
			exit();
		}
		
		
		/* No image was found, output default */
		readfile ( "images/Default.png" );
		$result->close();
		exit();
	}

	$mysqli->close();

})

?>