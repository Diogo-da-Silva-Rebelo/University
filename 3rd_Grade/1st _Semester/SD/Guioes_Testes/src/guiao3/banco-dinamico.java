package guiao3;

import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

class Bank {
    private ReentrantReadWriteLock lock = new ReentrantReadWriteLock();
    private Lock readLock = lock.readLock();
    private Lock writeLock = lock.writeLock();

    private static class Account {
        private ReentrantLock lock = new ReentrantLock();
        private int balance;
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        boolean deposit(int value) {
            balance += value;
            return true;
        }
        boolean withdraw(int value) {
            if (value > balance)
                return false;
            balance -= value;
            return true;
        }
    }

    private Map<Integer, Account> map = new HashMap<>();
    private int nextId = 0;

    // create account and return account id
    public int createAccount(int balance) {
        Account c = new Account(balance);

        writeLock.lock();
        int id = nextId;
        nextId += 1;
        map.put(id, c);
        writeLock.unlock();

        return id;
    }

    // close account and return balance, or 0 if no such account
    public int closeAccount(int id) {
        writeLock.lock();
        Account c = map.remove(id);

        if (c == null) {
            writeLock.unlock();
            return 0;
        }

        c.lock.unlock();
        writeLock.unlock();

        int balance = c.balance();
        c.lock.unlock();

        return balance;
    }

    // account balance; 0 if no such account
    //completar com locks
    public int balance(int id) {
        readLock.lock();
        Account c = map.get(id);
        if (c == null) {
            readLock.lock();
            return 0;
        }
        readLock.unlock();
        return c.balance();
    }

    // deposit; fails if no such account
    //A conta fica bloqueada enquanto se faz o depósito
    public boolean deposit(int id, int value) {
        readLock.lock();
        Account c = map.get(id);


        if (c == null) {
            readLock.unlock();
            return false;
        }

        c.lock.lock();
        readLock.unlock();

        boolean result = c.deposit(value);
        c.lock.unlock();

        return result;
    }

    // withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        Account c = map.get(id);
        if (c == null)
            return false;
        return c.withdraw(value);
    }

    // transfer value between accounts;
    // fails if either account does not exist or insufficient balance
    public boolean transfer(int from, int to, int value) {
        Account cfrom, cto;

        readLock.lock();
        cfrom = map.get(from);
        cto = map.get(to);
        if (cfrom == null || cto ==  null) {
            readLock.unlock();
            return false;
        }

        cfrom.lock.lock();
        cto.lock.lock();
        readLock.unlock();

        try {
            return cfrom.withdraw(value) && cto.deposit(value);
        } finally {
            cfrom.lock.unlock();
            cto.lock.unlock();
        }
    }

    // sum of balances in set of accounts; 0 if some does not exist
    //garantir que as contas não estão a ser usadas
    public int totalBalance(int[] ids) {
        int total = 0;

        readLock.lock();
        for (int i : ids) {
            Account c = map.get(i);
            if (c == null)
                return 0;
            c.lock.lock();
            total += c.balance();
            c.lock.unlock();
        }

        readLock.unlock();
        return total;
    }
}