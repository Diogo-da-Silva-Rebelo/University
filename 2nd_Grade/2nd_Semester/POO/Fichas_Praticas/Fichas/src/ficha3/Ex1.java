package ficha3;

public class Ex1 {
    private double x;
    private double y;
    private double raio;

    public Ex1(){
        this.x = this.y = this.raio = 0;
    }

    public Ex1(double x, double y, double raio){
        this.x = x;
        this.y = y;
        this.raio = raio;
    }

    public Ex1(Ex1 obj){
        this.x = obj.getX();
        this.y = obj.getY();
        this.raio = obj.getRaio();
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getRaio() {
        return raio;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public void setRaio(double raio) {
        this.raio = raio;
    }

    public void alteraCentro(double x, double y) {
        this.x = x;
        this.setY(y);
    }

    public double calculaArea() {
        return Math.PI * Math.pow(this.raio, 2);
    }

    public double calculaPerimetro() {
        return Math.PI * 2 * this.raio;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) {
            return false;
        }

        Ex1 p = (Ex1) o;
        return (this.x == p.getX()
                && this.y == p.getY()
                && this.raio == p.getRaio());
    }

    public Ex1 clone(){
        return new Ex1(this);
    }

    @Override
    public String toString() {
        return "Ex1{" +
                "x=" + x +
                ", y=" + y +
                ", raio=" + raio +
                '}';
    }
}
