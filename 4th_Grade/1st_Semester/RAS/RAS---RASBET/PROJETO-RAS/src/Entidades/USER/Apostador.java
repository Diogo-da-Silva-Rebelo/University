package Entidades.USER;

import java.util.Date;

public class Apostador extends Utilizador{
    private double saldo;

    public Apostador(String nome, String nomeutilizador, String email, String password, boolean isLogged, Date dataNascimento, String numeroidfical, String numeroidcivil, double saldo) {
        super(nome, nomeutilizador, email, password, isLogged, dataNascimento, numeroidfical, numeroidcivil);
        this.saldo = saldo;
    }

    public double getSaldo() {
        return saldo;
    }

    public void setSaldo(double saldo) {
        if (saldo < 0)
            throw new IllegalArgumentException("Saldo não pode ser negativo");
        this.saldo = saldo;
    }

}