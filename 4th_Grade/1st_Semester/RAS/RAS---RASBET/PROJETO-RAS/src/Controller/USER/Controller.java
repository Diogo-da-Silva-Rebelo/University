package Controller.USER;

import DAO.USER.DAO;
import Entidades.USER.*;
import View.Menu;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class Controller {
    DAO db;
    Menu view;
    Scanner scan;
    CurrencyTime currencyTime;

    public Controller() {
        this.db = new DAO();
        this.view = new Menu();
        this.scan = new Scanner(System.in);
        this.currencyTime = new CurrencyTime();
    }

    public Controller(Controller c) {
        this.db = c.getDb();
        this.view = c.getView();
        this.scan = c.getScan();
        this.currencyTime = c.getCurrencyTime();
    }

    private CurrencyTime getCurrencyTime() {
        return currencyTime;
    }

    private Utilizador login() {

        this.view.line("Username: ");
        String username = this.scan.nextLine();
        this.view.line("Password: ");
        String password = this.scan.nextLine();
        Utilizador user = this.db.getUser(username, password);
        if (user != null) {
            this.db.login(username);
            this.view.line("Login efetuado com sucesso!");
            return user;


        } else {
            this.view.line("Login falhou!");
            return null;
        }
    }

    private Date stringToDate(String s) {
        try {
            return new SimpleDateFormat("dd/MM/yyyy").parse(s);
        } catch (ParseException e) {
            this.view.line("Data inválida!");
            return null;
        }
    }

    private void registar() {
        this.view.line("Nome: ");
        String nome = this.scan.nextLine();
        this.view.line("Username: ");
        String username = this.scan.nextLine();
        this.view.line("Email: ");
        String email = this.scan.nextLine();
        this.view.line("Password: ");
        String password = this.scan.nextLine();
        Date data = null;
        while (data == null) {
            this.view.line("Data de Nascimento (dd/MM/yyyy): ");
            String d = this.scan.nextLine();
            data = this.stringToDate(d);
        }
        this.view.line("Numero de Identificacao Fiscal: ");
        String nif = this.scan.nextLine();
        this.view.line("Numero de Identificacao Civil: ");
        String nic = this.scan.nextLine();

        if (this.db.registar(nome, username, email, password, new SimpleDateFormat("yyyy/MM/dd").format(data), nif, nic)) {
            this.view.line("Registo efetuado com sucesso!\n");
        } else {
            this.view.line("Erro ao registar!");
        }
    }

    public int scanOption(int min, int max) {
        int opt = -1;
        while (opt < min || opt > max) {
            try {
                opt = this.scan.nextInt();
                if (opt < min || opt > max) this.view.line("Opção inválida, tente novamente.");
            } catch (InputMismatchException e) {
                this.view.line("Opção inválida, tente novamente.\n");
                this.view.line("Opção: ");
            }
            this.scan.nextLine();
        }
        return opt;
    }


    public void run() {
        this.view.mainMenu();
        int opt = this.scanOption(0, 2);
        switch (opt) {
            case 1:
                this.registar();
                this.run();
                break;
            case 2:
                Utilizador user = this.login();
                if (user instanceof Apostador)
                    new ControllerApostador((Apostador) user, this).run();
                else if (user instanceof Tecnico)
                    new ControllerTecnico((Tecnico) user, this).run();
                else if (user instanceof Especialista)
                    new ControllerEspecialista((Especialista) user, this).run();
                else if (user instanceof Administrador)
                    new ControllerAdmin((Administrador) user, this).run();
                else this.run();
                break;
            case 0:
                break;
        }
    }

    public String getDesporto(){
        List<String> desportos = this.db.getDesportos();
        desportos.add("0 - Voltar");
        this.view.optionsMenu(desportos.toArray(new String[0]));

        this.view.line("Insira o id do desporto: ");
        int opcao = this.scan.nextInt();

        if (opcao == 0) return null;
        return desportos.get(opcao - 1).split(" - ")[1];
    }


    public List<String> getMenuJogos(List<Jogo> jogos) {

        ArrayList<String> jogosString = new ArrayList<>();

        for (Jogo j : jogos) {
            jogosString.add(j.getId() + " - " + j);
        }

        jogosString.add("0 - Voltar");
        return jogosString;
    }

    public Utilizador changeInfo(int opcao, Utilizador user) {
        switch (opcao) {
            case 1:
                this.view.line("Username atual: " + user.getNomeutilizador() + "\n");
                this.view.line("Insira o novo nome de utilizador: ");
                String nome = this.scan.next();
                if(this.db.updateUserID(nome, user.getNomeutilizador())){
                    user.setNomeutilizador(nome);
                    this.view.line("Username alterado com sucesso!");
                }
                else{
                    this.view.line("Erro ao alterar nome!");
                }
                break;
            case 2:
                this.view.line("Email atual: " + user.getEmail() + "\n");
                this.view.line("Insira o novo email: ");
                String email = this.scan.next();
                if(this.db.updateEmail(email, user.getNomeutilizador())){
                    user.setEmail(email);
                    this.view.line("Email alterado com sucesso!");
                }
                else{
                    this.view.line("Erro ao alterar email!");
                }
                break;
            case 3:
                this.view.line("Password atual: " + user.getPassword() + "\n");
                this.view.line("Insira a nova password: ");
                String password = this.scan.next();
                if(this.db.updatePassword(password, user.getNomeutilizador())){
                    user.setPassword(password);
                    this.view.line("Password alterada com sucesso!");
                }
                else
                    this.view.line("Erro ao alterar password!");
                break;
            default:
                return user;
        }
        return user;
    }

    public void enviarNotificacoes(String notificacao, String destinatario, String idTrabalhador) {
        if (this.db.enviarNotificacao(notificacao, idTrabalhador, destinatario))
            this.view.line("Notificação enviada com sucesso!");
        else
            this.view.line("Erro ao enviar notificação!");
    }

    public DAO getDb() {
        return db;
    }

    public Menu getView() {
        return view;
    }

    public Scanner getScan() {
        return scan;
    }
}