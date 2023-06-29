package repository;

import config.DatabaseConfiguration;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class PersonRepositoryUsingStatements {

    public void createTable(){
        String createTableSql = "CREATE TABLE IF NOT EXISTS person" +
                "(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(29), age DOUBLE)";
        // in numele de tabele nu folosim plural

        Connection connection = DatabaseConfiguration.getDatabaseConnection();

        try {
            Statement s = connection.createStatement();
            s.execute(createTableSql);
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }

    public void addPerson(){
        String insertPersonSql = "INSERT INTO person(name,age) VALUES ('john',20)";

        Connection connection = DatabaseConfiguration.getDatabaseConnection();

        try {
            Statement stmt = connection.createStatement();
            stmt.executeUpdate(insertPersonSql);
        }
        catch(SQLException e) {
            e.printStackTrace();
        }
    }


    public void displayPerson() {
        String displaySql = "SELECT * FROM person";

        Connection connection = DatabaseConfiguration.getDatabaseConnection();

        try{
            Statement stmt = connection.createStatement();
            ResultSet resultSet= stmt.executeQuery(displaySql);

            while(resultSet.next()){
                System.out.println("Id: "+resultSet.getInt(1));
                System.out.println("Name: "+resultSet.getString(2));
                System.out.println("Age: "+resultSet.getDouble(3));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }




}
