<?php

$Blog = false;

include_once( "php/theme.class.php" );
include_once( "php/page.class.php" );
include_once( "php/blog.class.php" );

$Blog = new Blog;

include_once( "php/pages/index.php" );
include_once( "php/pages/404.php" );
include_once( "php/pages/blog.php" );
include_once( "php/pages/mousetrap.php" );

$Blog->PageSystem->NegotiatePage();

?>