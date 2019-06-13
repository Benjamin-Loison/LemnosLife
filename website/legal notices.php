<!DOCTYPE html>
<html lang="fr">
	<head>
		<title><?php include("Website/PhP/Menu.php"); echo $product; ?></title>
		<link rel="stylesheet" type="text/css" href="Website/Media/Style/Main.css" />
		<link rel="stylesheet" type="text/css" href="Website/Media/Style/Index.css" />
		<script language="JavaScript" src="Website/JavaScript/Menu.js"></script>
		<script language="JavaScript" src="Website/JavaScript/SlideShow.js"></script>
	</head>
	<body onLoad="preload()">
		<div id="box_gen">
   			<?php menu(); ?>
			<div id="text_cookies">
				<h1>Mentions légales:</h1>

				<h2>Description</h2>
				<?php echo $product; ?> est un jeu vidéo gratuit et ouvert à tous créé par Benjamin LOISON le 23 octobre 2018. Il en est également l'actuel propriétaire.

				<h2>Hébergement</h2>

				<h3>Hébergement relais</h3>
				Le traffic de <?php echo $product; ?> est transité par:<br/>
				OVH SAS<br/>
				2 rue Kellermann<br/>
				59100 Roubaix<br/>
				France<br/>

				<h3>Hébergement</h3>
				<?php echo $product; ?> est hébergé par Benjamin LOISON en France<br/><br/>
				

				<h2>Contact</h2>
				L'équipe du site peut-être contactée ainsi:<br/>
				- Email: serveur@lemnoslife.com<br/>
				- TeamSpeak 3: ts.lemnoslife.com<br/>
				- Facebook: https://fb.me/lemnoslife
			</div>
		</div>
	</body>
</html>
