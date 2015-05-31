<?php

// Pages : Home

class ErrorPage extends BlogTheme{
	public function BuildContent( ){
		$this->CardPanel("<center><img src=\"http://zenit.senecac.on.ca/wiki/imgs/404-not-found.gif\"/></center><p>So, you tried to access a page that doesn't exist, huh? Thought it would be funny did you? I'm not one to push blame onto other people, but this is very obviously your fault. Did you try to retrace your steps?</p><p> If the error persists, please contact <a href=\"mailto:james.rt.swift@gmail.com\">The awesome webmaster</a> so he can patronize you some more.");
	}
};

$Blog->PageSystem->AddPage( "error404", function( ){
	(new ErrorPage)->BuildPage();
});

?>