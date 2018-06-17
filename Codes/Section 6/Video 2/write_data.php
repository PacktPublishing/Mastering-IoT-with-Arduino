<?php

    $dbusername = "root";  
    $dbpassword = "";  
    $server = "localhost"; 
    $dbname = "arduino";
   
    $dbconnect = mysqli_connect($server, $dbusername, $dbpassword,$dbname);
	
    if (!$dbconnect) {
        die("Database connection failed: " . mysqli_connect_error());
    }
	
    $dbselect = mysqli_select_db($dbconnect, $dbname);
    if (!$dbselect) {
        die("Database selection failed: " . mysqli_connect_error());
    }
	
    $sql = "INSERT INTO arduino.table1 (temperature,humidity,soilMoisture,lightPresence) VALUES ('".$_GET["temperature"]."','".$_GET["humidity"]."','".$_GET["soilmoisture"]."','".$_GET["ldrvalue"]."')";    

    mysqli_query($dbconnect,$sql);
?>
