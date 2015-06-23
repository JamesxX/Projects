<?php

include_once "php/method.class.php";

class API_ExampleTraitMethod extends API_Method_AuthenticationRequired{
	use Database, NoRequiredArguments, DefaultNoAPIKeyMessage;
	
	public function Authed( $key ){
		
		$ID = 1;
		
		$prepstatement = $this->Database->prepare( 'SELECT * FROM gm_user WHERE ID = :ID' );
		$prepstatement->bindParam(":ID", $ID);
		$prepstatement->execute();
		
		$array = $prepstatement->fetchAll( );
		
		/** Sanitize */
		foreach ( $array[0] as $key=>$value ){
			if ( gettype( $key ) == "integer" ){
				unset( $array[0][$key] );
			}
		}
		
		return $array[0];

	}
}

$API->AddMethod( "test", function(){ return new API_ExampleTraitMethod; } )


?>