<?php $product = 'LemnosLife';
      $productTitle = 'Lem n o s&emsp;Life';
	  
	  include 'Translation.php';

	function menu()
	{
		$menu = false;
		echo '<meta charset="utf-8" />
			<link rel="shortcut icon" href="favicon.ico" type="image/x-icon">
			<ul id="menu">
	    		<li><a class="reception" href=".">' . lg('WELCOME') . '</a></li>
	    		<li><a class="a1" href="http://lemnoslife.com/Shop">' . lg('SHOP') . '</a></li>';
	    		//<li><a class="a1" href="http://altiscraft.fr:8123">CARTE</a></li>
	    	echo '<li><a class="a1" href="ts3server://ts.lemnoslife.com:9987">TEAMSPEAK 3</a></li>
	    		<li><a class="a1">' . lg('MAIL') . '</a>
			<ul>
			<li><a class="a2">SERVEUR@LEMNOSLIFE.COM</a></li>
			</ul>
			</li>
			<a href="." id="triangle"></a>';/*
			<li><input type="button" onclick="alert(\"ah\")">
			
			<object type="image/svg+xml" data="Website/Media/Pictures/';
			if(isset($_COOKIE["language"]))
				echo 'french';
			else
				echo 'english';
			echo '.svg" width="200" height="100">Change language</object>
			
			</a></li>*/
			echo '
			</ul>
			<div id="banner"><p>' . $GLOBALS['productTitle'] . '</p></div>
			<div id="ac-wrapper" style="display: none" onClick="hideNow(event)">
    			<div id="popup">
        			<center>
             		<h2>' . lg('Cookies make it easier for us to offer you our services. By using our services, you expressly give us your consent to use these cookies.') . '</h2> 
					<input type="submit" name="submit" value="' . lg('Close') . '" onClick="PopUp(\'hide\')" />
					<input type="submit" value="' . lg('More') . '" onClick="location.href=\'cookies.php\';"/> 
					</center>
    			</div>
			</div>';
	}

?>
