<?php

// Moderation Page

require_once( "php/database.php" );
require_once('php/steamauth/steamauth.php');

class ModerationPage extends BlogTheme{
	
	public $Title = "Moderator Page";
	
	/* Helper function to create display for image */
	private function BuildModerationThingy( $ID ){
		print('<div class="col s4">');
		$this->CardImage($ID, "index.php?override&p=image&s=".$ID, "", array("Approve"=>"index.php?p=mod&approve=".$ID, "Delete"=>"index.php?p=mod&delete=".$ID));
		print('</div>');
	}
	
	/* What is displayed when the user isn't logged in */
	private function NotAuthed( ){
		
		$this->StartCardPanel();
		echo "<h5>SolarPower SprayLoader Moderation P.O.C</h5>";
		echo "<p>Welcome! This page is used to moderate images uploaded through the upload page. Feel free to try and log in, but you won't have access.</p>";
		echo "<center>";
		steamlogin(); //login button
		echo "</center>";
		$this->EndCardPanel();
	}
	
	/* What is displayed when the user is logged in */
	private function BuildModeratorPage($profile){
		$mysqli = GetDatabaseObject();
		if ($result = $mysqli->query("SELECT SteamID64 FROM images WHERE Approved=0")) {
			$counter = 0;
			print( '<div class="row">' );
			while($obj = $result->fetch_object()){ 
				if ($counter == 3 ){
					print('</div><div class="row">');
				}
				$this->BuildModerationThingy( $obj->SteamID64 );
				$counter++;
			}
			print( '</div>' );
			
			$result->close();
		}
		$mysqli->close();
	}
	
	/* Logic for the moderating */
	private function HandleModeration($profile){
		if ( isset($_GET["approve"]) ){
			$mysqli = GetDatabaseObject();
			$mysqli->query(sprintf("UPDATE images SET Approved=1 WHERE SteamID64='%s'", $mysqli->real_escape_String($_GET["approve"])));
		}
		
		if ( isset($_GET["delete"]) ){
			$mysqli = GetDatabaseObject();
			$mysqli->query(sprintf("DELETE FROM images WHERE SteamID64='%s'", $mysqli->real_escape_String($_GET["delete"])));
		}
		
	}
	
	/* Generate the content for the page */
	public function BuildContent( ){
		if(!isset($_SESSION['steamid']) or $_SESSION['steamid'] != "76561198006055559") {
			$this->NotAuthed();
		}else{
			include ('php/steamauth/userInfo.php');
			$this->HandleModeration($steamprofile);
			$this->BuildModeratorPage($steamprofile);
		}
	}
};

$Blog->PageSystem->AddPage( "mod", function( ){
	$Page = new ModerationPage;
	if (isset($_SESSION['steamid'])){
		$Page->NavLinks["Logout"] = "php/steamauth/logout.php?p=".$_GET['p'];
	}else{
		$Page->NavLinks["Login"] = "?login&p=".$_GET['p'];
	}
	$Page->BuildPage();
})

?>