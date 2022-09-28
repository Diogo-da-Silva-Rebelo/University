package guiao5;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WarehouseCoop {
    //private Lock l = new ReentrantLock();
    private ReentrantLock l;
    private Map<String, Product> map = new HashMap<>();

    private class Product {
        private Condition waitForStock = l.newCondition();
        int quantity = 0;
    }

    //Não necessita de lock porque é um método privado e cada método que evoca o "get" está protegido.
    private Product get(String item) {
        Product p = map.get(item);
        if (p != null) return p;
        p = new Product();
        map.put(item, p);
        return p;
    }

    //abastecer um produto
    void supply(String item, int quantity) throws InterruptedException {
        this.l.lock();
        Product p = get(item);
        p.quantity += quantity;
        p.waitForStock.signalAll();
        this.l.unlock();
    }

    //não desconto o stock se não o conseguir descontar de uma só vez
    //consumir um produto
    //ver caso em que falta algum produto (quantity < 0)
    void consume(Set<String> items) throws InterruptedException {
        this.l.lock();
        boolean hasStock = false;
        while (!hasStock) {
            for (String s : items) {
                while (get(s).quantity < 1) {
                    get(s).waitForStock.await();
                    hasStock = true;
                }
            }

            for (String s : items) {
                get(s).quantity--;
            }

            this.l.unlock();
        }
    }
}
//1- verificar se há stock ou não
//1.2 - se tivermos -> descontamos o stock
//1.3 - se não tivermos -> esperamos
//2- Verficar
