package proiect_inc1.services;
import proiect_inc1.entity.*;

import java.util.*;

public class ServiceStoc {

    private Map<Produs, Integer> stoc;

    public Map<Produs, Integer> getStoc() {
        return stoc;
    }

    public void cautaFacturiFurnizor(long codFurnizor, Dosar d) {
        int gasit=0;
        for (FacturaIntrare factura : d.getFacturiIntrare()) {
            if (factura.getF().getCNP()  == codFurnizor) {
                factura.afisareFacturaIntrare(factura);
                System.out.println("\n");
                gasit=1;
            }
        }
        if(gasit==0) {
            System.out.println("Acest furnizor nu are nicio factura.");
        }
    }

    public void cautaFacturiClient(long codClient, Dosar d) {
        int gasit=0;
        for (FacturaIesire factura : d.getFacturiIesire()) {
            if (factura.getC().getCNP()  == codClient) {
                factura.afisareIesire(factura);
                System.out.println("\n");
                gasit=1;
            }
        }
        if(gasit==0) {
            System.out.println("Acest client nu are nicio factura.");
        }


    }


    public void sortareDupaPret() {
        List<Map.Entry<Produs, Integer>> list = new ArrayList<>(stoc.entrySet());
        Collections.sort(list, new Comparator<Map.Entry<Produs, Integer>>() {
            public int compare(Map.Entry<Produs, Integer> o1, Map.Entry<Produs, Integer> o2) {
                return Double.compare(o1.getKey().getPret(), o2.getKey().getPret());
            }
        });

        System.out.println(" -- Stoc sortat dupa pret: --");
        for (Map.Entry<Produs, Integer> entry : list) {
            System.out.println(entry.getKey().getNume() + " - Pret: " + entry.getKey().getPret() + " - Cantitate: " + entry.getValue());
        }
    }


    public void sortareDupaNrBucati() {
        List<Map.Entry<Produs, Integer>> stocList = new ArrayList<>(stoc.entrySet());
        Collections.sort(stocList, Comparator.comparing(Map.Entry::getValue));

        System.out.println(" -- Stoc sortat dupa numarul de bucati: --");
        for (Map.Entry<Produs, Integer> entry : stocList) {
            System.out.println(entry.getKey().getNume() + " - " + entry.getValue() + " buc.");
        }
    }

    public void aplicaReducere(int procent) {
        for (Produs p : stoc.keySet()) {
            double pretRedus = p.getPret() * (100 - procent) / 100.0;
            p.setPret(pretRedus);
        }
    }

    public ServiceStoc() {
        this.stoc = new HashMap<Produs, Integer>();
    }
    public ServiceStoc(Map<Produs, Integer> stoc) {
        this.stoc = stoc;
    }

    public void adaugaProdus(Produs produs, int cantitate) {
        if (stoc.containsKey(produs)) {
            int cantitateVeche = stoc.get(produs);
            stoc.put(produs, cantitateVeche + cantitate);
        } else {
            stoc.put(produs, cantitate);
        }
    }

    public void eliminaProdus(Produs produs, int cantitate) {
        if (stoc.containsKey(produs)) {
            int cantitateVeche = stoc.get(produs);
            int cantitateNoua = cantitateVeche - cantitate;
            if (cantitateNoua <= 0) {
                stoc.remove(produs);
            } else {
                stoc.put(produs, cantitateNoua);
            }
        }
        else System.out.println("Produsul acesta nu exista in stoc/\nNu exista o cantitate suficienta in stoc");
    }


    public int getStocProdus(Produs produs) {
        if (stoc.containsKey(produs)) {
            return stoc.get(produs);
        } else {
            return 0;
        }
    }
    public void afisareStoc() {
        for (Produs produs : stoc.keySet()) {
        System.out.println("Cod: " + produs.getCod() + ", Nume: " + produs.getNume() + ", Pret: " + produs.getPret() + ", Cantitate: " + stoc.get(produs));
        }
    }


    public void Vanzare( List<Produs> produse, List<Integer> cantitati) {
        for (int j = 0; j < produse.size(); j++) {
            Produs produs = produse.get(j);
            int cantitateActualizata = stoc.get(produs) - cantitati.get(j);
            if ( cantitateActualizata < 0 )
                System.out.println("Nu exista suficiente produse\n");
            else if(cantitateActualizata!=0)
                stoc.put(produs, cantitateActualizata);
        }
    }
    private static int numaratorFacturi = 0;



