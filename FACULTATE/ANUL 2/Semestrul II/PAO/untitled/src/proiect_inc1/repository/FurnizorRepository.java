package proiect_inc1.repository;

import config.DatabaseConfiguration;
import config.DatabaseLogWriter;
import proiect_inc1.entity.FacturaIntrare;
import proiect_inc1.entity.Furnizor;
import proiect_inc1.entity.Locatie;

import java.sql.*;
import java.time.LocalDate;

public class FurnizorRepository {

    public void insertFurnizor(Furnizor furnizor) {
        String insertSql = "INSERT INTO furnizor(nume, cnp2, varsta) VALUES (?, ?, ?)";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(insertSql)) {
            preparedStatement.setString(1, furnizor.getNume());
            preparedStatement.setLong(2, furnizor.getCNP());
            preparedStatement.setInt(3, furnizor.getVarsta());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("furnizor","insert");


    }

    public void afisareFurnizor(int cnp) {
        String selectSql = "SELECT nume, CNP2, varsta FROM furnizor WHERE CNP2 = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(selectSql)) {
            preparedStatement.setInt(1, cnp);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                String nume = resultSet.getString("nume");
                int cnpFurnizor = resultSet.getInt("cnp");
                int varsta = resultSet.getInt("varsta");

                Furnizor furnizor = new Furnizor(nume, cnpFurnizor, varsta);
                // Utilizați obiectul furnizor cum doriți, de exemplu, afișați valorile sau procesați-le în alt mod.
            } else {
                System.out.println("Furnizorul cu CNP-ul specificat nu a fost găsit în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("furnizor","read");
    }
    public void deleteFurnizor(int cnp) {
        String deleteSql = "DELETE FROM furnizor WHERE CNP2 = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(deleteSql)) {
            preparedStatement.setInt(1, cnp);

            int rowsDeleted = preparedStatement.executeUpdate();
            if (rowsDeleted > 0) {
                System.out.println("Furnizorul a fost șters din baza de date.");
            } else {
                System.out.println("Nu există niciun furnizor cu CNP-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("furnizor","delete");
    }
    public void updateFurnizor(Furnizor furnizor) {
        String updateSql = "UPDATE furnizor SET nume = ?, varsta = ? WHERE CNP2 = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(updateSql)) {
            preparedStatement.setString(1, furnizor.getNume());
            preparedStatement.setInt(2, furnizor.getVarsta());
            preparedStatement.setLong(3, furnizor.getCNP());

            int rowsUpdated = preparedStatement.executeUpdate();
            if (rowsUpdated > 0) {
                System.out.println("Furnizorul a fost actualizat în baza de date.");
            } else {
                System.out.println("Nu există niciun furnizor cu CNP-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("furnizor","update");
    }

}
