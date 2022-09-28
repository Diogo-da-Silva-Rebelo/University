package ficha1;
import java.util.Scanner;

/**
        * Nesta classe, temos a nossa função main, responsável por
        * aceder à porção computacional, porque é static e, por isso
        * acede aos métodos static estabelecidos na outra classe.
        * @author (Diogo Rebelo)
 * @version (1.0)
 */

public class TestePrograma {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Ficha1 f = new Ficha1();
        char c1 = 'S';

        while (c1 != 'N') {
            System.out.println("Introduza o nº da pergunta: ");
            int pergunta = input.nextInt();

            switch (pergunta) {
                case 1:
                    //1
                    System.out.println("Insira o valor de temperatura em graus Celsius: ");
                    double tc = input.nextDouble();
                    double tf = f.celsiusParaFarenheit(tc);
                    System.out.println("A temperatura convertida para Farenheit é: " + tf);
                    break;

                case 2:
                    //2
                    System.out.println("Insira os dois inteiros: ");
                    int one = input.nextInt();
                    int two = input.nextInt();
                    int max = f.maximoNumeros(one, two);
                    System.out.println("O máximo é: " + max);
                    break;

                case 3:
                    //3
                    System.out.println("Insira o nome: ");
                    String nome = input.toString();
                    System.out.println("Insira o respetivo saldo: ");
                    double saldo = input.nextDouble();
                    String dados = f.criaDescricaoConta(nome, saldo);
                    System.out.println(dados);
                    break;

                case 4:
                    //4
                    System.out.println("Insira o valor em euros e a respetiva taxa de conversão: ");
                    double valor = input.nextDouble();
                    double taxa = input.nextDouble();
                    double libras = f.eurosParaLibras(valor, taxa);
                    System.out.println("O valor convertido é: " + libras);
                    break;

                case 5:
                    //5
                    System.out.println("Insira os dois inteiros: ");
                    int one1 = input.nextInt();
                    int two1 = input.nextInt();
                    String average = f.descrescenteMedia(one1, two1);
                    System.out.println(average);
                    break;

                case 6:
                    //6
                    if (args.length == 0) System.out.println("Não foi dado argumento!");
                    System.out.println("O factorial desse número é: " + f.factorial(Integer.parseInt(args[0])));
                    break;

                case 7:
                    //7
                    System.out.println("Tempo gasto: " + (f.tempoGasto() / 100000.0) + " ns");
                    break;

                default:
                    System.out.println("Input inválido.");

            }
            System.out.println("Deseja fazer outra pergunta? [S/N] ");
            Scanner careter= new Scanner(System.in);
            c1 = careter.next().charAt(0);
        }
    }
}