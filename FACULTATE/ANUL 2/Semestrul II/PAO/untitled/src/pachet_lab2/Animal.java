package pachet_lab2;

public class Animal {

    private String name, sound, food;
    private int age, noOfLegs=4;
    private CatBreed breed;
    public Animal() {}

    public Animal(int x){
        noOfLegs=x;
        breed=CatBreed.BRITISH_SHORT_HAIR;
    }

    public Animal(String nume, String sunet){
        sound=sunet;
        name=nume;
    }

    //public Animal(String nume,String food) => nu va merge ptc avem deja un
    // constr cu 2 param string

}
