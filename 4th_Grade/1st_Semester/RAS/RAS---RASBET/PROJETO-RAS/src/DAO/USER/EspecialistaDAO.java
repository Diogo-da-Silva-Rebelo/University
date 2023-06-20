package DAO.USER;

import Entidades.USER.EstadoJogo;
import Entidades.USER.Jogo;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

public class EspecialistaDAO extends DAO{

    public EspecialistaDAO(DAO dao) {
        super(dao);
    }

    public boolean atualizarOdd(float newOdd, String prognosticoString, String idJogo) {
        return this.update("UPDATE Odds SET valor=" + newOdd + " WHERE idJogo='" + idJogo + "' AND prognostico='" + prognosticoString + "';");
    }

    public List<Jogo> getJogosSemOdd(String desporto) {
        List<Jogo> jogos = new ArrayList<>();

        if (desporto.equals("")) return jogos;

        ResultSet rs = this.query("SELECT * FROM Jogo INNER JOIN Odds where Odds.idJogo=Jogo.id AND Odds.valor IS NULL AND Jogo.desporto='" + desporto + "';");

        try {
            while (rs.next())
                jogos.add(new Jogo(rs.getString("id"), EstadoJogo.values()[rs.getInt("estado")],
                        LocalDateTime.parse(rs.getString("data"), DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")), null, new LinkedHashMap<>()));

            for (Jogo j : jogos) {
                ResultSet odds = this.query("SELECT * FROM Odds WHERE idJogo = '" + j.getId() + "'");
                LinkedHashMap<String, Double> oddsMap = new LinkedHashMap<>();
                while (odds != null && odds.next()) {
                    oddsMap.put(odds.getString("prognostico"), odds.getDouble("valor"));
                }
                j.setOdds(oddsMap);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return jogos;
    }

    public boolean inserirOdd(String idJogo, String equipa, double odd) {
        return this.update("INSERT INTO Odds values('" + idJogo + "','" + equipa + "'," + odd + ");");
    }

    public LinkedHashMap<String, Double> getOdds(String idJogo) {
        ResultSet rs = this.query("SELECT prognostico, valor FROM Odds WHERE idJogo='" + idJogo + "'");
        LinkedHashMap<String, Double> result = new LinkedHashMap<>();
        try {
            while (rs.next())
                result.put(rs.getString("prognostico"), rs.getDouble("valor"));
        }
        catch (SQLException e) {
            System.err.println("Got an exception! ");
            System.err.println(e.getMessage());
        }
        return result;
    }
}
