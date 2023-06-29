package proiect_inc1.entity;
// sealed, non sealed, final
public class Angajat extends Client {

    public String functie;

    public double salariu;


    public Angajat(String nume, int CNP, int varsta, String gen, String functie, double salariu) {
        super(nume, CNP, varsta, gen);
        this.functie = functie;
        this.salariu = salariu;
    }

    public double getSalariu() {
        return salariu;
    }

    public void setSalariu(double salariu) {
        this.salariu = salariu;
    }

    public String getFunctie() {
        return functie;
    }

    public void setFunctie(String functie) {
        this.functie = functie;
    }


}
