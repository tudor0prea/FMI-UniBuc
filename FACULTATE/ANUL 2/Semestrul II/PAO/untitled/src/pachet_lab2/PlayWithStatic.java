package pachet_lab2;

public class PlayWithStatic {


    //Static se executa inainte de main

    //intai var statica
    //apoi blocul static
    //apoi constructorul


    private static int a = m1();

    static {
        System.out.println("in blocul static");
    }

    public static int m1() {
        System.out.println("from m1");
        return 20;
    }

    private int m2() {
        return 30;
    }

    public PlayWithStatic() {
        System.out.println("Constructor");
    }


}
