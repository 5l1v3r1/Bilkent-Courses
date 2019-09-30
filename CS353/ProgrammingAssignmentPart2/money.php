<?php
/**
 * Created by IntelliJ IDEA.
 * User: boran
 * Date: 17.04.2017
 * Time: 19:46
 */
include ('config.php');

session_start();

if(isset($_SESSION['username'])) {
    $query = "SELECT * from ACCOUNT WHERE cid='$password'";

    $result = mysqli_query($connection, $query) or die(mysqli_error($connection));
    $count = mysqli_num_rows($result);

    // generate table for current user account
    $account_table = '<table><tr><th>Account ID</th><th>Branch</th><th>Balance</th><th>Open Date</th></tr>';
    $aid = '';
    // fill table
    while ($tupple = mysqli_fetch_array($result)) {
        $account_table .= "<tr><td>'$tupple[aid]'</td><td>'$tupple[branch]'</td><td>'$tupple[balance]'</td><td>'$tupple[openDate]'</td></tr>";
        $aid .= "<option>'$tupple[aid]'</option>";
    }
    // close table
    $account_table .= "</table>";


    // generate all user account
    $query = "SELECT * from ACCOUNT";

    $result = mysqli_query($connection, $query) or die(mysqli_error($connection));
    $count = mysqli_num_rows($result);

    // generate table for accounts
    $all_account_table = '<table><tr><th>Account ID</th><th>Branch</th><th>Balance</th><th>Open Date</th></tr>';
    $all_aid = '';

    // fill table
    while ($tupple = mysqli_fetch_array($result)) {
        $all_account_table .= "<tr><td>'$tupple[aid]'</td><td>'$tupple[branch]'</td><td>'$tupple[balance]'</td><td>'$tupple[openDate]'</td></tr>";
        $all_aid .= "<option>'$tupple[aid]'</option>";
    }
    // close table
    $all_account_table .= "</table>";
}

?>
<!DOCTYPE html>
<html>
<head>
    <title>Money</title>
</head>
<body>
<div id="profile">
    <b id="welcome">Your Accounts :</b>
    <span>
        <?php echo $account_table; ?>
    </span>
    <br>
    <b id="welcome">All Accounts :</b>
    <span>
        <?php echo $all_account_tables; ?>
    </span>

    <br>

    <b id="welcome">From Account :</b>

    <select class="form-control" id="user_aid" style="width: auto;">
        <?php echo $aid; ?>
    </select>

    <b id="welcome">To Account :</b>

    <select class="form-control" id="all_aid" style="width: auto;">
        <?php echo $all_aid; ?>
    </select>

    <b id="welcome">Amount :</b>

    <input type="text" class="form-control" id="studentSurname">

    <br>
    <b id="moneyTransfer"><a href="profile.php">Back To Account Management</a></b>
    <b id="logout"><a href="logout.php">Log Out</a></b>
</div>
</body>
</html>