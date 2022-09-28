package ficha3;
import java.util.ArrayList;
import java.util.List;

public class Ex9 {
    private List<Triangulo> triangulos;

    public Ex9(){
        triangulos = new ArrayList<>();
    }

    public void AddTriangle(Triangulo  t){
        this.triangulos.add(t.clone());
    }

    public Triangulo findTriangle(Triangulo t){
        for (Triangulo triang : triangulos){
            if (triang.equals(t)) return triang.clone();
        }
        return null;
    }

    public Triangulo findTriangle2(Triangulo t){
        if (this.triangulos.contains(t)){
            int i = triangulos.indexOf(t);
            return triangulos.get(i).clone();
        }
        return null;
    }

    public Triangulo biggerArea(){
        double maxA = Double.MIN_VALUE;
        Triangulo t = null;
        for (Triangulo triang : triangulos){
            if (triang.calculaAreaTriangulo() > maxA){
                maxA = triang.calculaAreaTriangulo();
                t = triang;
            }
            if(t!=null) t = t.clone();
        }
        return t;
    }
}