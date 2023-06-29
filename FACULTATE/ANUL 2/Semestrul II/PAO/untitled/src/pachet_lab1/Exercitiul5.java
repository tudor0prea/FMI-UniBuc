package pachet_lab1;

import java.util.Scanner;
/**
 * Organizarea el in 2 vectori in fct de paritate
 *
 */
public class Exercitiul5 {

    //psvm
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Read n: ");
        int n = scanner.nextInt();

        int x[] = new int[n];
        int y[] = new int[n];
        int i = 0, j = 0;

        for (int el = 0; el < n; el++) {
            int element = scanner.nextInt();
            if (element % 2 == 0) {
                x[i] = element;
                i++;
            } else {
                y[j] = element;
                j++;
            }
        }

        System.out.println("Vectorul x: ");
        for (int el = 0; el < i; el++) {
            System.out.print(x[el] + " ");
        }

        System.out.println();

        System.out.println("Vectorul y: ");
        for (int el = 0; el < j; el++) {
            System.out.print(y[el] + " ");
        }
    }
}