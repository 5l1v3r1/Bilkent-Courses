<?php
/**
 * Created by IntelliJ IDEA.
 * User: boran
 * Date: 17.04.2017
 * Time: 20:05
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
}