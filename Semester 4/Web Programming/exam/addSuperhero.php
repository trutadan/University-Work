<?php
    require "connection.php";

    $conn = openConnection();

    session_start();

    $name = $_SESSION['name'] ?? '';

    if ($name == '') {
        header("Location: login.html");
    }

    $superheroName = $_POST["name"];
    $powers = $_POST['powers'];

    $result = mysqli_query($conn, "SELECT * FROM superhero WHERE name = '" . $superheroName . "'");
    $row = mysqli_fetch_array($result);

    if (!$row) {
        mysqli_query($conn, "INSERT INTO superhero (name, powers) VALUES ('$superheroName', '$powers')");
    }

    closeConnection($conn);
?>
