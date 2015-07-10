function ChangePage( but, NewPage ){

	var NewPageLower = NewPage.toLowerCase();
	var CurrentPage = document.getElementById('content').getAttribute( "page" );
	
	if( NewPageLower != CurrentPage ){
		
		$('.content').fadeOut(400, function(){
			var xmlhttp;
			if (window.XMLHttpRequest){
				xmlhttp=new XMLHttpRequest();
			}else{
				xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
			}
			xmlhttp.onreadystatechange=function(){
				if (xmlhttp.readyState==4 && xmlhttp.status==200){
					$('.content').html( xmlhttp.responseText );
					$('.content').fadeIn(400, function(){});
					
					if ( NewPageLower != "index" ){
						window.history.pushState({},"",NewPage );
					}else{
						window.history.pushState({},"","/flatpoc/" );
					}
					document.getElementById('content').setAttribute( "page", NewPageLower );
				}
			}
			xmlhttp.open( "GET", "index.php?internal&p="+NewPage , true );
			xmlhttp.send( null );
		});
		$("[active='true']").removeAttr( "active" );
		but.setAttribute( "active", true );
	}
	return true;
}

$(document).ready(function() {

	$('.content').css('display', 'none');
	$('.content').fadeIn(500);

});