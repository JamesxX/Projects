<?php

abstract class API_Method{
	
	/** Overrides */
	abstract public function Check();
	abstract public function Output();
	
	/** Private */
	private $API = null;
	
	/** Public */
	public function SetParent( $API ){
		$this->API = $API;
	}
}

?>