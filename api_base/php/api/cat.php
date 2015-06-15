<?php

include "php/method.class.php";

class API_CAT_Method extends API_Method{
	
	public function Check(){
		return isset( $_GET["i"] );
	}
	
	public function Output(){
		return $_GET["i"];
	}
	
}

$API->AddMethod( "cat", function(){ return new API_CAT_Method; } )

?>