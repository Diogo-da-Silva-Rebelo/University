//Receita ou instruções para cada thread - o que cada thread vai fazer
//Cada thread executa este código individualmente
//Quero uma nova thread que executa o código que aqui está
//Não é garantido que a t1 começa primeiro que t2 ou t3
//Não há uma ordem de execução das threads, cada uma executa individualmente
class Increment implements Runnable {
    public void run() {
        final long I = 100;

        for (long i = 0; i < I; i++)
            System.out.println(i);
    }
}