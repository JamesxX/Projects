<?php

// Pages : 404

class ErrorPage extends BlogTheme{
	public function BuildContent( ){
		print( "<h1>Error 404</h1>" );
	}
};

$Blog->PageSystem->AddPage( "error404", function( ){
	(new ErrorPage)->BuildPage();
});

?>