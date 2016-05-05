<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
	<title>DASA</title>
	<?php include 'includes.php' ?>
</head>
<body role="document">
<?php include 'nav.php' ?>
<?php
include('Net/SSH2.php');

// define variables and set to empty values
$tempErr = $modeErr = $xErr = $yErr = $zErr = "";
$temp = $mode = $x = $y = $z = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
   if (empty($_POST["temp"])) {
     $nameErr = "Temperature value is required.";
   } else {
     $temp = test_input($_POST["temp"]);
     if (!is_numeric($temp)) {
       $tempErr = "Only numbers are allowed."; 
     }
   }
   
   if (empty($_POST["mode"])) {
     $modeErr = "Shower mode is required.";
   } else {
     $mode = test_input($_POST["mode"]);
   }
     
   if (empty($_POST["x"])) {
     $xErr = "X value is required.";
   } else {
     $x = test_input($_POST["x"]);
   }

   if (empty($_POST["y"])) {
     $yErr = "Y value is required.";
   } else {
     $y = test_input($_POST["y"]);
   }

   if (empty($_POST["z"])) {
     $zErr = "Z value is required.";
   } else {
     $z = test_input($_POST["z"]);
   }
}

function test_input($data) {
   $data = trim($data);
   $data = stripslashes($data);
   $data = htmlspecialchars($data);
   return $data;
}
?>
<center>
<div class="container theme-showcase" role="main">
<form method="post" id="shower" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>"> 
   <strong>Shower Temperature:</strong>
   <div id="slider-temp"></div>
   <input id="temp" type="text" readonly name="temp" value="<?php echo $temp;?>"> Fahrenheit
   <br><br>
   <label for="mode">Shower Mode</label><br>
   <input type="radio" name="mode" value="rain" checked> Rain<br>
   <input type="radio" name="mode" value="shower"> Shower<br>
   <input type="radio" name="mode" value="massage"> Massage<br>
   <input type="radio" name="mode" value="jet"> Jet
   <br><br>
   Shower Head Position (Top-down view)<br>
   Drag shower head to desired position:
   <div id="canvas">
		<div id="box">
		Shower Head
        </div>
   </div>
   <input type="hidden" name="z" value="<?php echo $z;?>">
   <input type="hidden" name="x" value="<?php echo $x;?>">
   <strong>Shower Location (Up/Down)</strong>
   <br><br>
   <div id="slider-y"></div>
   <input id="y" type="hidden" readonly name="y" value="<?php echo $y;?>">
   <br><br>
   <br><br>
   <input type="submit" name="submit" value="Start Shower">
</form>
<br><br>
<?php
$tempstring = './dasademo temp ';
$tempstring .= $temp;
$modestring = './dasademo mode ';
$modestring .= $mode;
$xstring = './dasademo x ';
$xstring .= $x;
$ystring = './dasademo y ';
$ystring .= $y;
$zstring = './dasademo z ';
$zstring .= $z;

echo "$tempstring";
echo "<br />";
echo "$modestring";
echo "<br />";
echo "$xstring";
echo "<br />";
echo "$ystring";
echo "<br />";
echo "$zstring";

$ssh = new Net_SSH2('10.0.0.11');
if (!$ssh->login('nathanbrown', 'dasa')) {
    exit('Login Failed');
}

echo $ssh->exec("./dasademo on")
echo $ssh->exec($tempstring);
echo $ssh->exec($modestring);
echo $ssh->exec($xstring);
echo $ssh->exec($ystring);
echo $ssh->exec($zstring);


?>
<?php include 'footer.php' ?>
</center>
<script src="includes/js/ui_tools.js"></script>
