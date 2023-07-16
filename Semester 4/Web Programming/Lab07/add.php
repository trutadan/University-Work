<?php
  if (!isset($_COOKIE["userID"])) {
    echo "notloggedin";
    die;
  }

  $conn = mysqli_connect("localhost", "root", "", "guestbook_db");

  $email = $_POST["email"];
  $title = $_POST["title"];
  $comment = $_POST["comment"];
  $date = $_POST["date"];

  $query = "INSERT INTO Entries(email, title, comment, date) VALUES ('$email', '$title', '$comment', '$date')";
  $result = mysqli_query($conn, $query);

  if (!$result)
    echo $conn->error;
  else
    echo "true"
?>
