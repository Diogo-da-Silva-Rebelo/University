package ficha2;


public class Ex2 {

    private final int[][] notasTurma = new int[5][5];

    //Método que lê as notas dos alunos e as coloca na matriz 5x5
    public void inicializaPauta() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                this.notasTurma[i][j] = 0;
            }
        }
    }

    //diz uma nota a uma certa uc de um aluno especifico
    //em comentário pois não é usado
    /*
    public int getNotaAluno(int aluno, int uc) {
        return (this.notasTurma[aluno][uc]);
    } */

    //devolve array de notas dos alunos de uma uc
    public int[] getNotasUc(int uc) {
        int[] todasNotasUc = new int[5];

       // System.arraycopy(this.notasTurma[k][uc], 0, todasNotasAluno, 0, 5);
        for (int i = 0; i < 5; i++) {
            for (int j = uc; j < 5; j++) {
                todasNotasUc[i] = this.notasTurma[i][uc];
            }
        }

        return todasNotasUc;

    }

    //devolve array de todas as notas de um aluno
    public int[] getNotasAluno(int aluno) {
        int[] todasNotasAluno = new int[5];

        System.arraycopy(this.notasTurma[aluno], 0, todasNotasAluno, 0, 5);

        /*for (int i = aluno; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                todasNotasAluno[j] = this.notasTurma[aluno][j];
            }
        } */

        return todasNotasAluno;
    }

    public int somaUC(int uc) {
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += this.notasTurma[i][uc];
        }
        return sum;
    }

    public float mediaNotasAluno(int aluno) {
        int[] arrayNotas = getNotasAluno(aluno);

        int sum = 0;
        float media;


        for (int n : arrayNotas) sum += n;
        media = ((float) sum) / (float) 5;
        return media;
    }

    public float mediaNotasUc(int uc) {
        int[] arrayNotas = getNotasUc(uc);
        int sum = 0;
        float media;

        for (int n : arrayNotas) sum += n;
        media = ((float) sum) / (float) 5;
        return media;
    }

    public int notaMax() {
        int max = this.notasTurma[0][0];

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                max = Math.max(max, this.notasTurma[i][j]);
            }
        }
        return max;
    }

    public int notaMin() {
        int min = this.notasTurma[0][0];

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                min = Math.min(min, this.notasTurma[i][j]);
            }
        }
        return min;
    }

    public int[] notasAcimaDe(int limite) {
        int[] aux = new int[25];
        int k = 0;

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int valor = this.notasTurma[i][j];
                if (valor > limite) {
                    aux[k] = valor;
                    k++;
                }
            }
        }
        return aux;
    }

    public void mostraString() {
        for (int i = 0; i < 5; i++) {
            System.out.printf(" Aluno nº %d: |", i + 1);
            System.out.println("\n");
            for (int j = 0; j < 5; j++) {
                System.out.printf(" -> UC nº %d: %d", j + 1, this.notasTurma[i][j]);
                System.out.println("\n");
            }
            System.out.println("\n");
        }
    }

    /*
    public String calculaString() {
        String aux = "";
        String string = "";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                aux = "Aluno nº: " + i + " - UC nº: " + j + " - Nota: " + this.notasTurma[i][j] + "; ";
                string += aux;
            }

        }
        return string;
    }
     */


    public int ucMediaMaior() {
        int indice = 0;
        int media = 0;
        int aux = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                aux += this.notasTurma[j][i];
            }
            if (aux > media) {
                media = aux;
                indice = i;
            }
        }
        return indice;
    }

    //em comentário, pois não é usado
    /*
    public int indMaxArray(float[] array) {
        Ex1 p1 = new Ex1();
        float max = p1.maxArray(array);
        int k = 0;

        while (k < array.length && array[k] != max) k++;

        return k;
    } */

    public void atualizaPauta(int[][] notas) {
        System.arraycopy(notas, 0, this.notasTurma, 0, this.notasTurma.length);
    }
}
