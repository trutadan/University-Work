<?php
  if (!isset($_COOKIE["userID"])) {
    echo "notloggedin";
    die;
  }

  $conn = mysqli_connect("localhost", "root", "", "guestbook_db");

  $user = $_COOKIE["userID"];

  $user_role_query = "SELECT role FROM Users WHERE id = $user";
  $user_role_result = mysqli_query($conn, $user_role_query);

  if (!$user_role_result) {
      echo $conn->error;
      die;
  }

  $user_role_row = mysqli_fetch_assoc($user_role_result);
  $user_role = $user_role_row['role'];

  echo $user_role;
  ?>
