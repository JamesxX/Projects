<?php

class BlogTheme{
	
	// Constants
	
	public $Title = "This is my page title";
	public $favicon = "favicon.ico";
	
	public $NavLinks = array( 
		array("flaticon-home7", "Index"),
		array("flaticon-daily-calendar2","Blog"),
		array("flaticon-cloud387","CDN"),
		array("flaticon-folder287","Mousetrap")
	);
	
	// Hooks
	
	protected function BuildContent(){}
	protected function BuildHead(){}
	
	
	// Functions
	
	public function GenerateHead($Title){
		print('<head>');
		print('<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>');
		print('<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no"/>');
		
		print('<link rel="stylesheet" href="css/style.css">');
		print('<link rel="icon"  type="image/icon" href="'. $this->favicon .'">');
		print('<script src="https://code.jquery.com/jquery-2.1.4.min.js"></script>');
		print('<script src="js/page.js"></script>');
		
		$this->BuildHead();
		print("<title>$Title</title>" );
		print('</head><body>');

	}
	
	public function BuildNavBar(array $NavLinks){
		print( "<nav><ul>");
		foreach ( $NavLinks as $Array ) {
			if ( strtolower($Array[1]) == $GLOBALS['Blog']->PageSystem->GetPage() ){
				print('<li><a onClick="ChangePage(this, \''.$Array[1].'\'); return false;" href="'.$Array[1].'" active="true"><span class="'.$Array[0].'">&nbsp;</span></a></li>');
			}else{
				print('<li><a onClick="ChangePage(this, \''.$Array[1].'\'); return false;" href="'.$Array[1].'"><span class="'.$Array[0].'">&nbsp;</span></a></li>');
			}
		}		
		print('</ul></nav>');
	}
	
	function StartContainer( ){
		print( '<div class="page"><div id="content" class="content" page="'.$GLOBALS['Blog']->PageSystem->GetPage().'">' );
	}
	
	function EndContainer( ){
		print( '</div></div>' );
	}

	function BlogPost( $Title, $Time, $Author, $Content ){
		print( "<article><header><h1>$Title<time><p>By $Author on</p>$Time</time></h1></header><main>$Content</main></article>");
	}
	public function BuildPage( ){
		print('<!DOCTYPE html><html lang="en">');

		if (!isset( $_GET["internal"] ) ){
			$this->GenerateHead($this->Title);
			$this->BuildNavBar($this->NavLinks);
			
			$this->StartContainer( );
		}
		
		$this->BuildContent();
		
		if (!isset( $_GET["internal"] ) ){
			$this->EndContainer( );
		}
		
		print('</body></html>');
	}
};


?>