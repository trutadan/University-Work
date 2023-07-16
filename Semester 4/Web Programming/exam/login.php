<?php
    require "connection.php";

    $conn = openConnection();

    $name = $_POST["name"];

    $result = mysqli_query($conn, "SELECT * FROM superhero WHERE name = '" . $name . "'");
    $row = mysqli_fetch_array($result);

    if ($row) {
        session_start();

        $_SESSION['id'] = $row['id'];
        $_SESSION['name'] = $row['name'];

        header("Location: main.html");
        exit();
    } else {
        echo "Could not login";
    }

    closeConnection($conn);
?>
