package proiect_inc1.entity;

public class Furnizor {
    public String nume;
    public long CNP;
    public int varsta;

    public Locatie sediu;

    public Furnizor(String nume, long CNP, int varsta) {
        this.nume = nume;
        this.CNP = CNP;
        this.varsta = varsta;
    }

    public Furnizor(String nume, long CNP, int varsta, Locatie sediu) {
        this.nume = nume;
        this.CNP = CNP;
        this.varsta = varsta;
        this.sediu = sediu;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public long getCNP() {
        return CNP;
    }

    public void setCNP(long CNP) {
        this.CNP = CNP;
    }

    public int getVarsta() {
        return varsta;
    }

    public void setVarsta(int varsta) {
        this.varsta = varsta;
    }

    public Locatie getSediu() {
        return sediu;
    }

    public void setSediu(Locatie sediu) {
        this.sediu = sediu;
    }
}
