package Teste19;

import java.util.ArrayList;
import java.util.List;

public class PolyAsList extends Poly {
    private List<Double> p;

    public PolyAsList(Poly a){
        List<Double> x = new ArrayList<>();
        for(int i = 0; i <= a.getGrau(); i++)
            x.add(a.getCoef()[i]);
        this.p = x;
    }
}
