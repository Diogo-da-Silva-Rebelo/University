import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

class Bank2 {
    private static class Account {
        private int balance;
        public ReentrantLock lock = new ReentrantLock();
        Account(int balance) { this.balance = balance; }
        int balance() {
            lock.lock();
            try {
                return balance;
            }
            finally {
                lock.unlock();
            }
        }
        boolean deposit(int value) {
            lock.lock();
            try {
                balance += value;
                return true;
            }finally {
                lock.unlock();
            }

        }
        boolean withdraw(int value) {
            lock.lock();
            try {
                if (value > balance)
                    return false;
                balance -= value;
                return true;
            }finally {
                lock.unlock();
            }

        }


    }

    // Bank slots and vector of accounts
    private int slots;
    private Account[] av;


    public Bank2(int n)
    {
        slots=n;
        av=new Account[slots];
        for (int i=0; i<slots; i++) av[i]=new Account(0);
    }

    // Account balance
    public int balance(int id) {
        if (id < 0 || id >= slots)
            return 0;
        return av[id].balance();

    }

    // Deposit
    boolean deposit(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        return av[id].deposit(value);

    }

    // Withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        return av[id].withdraw(value);

    }
    public boolean transfer (int from, int to, int value){
        av[from].lock.lock();
        av[to].lock.lock();
        av[from].withdraw(value);
        av[to].deposit(value);
        av[from].lock.unlock();
        av[to].lock.unlock();

        return true;

    }

    public int totalBalance(){
        int sum = 0;

        for(int i = 0; i < slots; i++) {
            sum += av[i].balance();
        }
        return sum;

    }
}


class Mover1 implements Runnable {
    Bank2 b;
    int s; // Number of accounts

    public Mover1(Bank2 b, int s) {
        this.b = b;
        this.s = s;
    }

    public void run() {
        final int moves = 100000;
        int from, to;
        Random rand = new Random();

        for (int m = 0; m < moves; m++) {
            from = rand.nextInt(s); // Get one
            while ((to = rand.nextInt(s)) == from) ; // Slow way to get distinct
                b.transfer(from, to, 1);
        }
    }
}