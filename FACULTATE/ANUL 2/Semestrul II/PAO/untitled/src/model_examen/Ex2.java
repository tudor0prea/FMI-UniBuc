//package model_examen;
//
//import java.util.Collection;
//import java.util.Comparator;
//import java.util.LinkedList;
//import java.util.stream.Collectors;
//import java.util.stream.IntStream;
//
//public class Ex2 {
//    public class Automobil {};
//
//    public void functie() {
//        // Subiectul al II-lea
//        LinkedList<Automobil> la = new LinkedList<>();
//        la.add(new Automobil());
//
//
//        la.stream().filter(x -> x.getPret() >= 5000)
//                .sorted(Comparator.comparing(Automobil::getPret)).reversed()
//                .forEach(System.out::prinln);
//
//        la.stream().map(Automobil::getMarca).distinct().forEach(System.out::println);
//
//        LinkedList<Automobil> l2 = la.stream().filter(x->x.getCapacitate() >= 2000)
//                .filter(x-> x.getCapacitate() <= 3000).collect(Collectors.toList());
//
//
//        System.out.println(la.stream().filter(x->x.getMarca().equals("Audi"))
//                .collect(Collectors.maxBy(Comparator.comparing(Automobil::getPret))));
//
//
//    }
//
//
//
//
////
////
////
////
////
////    System.out.println("Cerinta a)");
////        la.stream().filter(a -> a.getPret() >= 5000).
////        sorted(Comparator.comparing(Automobil::getPret).reversed()).forEach(System.out::println);
////        System.out.println();
////     // --
////    l.stream().filter( x -> x.getPret() >=5000).
////
////    sorted( (x,y) -> {
////        if(x.getPret() > y.getPret() )
////            return -1;
////        else if(x.getPret() < y.getPret() )
////            return 1;
////        else return 0;
////    }).
////
////    forEach(System.out::println);
////
////    //--
////    System.out.println("Cerinta b)");
////    la.stream().map(Automobil::getMarca).distinct().forEach(System.out::println);
////    System.out.println();
////
////
////    // ---
////    System.out.println("Cerinta c)");
////    List<Automobil> ln = la.stream().filter(a -> a.getCapacitate() >= 2000).
////            filter(a -> a.getCapacitate() <= 3000).collect(Collectors.toList());
////
////    ln.stream().forEach(System.out::println);
////    System.out.println();
////
////
////    // ---
////    System.out.println("Cerinta d)");
////    System.out.println(la.stream().filter(a -> a.getMarca().equals("Audi")).
////    collect(Collectors.minBy(Comparator.comparing(Automobil::getPret))));
////    System.out.println();
////
////
//
////
////
////
////
////    // examen iunie  ?
////
////    LinkedList<Imobil> la=new LinkedList<>();
////    li.add(new Imobil("casa","Bucuresti",5,60.2,65.5));
////    li.add(new Imobil("apartament","Bucuresti",3,54.2,575));
////    li.add(new Imobil("casa","Buzau",5,60.2,650.5));
////    li.add(new Imobil("casa","Bacau",5,60.2,65.5));
////    li.add(new Imobil("apartament","Brasov",2,30.5,78.5));
////
////    //a
////    la.stream().filter(x->x.getNrCamere() >=3 ).filter(x->x.getPret()<=10000)
////            .sorted(Comparator.comparing(Imobil::getSuprafata)).reversed()
////    .forEach(System.out::println);
////
////    //b
////    la.stream().map(Imobil::getLocalitate).distinct().forEach(System.out::println);
////
////
////    //c
////    LinkedList<Imobil> l2= la.stream().filter(x-> x.getPret()>200)
////            .filter(x->x.getPret()<500)
////            .filter(x-> x.getLocalitate().equals("Bucuresti"))
////            .collect(Collectors.toList());
////    l2.stream().forEach(System.out::println);
////
////    //d
//////    la.stream().filter(x->x.getLocalitate().eqals( la.stream()
//////    .map(Imobil::getOras).distrinct()));
//////
////
////
////    List <String> lista_orase=la.stream().map(Imobil::getOras).distinct(). collect(Collectors.toList());
////
////    for ( String loca: lista_orase)
////            la.stream().filter(x->x.getLocalitate().eqals(loca).forEach(System.out::println()));
////
////
////
////
////
////
//////
////    // iunie 2
////    //a
////    la.stream().filter(x-> x.getMaterial().eqals("aur")).filter(x->x.getPret() <= 100)
////            .sorted(Comparator.comparing(Suvenir::getPret))
////            .forEach(System.out::println);
////
////    //b
////    la.stream().map(Suvenir::getMaterial).distinct().forEach(System.out::println);
////
////
////    //c
////    Collection<Suvenir> c= la.stream().filter(x->x.getMaterial().equals("plastic"))
////            .filter(x->x.getPret() >= 500).filter(x->x.getPret() <=1000)
////            .collect(Collectors.toCollection());
////
////    //d
////    List<String> materiale= la.stream().map(Suvenir::getMaterial).distinct()
////            .collect(Collectors.toList());
////    for(String material : materiale )
////        la.stream().filter(x->x.getMaterial().equals(material))
////
//////
////
////
////
////
////
////
////
////
////
////
////
////
////
////    //// S3 model
////
////    public class FirExecutare extens Thread {
////        private String cuvant;
////        private String cale_fisier;
////
////        private int nrAparitii;
////
////        public FirExecutare(String c, String f){
////            this.cuvant=c;
////            this.cale_fisier=f;
////            this.nrAparitii=0;
////        }
////
////        @Override
////        public void run(){
////
////        }
////
////    }
////    public static void main(String[] args) {
////
////    }
////}
//
//
//
//
///// model 2020
////
////    public void functie(){
////
////        LinkedList<DiplomaLicenta> dl=new LinkedList<> ();
////        dl.add(new DiplomaLicenta(24,"Gigel",2023,"FMI","Informatica",8));
////
////        dl.stream().filter(x->x.getAn() >=2000).filter(x->x.getAn() <=2010)
////                .sorted(Comparator.comparing(DiplomaLicenta::getMedie))
////                .reversed().forEach(System.out::println);
////
////        dl.stream().filter(x->x.getAn().equals(2018))
////                .filter(x->x.getFacultate().equals("Informatica"))
////                .map(DiplomaLicenta::getSpecializare).distinct()
////                .forEach(System.out::println);
////
////        LinkedList<String> nume = dl.stream().filter(x->x.getMedie().equals(10))
////                .map(DiplomaLicenta::getAbsolvent)
////                .collect(Collectors.toList());
////
////        System.out.println(dl.stream().filter(x->x.getSpecializare().equals("Informatica"))
////                .count());
////
////
////    }
////}
//
//
// pao septembrie 2020
//
//    public void functie()
//    {
//
//        class ProdusAlimentar{
//            public String denumire;
//
//            public String getDenumire() {
//                return denumire;
//            }
//        }
//
//
//        LinkedList<ProdusAlimentar> pa= new LinkedList<>();
//        pa.add(new ProdusAlimentar("Salam",5,10,"21-06-2023"));
//
//
//        pa.stream().filter(x-> x.getDenumire().startsWith("A"))
//                .sorted(Comparator.comparing(ProdusAlimentar::getPret))
//                .forEach(System.out::println);
//
//        Collection<ProdusAlimentar> lista = pa.stream().filter(x->x.getPret() >= 100)
//                .filter(x->x.getPret() <=1000).collect(Collectors.toCollection());
//
//        System.out.println(pa.stream().map(ProdusAlimentar::getPret).sum() );
//
//
//        for(int i=1;i<=12;i++)
//            pa.stream().filter( x->Integer.parseInt(x.getData().split("-")[1]).equals(i))
//                .forEach(System.out::println);
//        //
//
//        IntStream.rangeClosed(1, 12)
//                .forEach(i -> pa.stream()
//                        .filter(x -> Integer.parseInt(x.getData().split("-")[1]) == i)
//                        .forEach(System.out::println));
//
//    }

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
