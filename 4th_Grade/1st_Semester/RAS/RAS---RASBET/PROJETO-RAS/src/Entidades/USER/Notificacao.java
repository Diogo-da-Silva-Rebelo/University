package Entidades.USER;

public class Notificacao {
    private String id;
    private String idTrabalhador;
    private String texto;
    private boolean geral;
    private boolean lida;

    public Notificacao(String id, String texto) {
        this.id = id;
        this.idTrabalhador = "Sistema";
        this.texto = texto;
        this.geral = false;
        this.lida = false;
    }

    public Notificacao(String id, String idTrabalhador, String texto, boolean geral, boolean lida){
        this.id = id;
        this.idTrabalhador = idTrabalhador==null? "Sistema":idTrabalhador;
        this.texto = texto;
        this.geral = geral;
        this.lida = lida;
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

    @Override

    public String toString() {
        return "Notificacao{" + "id=" + id + ", texto=" + texto + '}';
    }
}
