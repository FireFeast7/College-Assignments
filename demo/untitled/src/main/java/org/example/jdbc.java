package demo.untitled.src.main.java.org.example;

import java.sql.*;
import java.util.Scanner;

public class jdbc {
    public Connection connection;
    String name_column;
    String rollno_name;

    public void checkconnection() throws ClassNotFoundException {
        Class.forName("com.mysql.cj.jdbc.Driver");
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/31373_dbms", "root", "root123");
            if (connection != null && !connection.isClosed()) {
                System.out.println("Database is Connected");
            } else {
                System.out.println("Not connected with Database");
            }
        } catch (SQLException e) {
            System.out.println("Wrong Credentials");
        } catch (Exception e) {
            System.out.println("Error 404 Timed Out.");
        }
    }

    public void updateTable(String table_name, int roll_no, String name) {
        String sql = "update " + table_name + " set " + this.name_column + "= '" + name + "' where " + this.rollno_name
                + "=" + roll_no + ";";
        System.out.println(sql);
        try {
            PreparedStatement ps = connection.prepareStatement(sql);
            int rowsAffected = ps.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Successfully updated Table");
            } else {
                System.out.println("Error Occured");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void createTable(String table_name, String roll_no, String name) {
        this.name_column = name;
        this.rollno_name = roll_no;
        String sql = "create table " + table_name + "(" + name + " varchar(25)," + roll_no + " int not null)";
        try {
            PreparedStatement ps = connection.prepareStatement(sql);
            ps.executeUpdate();
            System.out.println("Successfully created Table");
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    public void insertTable(String table_name, int roll_no, String name) {
        String sql = "Insert into " + table_name + "(" + this.name_column + "," + this.rollno_name + ")" + "values"
                + "('" + name + "'," + roll_no + ")";
        try {
            PreparedStatement ps = connection.prepareStatement(sql);
            int rowsAffected = ps.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Successfully inserted into Table");
            } else {
                System.out.println("Error Occured");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void deleteTable(String table_name, int roll_no) {
        String sql = "delete from " + table_name + " where " + this.rollno_name + " = " + roll_no;
        try {
            PreparedStatement ps = connection.prepareStatement(sql);
            int rowsAffected = ps.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Successfully deleted entry from Table");
            } else {
                System.out.println("Error Occured");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void contentTable(String tablename) {
        try {
            Statement statement = connection.createStatement();
            String sql = "select * from " + tablename + ";";
            ResultSet rs = statement.executeQuery(sql);
            while (rs.next()) {
                String name = rs.getString(this.name_column);
                int no = rs.getInt(this.rollno_name);
                System.out.println(this.name_column + ":" + name + " " + this.rollno_name + ": " + no);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) throws ClassNotFoundException {
        Scanner sc = new Scanner(System.in);
        jdbc myjdbc = new jdbc();
        int a = 99;
        String table_name = "";
        while (a != 0) {
            System.out.println("1 . Check Connection");
            System.out.println("2 . Create Table ");
            System.out.println("3 . Insertion");
            System.out.println("4 . Updation");
            System.out.println("5 . Deletion");
            System.out.println("6 . Show Contents");
            System.out.println("7 . Press 0 to exit");
            a = sc.nextInt();
            switch (a) {
                case 1:
                    myjdbc.checkconnection();
                    break;
                case 3:
                    System.out.println("Enter the Roll no and Name of the student ");
                    int roll_no = sc.nextInt();
                    String name = sc.next();
                    myjdbc.insertTable(table_name, roll_no, name);
                    break;
                case 4:
                    System.out.println("Enter the new name to be replaced and its roll no : ");
                    String new_name = sc.next();
                    int id = sc.nextInt();
                    myjdbc.updateTable(table_name, id, new_name);
                    break;
                case 5:
                    System.out.println("Enter the roll no of the record to be deleted : ");
                    int rol = sc.nextInt();
                    myjdbc.deleteTable(table_name, rol);
                    break;
                case 2:
                    System.out.print("Enter the name of the table you would like to create : ");
                    table_name = sc.next();
                    myjdbc.createTable(table_name, "Roll_no", "Name");
                    break;
                case 6:
                    System.out.println("Contents are : ");
                    myjdbc.contentTable(table_name);
                    break;
                case 0:
                    a = 0;
                    break;
                default:
                    System.out.println("Wrong Input Entered");
                    break;
            }
        }
    }
}
