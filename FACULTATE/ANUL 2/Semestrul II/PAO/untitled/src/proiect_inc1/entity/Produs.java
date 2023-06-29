package proiect_inc1.entity;

public class Produs {
    private String nume;
    private double pret;
    private int cod;


    public Produs(String nume, double pret, int cod) {
        this.nume = nume;
        this.pret = pret;
        this.cod = cod;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public double getPret() {
        return pret;
    }

    public void setPret(double pret) {
        this.pret = pret;
    }

    public int getCod() {
        return cod;
    }

    public void setCod(int cod) {
        this.cod = cod;
    }
}
