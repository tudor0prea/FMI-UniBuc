package proiect_inc1.entity;

import java.time.LocalDate;
import java.util.List;

public class FacturaIntrare extends Factura {
    private Furnizor f;

    private List<Produs> produse;
    private List<Integer> cantitati;

    public FacturaIntrare(Furnizor f, List<Produs> produse, List<Integer> cantitati) {
        this.f = f;
        this.produse = produse;
        this.cantitati = cantitati;
    }
    public FacturaIntrare(int numarFactura, double pret, Furnizor f) {
        super(numarFactura, pret);
        this.f = f;
     }

    public FacturaIntrare(int numarFactura, double pret, Furnizor f, List<Produs> produse, List<Integer> cantitati) {
        super(numarFactura, pret);
        this.f = f;
        this.produse = produse;
        this.cantitati = cantitati;
    }


    public List<Produs> getProduse() {
        return produse;
    }

    public void setProduse(List<Produs> produse) {
        this.produse = produse;
    }

    public List<Integer> getCantitati() {
        return cantitati;
    }

    public void setCantitati(List<Integer> cantitati) {
        this.cantitati = cantitati;
    }

    public Furnizor getF() {
        return f;
    }

    public void setF(Furnizor f) {
        this.f = f;
    }

    public void afisareFacturaIntrare(FacturaIntrare factura) {
        System.out.println("╔══════════════════════════════════════════════════╗\n");
        System.out.println("                  FACTURA FISCALA \n" +
                           "                     de intrare \n" +
                           "                      nr. " + factura.getNumarFactura() + "\n");

        System.out.println(" ~Furnizor: " + factura.getF().getNume());
        System.out.println( "    CNP/CUI: " + factura.getF().getCNP());
        System.out.println("    Varsta/vechime: " + factura.getF().getVarsta());
        System.out.println("    Adresa sediului: " + factura.getF().getSediu().getOras() + ", " + factura.getF().getSediu().getStrada() + " " + factura.getF().getSediu().getNumar() + "\n");

        System.out.println(" ~Produse:");
        List<Produs> produse = factura.getProduse();
        List<Integer> cantitati = factura.getCantitati();
        for (int i = 0; i < produse.size(); i++) {
            Produs produs = produse.get(i);
            int cantitate = cantitati.get(i);
            System.out.println("  - " + produs.getNume() + " x " + cantitate + " buc. la pretul de " + produs.getPret() + " lei/buc.");
            factura.setPret(factura.getPret()+produs.getPret()*cantitate);
        }

        System.out.println("\n ~Total factura: " + factura.getPret() + " lei\n\n");

        this.setDataEmiterii(LocalDate.now());
        this.setDataScadentei(LocalDate.now().plusDays(14));
        System.out.println("Data emiterii: " + getDataEmiterii() + " | Data scadentei: " + getDataScadentei() + "\n\n");
        System.out.println("     Factura autorizata valabila fara stampila");
        System.out.println("╚══════════════════════════════════════════════════╝\n");
    }



}
