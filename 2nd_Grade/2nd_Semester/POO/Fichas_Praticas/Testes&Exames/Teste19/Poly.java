package Teste19;

public class Poly{
    //variáveis de instância
    private double[] coef;
    private int grau;
    private int size;

    //dá o grau do polinomio
    public int graus(){
        int d = 0;
        for( int i = 0; i < this.coef.length; i++ )
            if( this.coef[i] != 0 ) d = i;

        return d;
    }

    //getters & setters
    //Não precisamos de copiar os elementos todos da lista porque são imutáveis
    public double[] getCoef(){
      return this.coef;
    }

    public int getSize(){
        return this.size;
    }

    public int getGrau(){
        return this.grau;
    }

    //não precisamos de copiar índice a índice, pois Double é imutável
    public void setCoef(double[] c){
       this.coef = c;
    }

     public void setGrau(int g){
        this.grau = g;
     }

    //construtor vazio
    public Poly(){
        this.coef = new double[1];
        this.grau = 0;
        this.size = 0;
    }

    //construtor de cópia
    public Poly(Poly p){
       this.coef = new double[p.getCoef().length];
       System.arraycopy(p.getCoef(), 0, this.coef, 0, p.getCoef().length);
       this.grau = p.graus();
       this.size = p.getSize();
    }

    //construtor parametrizado
    public Poly(int g, double[] c, int size){
        this.coef = new double[size];
        System.arraycopy(c,0,this.coef,0,this.coef.length);
        this.grau = g;
        this.size = g;
    }

    //cria polinómio com o tamanho fornecido
    public Poly(int size){
        this.coef = new double[size];
        this.grau = 0;
        this.size = size;
    }

    //método clone
    public Poly clone(){
        return new Poly(this);
    }

    //métodos de instância
    //adiciona um termo a uma lista
    public void addMonomio(double coef, int grau) {
        for (int i = 0; i < this.grau; i++) {
            if (this.grau == grau) {
                this.coef[i] += coef;
            }
        }
    }

    public double calcula(double x){
        double res = 0.0;
        for(int i=0; i < this.coef.length; i++){
            res += this.coef[i] * (Math.pow(x,i));
        }
        return res;
    }

    public Poly derivada(){
        Poly p = new Poly(this.grau-2);
        int k = 0;
        for(int i = 0; i <= this.grau; i++) {
            if (i > 0) {
                p.coef[k] = this.coef[i] * (i);
                p.grau++;
                k++;
            } else {
                k = 0;
            }
        }
        return p;
    }

    //métodos que podem ser implementados como treino
    //implementação de ToString
    //implementação de equals
}