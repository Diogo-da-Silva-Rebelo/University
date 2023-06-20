package DAO.USER;

import Entidades.USER.Jogo;

import java.util.UUID;

public class AdminDAO extends DAO {

    public AdminDAO(DAO db) {
        super(db);
    }

    public boolean criarPromo(double oddalterada, String idjogo, String prognostico) {
        return this.update("INSERT INTO Promocao VALUES ('" + UUID.randomUUID() + "', '" + idjogo + "', '" + prognostico + "', " + oddalterada + ")");
    }

    public boolean alterarEstadoJogo(int estado, Jogo jogo) {
        return this.update("UPDATE Jogo SET estado = " + estado + " WHERE id = '" + jogo.getId() + "'");
    }






}


