<?php

include_once "php/method.class.php";

class API_CAT_Method extends API_Method{
	
	public function Check(){
		return (null !== $this->GetInput("i") );
	}
	
	public function Output(){
		return $this->GetInput("i");
	}
	
}

$API->AddMethod( "cat", function(){ return new API_CAT_Method; } )

?>