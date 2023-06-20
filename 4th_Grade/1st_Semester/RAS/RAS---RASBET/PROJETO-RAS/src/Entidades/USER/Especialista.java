package Entidades.USER;

import java.util.Date;

public class Especialista extends Utilizador{

    public Especialista(String nome, String nomeutilizador, String email, String password, boolean isLogged, Date dataNascimento, String numeroidfical, String numeroidcivil) {
        super(nome, nomeutilizador, email, password, isLogged, dataNascimento, numeroidfical, numeroidcivil);
    }

}
