<?php

abstract class API_Method{
	
	/** Overrides */
	abstract public function Check();
	abstract public function Output();
	
	/** Protected */
	protected $API;
	
	protected $UseDatabase = false; /** Set this to true when extending to enable database */
	protected $Database;
	
	protected function GetInput( $Name ){
		if ( isset( $this->API ) ){
			return $this->API->input[ $Name ];
		}
	}	
	
	/** Public */
	public function SetParent( $API ){
		$this->API = $API;
	}
	
	public function InitiateDatabase( ){
		if ( $this->UseDatabase ){
			try{
				$this->Database = new PDO('mysql:host=hostname;dbname=ssldb','username','password'); /** Fill this in */
				$con->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);
			}
			catch (PDOException $e)  
			{ 
				die( json_encode($this->BuildOutput( false, "MySQL Error", $e->getMessage() ), JSON_PRETTY_PRINT));  
			}
		}
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
		if ( null == $this->GetInput("key") ) return false;
		foreach ( $this->required_arguments as $Key=>$Value ){
			if ( null == $this->GetInput($Value) ) return false;
		}
		return true;
	}
	
	public function Output(){
		if ( $this->Authenticate( $this->GetInput("key") ) ){
			return $this->Authed( $this->GetInput("key") );
		}else{
			return $this->NotAuthed( $this->GetInput("key") );
		}
	}
}

?>