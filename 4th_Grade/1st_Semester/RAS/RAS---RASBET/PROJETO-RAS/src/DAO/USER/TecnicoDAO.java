package DAO.USER;

import Entidades.USER.PedidoAjuda;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class TecnicoDAO extends DAO{
    public TecnicoDAO(DAO dao) {
        super(dao);
    }

    public List<PedidoAjuda> getPedidos(){
        ResultSet rs = this.query("SELECT * FROM PedidoAjuda WHERE userTecnico IS NULL");

        List<PedidoAjuda> pedidos = new ArrayList<>();
        try {
            while (rs.next()) {
                pedidos.add(new PedidoAjuda("0", rs.getString("texto"), rs.getString("resposta"),
                        null,rs.getDate("data"),  rs.getString("userApostador"),
                        rs.getString("userTecnico")));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return pedidos;

    }

    public boolean responderPedido(String resposta, PedidoAjuda pedido, String idTrabalhador) {
        return this.update("UPDATE PedidoAjuda SET resposta = '" + resposta + "' , userTecnico = '" + idTrabalhador +  "' WHERE data = '" + pedido.getData() + "'");
    }
}
