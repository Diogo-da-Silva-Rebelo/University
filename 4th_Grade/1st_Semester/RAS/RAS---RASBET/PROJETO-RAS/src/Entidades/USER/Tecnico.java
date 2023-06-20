package Entidades.USER;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;


public class Tecnico extends Utilizador{
    public Tecnico(String nome, String nomeutilizador, String email, String password, boolean isLogged, Date dataNascimento, String numeroidfical, String numeroidcivil) {
        super(nome, nomeutilizador, email, password, isLogged, dataNascimento, numeroidfical, numeroidcivil);
    }
}