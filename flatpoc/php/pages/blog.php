<?php

// Pages : Blog

class BlogPage extends BlogTheme{
	public function BuildContent( ){
		print( '<h1>This is a proof of concept : Blog</h1>');
		
		$this->BlogPost( "This is the article title", "7th July 2015", "James", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras sodales luctus arcu eu vulputate. Sed leo nisi, consectetur vel turpis vel, porttitor pretium ipsum. Donec vitae libero luctus, egestas metus vitae, dignissim purus. Sed eleifend lectus sit amet mauris convallis, ac sollicitudin nunc varius. Aliquam dignissim laoreet condimentum. Nullam mi magna, varius vel tortor molestie, elementum congue orci. Integer lorem ante, posuere posuere mauris vitae, rutrum rutrum lorem." );
		$this->BlogPost( "This is the article title", "7th July 2015", "James", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras sodales luctus arcu eu vulputate. Sed leo nisi, consectetur vel turpis vel, porttitor pretium ipsum. Donec vitae libero luctus, egestas metus vitae, dignissim purus. Sed eleifend lectus sit amet mauris convallis, ac sollicitudin nunc varius. Aliquam dignissim laoreet condimentum. Nullam mi magna, varius vel tortor molestie, elementum congue orci. Integer lorem ante, posuere posuere mauris vitae, rutrum rutrum lorem." );
		$this->BlogPost( "This is the article title", "7th July 2015", "James", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras sodales luctus arcu eu vulputate. Sed leo nisi, consectetur vel turpis vel, porttitor pretium ipsum. Donec vitae libero luctus, egestas metus vitae, dignissim purus. Sed eleifend lectus sit amet mauris convallis, ac sollicitudin nunc varius. Aliquam dignissim laoreet condimentum. Nullam mi magna, varius vel tortor molestie, elementum congue orci. Integer lorem ante, posuere posuere mauris vitae, rutrum rutrum lorem." );
	}
	
	protected function BuildHead(){
	
	}
};

$Blog->PageSystem->AddPage( "blog", function( ){
	(new BlogPage)->BuildPage();
})

?>