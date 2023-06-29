package proiect_inc1.repository;

import config.DatabaseConfiguration;
import config.DatabaseLogWriter;
import entity.Person;
import proiect_inc1.entity.Factura;
import proiect_inc1.entity.FacturaIntrare;
import proiect_inc1.entity.Furnizor;

import java.sql.*;
import java.time.LocalDate;

public class FacturaRepository {

    public void insertFactura(int numarfactura, LocalDate dataemiterii, LocalDate datascadentei, int cnp, int cnp2) {
        String insertPSql = "INSERT INTO factura(idfactura,dataemiterii,datascadentei, cnp, cnp2) VALUES (?,?,?,?,?)";

        Connection connection = DatabaseConfiguration.getDatabaseConnection();

        try{
            PreparedStatement preparedStatement= connection.prepareStatement(insertPSql);
            preparedStatement.setInt(1,numarfactura);
            preparedStatement.setDate(2, Date.valueOf(dataemiterii));
            preparedStatement.setDate(3, Date.valueOf(datascadentei));
            preparedStatement.setInt(4,cnp);
            preparedStatement.setInt(5,cnp2);
            preparedStatement.executeUpdate();
        }catch(SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("Factura","insert");
    }

    public void afisareFacturaIntrareSql(int numarfactura) {
        String selectSql = "SELECT fa.idfactura, fa.dataemiterii, fa.datascadentei, fa.cnp, fa.cnp2," +
                "fu.nume,fu.varsta, fa.pret  from factura fa "
        + "inner join furnizor fu on fa.cnp2=fu.cnp2 "
        + "where fa.idfactura = ?";


        Connection connection = DatabaseConfiguration.getDatabaseConnection();

        try{

            PreparedStatement preparedStatement= connection.prepareStatement(selectSql);
            preparedStatement.setInt(1, numarfactura);

            ResultSet resultSet = preparedStatement.executeQuery();
            if(resultSet.next()) {
                Furnizor furnizor = new Furnizor(resultSet.getString(6), resultSet.getLong(5), resultSet.getInt(7) );


                FacturaIntrare f = new FacturaIntrare(resultSet.getInt(1), resultSet.getInt(8), furnizor);

                f.afisareFacturaIntrare(f);
            }

        }catch(SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("Factura","read");
    }

    public void deleteFactura(int idFactura) {
        String deleteSql = "DELETE FROM factura WHERE idfactura = ?";

        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(deleteSql)) {
            preparedStatement.setInt(1, idFactura);

            int rowsDeleted = preparedStatement.executeUpdate();
            if (rowsDeleted > 0) {
                System.out.println("Factura a fost ștearsă din baza de date.");
            } else {
                System.out.println("Nu există nicio factură cu ID-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("Factura","delete");
    }


    public void updateFactura(Factura factura) {
        String updateSql = "UPDATE factura SET dataemiterii = ?, datascadentei = ? WHERE idfactura = ?";
        int rowsUpdated = 0;
        try (Connection connection = DatabaseConfiguration.getDatabaseConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(updateSql)) {
            if(factura.getDataEmiterii()!=null && factura.getDataScadentei()!=null) {
                preparedStatement.setDate(1, Date.valueOf(factura.getDataEmiterii()));
                preparedStatement.setDate(2, Date.valueOf(factura.getDataScadentei()));
                preparedStatement.setInt(3,factura.getNumarFactura());
                rowsUpdated = preparedStatement.executeUpdate();
            }


            if (rowsUpdated > 0) {
                System.out.println("Factura a fost actualizată în baza de date.");
            } else {
                System.out.println("Nu există nicio factură cu ID-ul specificat în baza de date.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        DatabaseLogWriter.logOperation("Factura","update");
    }
}
