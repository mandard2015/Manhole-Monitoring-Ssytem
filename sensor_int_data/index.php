<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="5" >
    <link rel="stylesheet" type="text/css" href="style.css" media="screen"/>

	<title> MQ2 Data </title>

</head>

<style>
    <?php include "style.css" ?>
</style>
<body class="background firstSection" id="home">
    <nav class="navbar background h-nav-resp ">
        <h1>Manhole Monitoring System</h1>
    </nav>
    <!-- <div class="services"> -->
    <!-- <div class="column" style="padding: 5px, height: 300px, overflow-y: scroll;">
        <h2>MQ2 GAS DATA</h2> -->
<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "manhole";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, location, value1, value2, value3, reading_time FROM all_sensor_data ORDER BY id DESC";//value3, 
/*select items to display from the sensordata table in the data base*/

echo '<table style="height: 250px; overflow-y: scroll;" cellspacing="5" cellpadding="5">
        <tbody height="250px">
        <tr>
        <th>ID</th> 
        <th>Date $ Time</th> 
        <th>Location</th> 
        <th>Gas level</th>
        <th>Lid presence</th> 
        <th>Water level</th>    
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_reading_time = $row["reading_time"];
        $row_location = $row["location"];
        $row_value1 = $row["value1"];
        $row_value2 = $row["value2"]; 
        $row_value3 = $row["value3"]; 

        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
       // $row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
        $status_colors = array(0 => '#FF0000', 1 => '#666');
        echo "<tr> 
                <td>$row_id</td> 
                <td>$row_reading_time</td> 
                <td>$row_location</td> 
                <td>$row_value1</td>
                <td style='background-color: $status_colors[$row_value2];'>$row_value2</td>
                <td>$row_value3</td>
              </tr>";//<td>$row_value2</td> <td>' . $row_value3 . '</td> 
    }
    $result->free();
}
$conn->close();
?>
</table>
        </div>
        <div class="column" style="padding: 5px;">
        <h2>SLUDGE DATA</h2>
        <table>
            <tr>
            <th>ID</th> 
            <th>Date $ Time</th>
            <th>Location</th> 
            <th>Capacitance</th>
            </tr>
</tbody>
</table>
        </div>
<!-- </div> -->
</body>
</html>
