<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 5; URL=$url");  
?>
<html>
<head>
    <title>Gardening System</title>
</head>
    <body>
        <h1>Sensor readings</h1>
    <table border="6" cellspacing="4" cellpadding="8">
      <tr>
            <td>ID</td>
            <td>Timestamp</td>
            <td>Temperature</td>
			<td>Humidity</td>
			<td>SoilMoisture</td>
			<td>LDR</td>
      </tr>
    
<?php

    $con=mysqli_connect("localhost","root","","arduino");
       
 
    $result = mysqli_query($con,"SELECT * FROM table1 ORDER BY id DESC");
      

    
	
    while($row = mysqli_fetch_array($result))
    {      
        echo "<tr>";
        echo "<td>" . $row['id'] . "</td>";
        echo "<td>" . $row['time'] . "</td>";
        echo "<td>" . $row['temperature'] . "</td>";
		echo "<td>" . $row['humidity'] . "</td>";
		echo "<td>" . $row['soilMoisture'] . "</td>";
		echo "<td>" . $row['lightPresence'] . "</td>";
        echo "</tr>";
        
    }
    
  
    mysqli_close($con);
?>	
    </table>
    </body>
</html>