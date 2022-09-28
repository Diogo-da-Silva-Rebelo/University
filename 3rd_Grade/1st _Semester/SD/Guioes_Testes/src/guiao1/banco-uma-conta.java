package guiao1;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

//devemos questionarmo-nos quais as regiões críticas.
class Bank {

    private static class Account {
        private int balance;

        Account(int balance) {
            this.balance = balance;
        }

        int balance() {
            return balance;
        }

        boolean deposit(int value) {
            balance += value;
            return true;
        }
    }

    Lock lock = new ReentrantLock();

    // Our single account, for now
    private Account savings = new Account(0);

    // Account balance
    public int balance() {
        try{
            lock.lock();
            return savings.balance();
        }
        finally {
            lock.unlock();
        }
    }

    // Deposit
    boolean deposit(int value) {
        try {
            this.lock.lock();
            return savings.deposit(value);
        } finally {
            this.lock.unlock();
        }
    }
}