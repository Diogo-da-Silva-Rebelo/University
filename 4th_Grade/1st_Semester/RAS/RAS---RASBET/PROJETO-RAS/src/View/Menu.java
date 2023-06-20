package View;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.LinkedHashMap;
import java.util.List;

public class Menu implements Serializable {

    public void optionsMenu(String[] options) {
        /*StringBuilder sb = new StringBuilder("|");
        int length = 0;
        for (String str : options) length += str.length();
        int spaces = (200 - length) / (options.length + 1);
        StringBuilder space = new StringBuilder();
        space.append(" ".repeat(Math.max(0, spaces)));
        for (String option : options) sb.append(space).append(option);
        sb.append(space).append(" ".repeat(((200 - length) % ((options.length) + 1)))).append("|\n|").append("*".repeat(200)).append("|");
        System.out.println(sb);*/
        StringBuilder sb = new StringBuilder("");
        for(String option : options) sb.append(">> ").append(option).append("\n");
        System.out.println(sb);
    }


    //header de cada menu de entidades
    public void subheader(String menu, String username) {
        System.out.print("\n\n|");
        System.out.print("*".repeat(200));
        System.out.print("|\n");
        System.out.print("|");
        int length = 200 - (username).length() - menu.length();
        String repeat = " ".repeat(Math.max(0, length / 3));
        System.out.print(repeat);
        System.out.print(username);
        System.out.print(repeat);
        System.out.print(menu);
        System.out.print(repeat);
        System.out.print(" ".repeat(Math.max(0, length % 3)));
        System.out.print("|\n");
        System.out.println("|" + "*".repeat(200) + "|");
    }

    public void whiteline(int lines) {
        for (int i = 0; i < lines; i++)
            System.out.print("\n");
    }

    public void line(String ask) {
        System.out.print("|-> " + ask);
    }

    public void genericMenu(String generic) {
        System.out.println(generic);
    }

    public void mainMenu() {
        subheader("Bem-vindo ao RASBET!","Utilizador não logado");
        optionsMenu(new String[]{"1 - Registar", "2 - Iniciar Sessão", "0 - Sair"});
        line("Pretende: ");
    }

    public void TecnicoMainMenu(String username) {
        subheader("View.Menu principal", username);
        optionsMenu(new String[]{"1 - Consultar Jogos",
                "2 - Responder a pedidos",
                "0 - Terminar Sessão"});
        line("Pretende: ");
    }

    public void especialistaMainMenu(String username) {
        subheader("Menu principal", username);
        optionsMenu(new String[]{"1 - Consultar Jogos",
                "2 - Inserir Odd",
                "3 - Atualizar Odd",
                "0 - Terminar Sessão"});
        line("Pretende: ");
    }

    public void apostadorMainMenu(String username) {
        subheader("View.Menu principal", username);
        optionsMenu(new String[]{"1 - Consultar Jogos",
                "2 - Alterar Informações de Perfil",
                "3 - Consultar Histórico de Transações",
                "4 - Consultar Histórico de Apostas",
                "5 - Depositar Dinheiro",
                "6 - Fazer Aposta",
                "7 - Levantar Dinheiro",
                "8 - Consultar Promoções",
                "9 - Consultar Notificações",
                "10 - Fazer Pedidos de Ajuda",
                "0 - Terminar Sessão"});
        line("Pretende: ");
    }

    public void adminMainMenu(String username) {
        subheader("View.Menu principal", username);
        optionsMenu(new String[]{"1 - Consultar Jogos",
                "2 - Alterar Estado da Aposta",
                "3 - Criar Promoções",
                "4 - Enviar notificações",
                "0 - Terminar Sessão"});
        line("Pretende: ");
    }
}