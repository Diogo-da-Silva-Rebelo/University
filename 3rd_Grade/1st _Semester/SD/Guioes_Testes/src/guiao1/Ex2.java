package guiao1;

//Criação de threads e especificação se esperam ou não
public class Ex2 {
    public static void main(String[] args) {
        int N = 10;
        Thread[] threads = new Thread[N];
        Bank bank = new Bank();

        //Criar trheads
        //Criamos as threads uma a uma
        for (int i = 0; i < N; i++)
            threads[i] = new Thread((new Deposit(bank)));

        //Começar threads...
        for (int i = 0; i < N; i++)
            threads[i].start();

        //Esperar que cada thread termine...
        //Não há forma de dizer que queremos guardar todas, logo mandamos esperar uma a uma.
        for (int i = 0; i < N; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("The end, Balance: " + bank.balance());
    }
}

//O que cada thread faz
class Deposit implements Runnable {
    Bank bank; //estado potencialmente partilhado pelas threads
    //o mesmo banco para todas
    public Deposit(Bank bank) {
        this.bank = bank;
    }

    public void run() {
        final long I = 1000;
        int V = 100;
        for (long i = 0; i < I; i++)
            //depositar 100 no banco
            this.bank.deposit(V);
    }
}
//Propriedade de exclusão mútua, importante para que uma thread não aceda a dados utilizados
// por outra thread. Para isso, identificamos a secção crítica e altermos o código
// Existem vários métodos para isso: ReetrankLock, lock, unlock.
