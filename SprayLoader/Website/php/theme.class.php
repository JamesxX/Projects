<?php

class BlogTheme{
	
	// Constants
	
	public $SiteName = "My Proof Of Concept";
	public $Title = "This is my page title";
	public $CopyrightText = "© 2015 James Rupert Swift";
	
	public $NavLinks = array("<i class=\"mdi-action-search\"></i> Home"=>"?p=index",
		"<i class=\"mdi-action-view-module\"></i> Upload"=>"?p=upload",
		"Moderate"=>"?p=mod");
	public $FooterLinks = array("Home"=>"?p=index");
	
	// Hooks
	
	public function BuildContent(){
		
	}
	
	// Functions
	
	public function BuildHead($Title){
		print('	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
		<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no"/>
		<title>'.$Title.'</title>
		
		<!-- CSS  -->
		<link href="css/materialize.css" type="text/css" rel="stylesheet" media="screen,projection"/>
		<link href="css/style.css" type="text/css" rel="stylesheet" media="screen,projection"/>
	</head>
	<body>');

	}
	
	public function BuildNavBar($SiteName, array $NavLinks){
		print('		<nav class="nav-wrapper light-blue darken-3">
			<div class="container">
				<a href="#" class="brand-logo">'.$SiteName.'</a>
				<ul id="nav-mobile" class="right hide-on-med-and-down">');
				
		foreach ( $NavLinks as $Name=>$URL ) {
			print('					<li><a class="waves-effect waves-light" href="'.$URL.'">'.$Name.'</a></li>');
		}
				
		print('				</ul>
			</div>
		</nav>');
		
		
	}
	
	public function StartContainer( ){
		print('<div class="container">');
	}
	
	public function CardPanel( $HTML ){
		$this->StartCardPanel();
		print($HTML);
		$this->EndCardPanel();
	}
	
	public function StartCardPanel( ){
		print('<div class="card-panel"><span class="dark-grey-text text-darken-4">');
	}
	
	public function EndCardPanel( ){
		print('</span></div>');
	}
	
	public function CardImage($Title, $Image, $Content, array $links ){
		print( '<div class="card">
				<div class="card-image">
					<img src="'.$Image.'">
					<span class="card-title">'.$Title.'</span>
				</div>');
		if ( $Content != "" ){
			print('<div class="card-content dark-grey-text text-darken-4"> <p>'.$Content.'</p> </div>');
		}
		
		print('<div class="card-action">');
		foreach ( $links as $Name=>$URL ) {
			print('<a href="'.$URL.'">'.$Name.'</a>');
		}
		print('</div>
			</div>');
		
	}
	
	public function EndContainer( ){
		print('		</div>');
	}
	
	public function BuildFooter($CopyrightText, $FooterLinks ){
		print('<footer class="page-footer light-blue darken-3">
			<div class="footer-copyright">
				<div class="container">');
		print("				$CopyrightText");
		foreach ( $FooterLinks as $Name=>$URL ) {
			print('					<a class="grey-text text-lighten-4 right waves-effect waves-light" href="'.$URL.'">'.$Name.'</a>');
		}
		print('				</div>
			</div>
		</footer>');
		
	}
	
	
	public function BuildPage( ){
		print('<!DOCTYPE html>
<html lang="en">');

		$this->BuildHead($this->Title);
		$this->BuildNavBar($this->SiteName, $this->NavLinks);
		
		$this->StartContainer( );
		$this->BuildContent();
		$this->EndContainer( );
		
		$this->BuildFooter($this->CopyrightText, $this->FooterLinks );
		print('	<!--  Scripts-->
		<script src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
		<script src="js/materialize.js"></script>
		<script src="js/init.js"></script>
	
		</body>
</html>');
	}
	
	
};


?>