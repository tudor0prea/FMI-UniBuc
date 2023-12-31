package pachet_lab2;

import java.util.Arrays;

public class Matrice {

    public static void main(String[] args) {
//      int[][] wrong = new int[][]; // not OK, you must specify 1st dimension
        int[][] right = new int[2][]; // OK
        int right2[][] = new int[2][]; // OK

        String[][] myArray = new String[5][]; // OK
        String[][] yourArray = new String[5][4]; // OK

        // initializing two dimensional array as literal
        String[][] names = {{"Sam", "Smith"}, {"Robert", "Downey Jr"}, {"Ryan", "Gosling"}};
        for (int i = 0; i < names.length; i++) {
            for (int j = 0; j < names[i].length; j++) {
                System.out.print(names[i][j]+ " ");
            }
            System.out.println();
        }


        String[][] names2={{"AA","b"},{"AB","b"},{"ABC","b"},{"ABCD","b"}};
        //deep equals
        System.out.println("Names + names2 are: " + Arrays.deepEquals(names,names2));

        int[][] board = new int[3][3];
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                board[i][j] = i + j;
            }
        }
        for (int[] cols : board) {
            for (int anInt : cols) {
                System.out.print(anInt);
            }
            System.out.println();
        }

    }
}
