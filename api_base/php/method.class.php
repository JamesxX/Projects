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

?>