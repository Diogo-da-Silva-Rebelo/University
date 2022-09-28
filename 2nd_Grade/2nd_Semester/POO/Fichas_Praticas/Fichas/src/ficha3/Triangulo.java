package ficha3;

public class Triangulo {
    private Ponto a;
    private Ponto b;
    private Ponto c;

    public Triangulo() {
        this.a = new Ponto();
        this.b = new Ponto();
        this.c = new Ponto();
    }

    public Triangulo(Ponto a, Ponto b, Ponto c) {
        this.a = a.clone();
        this.b = b.clone();
        this.c = c.clone();
    }

    public Triangulo(Triangulo triangulo) {
        this.a = triangulo.getA().clone();
        this.b = triangulo.getB().clone();
        this.c = triangulo.getC().clone();
    }

    public Ponto getA() {
        return this.a;
    }

    public void setA(Ponto a) {
        this.a = a.clone();
    }

    public Ponto getB() {
        return this.b;
    }

    public void setB(Ponto b) {
        this.b = b.clone();
    }

    public Ponto getC() {
        return this.c;
    }

    public void setC(Ponto c) {
        this.c = c.clone();
    }

    public double dist(Ponto p1, Ponto p2) {
        double dx = Math.abs(p1.getX() - p2.getX());
        double dy = Math.abs(p1.getY() - p2.getY());
        return Math.sqrt(Math.pow(dx,2) + Math.pow(dy,2));
    }

    public double[] getSides() {
        double[] sides = {dist(this.a,this.b),dist(this.b,this.c),dist(this.a,this.c)};
        return sides;
    }

    public double calculaAreaTriangulo() {
        double[] sides = getSides();
        double s = (sides[0] + sides[1] + sides[2]) / 2;
        return Math.sqrt(s * (s - sides[0]) * (s - sides[1]) * (s - sides[2]));
    }

    public double calculaPerimetroTriangulo() {
        double[] sides = getSides();
        return sides[0] + sides[1] + sides[2];
    }

    public double calculaAltura() {
        double minY = Double.POSITIVE_INFINITY;
        double maxY = Double.NEGATIVE_INFINITY;
        double[] ys = {this.a.getY(), this.b.getY(), this.c.getY()};
        for(double y : ys) {
            if(y < minY) minY = y;
            if(y > maxY) maxY = y;
        }
        return maxY - minY;
    }

    public String toString() {
        final StringBuffer sb = new StringBuffer("Triangulo {");
        sb.append("\na=").append(a.toString());
        sb.append("\nb=").append(b.toString());
        sb.append("\nc=").append(c.toString());
        sb.append("\n}");
        return sb.toString();
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || o.getClass() != this.getClass()) return false;
        Triangulo triangulo = (Triangulo) o;
        return this.a.equals(triangulo.a) &&
                this.b.equals(triangulo.b) &&
                this.c.equals(triangulo.c);
    }

    public Triangulo clone() {
        return new Triangulo(this);
    }
}
