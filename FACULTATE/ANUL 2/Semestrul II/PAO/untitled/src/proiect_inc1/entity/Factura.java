package proiect_inc1.entity;

import java.time.LocalDate;

public class Factura {
    private int numarFactura;
    private static int ultimulNumarFactura = 0;

    private double pret;

    private LocalDate dataEmiterii;
    private LocalDate dataScadentei;

    public LocalDate getDataEmiterii() {
        return dataEmiterii;
    }

    public void setDataEmiterii(LocalDate dataEmiterii) {
        this.dataEmiterii = dataEmiterii;
    }

    public LocalDate getDataScadentei() {
        return dataScadentei;
    }

    public void setDataScadentei(LocalDate dataScadentei) {
        this.dataScadentei = dataScadentei;
    }

    public Factura() {
        this.numarFactura = ++ultimulNumarFactura;
    }

    public Factura(int numarFactura, double pret, LocalDate dataEmiterii, LocalDate dataScadentei) {
        this.numarFactura = numarFactura;
        this.pret = pret;
        this.dataEmiterii = dataEmiterii;
        this.dataScadentei = dataScadentei;
    }

    public Factura(int numarFactura, double pret) {
        this.numarFactura = numarFactura;
        this.pret = pret;
    }

    public int getNumarFactura() {
        return numarFactura;
    }

    public void setNumarFactura(int numarFactura) {
        this.numarFactura = numarFactura;
    }

    public static int getUltimulNumarFactura() {
        return ultimulNumarFactura;
    }

    public static void setUltimulNumarFactura(int ultimulNumarFactura) {
        Factura.ultimulNumarFactura = ultimulNumarFactura;
    }

    public double getPret() {
        return pret;
    }

    public void setPret(double pret) {
        this.pret = pret;
    }




}
