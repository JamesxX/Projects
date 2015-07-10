<?php

include_once( "theme.class.php" );
include_once( "page.class.php" );

class Blog{

	public $PageSystem;
	public $BaseTheme;
	
	public function __construct(){
		$this->PageSystem = new PageSystem;
		$this->BaseTheme = new BlogTheme;
	}

}


?>