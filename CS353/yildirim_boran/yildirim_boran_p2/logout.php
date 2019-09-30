<?php
/**
 * Created by IntelliJ IDEA.
 * User: boranyildirim
 * Date: 17.04.2017
 * Time: 15:30
 */

session_start();
session_destroy();
header('Location: index.php');
?>