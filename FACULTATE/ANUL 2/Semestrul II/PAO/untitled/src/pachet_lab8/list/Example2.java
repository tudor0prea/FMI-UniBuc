package pachet_lab8.list;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Example2 {


    public static void main(String[] args) {


        List<Integer> numbers = new ArrayList<>();


        numbers.add(1);
        numbers.add(8);
        numbers.add(7);
        numbers.add(5);
        Collections.sort(numbers, new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1-o2;
            }
        });


    }
}
