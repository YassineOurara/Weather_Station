<?php

// Create connection
$con = mysqli_connect('localhost', 'root', '', 'moisture_base');

// Check connection
if ($con->connect_error) {
    die("Connection failed: " . $con->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $moisture = $_POST["moisture"];
    $temperature = $_POST["temperature"];
    
    // $sql = "INSERT INTO `soil_humi_table` (`val_humi`) VALUES ($moisture)";
    $sql = "INSERT INTO soil_humitemp_table (val_humi, val_temp) VALUES ('$moisture', '$temperature')";

    
    if ($con->query($sql) === TRUE) {
        echo "Number stored successfully";
    } else {
        echo "Error storing number: " . $con->error;
    }
}

$con->close();
?>
