package Entidades.USER;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Boletim {
    private String id;
    private String idUser;
    private List<Prognostico> prognosticos;
    private EstadoBoletim estado;
    private Date data;
    private Double montante;
    private Double ganho;

    public Boletim() {
        this.id = "";
        this.idUser = "";
        this.prognosticos = new ArrayList<>();
        this.estado = EstadoBoletim.ABERTO;
        this.data = null;
        this.montante = 0.0;
        this.ganho = 0.0;
    }

    public Boletim(String id, String idUser, List<Prognostico> prognosticos, EstadoBoletim estado, Date data, Double montante, Double ganho) {
        this.id = id;
        this.idUser = idUser;
        this.prognosticos = prognosticos;
        this.estado = estado;
        this.data = data;
        this.montante = montante;
        this.ganho=ganho;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public List<Prognostico> getPrognosticos() {
        return prognosticos;
    }

    public void setPrognosticos(List<Prognostico> prognosticos) {
        this.prognosticos = prognosticos;
    }

    public EstadoBoletim getEstado() {
        return estado;
    }

    public void setEstado(EstadoBoletim estado) {
        this.estado = estado;
    }

    public Date getData() {
        return data;
    }

    public void setData(Date data) {
        this.data = data;
    }

    public Double getMontante() {
        return montante;
    }

    public void setMontante(Double montante) {
        this.montante = montante;
    }

    public Double getGanho() {
        return ganho;
    }

    public void setGanho(Double ganho) {
        this.ganho = ganho;
    }

    public String getIdUser() {
        return idUser;
    }

    public void setIdUser(String idUser) {
        this.idUser = idUser;
    }

    public String toString(){
        return "Boletim: " + this.id + " - " + this.estado + " - " + this.data + " - " + this.montante + " - " + this.ganho + "\n" + this.prognosticos;
    }
}
