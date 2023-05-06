<?php

$con = mysqli_connect('localhost', 'root', '', 'ht_data_test');

$filename = "C:\\xampp\\htdocs\\lms\\htdata.json";

$data = file_get_contents($filename);

$array = json_decode($data, true);
// echo "<pre>";
// print_r($array);
// echo "</pre>";


foreach ($array as $value) {

    $query = "INSERT INTO `jsontable` (`name`, `gender`, `designation`) VALUES ('" . $value['name'] . "', '" . $value['gender'] . "' , '" . $value['designation'] . "')";

    mysqli_query($con, $query);
}

echo "Data Inserted Successfully";

?>
