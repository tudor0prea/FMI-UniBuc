package proiect_inc1.entity;


public class Client {
    public String nume;
    public long CNP;
    public int varsta;
    public String gen;


    public Client(String nume, long CNP, int varsta, String gen) {
        this.nume = nume;
        this.CNP = CNP;
        this.varsta = varsta;
        this.gen = gen;
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

    public String getGen() {
        return gen;
    }

    public void setGen(String gen) {
        this.gen = gen;
    }
}
