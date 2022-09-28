public class SayHello implements Runnable {
    @Override
    public void run() {
        System.out.println("Say hello from a thread");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Example{
    public static void main(String[] args) throws InterruptedException{
           Thread t = new Thread(new SayHello());
           t.start();
        System.out.println("Say hello from main thread");
    }
}
