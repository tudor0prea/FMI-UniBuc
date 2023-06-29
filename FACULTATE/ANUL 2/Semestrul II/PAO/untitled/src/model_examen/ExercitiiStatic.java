package model_examen;

    class A{
        public static int x=1 ;

        public void met(){
            System.out.println("met-A-non-static");
        }
        public static void met1(){
            System.out.println("met1-A-static");
        }
    }
    class B extends A{
        public static int x=2;
        public void met(){
            System.out.println("met-B-non-static");
        }
        public static void met1(){
            System.out.println("met1-B-static");
        }


    }

    public class ExercitiiStatic {

        public static void main(String[] args) {
            A ob = new B();
            //System.out.println(++ob.x);

            ob.met();
}
    }

