package proiect_inc1;

import config.DatabaseLogWriter;
import proiect_inc1.entity.*;
import proiect_inc1.services.ServiceStoc;

import java.time.LocalDate;
import java.util.*;
import java.util.Map;
import proiect_inc1.repository.*;

public class Main {


    public static void rulareTest() {

            Scanner scanner = new Scanner(System.in);

            // Testarea metodelor pentru clasa Locatie
            Locatie locatie = new Locatie("Oras", "Strada", 123);
            LocatieRepository locatieRepository = new LocatieRepository();

            // Inserare locatie
            locatieRepository.insertLocatie(locatie);


            // Actualizare locatie
            locatie.setOras("Oras Actualizat");
            locatieRepository.updateLocatie(locatie);


            // Testarea metodelor pentru clasa Factura
            Factura factura = new Factura(1,456);
            FacturaRepository facturaRepository = new FacturaRepository();

            // Inserare factura

            Factura factura2 = new Factura(1,3, LocalDate.of(2023, 05, 26),LocalDate.of(2023, 06, 26));
            System.out.println("Introduceti cnp pentru factura:");
            int cnpFactura=scanner.nextInt();
            facturaRepository.insertFactura(factura2.getNumarFactura(),factura2.getDataEmiterii(),factura2.getDataScadentei(), cnpFactura, cnpFactura+1);

            // Afisare factura
            //facturaRepository.afisareFacturaIntrareSql(factura.getNumarFactura());

            // Actualizare factura
            factura.setDataEmiterii(LocalDate.now().minusDays(1));
            facturaRepository.updateFactura(factura);

            // Stergere factura
            facturaRepository.deleteFactura(factura.getNumarFactura());

            // Testarea metodelor pentru clasa Furnizor

            System.out.print("Introduceti cnp pentru furnizor: ");
            int cnp = scanner.nextInt();
            Furnizor furnizor = new Furnizor("Nume Furnizor", cnp, 35);
            FurnizorRepository furnizorRepository = new FurnizorRepository();

            // Inserare furnizor
            furnizorRepository.insertFurnizor(furnizor);


            // Actualizare furnizor
            furnizor.setNume("Nume Furnizor Actualizat");
            furnizorRepository.updateFurnizor(furnizor);


            // Testarea metodelor pentru clasa Client
            Client client = new Client("Nume Client", 1234567890, 35, "F");
            ClientRepository clientRepository = new ClientRepository();

            // Inserare client
            clientRepository.insertClient(client);

            // Afisare client
            clientRepository.afisareClient(client.getCNP());

            // Actualizare client
            client.setNume("Nume Client Actualizat");
            clientRepository.updateClient(client);

            // Stergere client
            clientRepository.deleteClient(client.getCNP());
    }



