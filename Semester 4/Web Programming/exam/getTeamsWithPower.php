<?php
    require "connection.php";

    $conn = openConnection();

    session_start();

    $name = $_SESSION['name'] ?? '';

    if ($name == '') {
        header("Location: login.html");
    }

    $power = $_GET['power'];

    $result = mysqli_query($conn, "SELECT * FROM team WHERE EXISTS (SELECT 1 FROM superhero WHERE FIND_IN_SET(name, REPLACE(superherosList, ', ', ',')) > 0 AND FIND_IN_SET('$power', REPLACE(powers, ', ', ',')) > 0)");
    while ($row = mysqli_fetch_array($result)) {
        echo $row['name'] . "<br>";
    }

    closeConnection($conn);
?>
