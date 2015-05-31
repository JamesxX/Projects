<?php

// Pages : Home

class IndexPage extends BlogTheme{
	public function BuildContent( ){
		$this->CardImage("Title", "images/Placeholder.jfif", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla varius vestibulum nisl. Pellentesque pharetra dignissim mauris non semper. Aenean luctus tellus vel tempor suscipit. Integer commodo iaculis commodo. Cras in leo eu magna pretium imperdiet. Maecenas sed lobortis elit, quis venenatis eros. Sed a magna non orci ultrices facilisis consectetur vel mauris.", array("Link1"=>"#", "Link2"=>"#"));
	}
};

$Blog->PageSystem->AddPage( "index", function( ){
	(new IndexPage)->BuildPage();
})

?>