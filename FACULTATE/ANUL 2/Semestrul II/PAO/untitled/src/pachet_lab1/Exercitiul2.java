package pachet_lab1;

import java.util.Scanner;
/**
 * Scrieți un program care sa compare doua numere a și b citite de la tastatura si sa afiseze numarul mai
 * mare.
 */
public class Exercitiul2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Read a: ");
        int a = scanner.nextInt();

        System.out.println("Read b: ");
        int b = scanner.nextInt();

        System.out.println(Math.max(a, b));
    }
}