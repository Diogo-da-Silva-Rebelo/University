package ficha1;
import java.time.LocalDateTime;

/* Classe que contém cada um dos métodos dos exercícios solicitados,
ou seja, cada método pode ser visto como uma função diferente, que
faz, por isso, algo distinto e específico. Estes métodos vão ser
chamados na classe "TestePrograma", que contém o nosso método main.
Esta classe contém tudo o que diz respeito a parte computacional.
 */
public class Ficha1 {
    public double celsiusParaFarenheit(double graus) {
        double tF;
        tF = graus * (1.8) + 32;
        return tF;
    }

    public int maximoNumeros(int a, int b) {
        int max;
        max = java.lang.Math.max(a, b);
        return max;
    }

    public int minimoNumeros(int a, int b) {
        return java.lang.Math.min(a, b);
    }

    public double media(int a, int b) {
        return ((double) a + (double) b) / 2;
    }

    public String criaDescricaoConta(String nome, double saldo) {
        return "Nome: " + nome + ", saldo: " + saldo;
    }

    public double eurosParaLibras(double valor, double taxaConversao) {
        return valor * taxaConversao;
    }

    public String descrescenteMedia(int a, int b) {
        return maximoNumeros(a, b) + " " + minimoNumeros(a, b) + ", média: " + media(a, b);
    }

    public long factorial(int num) {
        long fact = 1;
        for (int i = 1; i <= num; i++) fact *= i;
        return fact;
    }

    public long tempoGasto() {
        long start_time = LocalDateTime.now().getNano();
        long fact2 = factorial(5000);
        long finish_time = LocalDateTime.now().getNano();
        return finish_time - start_time;
        //o tempo vai dar sempre 0, pois a diferença é mínima, poderíamos ler em nanosegundos!
    }
}
