//package model_examen;
//
//
//import java.io.File;
//import java.util.Scanner;
////
//////class FirExecutare extends Thread {
//////    private String cuvant;
//////    private String cale_fisier;
//////
//////    private int nrAparitii;
//////
//////    public FirExecutare(String c, String f){
//////        this.cuvant=c;
//////        this.cale_fisier=f;
//////        this.nrAparitii=0;
//////    }
//////
//////    public int getNrAparitii(){
//////        return nrAparitii;
//////    }
//////    @Override
//////    public void run(){
//////        Scanner in = new Scanner(new File(cale_fisier));
//////
//////        while(in.hasNext()){
//////            String linie = in.nextLine();
//////            String []cuvinte= linie.split(",.+- ");
//////
//////            for(String i: cuvinte){
//////                if(cuvant.equals(i))
//////                    nrAparitii=nrAparitii+1;
//////            }
//////        }
//////
//////        in.close();
//////    }
//////
//////}
//////
//////
//////public class TestRulare {
//////
//////    public static void main(String[] args) {
//////        Scanner s = new Scanner(System.in);
//////        String cuvant = s.next();
//////
//////        FirExecutare f1 = new FirExecutare(cuvant,"exemplu_1.txt");
//////        FirExecutare f2 = new FirExecutare(cuvant,"exemplu_2.txt");
//////        FirExecutare f3 = new FirExecutare(cuvant,"exemplu_3.txt");
//////
//////        f1.start();
//////        f1.join();
//////
//////        f2.start();
//////        f2.join();
//////
//////        f3.start();
//////        f3.join();
//////
//////
//////        int t= f1.getNrAparitii()+f2.getNrAparitii()+f3.getNrAparitii();
//////    }
//////}
//////
//////
////
////
///////
////
//////class A{
//////    public int x=1 ;
//////}
//////class B extends A{
//////    public int x=2;
//////
//////}
//////public class Test {
//////
//////    public static void main(String[] args) {
//////        A ob = new B();
//////        System.out.println(++ob.x);
//////}
//////} -? se af.2
////
//////
////
////
//////class Tablou{
//////    static void met (int[] a, int b) {
//////        int aux;
//////        aux=a[0];a[0]=b;b=aux;
//////    }
//////}
//////
//////
//////public class Test {
//////    public static void main(String[] args) {
//////        int a[]={1, 2, 3, 4, 5}, b = 6;
//////        Tablou.met (a, b);
//////        int s = b;
//////        for (int i = 0; i < a.length; i++) s= s + a[i];
//////        System.out.println(s);
//////
//////    }
//////
//////
//////      6 2 3 4 5      b=1
//////}
////
////
/////// model 2
//////
//////public class FirExec extends Thread {
//////    private int nrImobile;
//////    private double suprafata;
//////    private int numarCamere;
//////
//////    private String caleFisier;
//////
//////    public FirExec(double suprafata, int numarCamere, String caleFisier) {
//////        this.nrImobile = 0;
//////        this.suprafata = suprafata;
//////        this.numarCamere = numarCamere;
//////        this.caleFisier = caleFisier;
//////    }
//////
//////    public int getNrImobile(){
//////        return nrImobile;
//////    }
//////
//////    @Override
//////    public void run(){
//////        Scanner in = new Scanner( new File(caleFisier));
//////
//////        while(in.hasNext()){
//////            String linie = in.nextLine();
//////            String[] date = linie.split(",");
//////            if( Integer.parseInt(date[2]) > numarCamere
//////                    && Integer.parseInt(date[3]) > suprafata ) {
//////                nrImobile=nrImobile+1;
//////            }
//////        }
//////
//////        in.close();
//////    }
//////}
//////
//////
//////public class TestImobile{
//////
//////    public static void main(String[] args) {
//////        Scanner s= new Scanner(System.in);
//////
//////        double smin;
//////        int cmin;
//////
//////        smin = s.nextDouble();
//////        cmin = s.nextInt();
//////
//////        FirExec f1 = new FirExec(smin,cmin,"agentieRentSale_1.txt");
//////        FirExec f2 = new FirExec(smin,cmin,"agentieRentSale_2.txt");
//////
//////
//////        f1.start();
//////        f1.join();
//////
//////        f2.start();
//////        f2.join();
//////
//////        int total = f1.getNrImobile()+f2.getNrImobile();
//////    }
//////
//////}
////
////
//////model  3
////
////
////public class FirExecutare extends Thread {
////
////    private double suma;
////
////    private String lexp;
////    private double pmin;
////    private String caleFisier;
////
////    public FirExecutare(String lexp, double pmin, String caleFisier){
////        this.suma=0;
////        this.lexp=lexp;
////        this.pmin=pmin;
////        this.caleFisier=caleFisier;
////
////    }
////
////    public double getSuma(){
////        return suma;
////    }
////
////    @Override
////    public void run(){
////
////        Scanner in = new Scanner( new File(caleFisier));
////
////        while(in.hasNext()){
////            String linie = in.nextLine();
////            String[] date = linie.split(",");
////
////            if( Integer.parseInt(date[3]) >= pmin && Integer.parseInt(date[4]) >=Integer.parseInt(lexp))
////            {
////                suma=suma+ Integer.parseInt(date[3]);
////            }
////        }
////
////        in.close();
////    }
////
////}
////
////public class TestRulare{
////
////    public static void main (String[] args){
////        Scanner s= new Scanner(System.in);
////
////        double p;
////        String l;
////
////        p=s.nextDouble();
////        l=s.next();
////
////        FirExecutare f1= new FirExecutare(l,p,"produse_1.txt");
////        FirExecutare f2 = new FirExecutare(l,p,"produse_2.txt");
////
////        f1.start();
////        f1.join();
////
////        f2.start();
////        f2.join();
////
////        double rezultat = f1.getSuma()+f2.getSuma();
////
////        System.out.println(rezultat);
////
////    }
////}
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
////
////
////
////
//
//public class FirExecutare extends Thread{
//    private String cuvant;
//
//    private String caleFisier;
//
//    private int numarAparitii;
//
//
//    public FirExecutare(String cuvant, String caleFisier) {
//        this.cuvant = cuvant;
//        this.caleFisier = caleFisier;
//        this.numarAparitii = 0;
//    }
//
//    public int getNumarAparitii() {
//        return numarAparitii;
//    }
//
//    @Override
//    public void run() {
//        Scanner in = new Scanner(new File(caleFisier));
//
//        while(in.hasNext()){
//            String linie=in.nextLine();
//            String[] date = linie.split(",.:;[\n]");
//            for(String i : date)
//                if(i.equals(cuvant))
//                    numarAparitii=numarAparitii+1;
//
//        }
//
//        in.close();
//    }
//
//}
////
////
////public class TestRulare{
////
////    public static void main(String[] args) {
////        Scanner s = new Scanner(System.in);
////
////        String cuvant = s.next();
////
////        FirExecutare f1= new FirExecutare(cuvant,"exemplu_1.txt");
////        FirExecutare f2= new FirExecutare(cuvant,"exemplu_2.txt");
////        FirExecutare f3= new FirExecutare(cuvant,"exemplu_3.txt");
////
////        f1.start();
////        f1.join();
////
////        f2.start();
////        f2.join();
////
////        f3.start();
////        f3.join();
////
////        int total = f1.getNumarAparitii()+f2.getNumarAparitii()+f3.getNumarAparitii();
////
////        System.out.println(total);
////    }
////
////}
//
//
//
//
//
//public class FirExecutare extends Thread{
//
//    private int n;
//    private String caleFisier;
//    private int numarCuvinte;
//
//    public FirExecutare(int n, String caleFisier) {
//        this.n = n;
//        this.caleFisier = caleFisier;
//        this.numarCuvinte = 0;
//    }
//
//    public int getNumarCuvinte(){return numarCuvinte;}
//
//    @Override
//    public void run(){
//
//        Scanner in = new Scanner(new File(caleFisier));
//
//        while(in.hasNext())
//        {
//            String linie = in.nextLine();
//            String[] date = linie.split(" ,.;:");
//            for(String cuvant:date){
//                if(cuvant.length() == n)
//                    numarCuvinte++;
//            }
//        }
//
//        in.close();
//    }
//}
//
//
//public class TestRulare(){
//
//    public static void main(String[] args) {
//        Scanner s = new Scanner(System.in);
//        int n = s.nextInt();
//
//        FirExecutare f1 = new FirExecutare(n,"poezie_1.txt");
//        FirExecutare f2 = new FirExecutare(n,"poezie_2.txt");
//
//        f1.start();
//        f1.join();
//
//        f2.start();
//        f2.join();
//
//        int numar = f1.getNumarCuvinte()+f2.getNumarCuvinte();
//        System.out.println(numar);
//
//    }
//}
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
