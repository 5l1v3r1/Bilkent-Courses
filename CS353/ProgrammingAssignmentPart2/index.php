<?php
/**
 * Created by IntelliJ IDEA.
 * User: boranyildirim
 * Date: 17.04.2017
 * Time: 14:34
 */

include ("config.php");

session_status();

if (isset($_POST['submit'])) {

    $username = $_POST['username'];
    $password = $_POST['password'];

    $query = "SELECT * FROM CUSTOMER WHERE name='$username' and cid='$password'";

    $result = mysqli_query($connection, $query) or die(mysqli_error($connection));
    $count = mysqli_num_rows($result);

    if ($count == 1) {
        $_SESSION['username'] = $username;
    } else {
        $fmsg = "Invalid Login Credentials.";
    }
}
//if the user is logged in
if (isset($_SESSION['username'])){
    header('Location: money.php');
    echo "<a href='logout.php'>Logout</a>";

}else {
    mysqli_close($connection);
}
?>

<html>

<head>
    <title>Login Page</title>
</head>

<body bgcolor = "#FFFFFF">
<div align = "center">
    <form method="POST">
        <h2>Please Login</h2>
        <div class="input-group">
            <span class="input-group-addon" id="basic-addon1">Username</span>
            <input type="text" name="username" class="form-control" placeholder="Username" required>
        </div>
        <label for="inputPassword" class="sr-only">Password</label>
        <input type="password" name="password" id="inputPassword" class="form-control" placeholder="Password" required> <br>
        <button class="btn btn-lg btn-primary btn-block" type="submit" name="submit">Login</button>
    </form>
</div>
</body>
</html>