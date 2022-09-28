/*
No método main (criação threads) -> criar N (N=10) threads;
No método run (o que cada thread faz) -> escrever os números de 1 a I (I=100);
Thread Principal -> esperar que as threads criadas terminem e escrever "Fim".
 */

//Criamos 1 a 1 e esperamos por elas 1 a 1
public class Ex1 {
    public static void main(String[] args) {
        int N = 10;
        Thread[] threads = new Thread[N];

        //Criar trheads
        //Criamos as threads uma a uma
        for (int i = 0; i<N; i++)
            threads[i] = new Thread((new Increment()));

        //Começar threads...
        for (int i = 0; i < N; i++)
            threads[i].start();

        //Esperar que cada thread termine...
        //Não há forma de dizer que queremos guardar todas, logo mandamos esperar uma a uma.
        for (int i = 0; i<N; i++){
            try {
                threads[i].join(); //vai obrigar todas as threads criadas e esperar pela principal.
                // threads[0].join -> obriga a thread main a esperar que t0 termine a sua execução
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("The end");
    }
}

/*
Não podemos ter:
t1 0    ->O que cada thread executa tem de ser feita por ordem,
          contudo, a ordem de execução das threads pode não ser por ordem.
t2 1
t1 2
t2 0
t3 1
*/