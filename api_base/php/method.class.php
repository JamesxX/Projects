<?php

abstract class API_Method{
	
	/** Overrides */
	abstract public function Check();
	abstract public function Output();
	
	/** Protected */
	protected $API;
	
	/** Public */
	public function SetParent( $API ){
		$this->API = $API;
	}
}

abstract class API_Method_AuthenticationRequired extends API_Method{
	
	public $required_arguments = array();
	
	abstract public function NotAuthed( $badkey ); // called if not
	abstract public function Authed( $key ); // Called if authenticated
	
	public function Authenticate( $key ){
		// Return true if authenticated
	}
	
	public function Check(){
		if ( !isset($_GET["key"]) ) return false;
		foreach ( $this->required_arguments as $Key=>$Value ){
			if ( !isset($_GET[$Key]) ) return false;
		}
		return true;
	}
	
	public function Output(){
		if ( $this->Authenticate( $_GET["key"] ) ){
			return $this->Authed( $_GET["key"] );
		}else{
			return $this->NotAuthed( $_GET["key"] );
		}
	}
}

?>