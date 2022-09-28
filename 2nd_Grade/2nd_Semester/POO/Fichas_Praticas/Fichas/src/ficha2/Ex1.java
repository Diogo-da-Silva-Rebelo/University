package ficha2;

import java.util.Arrays;
import java.util.Scanner;

//Uma vez que vamos trabalhar com inteiros, o array a criar deve ser do tipo int, podemos começar por aí.
public class Ex1 {

    //declaração do nosso array, visível apenas nesta classe
    // Vamos criar um método de lê o nosso array e que o cria
    int[] getArray() {
        Scanner input = new Scanner(System.in);
        System.out.println("Introduza o tamanho do seu array: ");
        int sizeArray = input.nextInt();
        int[] array = new int[sizeArray];
        int k = 0;

        for (int elem : array) {
            System.out.printf("Introduza o %dº valor: ", k + 1);
            array[k] = input.nextInt();
            k++;
        }
        return array;
    }

    public int minArray(int[] array) {
        int min = Integer.MAX_VALUE;

        //n guarda o conteúdo em casa índice do array
        for (int n : array)
            if (n < min) min = n;

        return min;
    }

    //dá o maximo elemento em formato float (usado no Ex2)
    public float maxArray(float[] array) {
        float max = Integer.MIN_VALUE;

        //n guarda o conteúdo em casa índice do array
        for (float n : array)
            if (n > max) max = n;

        return max;
    }

    public int[] betweenArray(int[] array, int a, int b) {
        int[] newArray = new int[b - a + 1];
        int j = 0;

        for (int i = a; i < newArray.length; i++) {
            newArray[j] = array[i];
            j++;
        }

        return newArray;
    }

    public int[] sameArray(int[] one, int[] two) {
        int len1 = one.length;
        int len2 = two.length;
        int n = Math.max(len1, len2);
        int[] newArray = new int[n];
        int k = 0;

        for (int n1 : one) {
            for (int n2 : two) {
                if (n1 == n2) {
                    newArray[k] = n1;
                    k++;
                    break;
                }
            }
        }
        return newArray;
    }

    void sortArray(int[] array) {
        Arrays.sort(array);
    }

    int binarySearch(int[] array, int elemToFind) {
        return Arrays.binarySearch(array, elemToFind);
    }
}
