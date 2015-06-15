<?php

include_once "php/method.class.php";

class API_404 extends API_Method{
	
	public function Check(){ return true; }
	
	public function Output(){
		$this->API->status = "failed";
		return "There is an error in the URL. Please rectify.";
	}
	
}

$API->AddMethod( "failed", function(){ return new API_404; } )

?>