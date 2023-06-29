import repository.*;
import entity.*;
import config.*;


public class Main {

    public static void main(String[] args) {
        PersonRepositoryUsingStatements personRepositoryUsingStatements= new PersonRepositoryUsingStatements();
        personRepositoryUsingStatements.createTable();
        //personRepositoryUsingStatements.addPerson();
        personRepositoryUsingStatements.displayPerson();

        PersonRepUsingPrepareStatement personRepUsingPrepareStatement = new PersonRepUsingPrepareStatement();

        personRepUsingPrepareStatement.insertPerson("Tudor",20);

        Person p = personRepUsingPrepareStatement.getPersonById(2);
        System.out.println(p);
    }

}
