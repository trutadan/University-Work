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

  $query = "DELETE FROM Entries WHERE id = $id";
  $result = mysqli_query($conn, $query);

  ob_end_clean();

  if (!$result)
    echo $conn->error;
  else
    echo "true"

?>
