package Entidades.USER;

public class Prognostico {
    private String equipa;
    private double valorOdd;
    private boolean promocao;

    public Prognostico(String equipa, double valorOdd, boolean promocao) {
        this.equipa = equipa;
        this.valorOdd = valorOdd;
        this.promocao = promocao;
    }

    public String getEquipa() {
        return equipa;
    }

    public void setEquipa(String equipa) {
        this.equipa = equipa;
    }

    public double getValorOdd() {
        return valorOdd;
    }

    public void setValorOdd(double valorOdd) {
        this.valorOdd = valorOdd;
    }

    public boolean getPromocao() {
        return promocao;
    }

    public void setPromocao(boolean promocao) {
        this.promocao = promocao;
    }

    public String toString() {
        return "Prognostico{" + "equipa=" + equipa + ", valorOdd=" + valorOdd + ", promocao=" + promocao + '}';
    }

}
