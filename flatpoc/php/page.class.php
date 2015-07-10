<?php

class PageSystem{
	public $DefaultPage = "index";
	public $ErrorPage = "error404";
	public $Pages = array();
	
	public function GetPage( ){
		if ( isset($_GET['p']) ){
			$PageName = strtolower($_GET['p']);
			if ( isset( $this->Pages[$PageName] ) ){
				return $PageName;
			}else{
				return $this->ErrorPage;
			}
		}else{
			return $this->DefaultPage;
		}
	}
	
	public function AddPage( $id, $function ){
		$this->Pages[$id] = $function;
	}
	
	public function NegotiatePage(){
		$this->Pages[$this->GetPage()]( );
	}
};


?>