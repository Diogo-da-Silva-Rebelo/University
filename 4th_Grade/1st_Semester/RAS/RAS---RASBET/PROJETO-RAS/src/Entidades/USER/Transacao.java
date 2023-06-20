package Entidades.USER;

import java.util.Date;

public class Transacao {
    Date data;
    String idUtilizador;
    Double valor;
    TipoMovimento tipoMovimento;

    public Transacao(Date data, String idUtilizador, Double valor, int tipo) {
        this.data = data;
        this.idUtilizador = idUtilizador;
        this.valor = valor;
        this.tipoMovimento = TipoMovimento.values()[tipo];
    }

    public Date getData() {
        return data;
    }

    public Double getValor() {
        return valor;
    }

    public TipoMovimento getTipo() {
        return tipoMovimento;
    }

    public String toString() {
        return data + " | Tipo: " + tipoMovimento + " | Valor: " + valor;
    }
}
