<?php

include_once( "php/theme.class.php" );
include_once( "php/page.class.php" );
include_once( "php/blog.class.php" );

$Blog = new Blog;

include_once( "php/pages/index.php" );
include_once( "php/pages/404.php" );
include_once( "php/pages/upload.php" );
include_once( "php/pages/mod.php" );
include_once( "php/pages/image.php" );

$Blog->PageSystem->NegotiatePage();

?>