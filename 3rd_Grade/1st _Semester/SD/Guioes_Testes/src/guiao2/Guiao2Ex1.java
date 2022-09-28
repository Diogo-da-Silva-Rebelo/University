package guiao2;

public class Guiao2Ex1{
    public static void main(String[] args) throws InterruptedException {
        Bank b = new Bank(2);
        b.deposit(0,10);
        Thread t1 = new Thread(new Move(b,10));
        Thread t2 = new Thread(new Move(b,10));
        t1.start(); t2.start(); t1.join(); t2.join();
        System.out.println(b.totalBalance());
    }
}