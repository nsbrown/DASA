<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
	<title>DASA</title>
	<?php include 'includes.php' ?>
	<script>
		$(function() {
			$( "#slider-temp" ).slider({
				range: "max",
				min: 75,
				max: 110,
				value: 75,
				slide: function( event, ui ) {
					$( "#temp" ).val( ui.value );
				}
			});
			$( "#temp" ).val( $( "#slider-temp" ).slider( "value" ) );
		});
	</script>
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

<div id="wrapper">
<h2>Shower Input</h2>
<p><span>* required field.</span></p>
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>"> 
   <label for="temp">Shower Temperature:</label>
   <input id="temp" type="text" readonly name="temp" value="<?php echo $temp;?>">
   <div id="slider-temp"></div>
   <span>* <?php echo $tempErr;?></span>
   <br><br>
   Shower mode: <input type="text" name="mode" value="<?php echo $mode;?>">
   <span>* <?php echo $modeErr;?></span>
   <br><br>
   Shower Location: <br>
   X: <input type="text" name="x" value="<?php echo $x;?>">
   <span><?php echo $xErr;?></span>
   <br><br>
   Y: <input type="text" name="y" value="<?php echo $y;?>">
   <span><?php echo $yErr;?></span>
   Z: <input type="text" name="z" value="<?php echo $z;?>">
   <span><?php echo $zErr;?></span>
   <br><br>
   <input type="submit" name="submit" value="Submit"> 
</form>

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

/*$ssh = new Net_SSH2('155.42.112.33');
if (!$ssh->login('nathanbrown', 'dasa')) {
    exit('Login Failed');
}

echo $ssh->exec($tempstring);
echo $ssh->exec($modestring);
echo $ssh->exec($xstring);
echo $ssh->exec($ystring);
echo $ssh->exec($zstring); */


?>
<?php include 'footer.php' ?>