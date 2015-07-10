<?php

// Pages : Blog

class LeakersPage extends BlogTheme{
	public function BuildContent( ){
		$Database = NULL;
		$Database = new mysqli('', '', '', '');

		if($Database->connect_errno > 0){
			die('Unable to connect to database [' . $Database->connect_error . ']');
		}else{
			try{
				
				if(!$result = $Database->query('SELECT * FROM leakers')){
					die('There was an error running the query [' . $Database->error . ']');
				}
				
				print( '<h1>Leaker Tracker</h1><table class="CSSTableGenerator" style="width: 100%"><tr><td>Name</td><td>Address</td><td>Addons</td><td>Users</td></tr>' );
				while ($row = $result->fetch_assoc()){
					print( "<tr><td>" . $row['Name'] . "</td><td>" . $row['IP'] .":". $row['Port'] . "</td><td>" . $row['Addons']. "</td><td>" . $row['Usergroups'] . "</td></tr>" );
				}
				print( '</table>' );
				
			}catch(PDOException $e){ 
				print( "While Insertion: FAIL!");
				var_dump( $e->getMessage() );
			}
		}
	}
	
	protected function BuildHead(){
	
	}
};

$Blog->PageSystem->AddPage( "mousetrap", function( ){
	(new LeakersPage)->BuildPage();
})

?>