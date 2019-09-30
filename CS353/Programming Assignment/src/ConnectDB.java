/**
 * Created by boranyildirim on 14.04.2017.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.security.spec.ECField;
import java.sql.*;
import java.util.Scanner;

public class ConnectDB {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://dijkstra2.ug.bcc.bilkent.edu.tr/celik_koseoglu";

    //  Database credentials
    private static final String USER = "celik.koseoglu";
    private static final String PASS = "3slndceo";

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
            createViews();
            createTriggers();
            createIndexes();

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
        // try to create the user table
        try {
            String user = "CREATE TABLE USER ( " +
                    "ID INT(24) AUTO_INCREMENT, " +
                    "email VARCHAR(50) NOT NULL UNIQUE, " +
                    "password VARCHAR(255) NOT NULL, " +
                    "fname VARCHAR(50) NOT NULL, " +
                    "lname VARCHAR(50) NOT NULL, " +
                    "phone_num VARCHAR(14), " +
                    "age INT(3), " +
                    "rating	DECIMAL(1,1), " +
                    "member_since VARCHAR(10) NOT NULL, " +
                    "gender VARCHAR(6), " +
                    "car_license_plate VARCHAR(10) UNIQUE, " +
                    "bank_account VARCHAR(32), " +
                    "smokes TINYINT(1), " +
                    "chattiness TINYINT(1)," +
                    "PRIMARY KEY(ID))";

            STMT.executeUpdate(user);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create the card table
        try {
            String card = "CREATE TABLE CARD ( " +
                    "owner_id INT(24) NOT NULL, " +
                    "card_number INT(16) NOT NULL, " +
                    "cvc2 INT(3) NOT NULL, " +
                    "expr_date DATETIME NOT NULL, " +
                    "FOREIGN KEY (owner_id) REFERENCES USER(ID)," +
                    "PRIMARY KEY (owner_id, card_number, cvc2, expr_date))";

            STMT.executeUpdate(card);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create Car table
        try {
            String car = "CREATE TABLE CAR (" +
                    "owner_id INT(24) NOT NULL," +
                    "model INT(16) NOT NULL," +
                    "brand INT(3) NOT NULL," +
                    "color VARCHAR(10) NOT NULL," +
                    "FOREIGN KEY (owner_id) REFERENCES USER(ID)," +
                    "PRIMARY KEY (owner_id, model, brand, color))";

            STMT.executeUpdate(car);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create Ride table
        try {
            String ride = "CREATE TABLE RIDE (" +
                    "ride_id INT(24) AUTO_INCREMENT," +
                    "elapsed_time INT(4) NOT NULL," +
                    "elapsed_distance INT(4) NOT NULL," +
                    "price INT(4) NOT NULL," +
                    "pickup_location VARCHAR(50) NOT NULL," +
                    "dropoff_location VARCHAR(50) NOT NULL," +
                    "driver_id INT(24) NOT NULL," +
                    "car_license_plate VARCHAR(10) NOT NULL," +
                    "is_complete TINYINT(1) NOT NULL," +
                    "PRIMARY KEY (ride_id)," +
                    "FOREIGN KEY (driver_id) REFERENCES USER(ID)," +
                    "FOREIGN KEY (car_license_plate) REFERENCES USER(car_license_plate))";;

            STMT.executeUpdate(ride);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create current ride passengers table
        try {
            String cur_ride_pass = "CREATE TABLE CURRENTRIDEPASSENGERS (" +
                    "passenger_id INT(24)," +
                    "ride_id INT(24)," +
                    "PRIMARY KEY (passenger_id, ride_id)," +
                    "FOREIGN KEY (passenger_id) REFERENCES USER(ID)," +
                    "FOREIGN KEY (ride_id) REFERENCES RIDE(ride_id))";

            STMT.executeUpdate(cur_ride_pass);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create rating table
        try {
            String rating = "CREATE TABLE RATING (" +
                    "ride_id INT(24)," +
                    "reviewer_id INT(24)," +
                    "reviewed_id INT(24)," +
                    "PRIMARY KEY (ride_id, reviewer_id, reviewed_id)," +
                    "FOREIGN KEY (ride_id) REFERENCES RIDE(ride_id)," +
                    "FOREIGN KEY (reviewer_id) REFERENCES USER(ID)," +
                    "FOREIGN KEY (reviewed_id) REFERENCES USER(ID))";

            STMT.executeUpdate(rating);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create scheduled ride table
        try {
            String sched_ride = "CREATE TABLE SCHEDULEDRIDE (" +
                    "ride_id INT(24) AUTO_INCREMENT," +
                    "number_of_empty_seats INT(2) NOT NULL," +
                    "date_and_time DATETIME NOT NULL," +
                    "pickup_location VARCHAR(50) NOT NULL," +
                    "dropoff_location VARCHAR(50) NOT NULL ," +
                    "driver_id INT(24) NOT NULL ," +
                    "car_license_plate VARCHAR(10) NOT NULL," +
                    "PRIMARY KEY (ride_id)," +
                    "FOREIGN KEY (driver_id) REFERENCES USER(ID)," +
                    "FOREIGN KEY (car_license_plate) REFERENCES USER(car_license_plate))";

            STMT.executeUpdate(sched_ride);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // try to create reservations table
        try {
            String reservation = "CREATE TABLE RESERVATION (" +
                    "passenger_id INT(24)," +
                    "ride_id INT(24)," +
                    "PRIMARY KEY (passenger_id, ride_id)," +
                    "FOREIGN KEY (passenger_id) REFERENCES USER(ID)," +
                    "FOREIGN KEY (ride_id) REFERENCES SCHEDULEDRIDE(ride_id))";

            STMT.executeUpdate(reservation);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }


    private static void createViews() throws SQLException {

        // create view for money of user
        try {
            String user_price = "CREATE VIEW USERMONEY AS " +
                    "SELECT driver_id, sum(price) AS money " +
                    "FROM RIDE " +
                    "GROUP BY driver_id";

            STMT.executeUpdate(user_price);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // create view for number of rides per date
        try {
            String rides_per_date = "CREATE VIEW RIDES_PER_DATE AS " +
                    "(SELECT DATE(date_and_time), COUNT(ride_id) AS ride_count " +
                    "FROM SCHEDULEDRIDE " +
                    "GROUP BY date_and_time)";

            STMT.executeUpdate(rides_per_date);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }


    private static void createTriggers() throws SQLException {

        // create trigger between user and card
        try {
            String user_card = "CREATE TRIGGER DELETECARD AFTER DELETE ON USER " +
                    "FOR EACH ROW " +
                    "BEGIN " +
                    "DELETE FROM CARD WHERE OLD.ID = CARD.owner_id; " +
                    "END";

            STMT.executeUpdate(user_card);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // create trigger between user and car
        try {
            String user_car = "CREATE TRIGGER DELETECAR AFTER DELETE ON USER " +
                    "FOR EACH ROW " +
                    "BEGIN " +
                    "DELETE FROM CAR WHERE OLD.ID = CAR.owner_id; " +
                    "END";

            STMT.executeUpdate(user_car);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // create trigger between rating and user
        try {
            String rating_user = "CREATE TRIGGER RATINGADDED AFTER INSERT ON RATING " +
                    "FOR EACH ROW " +
                    "BEGIN " +
                    "UPDATE USER " +
                    "SET USER.rating = (USER.rating + NEW.rating) / (SELECT count(reviewed_id) FROM RATING)" +
                    "WHERE reviewed_id = ID;" +
                    "END";

            STMT.executeUpdate(rating_user);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private static void createIndexes() throws SQLException {
        try {
            String user_email_index = "CREATE INDEX email_index " +
                    "USING BTREE ON USER(email)";

            STMT.executeUpdate(user_email_index);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }


        try {
            String pickup_index = "CREATE INDEX pickup_location_index " +
                    "USING BTREE ON SCHEDULEDRIDE (pickup_location)";

            STMT.executeUpdate(pickup_index);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            String pickup_index = "CREATE INDEX dropoff_location_index " +
                    "USING BTREE ON SCHEDULEDRIDE (dropoff_location)";

            STMT.executeUpdate(pickup_index);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}