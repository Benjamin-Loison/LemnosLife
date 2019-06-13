<?php

	function lg($element)
	{
		if(!isset($_COOKIE['language']))
		{
			switch($element)
			{
				case 'WELCOME': return 'ACCUEIL';
				case 'SHOP': return 'BOUTIQUE';
				case 'MAIL': return 'EMAIL';
				case 'Cookies make it easier for us to offer you our services. By using our services, you expressly give us your consent to use these cookies.': return 'Les cookies nous permettent de vous proposer nos services plus facilement. En utilisant nos services, vous nous donnez expressÃ©ment votre accord pour exploiter ces cookies.';
				case 'Close': return 'Fermer';
				case 'More': return 'En savoir plus';
				default: return 'TRADUCTION NON TROUVEE';
			}
		}
		return $element;
	}
	
?>