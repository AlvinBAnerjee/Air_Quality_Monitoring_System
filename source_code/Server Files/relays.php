<?php

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "SmartAirMonitor";
$conn = new mysqli($servername, $username, $password, $dbname);

$exhaust=$_GET["exhaust"];
$purifier=$_GET["purifier"];
echo $exhaust;
echo $purifier;


if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
$sql="UPDATE relays SET exhaust=$exhaust,air_purifier=$purifier";
$result = $conn->query($sql);
$conn->close();
//UPDATE relays SET exhaust=0,air_purifier=0;



 ?>
