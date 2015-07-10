<?php

// Pages : Home

class IndexPage extends BlogTheme{
	public function BuildContent( ){
		print( '<h1>This is a proof of concept</h1>
				
				<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras sodales luctus arcu eu vulputate. Sed leo nisi, consectetur vel turpis vel, porttitor pretium ipsum. Donec vitae libero luctus, egestas metus vitae, dignissim purus. Sed eleifend lectus sit amet mauris convallis, ac sollicitudin nunc varius. Aliquam dignissim laoreet condimentum. Nullam mi magna, varius vel tortor molestie, elementum congue orci. Integer lorem ante, posuere posuere mauris vitae, rutrum rutrum lorem.</p>
				<p>Nunc tempor nunc ac mi pulvinar, a facilisis neque molestie. Etiam odio ex, sollicitudin ut arcu eu, ultricies mattis diam. Morbi pharetra eleifend orci, non molestie lacus. Morbi id scelerisque ipsum. Nullam a varius diam. Morbi ornare nisi ligula, a efficitur sapien bibendum quis. Nam molestie eget diam ac fringilla.</p>
			
				<div class="form">
					<form>
						<input placeholder="Username" type="text">
						<input placeholder="Password" type="password">
						<button>Login</button>
					</form>
				</div>');
	}
	
	protected function BuildHead(){
	
	}
};

$Blog->PageSystem->AddPage( "index", function( ){
	(new IndexPage)->BuildPage();
})

?>