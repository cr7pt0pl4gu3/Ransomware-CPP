<?php
$servername = "localhost";
$username = "username";
$password = "password";
$database = "databasename";

try {
  $conn = new PDO("mysql:host=$servername;dbname=$database", $username, $password);
  $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}
catch(PDOException $e) {}
if(isset($_POST['submit'])) {
$tid = $_POST['tid'];
$key = $_POST['dec'];
$email = $_POST['ema'];
$stmt = $conn->prepare("INSERT INTO table1 (transactionID, key, email) VALUES (?, ?, ?)");
$stmt->bind_param($tid, $key, $email);
$stmt->execute();
}