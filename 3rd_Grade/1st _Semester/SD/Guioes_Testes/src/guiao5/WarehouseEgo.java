package guiao5;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WarehouseEgo {
    //private Lock l = new ReentrantLock();
    private ReentrantLock l;
    private Map<String, Product> map = new HashMap<>();
    private Condition waitForStock = l.newCondition();

    private class Product {
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
        waitForStock.signalAll();
        this.l.unlock();
    }

    //consumir um produto
    //ver caso em que falta algum produto (quantity < 0)
    void consume(Set<String> items) throws InterruptedException {
        this.l.lock();
        for (String s : items) {
            while (get(s).quantity < 1) {
                waitForStock.await();
            }
            get(s).quantity--;
        }
        this.l.unlock();
    }
}
