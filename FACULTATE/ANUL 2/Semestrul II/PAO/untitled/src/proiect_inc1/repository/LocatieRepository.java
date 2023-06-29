package proiect_inc1.repository;

import config.DatabaseConfiguration;
import config.DatabaseLogWriter;
import proiect_inc1.entity.FacturaIntrare;
import proiect_inc1.entity.Furnizor;
import proiect_inc1.entity.Locatie;

import java.sql.*;
import java.time.LocalDate;

public class LocatieRepository {


    public void insertLocatie(Locatie locatie) {
        String insertSql = "INSERT INTO locatie(oras, strada, numar) VALUES (?, ?, ?)";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(insertSql)) {
            preparedStatement.setString(1, locatie.getOras());
            preparedStatement.setString(2, locatie.getStrada());
            preparedStatement.setInt(3, locatie.getNumar());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("locatie","insert");
    }


    public void afisareLocatie(int idLocatie) {
        String selectSql = "SELECT oras, strada, numar FROM locatie WHERE idlocatie = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(selectSql)) {
            preparedStatement.setInt(1, idLocatie);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                String oras = resultSet.getString("oras");
                String strada = resultSet.getString("strada");
                int numar = resultSet.getInt("numar");

                Locatie locatie = new Locatie(oras, strada, numar);

            } else {
                System.out.println("Locația cu ID-ul specificat nu a fost găsită în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("locatie","read");
    }

    public void deleteLocatie(int idLocatie) {
        String deleteSql = "DELETE FROM locatie WHERE idlocatie = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(deleteSql)) {
            preparedStatement.setInt(1, idLocatie);

            int rowsDeleted = preparedStatement.executeUpdate();
            if (rowsDeleted > 0) {
                System.out.println("Locația a fost ștearsă din baza de date.");
            } else {
                System.out.println("Nu există nicio locație cu ID-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("locatie","delete");
    }

    public void updateLocatie(Locatie locatie) {
        String updateSql = "UPDATE locatie SET oras = ?, strada = ?, numar = ? WHERE idlocatie = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(updateSql)) {
            preparedStatement.setString(1, locatie.getOras());
            preparedStatement.setString(2, locatie.getStrada());
            preparedStatement.setInt(3, locatie.getNumar());
            preparedStatement.setInt(4,locatie.getNumar());


            int rowsUpdated = preparedStatement.executeUpdate();
            if (rowsUpdated > 0) {
                System.out.println("Locația a fost actualizată în baza de date.");
            } else {
                System.out.println("Nu există nicio locație cu ID-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        DatabaseLogWriter.logOperation("locatie","update");
    }
}

