package proiect_inc1.repository;

import config.DatabaseConfiguration;
import config.DatabaseLogWriter;
import proiect_inc1.entity.Client;
import proiect_inc1.entity.FacturaIntrare;
import proiect_inc1.entity.Furnizor;
import proiect_inc1.entity.Locatie;

import java.sql.*;
import java.time.LocalDate;

public class ClientRepository {

    public void insertClient(Client client) {
        String insertSql = "INSERT INTO client(nume, CNP, varsta, gen) VALUES (?, ?, ?, ?)";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(insertSql)) {
            preparedStatement.setString(1, client.getNume());
            preparedStatement.setLong(2, client.getCNP());
            preparedStatement.setInt(3, client.getVarsta());
            preparedStatement.setString(4, client.getGen());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        DatabaseLogWriter.logOperation("client","insert");
    }

    public void afisareClient(long CNP) {
        String selectSql = "SELECT nume, CNP, varsta, gen FROM client WHERE CNP = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(selectSql)) {
            preparedStatement.setLong(1, CNP);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                String nume = resultSet.getString("nume");
                long cnp = resultSet.getLong("CNP");
                int varsta = resultSet.getInt("varsta");
                String gen = resultSet.getString("gen");

                Client client = new Client(nume, cnp, varsta, gen);
                // Utilizați obiectul client cum doriți, de exemplu, afișați valorile sau procesați-le în alt mod.
            } else {
                System.out.println("Clientul cu CNP-ul specificat nu a fost găsit în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("client","read");
    }

    public void deleteClient(long CNP) {
        String deleteSql = "DELETE FROM client WHERE CNP = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(deleteSql)) {
            preparedStatement.setLong(1, CNP);

            int rowsDeleted = preparedStatement.executeUpdate();
            if (rowsDeleted > 0) {
                System.out.println("Clientul a fost șters din baza de date.");
            } else {
                System.out.println("Nu există niciun client cu CNP-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("client","delete");
    }

    public void updateClient(Client client) {
        String updateSql = "UPDATE client SET nume = ?, varsta = ?, gen = ? WHERE cnp = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(updateSql)) {
            preparedStatement.setString(1, client.getNume());
            preparedStatement.setInt(2, client.getVarsta());
            preparedStatement.setString(3, client.getGen());
            preparedStatement.setLong(4, client.getCNP());

            int rowsUpdated = preparedStatement.executeUpdate();
            if (rowsUpdated > 0) {
                System.out.println("Clientul a fost actualizat în baza de date.");
            } else {
                System.out.println("Nu există niciun client cu CNP-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("client","update");
    }
}
