<!DOCTYPE HTML> 
<html>
<head>
<style>
.error {color: #FF0000;}
</style>
</head>
<body> 

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

<h2>Shower Input</h2>
<p><span class="error">* required field.</span></p>
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>"> 
   Shower temperature: <input type="text" name="temp" value="<?php echo $temp;?>">
   <span class="error">* <?php echo $tempErr;?></span>
   <br><br>
   Shower mode: <input type="text" name="mode" value="<?php echo $mode;?>">
   <span class="error">* <?php echo $modeErr;?></span>
   <br><br>
   Shower Location: <br>
   X: <input type="text" name="x" value="<?php echo $x;?>">
   <span class="error"><?php echo $xErr;?></span>
   <br><br>
   Y: <input type="text" name="y" value="<?php echo $y;?>">
   <span class="error"><?php echo $yErr;?></span>
   Z: <input type="text" name="z" value="<?php echo $z;?>">
   <span class="error"><?php echo $zErr;?></span>
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

$ssh = new Net_SSH2('155.42.94.59');
if (!$ssh->login('nathanbrown', 'dasa')) {
    exit('Login Failed');
}

echo $ssh->exec($tempstring);
echo $ssh->exec($modestring);
echo $ssh->exec($xstring);
echo $ssh->exec($ystring);
echo $ssh->exec($zstring);


?>

</body>
</html>
