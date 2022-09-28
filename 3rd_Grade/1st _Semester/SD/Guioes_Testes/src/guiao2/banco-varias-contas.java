package guiao2;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

//Exercícios 1 e 2
//três execuções que não podem ser simultâneas
class Bank {
    private static class Account {
        Lock lock = new ReentrantLock();
        private int balance;

        Account(int balance) {
            this.balance = balance;
        }

        int balance() {
            return balance;
        }

        boolean deposit(int value) {
            try {
                lock.unlock();
                balance += value;
                return true;
            } finally {
                lock.unlock();
            }

        }

        boolean withdraw(int value) {
            try {
                lock.lock();
                if (value > balance)
                    return false;
                balance -= value;
                return true;
            }
            finally {
                lock.unlock();
            }
        }
    }

    // Bank slots and vector of accounts
    private final int slots;
    private final Account[] av;

    Lock lock = new ReentrantLock();

    public Bank(int n) {
        slots = n;
        av = new Account[slots];
        for (int i = 0; i < slots; i++) av[i] = new Account(0);
    }

    // Account balance
    public int balance(int id) {
        if (id < 0 || id >= slots)
            return 0;
        try {
            lock.lock();
            return av[id].balance();
        } finally {
            lock.unlock();
        }
    }

    // Deposit
    boolean deposit(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        try {
            lock.lock();
            return av[id].deposit(value);
        } finally {
            lock.unlock();
        }

    }

    // Withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        try {
            lock.lock();
            return av[id].withdraw(value);
        } finally {
            lock.unlock();
        }
    }

    //Transfer
    public boolean transfer(int from, int to, int value) {
        if (from < 0 || to < 0 || from >= slots || to >= slots)
            return false;
        try { //ver o cenário abaixo
            lock.lock();
            this.withdraw(from, value);
            this.deposit(to, value);
        } finally {
            lock.unlock();
        }
        return true;
    }

    //Total
    public int totalBalance() {
        int sum = 0;
        try {
            lock.lock();
            for (int i = 0; i < slots; i++)
                sum += av[i].balance();
        } finally {
            lock.unlock();
        }
        //E se usarmos o balance do bank?
        // sum += this.balance(i); -> possível alternativa a locks
        return sum;
    }
}

/* o lock faz com que nós leiamos antes, se façam as operações necessárias, e depois destas operações
se leia novamente. Durante as operações que alteram o saldo, não vamos lê-lo.
o lock pode não ser estritamente necessário, mas não se perde nada.
*/

/*
-----------------  Cenário: transfer(0,1,10) ----------------------------------------------
conta 0 - 10 euros
conta 1 - 0 euros

t1:

. withdraw(0,10) - lock,...,unlock
. ...
. deposit(1,10) - lock,...,unlock



t2:

. saldo total: 10 (saldo da conta 0 + saldo da conta 1)
. saldo total: 0  (saldo da conta 0 + saldo da conta 1)
. saldo final: 10 (saldo da conta 0 + saldo da conta 1)

-----------------------------------------------------------------------------------------
Cnclusão: a transferência tem de ser uma operação atómica.
O estado não pode ser alterado enquanto a transferência é feita.
Então, ao pôr um lock e unlock entre as duas operações (withdraw e deposit), a transferência
passa a ser atómica, e enquanto isso é feito, o ESTADO mantém-se.
Então, apesar de as operações individuais de withdraw ser mutuamente exclusivas, isso não
implica que as duas operações juntas o sejam.
ReentrantLock: uma chave abre todas as caixas que dependam dela.

Cenário: transfer(0,1,10) & Observação do Balanço Total ----------------------------------
Assumindo os mesmos valores de cima, a dado momento, quando a transferencia ocorre, o saldo
total apareceria como 20, quando apenas existiam 10 euros no banco. Daí ser preciso os locks
também.
------------------------------------------------------------------------------------------
*/

class Move implements Runnable {
    Bank b;

    public Move(Bank b, int s) {
        this.b = b;
    }

    public void run() {
        b.transfer(0, 1, 10);
    }
}

class Checker implements Runnable {
    Bank b;

    public Checker(Bank b, int s) {
        this.b = b;
    }

    public void run() {
        System.out.println("Bank balance #1: " + b.totalBalance());

        try{
            Thread.sleep(5000);
        } catch (InterruptedException e){
            e.printStackTrace();
        }
        System.out.println("Bank balance #2: " + b.totalBalance());

        try{
            Thread.sleep(10000);
        } catch (InterruptedException e){
            e.printStackTrace();
        }

        System.out.println("Bank balance #3: " + b.totalBalance());
    }
}
//Ex2:
/*
-----------------------------------------------
                     Lock                     |
-----------------------------------------------

Ex3:
-----------------------------------------------
  Lock  |   Lock    |     Lock   |    Lock    |
-----------------------------------------------
email: d8328@di...
 */