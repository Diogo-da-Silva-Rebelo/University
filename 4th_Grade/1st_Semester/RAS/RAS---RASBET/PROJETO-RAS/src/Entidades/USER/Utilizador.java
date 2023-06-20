package Entidades.USER;

import java.sql.ResultSet;
import java.util.*;

public abstract class Utilizador {
    private String nome;
    private String nomeutilizador;
    private String email;
    private String password;
    private boolean isLogged;
    private Date dataNascimento;
    private String numeroidfiscal;
    private String numeroidcivil;


    public Utilizador(String nome, String nomeutilizador, String email, String password, boolean isLogged, Date dataNascimento, String numeroidfiscal, String numeroidcivil) {
        this.nome = nome;
        this.nomeutilizador = nomeutilizador;
        this.email = email;
        this.password = password;
        this.isLogged = isLogged;
        this.dataNascimento = dataNascimento;
        this.numeroidfiscal = numeroidfiscal;
        this.numeroidcivil = numeroidcivil;
    }

    public Utilizador(){
        this.nome = "";
        this.nomeutilizador = "";
        this.email = "";
        this.password = "";
        this.isLogged = false;
        this.dataNascimento = new Date();
        this.numeroidfiscal = "";
        this.numeroidcivil = "";
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNomeutilizador() {
        return nomeutilizador;
    }

    public void setNomeutilizador(String nomeutilizador) {
        this.nomeutilizador = nomeutilizador;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }



    public boolean isLogged() {
        return isLogged;
    }

    public void setLogged(boolean logged) {
        isLogged = logged;
    }

    public Date getDataNascimento() {
        return dataNascimento;
    }

    public void setDataNascimento(Date dataNascimento) {
        this.dataNascimento = dataNascimento;
    }

    public String getNumeroidfiscal() {
        return numeroidfiscal;
    }

    public void setNumeroidfical(String numeroidfical) {
        this.numeroidfiscal = numeroidfical;
    }

    public String getNumeroidcivil() {
        return numeroidcivil;
    }

    public void setNumeroidcivil(String numeroidcivil) {
        this.numeroidcivil = numeroidcivil;
    }


    public void login(){
        this.isLogged = true;
    }

    public void logout(){
        this.isLogged = false;
    }

    public String toString() {
        return "Apostador{" +
                "nome='" + nome + '\'' +
                ", nomeutilizador='" + nomeutilizador + '\'' +
                ", email='" + email + '\'' +
                ", password='" + password + '\'' +
                ", isLogged=" + isLogged +
                ", dataNascimento=" + dataNascimento +
                ", numeroidfical='" + numeroidfiscal + '\'' +
                ", numeroidcivil='" + numeroidcivil + '\'' +
                '}';
    }

    
}