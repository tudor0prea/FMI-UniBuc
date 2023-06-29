package proiect_inc1.entity;

import java.time.LocalDate;
import java.util.List;

public class FacturaIesire extends Factura {

    private Client c;
    private List<Produs> produse;
    private List<Integer> cantitati;


    public FacturaIesire(Client c, List<Produs> produse, List<Integer> cantitati) {
        this.c = c;
        this.produse = produse;
        this.cantitati = cantitati;
    }

    public FacturaIesire(int numarFactura, double pret, Client c, List<Produs> produse, List<Integer> cantitati) {
        super(numarFactura, pret);
        this.c = c;
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

    public Client getC() {
        return c;
    }

    public void setC(Client c) {
        this.c = c;
    }

    public void afisareIesire(FacturaIesire factura) {
        System.out.println("╔══════════════════════════════════════════════════╗\n");
        System.out.println("                 FACTURA FISCALA \n" +
                           "                    de iesire \n" +
                           "                     nr. " + factura.getNumarFactura() + "\n");

        System.out.println(" ~Cumparator:");
        System.out.println("    Nume: " + factura.getC().getNume());
        System.out.println("    CNP/CUI: " + factura.getC().getCNP());
        System.out.println("    Varsta: " + factura.getC().getVarsta());
        System.out.println("    Gen: " + factura.getC().getGen() + "\n");

        System.out.println(" ~Produse cumparate:");
        List<Produs> produse = factura.getProduse();
        List<Integer> cantitati = factura.getCantitati();
        double total = 0;

        for (int i = 0; i < produse.size(); i++) {
            Produs produs = produse.get(i);
            int cantitate = cantitati.get(i);
            double pret = produs.getPret() * cantitate;
            total += pret;

            System.out.println("    - " + produs.getNume() + " (cod " + produs.getCod() + "), cantitate: " + cantitate + ", pret: " + pret);
        }

        System.out.println("Total: " + total + " lei\n\n");
        this.setDataEmiterii(LocalDate.now());
        this.setDataScadentei(LocalDate.now().plusDays(14));
        System.out.println("Data emiterii: " + getDataEmiterii() + " | Data scadentei: " + getDataScadentei() + "\n\n");
        System.out.println("     Factura autorizata valabila fara stampila");
        System.out.println("╚══════════════════════════════════════════════════╝\n");
    }
}
