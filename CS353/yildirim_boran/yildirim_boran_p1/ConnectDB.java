/**
 * Created by boranyildirim on 14.04.2017.
 */

import java.sql.*;

public class ConnectDB {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://dijkstra2.ug.bcc.bilkent.edu.tr/boran_yildirim";

    //  Database credentials
    private static final String USER = "boran.yildirim";
    private static final String PASS = "4a02xem3";

    private static Statement STMT = null;
    private static Connection CONN = null;

    public static void main(String[] args) {

        try {
            //STEP 2: Register JDBC driver
            Class.forName(JDBC_DRIVER);

            //STEP 3: Open a connection
            System.out.println("Connecting to a selected database...");
            CONN = DriverManager.getConnection(DB_URL, USER, PASS);
            System.out.println("Connected database successfully...");

            //STEP 4: Execute a query
            STMT = CONN.createStatement();

            createTables();

            insertCustomer("20000001", "Cem", new Date(1980 - 1900, 10 - 1, 10), "Tunali", "Ankara", "TC");
            insertCustomer("20000002", "Asli", new Date(1985 - 1900, 9 - 1, 8), "Nisantasi", "Istanbul", "TC");
            insertCustomer("20000003", "Ahmet", new Date(1995 - 1900, 2 - 1, 11), "Karsiyaka", "Izmir", "TC");


            insertAccount("A0000001", "Kizilay", 2000.00f, new Date(2009 - 1900, 1 - 1, 1));
            insertAccount("A0000002", "Bilkent", 8000.00f, new Date(2011 - 1900, 1 - 1, 1));
            insertAccount("A0000003", "Cankaya", 4000.00f, new Date(2012 - 1900, 1 - 1, 1));
            insertAccount("A0000004", "Sincan", 1000.00f, new Date(2012 - 1900, 1 - 1, 1));
            insertAccount("A0000005", "Tandogan", 3000.00f, new Date(2013 - 1900, 1 - 1, 1));
            insertAccount("A0000006", "Eryaman", 5000.00f, new Date(2015 - 1900, 1 - 1, 1));
            insertAccount("A0000007", "Umitkoy", 6000.00f, new Date(2017 - 1900, 1 - 1, 1));

            insertOwns("20000001", "A0000001");
            insertOwns("20000001", "A0000002");
            insertOwns("20000001", "A0000003");
            insertOwns("20000001", "A0000004");
            insertOwns("20000002", "A0000002");
            insertOwns("20000002", "A0000003");
            insertOwns("20000002", "A0000005");
            insertOwns("20000003", "A0000006");
            insertOwns("20000003", "A0000007");


            printTables();



        } catch (Exception e) {
            //Handle errors for Class.forName
            System.out.println(e.getMessage());
        } finally {
            //finally block used to close resources
            try {
                if (STMT != null)
                    CONN.close();
            } catch (SQLException se) {
            }// do nothing
            try {
                if (CONN != null)
                    CONN.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }//end finally try
        }//end try
        System.out.println("Goodbye!");
    }

    private static void createTables() throws SQLException {
        // try to create the customer table
        try {
            String customer = "CREATE TABLE CUSTOMER " +
                    "(cid CHAR(12), " +
                    "name VARCHAR(50), " +
                    "bdate DATE, " +
                    "address VARCHAR(50), " +
                    "city VARCHAR(20), " +
                    "nationality VARCHAR(20)," +
                    "PRIMARY KEY (cid)) ENGINE = InnoDB";

            STMT.executeUpdate(customer);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create the account table
        try {
            String account = "CREATE TABLE ACCOUNT " +
                    "(aid CHAR(8), " +
                    "branch VARCHAR(50), " +
                    "balance FLOAT, " +
                    "openDate DATE, " +
                    "PRIMARY KEY (aid)) ENGINE = InnoDB";

            STMT.executeUpdate(account);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create owns table
        try {
            String owns = "CREATE TABLE OWNS " +
                    "(cid CHAR(12), " +
                    "aid CHAR(8), " +
                    "PRIMARY KEY (cid, aid)," +
                    "FOREIGN KEY (cid) REFERENCES CUSTOMER(cid)," +
                    "FOREIGN KEY (aid) REFERENCES ACCOUNT(aid)) ENGINE = InnoDB";

            STMT.executeUpdate(owns);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private static void insertCustomer(String cid, String name, Date bdate, String address, String city, String nationality) {

        try {
            String customer = "INSERT INTO CUSTOMER " +
                    "values(" + cid +", \'" + name + "\', \'" + bdate + "\' ,\'" +
                    address + "\', \'" + city + "\', \'" + nationality + "\' )";

            STMT.executeUpdate(customer);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void insertAccount(String aid, String branch, float balance, Date openDate) {
        try {
            String account = "INSERT INTO ACCOUNT " +
                    "values(\'" + aid +"\', \'" + branch + "\', \'" + balance + "\' ,\'" +
                    openDate + "\')";

            STMT.executeUpdate(account);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void insertOwns(String cid, String aid) throws SQLException {
        try {
            String account = "INSERT INTO OWNS " +
                    "values(\'" + cid +"\', \'" + aid + "\')";

            STMT.executeUpdate(account);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void printTables() {
        try {
            System.out.println("\n");
            printCustomer();
            System.out.println("\n");
            printAccount();
            System.out.println("\n");
            printOwns();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void printCustomer() throws SQLException {
        String customerQuery = "SELECT * FROM CUSTOMER";

        ResultSet resultSet = STMT.executeQuery(customerQuery);

        System.out.println("| cid      | name  | bdate      | address   | city     | nationality |");
        while (resultSet.next()) {
            String cid = resultSet.getString("cid");
            String name = resultSet.getString("name");
            Date bdate = resultSet.getDate("bdate");
            String address = resultSet.getString("address");
            String city = resultSet.getString("city");
            String nationality = resultSet.getString("nationality");
            System.out.println("| " + cid + " | " + name + " | " + bdate +
                    " | " + address + " | " + city + " | " + nationality + " | ");
        }
    }

    private static void printAccount () throws SQLException {
        String customerQuery = "SELECT * FROM ACCOUNT";

        ResultSet resultSet = STMT.executeQuery(customerQuery);

        System.out.println("| aid      | branch   | balance | openDate   |");
        while (resultSet.next()) {
            String aid = resultSet.getString("aid");
            String branch = resultSet.getString("branch");
            Float balance = resultSet.getFloat("balance");
            Date openDate = resultSet.getDate("openDate");
            System.out.println("| " + aid + " | " + branch + " | " + balance +
                    " | " + openDate + " | ");
        }
    }

    private static void printOwns () throws SQLException {
        String customerQuery = "SELECT * FROM OWNS";

        ResultSet resultSet = STMT.executeQuery(customerQuery);

        System.out.println("| cid      | aid      |");
        while (resultSet.next()) {
            String cid = resultSet.getString("cid");
            String aid = resultSet.getString("aid");

            System.out.println("| " + cid + " | " + aid + " | ");
        }
    }
}

