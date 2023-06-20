package Entidades.USER;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.LinkedHashMap;

public class Jogo{
    private final String id;
    private EstadoJogo estado;
    private LocalDateTime data;
    private LinkedHashMap<String, Double> odds;
    private LinkedHashMap<String, Double> promocoes;

    public Jogo(String id, EstadoJogo estado, LocalDateTime data, LinkedHashMap<String, Double> odds, LinkedHashMap<String, Double> promocoes) {
        this.id = id;
        this.estado = estado;
        this.data = data;
        this.odds = odds;
        this.promocoes = promocoes;
    }

    public String getId() {
        return id;
    }

    public LinkedHashMap<String, Double> getOdds() {
        return odds;
    }

    public EstadoJogo getEstado() {
        return estado;
    }

    public void setOdds(LinkedHashMap<String, Double> odds) {
        this.odds = odds;
    }

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    public LocalDateTime getData() {
        return data;
    }

    public LinkedHashMap<String, Double> getPromocoes() {
        return promocoes;
    }

    public String toString(){
        //TODO: Mudar para o formato correto da data e das odds de acordo com a moeda
        DateTimeFormatter df = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");

        return "(" + this.estado + ") - Data: " + this.data.format(df) + "----- Odds: " + this.odds + "----- Promocoes: " + this.promocoes;
    }
}
