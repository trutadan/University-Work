<?php
  ob_start();

  if (!isset($_COOKIE["userID"])) {
    echo "notloggedin";
    die;
  }

  include 'get_user_role.php';
  if ($user_role !== "admin") {
    echo "unauthorized";
    die;
  }

  $conn = mysqli_connect("localhost", "root", "", "guestbook_db");

  $id = $_POST["id"];
  $email = $_POST["email"];
  $title = $_POST["title"];
  $comment = $_POST["comment"];
  $date = $_POST["date"];

  $updates = "";
  $hasUpdates = false;

  if (!empty($email)) {
    $updates .= "email = '$email'";
    $hasUpdates = true;
  }

  if (!empty($title)) {
    if ($hasUpdates)
      $updates .= ", ";

    $updates .= "title = '$title'";
    $hasUpdates = true;
  }

  if (!empty($comment)) {
    if ($hasUpdates)
      $updates .= ", ";

    $updates .= "comment = '$comment'";
    $hasUpdates = true;
  }

  if (!empty($date)) {
    if ($hasUpdates)
      $updates .= ", ";

    $updates .= "date = '$date'";
    $hasUpdates = true;
  }

  ob_end_clean();

  if ($hasUpdates) {
    $query = "UPDATE Entries SET $updates WHERE id = '$id'";
    $result = mysqli_query($conn, $query);

    if (!$result)
      echo $conn->error;
    else
      echo "true";
  } else
    echo "true"
?>
