package ficha2;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class TestePrograma {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        char c1 = 'S';

        while (c1 != 'N') {
            System.out.println("Introduza o nº da pergunta: ");
            int pergunta = input.nextInt();

            // Como vamos ler sempre arrays, porque não criar um método que faça isso na classe Ficha2?
            switch (pergunta) {
                case 1:
                    //1
                    Ex1 ex1 = new Ex1();
                    int[] array = ex1.getArray();
                    int min = ex1.minArray(array);
                    System.out.println("O menor elemento do array é: " + min);

                    System.out.println("Introduza os dois índices do array: ");
                    int a = input.nextInt(), b = input.nextInt();
                    int[] betweenArray = ex1.betweenArray(array, a, b);
                    System.out.println("O novo array dimensionado é: " + Arrays.toString(betweenArray));

                    System.out.println("Introduza o 2º array: ");
                    int[] array2 = ex1.getArray();
                    int[] compatibleArray = ex1.sameArray(array, array2);
                    System.out.println("O novo array compatível é: " + Arrays.toString(compatibleArray));

                    //ordenação do array com a interseção dos dois arrays anteriores
                    ex1.sortArray(compatibleArray);
                    break;

                case 2:
                    //2
                    Scanner input2 = new Scanner(System.in);
                    Ex2 ex2 = new Ex2();

                    ex2.inicializaPauta();

                    int[][] notasTurma = {
                            {10,12,16,11,19},
                            {10,10,10,10,10},
                            {11,12,13,14,15},
                            {8 ,9 ,12, 7, 5},
                            {7 ,6 ,4 ,18,15}
                    };

                    ex2.atualizaPauta(notasTurma);
                    System.out.println("Array é : "+ Arrays.deepToString(notasTurma) + "\n");
                    ex2.mostraString();

                    System.out.println("Selecione o índice da UC [0 a 4] sobre a qual quer saber a soma das notas: ");
                    int UC = input2.nextInt();
                    int sumUc = ex2.somaUC(UC);
                    float mediaUc = ex2.mediaNotasUc(UC);

                    System.out.printf("A soma e média das notas da UC selecionada são: %d e %f\n\n", sumUc, mediaUc);

                    System.out.println("Selecione o aluno [0 a 4] sobre o qual quer saber a média das notas: ");
                    int aluno = input2.nextInt();
                    float mediaAluno = ex2.mediaNotasAluno(aluno);
                    System.out.println("A média das notas do aluno selecionado é: " + mediaAluno);

                    int notaMaxima = ex2.notaMax();
                    int notaMinima = ex2.notaMin();
                    System.out.printf("A nota mais alta e mais baixa da pauta são: %d e %d\n\n", notaMaxima, notaMinima);


                    System.out.println("Pretendo ver as notas acima do valor:");
                    int valorlimite = input.nextInt();
                    int[] acima = ex2.notasAcimaDe(valorlimite);
                    System.out.println("O array dessas notas é: " + Arrays.toString(acima) + "\n");


                    //calcular media de cada UC e dar o indice maior
                    int indexMax = ex2.ucMediaMaior();
                    System.out.println("O índice da UC com maior média é: " + indexMax);

                    break;
                case 3:
                    //3
                    Ex3 ex3 = new Ex3(4);

                    //Inserção
                    ex3.insereDatas(LocalDate.now());
                    System.out.println("Inserção da data de hoje.");
                    ex3.insereDatas(LocalDate.of(2021,10,2));
                    System.out.println("Inserção da data 02-10-2021.");
                    ex3.insereDatas(LocalDate.of(2021,11,2));
                    System.out.println("Inserção da data 02-11-2021.");
                    ex3.insereDatas(LocalDate.of(2001,1,19));
                    System.out.println("Inserção da data de aniverśario do Purp.");

                    //Cálculo da data mais próxima do aniverśario do Purp
                    LocalDate datamProx = ex3.dataMaisProxima(LocalDate.of(2021,1,19));
                    System.out.println("A data mais próxima do aniv do Purp é: " + datamProx.toString());

                    System.out.println("\nO array de datas inseridas é: " + ex3 + "\n");
                    break;
                case 4:
                    //4
                    Scanner x = new Scanner(System.in);

                    int[] experiment = {10,42,45,87,567,172,129,116,114,166};
                    Ex4 ex4 = new Ex4(experiment);

                    System.out.println("O seu array ordenado é: " + Arrays.toString(ex4.ordena()));
                    System.out.println("Introduza o elemento a procurar: ");
                    int elem = x.nextInt();
                    System.out.println("Busca Binária \n " +
                            "[Valor negativo? Não existe]\n " +
                            "[Valor positivo? Índice]\n-> "+ ex4.procuraB(elem));
                    break;
                case 5:
                    //5
                    Ex5 ex5 = new Ex5();
                    System.out.println("Insert Strings separated by spaces [put a repetition for test]: ");
                    ex5.readString();
                    String[] stringArray = ex5.stoArrayStrings();
                    System.out.println("Your array of strings is: " + Arrays.toString(stringArray));

                    String[] stringNoRep = ex5.noRepetitions(stringArray);
                    System.out.println("Inserted string with no repetitions is: " + Arrays.toString(stringNoRep) + "\n");

                    String biggerString = ex5.greaterString(stringNoRep);
                    System.out.println("Bigger inserted string is: " + biggerString + "\n");

                    ArrayList<String> dup = ex5.dupStrings(stringArray);
                    System.out.println("Array of repetitions: " + dup + "\n");

                    System.out.println("Put the string whose number of times you want to know: ");
                    String s = input.next();
                    int numberOfRep = ex5.numberRep(stringArray,s);
                    System.out.printf("Inserted String shows up %d times.\n",numberOfRep);
                    break;

                case 6:
                    //6
                    Scanner n = new Scanner(System.in);
                    Ex6 ex6 = new Ex6();
                    ex6.readMatrixByUser();

                    int[][] initialMatrix = ex6.getMatrix();

                    System.out.println("Insert nº of rows & cols of matrix you want to sum with:  ");
                    int rows = n.nextInt();
                    int cols = n.nextInt();

                    System.out.println("Insert matrix you want to sum with:  ");
                    int[][] finalSum = ex6.sumMatrix(rows,cols);
                    System.out.println("Final matrix is: " + Arrays.deepToString(finalSum));

                    ex6.setMatrixOne(initialMatrix);
                    System.out.println("Matrix 1 & 2 are equals ? Answer: " + ex6.matrixEquals(finalSum));

                    int [][] oppositeMatrix = ex6.ConMatrix();
                    System.out.println("The Opposite Matrix of the initial one is: " + Arrays.deepToString(oppositeMatrix));
                    break;

                case 7:
                    //7
                    Ex7 ex7 = new Ex7();

                    ex7.generateNKey2();
                    ex7.generateSKey2();
                    System.out.println("Next key was generated: \n" +  ex7);
                    ex7.keySort();
                    System.out.println("Next key was generated was sorted: \n" +  ex7);

                    int[] numbers = ex7.readNumbers();
                    int[] stars = ex7.readStars();
                    System.out.println("Key inserted with sucess: \n" + "Numbers: " + Arrays.toString(numbers) + "\nStars:   " + Arrays.toString(stars));

                    int[] userNumbersSorted = ex7.userNumberSort(numbers);
                    int[] userStarsSorted = ex7.userStarSort(stars);
                    System.out.println("Key inserted was sorted: \n" + "Numbers: " + Arrays.toString(userNumbersSorted) + "\nStars:   " + Arrays.toString(userStarsSorted));

                    System.out.println("\nComparing...");
                    int [] correctNumbers = ex7.compareNumbers(numbers);
                    int[] correctStars = ex7.compareStars(stars);
                    System.out.println("Done.");
                    System.out.println("Matching numbers & stars appearing bellow: \n" + "\nNumbers:  "+ Arrays.toString(correctNumbers) + "\nStars:    " + Arrays.toString(correctStars));
                    ex7.checkAllKey(correctNumbers,correctStars);
                    break;

                default:
                    System.out.println("Input inválido.");
            }

            System.out.println("Deseja fazer outra pergunta? [S/N] ");
            Scanner careter = new Scanner(System.in);
            c1 = careter.next().charAt(0);
        }
    }
}
