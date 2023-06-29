package repository;

import config.DatabaseConfiguration;
import entity.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PersonRepUsingPrepareStatement {

    public void insertPerson(String name, double age) {
        String insertPSql = "INSERT INTO person(name,age) VALUES (?,?)";

        Connection connection = DatabaseConfiguration.getDatabaseConnection();

        try{
            PreparedStatement preparedStatement= connection.prepareStatement(insertPSql);
            preparedStatement.setString(1,name);
            preparedStatement.setDouble(2,age);

            preparedStatement.executeUpdate();
        }catch(SQLException e) {
            e.printStackTrace();
        }
    }

    public Person getPersonById(int id){
        String selectById = "SELECT id,name,age from person where id=?";

        Connection connection = DatabaseConfiguration.getDatabaseConnection();

        try{
            PreparedStatement preparedStatement= connection.prepareStatement(selectById);
            preparedStatement.setInt(1,id);

            ResultSet resultSet = preparedStatement.executeQuery();

            return mapToPerson(resultSet);

        }catch(SQLException e) {
            e.printStackTrace();
        }

        return null;
    }

    private static Person mapToPerson(ResultSet resultSet) throws SQLException {
        if(resultSet.next()) {
            return new Person(resultSet.getInt(1), resultSet.getString(2), resultSet.getDouble(3));
        }
        return null;
    }
}
