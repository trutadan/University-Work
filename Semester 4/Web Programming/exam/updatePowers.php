<?php
    require "connection.php";

    session_start();
    $id = $_SESSION['id'];

    if ($id == '') {
        header("Location: login.html");
    }

    $conn = openConnection();

    $newPowers = $_POST['powers'];

    mysqli_query($conn, "UPDATE superhero SET powers = '$newPowers' WHERE id = '$id'");

    header("Location: main.html");

    closeConnection($conn);
?>
