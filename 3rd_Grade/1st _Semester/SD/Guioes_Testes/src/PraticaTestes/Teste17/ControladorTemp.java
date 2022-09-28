package PraticaTestes.Teste17;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class ControladorTemp implements Controlador{
    private int temp;
    private int limiar;
    private boolean estadoCaldeira;
    private ReentrantLock lock;
    private Condition inalterado;

    //Construtor
    public ControladorTemp (int temp, int limiar, boolean e){
        this.temp = temp;
        this.limiar = limiar;
        this.estadoCaldeira = e;
        this.lock = new ReentrantLock();
        this.inalterado = lock.newCondition();
    }

    @Override
    public void temperatura(int centigrados) {
        this.lock.lock();
        this.temp = centigrados;
        if (this.temp >= this.limiar) this.estadoCaldeira = false;
        else this.estadoCaldeira = true;
        this.inalterado.signalAll();

        this.lock.unlock();
    }

    @Override
    public void limiar(int centigrados) {
        this.lock.lock();
        this.limiar = centigrados;
        if (this.temp >= this.limiar) this.estadoCaldeira = false;
        else this.estadoCaldeira = true;
        this.inalterado.signalAll();
        this.lock.unlock();
    }

    @Override
    public boolean on_off(boolean estadoatual) throws InterruptedException {
        try {
            this.lock.lock();
            while(this.estadoCaldeira == estadoatual)
                inalterado.await();
            return this.estadoCaldeira;
        } finally {
            this.lock.unlock();
        }
    }
}