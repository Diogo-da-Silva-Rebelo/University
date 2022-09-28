package ficha2;

import java.util.Arrays;
import java.util.Scanner;

public class Ex6 {
    private int[][] matrixOne;

    public void setMatrixOne(int[][] matrixOne) {
        this.matrixOne = matrixOne;
    }

    public int[][] getMatrix() {
        int[][] obj = new int[matrixOne.length][matrixOne[0].length];
        System.arraycopy(matrixOne, 0, obj, 0, this.matrixOne.length);
        return obj;
    }

    public void getSize(int rows, int cols) {
        this.matrixOne = new int[rows][cols];
    }

    public void readMatrixByUser() {
        int m, n, i, j;

        Scanner in = new Scanner(System.in);
        System.out.println("Enter the number of matrix's rows: ");
        m = in.nextInt();

        System.out.println("Enter the number of matrix's cols: ");
        n = in.nextInt();

        getSize(m, n);

        System.out.println("Enter matrix's elements: ");
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                this.matrixOne[i][j] = in.nextInt();

        System.out.println("The matrix's elements are");
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++)
                System.out.print(this.matrixOne[i][j] + " ");
            System.out.println();
        }
        System.out.println();
    }

    public int[][] sumMatrix(int o, int p) {
        int i, j;
        //assuming matrix of n order
        int m = this.matrixOne.length;
        int n = this.matrixOne[0].length;

        int[][] matrix1 = new int[m][n];
        System.arraycopy(this.matrixOne, 0, matrix1, 0, m);

        readMatrixByUser();

        if (m != o || n != p)
            System.out.println("Invalid matrix. ");
        else {
            for (i = 0; i < m; i++)
                for (j = 0; j < n; j++)
                    this.matrixOne[i][j] += matrix1[i][j];
        }

        return this.matrixOne.clone();
    }

    public boolean matrixEquals(int[][] matrix1) {
        return Arrays.deepEquals(matrix1, this.matrixOne);
    }

    public int[][] ConMatrix() {
        int i, j;
        //assuming matrix of n order
        int m = this.matrixOne.length;
        int n = this.matrixOne[0].length;

        int[][] matrix1 = new int[m][n];
        System.arraycopy(this.matrixOne, 0, matrix1, 0, m);

        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                this.matrixOne[i][j] = -(matrix1[i][j]);
        return matrix1;
    }
}