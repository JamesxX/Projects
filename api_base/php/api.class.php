<?php

include "error.enum.php";

class API{
	
	/** Private */
	private $methods = array();
	
	private function GetCurrentMethod( ){
		foreach ( $this->methods as $Key=>$Value ){
			if ( isset($_GET[$Key]) ) return $Key;
		}
		return "Error";
	}
	
	private function BuildOutput( $Success, $Name, $Output, $Base64 = false ){
		$output = array();
		$output["status"] = $Success ? "success" : "error";
		
		if ( $Success ){
			$output["Name"] = $Name;
			
			if ( $Base64 and gettype( $Output ) == "string" ){
				$output["output"] = base64_encode( $output );
			}else{
				$output["output"] = $Output;
			}
		}else{
			$output["code"] = $Name;
			$output["output"] = $Output;
		}
		return $output;
	}
	
	/** Public */
	
	public function AddMethod( $sName, $fCallable ){
		if ( isset($this->methods[$sName]) ) return API_ErrorEnum::MethodAlreadyExists;
		
		$this->methods[$sName] = $fCallable;
		return API_ErrorEnum::Success;
	}
	
	public function HandleExecution( $sName ){
		if ( !isset($this->methods[$sName]) ) return API_ErrorEnum::NoMethodExists;
		
		$method = $this->methods[$sName]();
		$method->SetParent( $this );
		
		if ( $method->Check() ){
			return $method->Output();
		}
		
		return API_ErrorEnum::MethodFailedChecks;
	}
	
	public function Run( ){
		$Name = $this->GetCurrentMethod( );
		$Output = $this->HandleExecution( $Name );
		if ( gettype($Output) == "array" or gettype($Output) == "string" ){
			print( json_encode($this->BuildOutput( true, $Name, $Output ), JSON_PRETTY_PRINT) );
		}else{
			print( json_encode($this->BuildOutput( false, $Output, "Something went wrong with your query" ), JSON_PRETTY_PRINT) );
		}
	}
}

?>