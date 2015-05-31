<?php

class PageSystem{
	public $DefaultPage = "index";
	public $ErrorPage = "error404";
	public $Pages = array();
	
	public function AddPage( $id, $function ){
		$this->Pages[$id] = $function;
	}
	
	public function NegotiatePage(){
		if ( isset($_GET['p']) ){
			$PageName = strtolower($_GET['p']);
			if ( isset( $this->Pages[$PageName] ) ){
				$this->Pages[$PageName]( );
			}else{
				$this->Pages[$this->ErrorPage]( );
			}
		}else{
			$this->Pages[$this->DefaultPage]( );
		}
	}
};


?>