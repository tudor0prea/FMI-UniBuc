package pachet_lab8.list;

import java.util.*;

public class Example1 {

    public static void main(String[] args) {


        //instantiere
        List<String> fruit = new ArrayList<>();

        ArrayList<String> flowers = new ArrayList<>();

        List<String> seasons = new ArrayList<>(4);

        List<String> animals = new ArrayList<>(Arrays.asList("Cat", "Dog", "Parrot"));


        System.out.println("iterator:");
        Iterator<String>  iterator= animals.iterator();

        while( iterator.hasNext()) {
            String animal = iterator.next();
            System.out.println(animal+" ");
        }
        //operatii pe lista
        animals.add(2,"Fish");
        animals.add("Turtle");

        animals.set(1, "Pig");

        animals.remove(3);


        Iterator<String> iterator2=animals.iterator();
        while(iterator2.hasNext()){
            String animal= iterator2.next();
            if("Cat".equals(animal))
                //intai punem valoarea pe care o stim(constanta)
                iterator2.remove();
        }


        //sortare
        Collections.sort(animals);

        Collections.reverse(animals);

        //iterare
        System.out.println("for-each iteration:");
        for(String animal : animals){
            System.out.println(animal+" ");
        }


        //cautare
        int pigIndex = Collections.binarySearch(animals,"Pig");
        if(pigIndex>=0)
            System.out.println("\nPig found at index:"+pigIndex);
        else
            System.out.println("Pig not found :(");

    }

}