    public static void main(String[] args) {
        FacturaRepository fr= new FacturaRepository();
        Dosar d = new Dosar();

        System.out.println("         --Program GEST. STOC v1.0 (04.2023)--\n");
        System.out.println(" ----Bine ati venit in programul de gestionare a stocului! ---- \n");

        Scanner scanner = new Scanner(System.in);


        ServiceStoc serviceStoc = new ServiceStoc();



        System.out.println("Pentru inceput, stocul magazinului este gol. Va recomandam sa introduceti o factura de intrare.");
        serviceStoc.AfisareOptiuni();
        System.out.print("Introduceti o optiune: \n->");
        int optiune = scanner.nextInt();
        System.out.println("Ati introdus: " + optiune);
            int ok=1;
            do{
                switch (optiune) {
                    case 1:
                        System.out.println(" --Introduceti datele clientului:--\n");

                        Client cumparator = serviceStoc.citireClient();
                        System.out.println("Cate (tipuri de) produse doreste clientul?\n->");
                        int numar_produse = scanner.nextInt();

                        System.out.println("Doriti o afisare a stocului mai intai? (1 pentru 'DA' si 0 pentru 'NU')\n->");
                        int dasaunu = scanner.nextInt();
                        if(dasaunu==1)
                            serviceStoc.afisareStoc();

                        double pret=0;
                        List<Produs> listaProduse = new ArrayList<>();
                        List<Integer> listaCantitati = new ArrayList<>();

                        for (int i = 1; i <= numar_produse; i++) {
                            System.out.println("Introduceti codul produsului:\n->");
                            int cod_produs= scanner.nextInt();
                            System.out.println("  Introduceti numarul de bucati:\n->");
                            int cantitate= scanner.nextInt();
                            Produs produs = null;
                            int stocActual = 0;
                            Map<Produs, Integer> stoc = serviceStoc.getStoc();
                            for (Map.Entry<Produs, Integer> entry : stoc.entrySet()) {
                                if (entry.getKey().getCod()==cod_produs) {
                                    produs = entry.getKey();
                                    stocActual = entry.getValue();
                                    break;
                                }
                            }

                            if (stocActual < cantitate) {
                                System.out.println("Nu exista suficient stoc pentru a onora comanda.");
                                break;
                            }

                            // actualizez stocul
                            stoc.put(produs, stocActual - cantitate);
                            serviceStoc.setStoc(stoc);

                            // calculez pretul
                            pret += cantitate * produs.getPret();

                            listaProduse.add(produs);
                            listaCantitati.add(cantitate);

                        }


                        FacturaIesire noua = new FacturaIesire(cumparator, listaProduse, listaCantitati) ;
                        //adaugam factura in dosar!
                        d.setFacturiIesire( d.getFacturiIesire().add(noua));
                        d.cresteNumarIes();

                        if (noua != null) {
                            noua.afisareIesire(noua);
                        }
                        break;

                    case 2:
                        System.out.println(" --Introduceti datele furnizorului:-- \n");
                        Furnizor furnizor=serviceStoc.citireFurnizor();
                        ServiceStoc articolev = serviceStoc.adaugaProduseInLista();
                        Map<Produs, Integer> listaArticolev = articolev.getStoc();
                        FacturaIntrare nouaIntrare = serviceStoc.generareFacturaIntrare(serviceStoc, furnizor, listaArticolev);

                        //adaugam factura in dosar
                        d.setFacturiIntrare( d.getFacturiIntrare().add(nouaIntrare));
                        d.cresteNumarInt();
                        nouaIntrare.afisareFacturaIntrare(nouaIntrare);


                        break;
                    case 3:
                        System.out.println(" -- Acesta este stocul magazinului: -- \n");
                        serviceStoc.afisareStoc();

                        break;
                    case 4:
                        System.out.println(" -- Acestea sunt facturile emise: -- \n");
                        d.afisareFacturi();

                        break;
                    case 5:
                        serviceStoc.sortareDupaPret();
                        break;
                    case 6:
                        serviceStoc.sortareDupaNrBucati();
                        break;
                    case 7:
                        System.out.println(" -- Reducere produse: -- ");
                        System.out.println("Introduceti procentul reducerii: \n->");
                        int x=scanner.nextInt();
                        serviceStoc.aplicaReducere(x);
                        System.out.println("Toate produsele au fost reduse cu "+ x+"%.\n");
                        break;
                    case 8:
                        System.out.println(" -- Cautare facturi client -- ");
                        System.out.println("Introduceti CNP-ul clientului: \n->");
                        long y=scanner.nextLong();
                        serviceStoc.cautaFacturiClient(y,d);



                        break;
                    case 9:
                        System.out.println(" -- Cautare facturi furnizor -- ");
                        System.out.println("Introduceti CNP-ul/CUI-ul furnizorului: \n->");
                        long z=scanner.nextLong();
                        serviceStoc.cautaFacturiFurnizor(z,d);

                        break;
                    case 10:
                        System.out.println(" -- Eliminare produs deteriorat/defect -- ");

                        System.out.println("Introduceti codul produsului:\n->");
                        int cod_produs= scanner.nextInt();
                        System.out.println("  Introduceti numarul de bucati:\n->");
                        int cantitate= scanner.nextInt();
                        Produs produs = null;
                        int stocActual = 0;
                        Map<Produs, Integer> stoc = serviceStoc.getStoc();
                        for (Map.Entry<Produs, Integer> entry : stoc.entrySet()) {
                            if (entry.getKey().getCod()==cod_produs) {
                                produs = entry.getKey();
                                stocActual = entry.getValue();
                                break;
                            }
                        }

                        if (stocActual < cantitate) {
                            System.out.println("Nu exista atatea bucati in stoc.");
                            break;
                        }

                        // actualizez stocul
                        stoc.put(produs, stocActual - cantitate);
                        serviceStoc.setStoc(stoc);


                        System.out.println("╔══════════════════════════════════════════════════╗\n");
                        System.out.println("               DEVIZ DE DETERIORARE\n");
                        System.out.println("      Astazi, " + LocalDate.now() + " , un numar de ");
                        System.out.println("     " + cantitate + " bucati din produsul cu codul" );
                        System.out.println("     " + cod_produs + " au fost declarate imposibil de");
                        System.out.println("      vandut si au fost eliminate din stoc.\n");

                        System.out.println("╚══════════════════════════════════════════════════╝\n");

                        break;
                    case 11:
                        System.out.println( "\n---- La revedere! ----\n" );
                        ok=0;
                        break;
                    case 12:
                        fr.afisareFacturaIntrareSql(1);

                    case 13:
                        rulareTest();

                }
                System.out.println("\n  Doriti sa mai efectuati vreo operatiune? (1 pentru 'DA' sau 0 pentru 'NU')");
                int dasaunu2=scanner.nextInt();
                if(dasaunu2!=0) {
                    System.out.println(" \n\n\n\n");
                    serviceStoc.AfisareOptiuni();
                    System.out.println("->");
                    optiune = scanner.nextInt();
                }
                else {
                    System.out.println("\n---- La revedere! ----\n");break; }
            } while(ok!=0);

        }


    }
