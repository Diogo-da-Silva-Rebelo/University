package Entidades.USER;

import java.util.Date;

public class PedidoAjuda {
    private String id;
    private String texto;
    private String resposta;
    EstadoPedido estado;
    private Date data;
    private String idUtilizador;

    private String idTrabalhador;

    public PedidoAjuda(String id, String texto, String resposta, EstadoPedido estado, Date data, String idUtilizador,String idTrabalhador) {
        this.id = id;
        this.texto = texto;
        this.resposta = resposta;
        this.estado = estado;
        this.data = data;
        this.idUtilizador = idUtilizador;
        this.idTrabalhador = idTrabalhador;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getTexto() {
        return texto;
    }

    public void setTexto(String texto) {
        this.texto = texto;
    }

    public String getResposta() {
        return resposta;
    }

    public void setResposta(String resposta) {
        this.resposta = resposta;
    }

    public EstadoPedido getEstado() {
        return estado;
    }

    public void setEstado(EstadoPedido estado) {
        this.estado = estado;
    }

    public String getIdTrabalhador() {
        return idTrabalhador;
    }

    public void setIdTrabalhador(String idTrabalhador) {
        this.idTrabalhador = idTrabalhador;
    }

    public Date getData() {
        return data;
    }

    public void setData(Date data) {
        this.data = data;
    }

    public String getIdUtilizador() {
        return idUtilizador;
    }

    public void setIdUtilizador(String idUtilizador) {
        this.idUtilizador = idUtilizador;
    }

    @Override

    public String toString() {
        return "PedidoAjuda{" + "id=" + id + ", texto=" + texto + ", resposta=" + resposta + ", estado=" + estado + ", data=" + data + ", idUtilizador=" + idUtilizador + '}';
    }



}
