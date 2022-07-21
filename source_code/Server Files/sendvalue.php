<?php

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "SmartAirMonitor";
$conn = new mysqli($servername, $username, $password, $dbname);

$sensor=$_GET["sensor_id"];
$lpg=$_GET["lpg"];
$density=$_GET["density"];
echo $sensor;
echo $lpg;
echo $density;

if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
$sql="INSERT INTO SensorData (sensor_id,lpg,dust_density) VALUES ($sensor,$lpg,$density )";
$result = $conn->query($sql);
$conn->close();
//UPDATE relays SET exhaust=0,air_purifier=0;



 ?>
