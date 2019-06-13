<!DOCTYPE html>
<html lang="fr">
	<head>
		<title><?php include 'Website/PhP/Menu.php'; echo $product; ?></title>
		<link rel="stylesheet" type="text/css" href="Website/Media/Style/Main.css"/>
		<link rel="stylesheet" type="text/css" href="Website/Media/Style/Launcher.css"/>
		<link rel="icon" type="image/png" href="Website/Media/Pictures/Icon.png"/>
		<script language="JavaScript" src="Website/JavaScript/Menu.js"></script>
	</head>
	<body>
		<div id="box_gen">
		<?php menu(); ?>
		<div id="text"><p>Télécharger le jeu vidéo <?php echo $product; ?></p></div>
		<img src="Website/Media/Pictures/Launcher.png" id="launcher"/>
		<a class="button" id="button1" href="<?php echo $product; ?>.exe">Télécharger le jeu vidéo <?php echo $product; ?> Windows</a>
  		<div id="list">
   		<ul>
    			<li>Le jeu vidéo <?php echo $product; ?> est optimisé pour tous les types de configurations.</li>
    			<li>Fait avec les technologies les plus performantes, permettez vous un véritable gain de FPS !</li>
				<li>Gameplay basé sur un roleplay entre civiles, gendarmes et rebelles.</li>
				<li>Le tout sur une île grecque de 476 km², importée de la vraie vie.</li>
    			<li>Mises à jour automatiques optimisées.</li><br/>
				<li>Vous aimez le jeu <?php echo $product; ?> et vous souhaitez être tenu informé des nouveautés ?<br/>
				Abonnez vous à notre newsletter (email d'informations) que nous envoyons occasionnellement.<br/>
				Pour ce faire envoyer un email à newsletter@lemnoslife.com</li>
				
   		</ul>
 	</body>
</html>
