package Controller.API;

import DAO.API.DAOAPI;
import Entidades.API.Jogo;
import Entidades.USER.Boletim;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.sql.SQLException;
import java.util.AbstractMap;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class ControllerAPI {
    private static HttpURLConnection connection;
    private final DAOAPI dao;

    public ControllerAPI() {
        dao = new DAOAPI();
    }

    private static List<Jogo> StringtoJson(String json) throws JsonProcessingException, SQLException {
        ObjectMapper objectMapper = new ObjectMapper();
        List<Jogo> listJogos = objectMapper.readValue(json, new TypeReference<>() {
        });

        for (Jogo j : listJogos) {
            System.out.println(j.toString());
        }
        return listJogos;
    }

    public void run() {
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                StringBuilder responseContent = new StringBuilder();
                try {
                    BufferedReader reader;
                    String line;

                    URL url = new URL("http://ucras.di.uminho.pt/v1/games/");
                    connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("GET");
                    connection.setConnectTimeout(500000);
                    connection.setReadTimeout(500000);

                    int status = connection.getResponseCode();

                    if (status > 299) {
                        reader = new BufferedReader(new InputStreamReader(connection.getErrorStream()));
                    } else {
                        reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                    }
                    while ((line = reader.readLine()) != null) {
                        responseContent.append(line);
                    }
                    reader.close();


                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    connection.disconnect();
                }

                try {
                    List<Jogo> jogos = StringtoJson(responseContent.toString());
                    System.out.println(jogos);
                    AbstractMap.SimpleEntry<List<Jogo>,List<Jogo>> jAlterados = dao.updateJogos(jogos);
                    List<Boletim> vencedores = dao.updateApostas(jAlterados.getKey());
                    dao.Notifica(jAlterados.getValue());
                    dao.updateUsers(vencedores);
                } catch (JsonProcessingException | SQLException e) {
                    throw new RuntimeException(e);
                }
            }
        };

        Timer timer = new Timer("Timer");

        long delay = 120000L;

        timer.scheduleAtFixedRate(task, 0, delay);
    }
}
