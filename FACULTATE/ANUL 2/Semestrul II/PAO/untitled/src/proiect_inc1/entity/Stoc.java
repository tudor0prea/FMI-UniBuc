package proiect_inc1.entity;
import java.util.Map;

public class Stoc {

    private Map<Produs, Integer> stocProduse;
    private int luna_actualizare;
    private int an_actualizare;


    public Stoc(Map<Produs, Integer> stocProduse, int luna_actualizare, int an_actualizare) {
        this.stocProduse = stocProduse;
        this.luna_actualizare = luna_actualizare;
        this.an_actualizare = an_actualizare;
    }

    public Map<Produs, Integer> getStocProduse() {
        return stocProduse;
    }

    public void setStocProduse(Map<Produs, Integer> stocProduse) {
        this.stocProduse = stocProduse;
    }

    public int getLuna_actualizare() {
        return luna_actualizare;
    }

    public void setLuna_actualizare(int luna_actualizare) {
        this.luna_actualizare = luna_actualizare;
    }

    public int getAn_actualizare() {
        return an_actualizare;
    }

    public void setAn_actualizare(int an_actualizare) {
        this.an_actualizare = an_actualizare;
    }


    // METODE:
    public void adaugaProdus(Produs produs, int cantitate) {
        if (stocProduse.containsKey(produs)) {
            int cantitateCurenta = stocProduse.get(produs);
            stocProduse.put(produs, cantitateCurenta + cantitate);
        } else {
            stocProduse.put(produs, cantitate);
        }
    }
    public void actualizeazaProdus(Produs produs, int cantitate) {
        if (stocProduse.containsKey(produs)) {
            stocProduse.put(produs, cantitate);
        } else {
            System.out.println("Produsul nu exista in stoc.");
        }
    }
    public void stergeProdus(Produs produs) {
        if (stocProduse.containsKey(produs)) {
            stocProduse.remove(produs);
        } else {
            System.out.println("Produsul nu exista in stoc.");
        }
    }

}
