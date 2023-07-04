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
    
    // Escape the values to prevent SQL injection
    $moisture = mysqli_real_escape_string($con, $moisture);
    $temperature = mysqli_real_escape_string($con, $temperature);
    
    $sql = "INSERT INTO soil_humitemp_table (val_humi, val_temp) VALUES ('$moisture', '$temperature')";
    
    if ($con->query($sql) === TRUE) {
        echo "Data stored successfully";
    } else {
        echo "Error storing data: " . $con->error;
    }
}

$con->close();
?>
