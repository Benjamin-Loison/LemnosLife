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
			<script language="JavaScript">PopUp('show');</script>
   			<div id="slider">
    				<img src="Website/Media/Pictures/1.png" id="image" name="image" class="img"/>
    				<script language="JavaScript">autoSlideShow('image')</script>
			</div>
			<div id="text">
				
				<p>Bienvenue à toi ! Jeune aventurier, si tu recherches le 1er jeu vidéo francophone, plongé sur une île grecque, où tes ambitions guident ton roleplay alors tu es tombé au bon endroit ! <?php echo $product; ?> possède maintenant une grande communauté, rejoins nous:</p>
				<a class="button" id="button1" href="game.php">Télécharger le jeu vidéo <?php echo $product; ?></a>
			</div>
			<p id="legal_notices"><a href="legal notices.php">Mentions légales</a></p>
		</div>
	</body>
</html>
