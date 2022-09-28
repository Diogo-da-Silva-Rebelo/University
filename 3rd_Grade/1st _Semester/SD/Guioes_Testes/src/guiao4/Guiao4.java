package guiao4;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Guiao4 {
    class Barrier {
        private ReentrantLock lock;
        private final Condition waitForLastThread;
        private final int N;
        private int round;
        private int current;

        Barrier (int N) {
            this.N = N;
            this.current = 0;
            this.lock = new ReentrantLock();
            this.waitForLastThread = this.lock.newCondition();

        }

        void await() throws InterruptedException {
            this.lock.lock();
            this.current++;
            int myRound = this.round;

            //verificar se é a última thread.
            if(this.current < this.N ) {
                System.out.println(Thread.currentThread().getName() + " is waiting ...");
                while (myRound == this.round) {
                    this.waitForLastThread.await();
                }
            }
            else {
                System.out.println(Thread.currentThread().getName() + " is waking up others ...");
                this.waitForLastThread.signalAll();
                this.round++;
                this.current = 0;
            }

            System.out.println(Thread.currentThread().getName() + " is leaving ...");
            this.lock.unlock();

                //se for:
                    //sinaliza todas
                //se não for:
                    // aguarda pela última thread

        }

    }
}