    public void adaugaProduse(Map<Produs, Integer> produseNoi) {
        for (Produs produs : produseNoi.keySet()) {
            int cantitate = produseNoi.get(produs);
            if (this.stoc.containsKey(produs)) {
                int cantitateVeche = this.stoc.get(produs);
                this.stoc.put(produs, cantitateVeche + cantitate);
            } else {
                this.stoc.put(produs, cantitate);
            }
        }
    }

    public FacturaIntrare generareFacturaIntrare(ServiceStoc ss, Furnizor furnizor, Map<Produs, Integer> produse) {
        // Crearea facturii
        numaratorFacturi++;
        int numarFactura = numaratorFacturi;
        double pret = 0;
        for (Produs produs : produse.keySet()) {
            pret += produs.getPret() * produse.get(produs);
        }
        List<Produs> listaProduse = new ArrayList<>(produse.keySet());
        List<Integer> listaCantitati = new ArrayList<>(produse.values());

        FacturaIntrare factura = new FacturaIntrare(furnizor, listaProduse, listaCantitati);

        // Adaugarea produselor în stoc
        ss.adaugaProduse(produse);

        return factura;
    }

    public Client citireClient() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("  -Introduceti numele clientului: ");
        String nume = scanner.nextLine();
        System.out.println(" -Introduceti CNP-ul clientului: ");
        long CNP = scanner.nextLong();
        scanner.nextLine(); // Consumam linia goala ramasa in buffer
        System.out.println(" -Introduceti varsta clientului: ");
        int varsta = scanner.nextInt();
        scanner.nextLine(); // Consumam linia goala ramasa in buffer
        System.out.println(" -Introduceti genul clientului: ");
        String gen = scanner.nextLine();

        return new Client(nume, CNP, varsta, gen);
    }

    public Furnizor citireFurnizor() {
        Scanner scanner = new Scanner(System.in);

        System.out.println(" -Introduceti numele furnizorului:");
        String nume = scanner.nextLine();

        System.out.println(" -Introduceti CNP-ul/CUI-ul furnizorului:");
        long CNP = scanner.nextLong();
        scanner.nextLine();

        System.out.println(" -Introduceti varsta/vechimea furnizorului:");
        int varsta = scanner.nextInt();
        scanner.nextLine();
        System.out.println(" -Adresa:");
        System.out.println("    *Introduceti orasul sediului:");
        String oras = scanner.nextLine();

        System.out.println("    *Introduceti strada sediului:");
        String strada = scanner.nextLine();

        System.out.println("    *Introduceti numarul sediului:");
        int numar = scanner.nextInt();
        scanner.nextLine();

        // initializam locatia furnizorului cu orasul, strada si numarul introduse
        Locatie locatie = new Locatie(oras, strada, numar);

        // returnam un nou obiect Furnizor cu toate campurile introduse
        return new Furnizor(nume, CNP, varsta, locatie);
    }
    public ServiceStoc adaugaProduseInLista() {
        ServiceStoc deVandut=new ServiceStoc();

        Scanner scanner = new Scanner(System.in);
        System.out.println("Introdu numarul de produse: ");
        int nrProduse = scanner.nextInt();
        scanner.nextLine();
        for (int i = 1; i <= nrProduse; i++) {
            System.out.println("Introdu numele produsului "+ i +": ");
            String nume = scanner.nextLine();
            System.out.println("Introdu pretul produsului "+ i +": ");
            double pret = scanner.nextDouble();
            System.out.println("Introdu codul produsului "+ i +": ");
            int cod = scanner.nextInt();
            System.out.println("Introdu cantitatea produsului "+ i +": ");
            int cantitate = scanner.nextInt();
            scanner.nextLine();

            Produs produs = new Produs(nume, pret, cod);
            deVandut.adaugaProdus(produs, cantitate);
        }

        return deVandut;
    }

    public void setStoc(Map<Produs, Integer> stoc) {
        this.stoc=stoc;
    }

    public void AfisareOptiuni(){
        System.out.println("Iata optiunile disponibile:");
        System.out.println("   1 - vanzare cu factura ");
        System.out.println("   2 - intrare cu factura ");
        System.out.println("   3 - vizualizare stoc curent ");
        System.out.println("   4 - vizualizare dosar ");
        System.out.println("   5 - vizualizare stoc sortat dupa pret ");
        System.out.println("   6 - vizualizare stoc sortat dupa numarul de bucati");
        System.out.println("   7 - aplicare reducere la intreg stocul ");
        System.out.println("   8 - vizualizare facturi pentru un client ");
        System.out.println("   9 - vizualizare facturi pentru un furnizor ");
        System.out.println("   10 - eliminare din stoc produs deteriorat/defect ");
        System.out.println("X| 13 |X - exclusiv pentru teste");


        System.out.println("   11 - IESIRE ");
    }
}

