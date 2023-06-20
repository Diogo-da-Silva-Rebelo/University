package DAO.USER;

import Entidades.USER.*;
import com.mysql.cj.jdbc.Blob;

import java.sql.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.UUID;

public class DAO {
    private Connection conn = null;

    public DAO() {
        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/projeto_ras", "ras", "ras");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public DAO(DAO dao) {
        this.conn = dao.getConn();
    }

    public Connection getConn() {
        return conn;
    }


    public boolean update(String query) {
        try {
            Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
            stmt.executeUpdate(query);
            return true;
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            return false;
        }
    }

    public ResultSet query(String s) {
        ResultSet rs = null;
        try {
            Statement statement = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
            rs = statement.executeQuery(s);
        } catch (Exception e) {
            System.err.println("Got an exception! ");
            System.err.println(e.getMessage());
        }
        return rs;
    }


    public boolean enviarNotificacao(String notificacao, String idTrabalhador, String idUser) {
        if (idUser.equalsIgnoreCase("todos")){
            return update("INSERT INTO Notificacao VALUES ('" + UUID.randomUUID() + "', "
                    + 1 + ", NULL, '" + notificacao + "', '" + idTrabalhador + "')");
        }
        return update("INSERT INTO Notificacao VALUES ('" + UUID.randomUUID() + "', "
                + 0 + ", '" + idUser + "', '" + notificacao + "', '" + idTrabalhador + "')");
    }

    public List<String> getDesportos() {
        ResultSet ans = this.query("SELECT desporto FROM Desporto");
        List<String> desportos = new ArrayList<>();

        try {
            for (int i = 1; ans.next(); i++) {
                desportos.add(i + " - " + ans.getString("desporto"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return desportos;
    }

    public Utilizador getUser(String username, String password) {
        ResultSet ans = this.query("SELECT * FROM User WHERE id = '" + username + "' AND password = '" + password + "'");
        try {
            if (ans.next()) {
                return switch (ans.getInt("tipo")) {
                    case 0 -> new Apostador(ans.getString("nome"),
                            ans.getString("id"), ans.getString("email"),
                            ans.getString("password"), true,
                            ans.getDate("dataNascimento"), ans.getString("idFiscal"),
                            ans.getString("idCivil"), ans.getDouble("saldo"));
                    case 1 -> new Tecnico(ans.getString("nome"), ans.getString("id"),
                            ans.getString("email"), ans.getString("password"),
                            ans.getBoolean("logado"), ans.getDate("dataNascimento"),
                            ans.getString("idFiscal"), ans.getString("idCivil"));
                    case 2 -> new Especialista(ans.getString("nome"), ans.getString("id"),
                            ans.getString("email"), ans.getString("password"),
                            ans.getBoolean("logado"), ans.getDate("dataNascimento"),
                            ans.getString("idFiscal"), ans.getString("idCivil"));
                    case 3 -> new Administrador(ans.getString("nome"), ans.getString("id"),
                            ans.getString("email"), ans.getString("password"),
                            ans.getBoolean("logado"), ans.getDate("dataNascimento"),
                            ans.getString("idFiscal"), ans.getString("idCivil"));
                    default -> null;
                };
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }



    public List<Promocao> getPromocoesAtivas() {
        ResultSet rs = this.query("SELECT * from Promocao INNER JOIN Jogo on Promocao.idJogo = Jogo.id WHERE Jogo.estado != 1;");
        List<Promocao> promocoes = new ArrayList<>();
        try {
            while (rs.next()) {
                promocoes.add(new Promocao(rs.getString("id"), rs.getString("idJogo"), rs.getDouble("oddMelhorada"), rs.getString("prognostico")));
            }
        } catch (Exception e) {
            System.err.println("Got an exception! ");
            System.err.println(e.getMessage());
        }
        return promocoes;
    }

    public boolean registar(String nome, String username, String email, String password, String dataNascimento, String nif, String nic) {
        try {
            PreparedStatement ps = this.conn.prepareStatement("INSERT INTO User VALUES(?,?,?,?,?,?,?,?,?,?)");
            ps.setString(1, username);
            ps.setString(2, password);
            ps.setString(3, email);
            ps.setString(4, nome);
            ps.setString(5, dataNascimento);
            ps.setBlob(6, new Blob(new byte[]{0}, null));
            ps.setString(7, nif);
            ps.setString(8, nic);
            ps.setInt(9, 0);
            ps.setDouble(10, 0.0);
            return ps.executeUpdate() == 1;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean updateUserID(String novo, String antigo) {
        return this.update("UPDATE User SET id = '" + novo + "' WHERE id = '" + antigo + "'");
    }

    public boolean updateEmail(String email, String nomeutilizador) {
        return this.update("UPDATE User SET email = '" + email + "' WHERE id = '" + nomeutilizador + "'");
    }

    public boolean updatePassword(String password, String nomeutilizador) {
        return this.update("UPDATE User SET password = '" + password + "' WHERE id = '" + nomeutilizador + "'");
    }

    public void logout(String nomeutilizador) {
        this.update("UPDATE User SET logado = 0 WHERE id = '" + nomeutilizador + "'");
    }

    public List<Jogo> getJogos(String desporto) {
        List<Promocao> promocoes = this.getPromocoesAtivas();
        List<Jogo> jogos = new ArrayList<>();

        ResultSet rs = this.query("SELECT * FROM Jogo WHERE desporto = '" + desporto + "'");

        try {
            while (rs.next()) {
                LinkedHashMap<String, Double> promJogo = new LinkedHashMap<>();
                int i = 0;
                while (i < promocoes.size()) {
                    if (promocoes.get(i).getIdJogo().equals(rs.getString("id"))) {
                        promJogo.put(promocoes.get(i).getPrognostico(), promocoes.get(i).getOddMelhorada());
                        promocoes.remove(i);
                    }
                    else i++;
                }

                jogos.add(new Jogo(rs.getString("id"), EstadoJogo.values()[rs.getInt("estado")],
                        LocalDateTime.parse(rs.getString("data"), DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")), null, promJogo));
            }

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

    public void login(String username) {
        this.update("UPDATE User SET logado = 1 WHERE id = '" + username + "'");
    }
}
