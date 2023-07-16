<?php
    require "connection.php";

    $conn = openConnection();

    session_start();

    $name = $_SESSION['name'] ?? '';

    if ($name == '') {
        header("Location: login.html");
    }

    $result = mysqli_query($conn, "SELECT powers FROM superhero WHERE name = '$name'");
    $row = mysqli_fetch_array($result);
    $powers = $row['powers'];

    echo $powers;

    closeConnection($conn);
?>
