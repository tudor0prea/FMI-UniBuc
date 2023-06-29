package proiect_inc1.entity;

import java.util.List;
import java.util.ArrayList;

public class Dosar {
    private List <FacturaIntrare> facturiIntrare;
    private List <FacturaIesire> facturiIesire;

    private int numarInt;

    private int numarIes;

    public void cresteNumarInt() {
        this.numarInt=this.numarInt+1;
    }
    public void cresteNumarIes() {
        this.numarIes=this.numarIes+1;
    }
    public Dosar() {
        this.facturiIntrare = new ArrayList<FacturaIntrare>();
        this.facturiIesire= new ArrayList<FacturaIesire>();
    }

    public List<FacturaIntrare> getFacturiIntrare() {
        return facturiIntrare;
    }
    public List<FacturaIesire> getFacturiIesire() {
        return facturiIesire;
    }
    public void setFacturiIntrare(List<FacturaIntrare> facturi) {
        this.facturiIntrare = facturi;
    }
    public void setFacturiIesire(List<FacturaIesire> facturi) {
        this.facturiIesire = facturi;
    }
    public void setFacturiIntrare(boolean add) {
    }
    public void setFacturiIesire(boolean add) {
    }

    public void afisareFacturi() {
        System.out.println("Dosarul contine " + numarInt + " facturi de intrare:");
        for(int i=0;i<numarInt;i++)
        {
            facturiIntrare.get(i).afisareFacturaIntrare(facturiIntrare.get(i));
        }

        System.out.println("\n Dosarul contine " + numarIes + " facturi de iesire:");
        for(int i=0;i<numarIes;i++)
        {
            facturiIesire.get(i).afisareIesire(facturiIesire.get(i));
        }
    }
}
