package Controller.USER;

import DAO.USER.ApostadorDAO;
import Entidades.USER.*;

import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class ControllerApostador extends Controller {
    private Apostador user;
    private final ApostadorDAO db;
    List<AbstractMap.SimpleEntry<Jogo, String>> boletim;


    public ControllerApostador(Apostador user, Controller controller) {
        this.user = user;
        this.view = controller.getView();
        this.scan = controller.getScan();
        this.db = new ApostadorDAO(controller.getDb());
        this.boletim = new ArrayList<>();
    }

    public void run() {
        int opcao = -1;
        while (opcao != 0) {
            this.view.apostadorMainMenu(this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency()); //mudar de acordo com região
            opcao = this.scanOption(0, 10);
            switch (opcao) {
                case 1 -> {
                    //Observa os jogos
                    this.view.subheader("Jogos", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    String desporto = this.getDesporto();
                    if (desporto != null) {
                        List<Jogo> jogos = this.db.getJogos(desporto);
                        for (int i = 0; i < jogos.size(); i++) {
                            this.view.line((i + 1) + " - " + jogos.get(i).toString() + "\n");
                        }

                        this.view.optionsMenu(new String[]{"1 - Seguir Jogo", "2 - Deixar de Seguir Jogo", "0 - Voltar"});
                        this.view.line("Insira a opção: ");
                        int opcao2 = this.scanOption(0, 2);
                        if (opcao2 == 1) {
                            this.view.line("Qual o jogo que deseja seguir? (0 para voltar): ");
                            int jogo = this.scanOption(0, jogos.size());
                            if (jogo!= 0) {
                                this.db.seguirJogo(this.user.getNomeutilizador(), jogos.get(jogo - 1).getId());
                                this.view.line("Jogo seguido com sucesso!");
                            }
                        }
                        else if (opcao2 == 2) {
                            this.view.line("Qual o jogo que deseja deixar de seguir? (0 para voltar): ");
                            jogos = this.db.getJogosSeguidos(this.user.getNomeutilizador());
                            for (int i = 0; i < jogos.size(); i++) {
                                this.view.line((i + 1) + " - " + jogos.get(i).toString() + "\n");
                            }
                            int jogo = this.scanOption(0, jogos.size());
                            if (jogo!= 0) {
                                this.db.deixarSeguirJogo(this.user.getNomeutilizador(), jogos.get(jogo - 1).getId());
                                this.view.line("Jogo deixado de seguir com sucesso!");
                            }
                        }
                    }
                }
                case 2 -> {
                    //altera informações do perfil
                    this.view.subheader("Alterar informações", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.view.optionsMenu(new String[]{"1 - Nome do Utilizador", "2 - Email", "3 - Password", "0 - Voltar"});
                    this.view.line("Insira a opção: ");
                    int alterar = this.scanOption(0, 3);
                    this.user = (Apostador) this.changeInfo(alterar, this.user);
                }
                case 3 -> {
                    //historico de transações
                    this.view.subheader("Histórico de transações", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.showTransacoes();
                }
                case 4 -> {
                    //historico de apostas
                    this.view.subheader("Histórico de apostas", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.showApostas();
                }
                case 5 -> {
                    //depositar dinheiro
                    this.view.subheader("Depositar dinheiro", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.movimento(TipoMovimento.DEPOSITO);
                }
                case 6 -> {
                    //fazer aposta
                    this.view.subheader("Apostas", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.apostar();
                }
                case 7 -> {
                    //levantar dinheiro
                    this.view.subheader("Levantar dinheiro", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.movimento(TipoMovimento.LEVANTAMENTO);
                }
                case 8 -> {
                    //consultar promoções
                    this.view.subheader("Promoções", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.promocoes();
                }
                case 9 -> {
                    //consultar notificações
                    this.view.subheader("Notificações", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.notificacoes();
                }
                case 10 -> {
                    this.view.subheader("Pedir ajuda", this.user.getNomeutilizador() + " - " + this.user.getSaldo() + this.currencyTime.getCurrency());
                    this.pedirAjuda();
                }
                case 0 -> this.db.logout(this.user.getNomeutilizador());
                default -> this.view.line("Opção inválida!");
            }
        }
    }

    private void notificacoes() {
        List<Notificacao> notificacoes = this.db.getNotificacoes(this.user.getNomeutilizador());

        for (Notificacao n : notificacoes) {
            this.view.line(n.toString());
        }
    }

    private void pedirAjuda() {
        this.view.line("Insira o seu pedido de ajuda:");
        String pedido = this.scan.nextLine();
        if (this.db.pedirAjuda(this.user.getNomeutilizador(), pedido))
            this.view.line("Pedido de ajuda enviado com sucesso!");
        else this.view.line("Erro ao enviar pedido de ajuda.");
    }

    private void promocoes() {
        List<Promocao> promocoes = this.db.getPromocoesAtivas();
        this.view.line("Promoções ativas:");
        for (Promocao p : promocoes) {
            this.view.line(p.toString());
        }
    }

    private void movimento(TipoMovimento tipo) {
        this.view.line("Insira o valor a depositar:");
        double valor = this.scan.nextDouble();
        if (tipo == TipoMovimento.DEPOSITO)
            this.user.setSaldo(this.user.getSaldo() + valor);
        else
            try {
                this.user.setSaldo(this.user.getSaldo() - valor);
            } catch (Exception e) {
                this.view.line("Saldo insuficiente!");
                return;
            }

        this.db.movimento(this.user.getNomeutilizador(), tipo, this.user.getSaldo(), valor);
        this.view.line(tipo + " efetuado com sucesso!");
    }

    private void showApostas() {
        List<Boletim> boletins = this.db.getBoletins(this.user.getNomeutilizador());
        for (Boletim b : boletins) {
            this.view.line(b.toString());
        }
    }

    private void showTransacoes() {
        List<Transacao> transacoes = this.db.getTransacoes(this.user.getNomeutilizador());
        this.view.line("Tipo\tData\tValor");
        for (Transacao t : transacoes) {
            this.view.line(t.getTipo() + "\t" + t.getData() + "\t" + t.getValor());
        }
    }


    private void apostar() {
        while (true) {
            String desporto = this.getDesporto();
            if (desporto == null) return;

            if (this.boletim.size() > 0) {
                this.view.optionsMenu(new String[]{"1 - Continuar", "2 - Limpar boletim", "0 - Voltar"});
                int opcao = this.scanOption(0, 2);
                if (opcao == 2) {
                    this.boletim.clear();
                } else if (opcao == 0) {
                    return;
                }
            }

            List<Jogo> jogos = this.db.getJogos(desporto);

            if (jogos.size() == 0) {
                this.view.line("Não existem jogos disponíveis para apostar!\n");
                return;
            }

            while (true) {
                this.view.line("Escolha o jogo que pretende apostar:");
                for (int i = 0; i < jogos.size(); i++) {
                    this.view.line((i + 1) + " - " + jogos.get(i).toString() + "\n");
                }
                this.view.line("0 - Voltar");
                int opcao = this.scanOption(0, jogos.size());
                if (opcao == 0) break;
                else {
                    Jogo jogo = jogos.get(opcao - 1);
                    this.view.line("Qual a aposta? 0 para voltar");
                    String prognostico = this.scan.nextLine();
                    if (prognostico.equals("0")) break;
                    else if(boletim.size() == 20) {
                        this.view.line("Não pode apostar em mais de 20 jogos!");
                        break;
                    }
                    else if ((jogo.getEstado() == EstadoJogo.ABERTO || jogo.getEstado() == EstadoJogo.ACORRER)
                            && jogo.getOdds().get(prognostico) != null &&
                            this.boletim.stream().findAny().filter(b -> Objects.equals(b.getKey().getId(), jogo.getId())).orElse(null) == null) {
                        this.boletim.add(new AbstractMap.SimpleEntry<>(jogo, prognostico));
                        this.view.line("Prognostico adicionado com sucesso!");
                    }
                    else this.view.line("Prognóstico inválido/jogo suspenso/jogo já inserido!");

                    this.view.line("Escolha a opção 1 - Apostar, 2 - Continuar a ver jogos, 0 - Voltar");
                    int opcao2 = this.scanOption(0, 2);
                    if (opcao2 == 1 && this.boletim.size() > 0) {
                        double mult = 1.0;
                        for (AbstractMap.Entry<Jogo, String> b : this.boletim) {
                            this.view.line(b.getKey().toString());
                            this.view.line("Prognóstico: " + b.getValue());
                            if (b.getKey().getPromocoes().get(b.getValue()) != null) {
                                this.view.line("Promoção: " + b.getKey().getPromocoes().get(b.getValue()));
                                mult *= b.getKey().getPromocoes().get(b.getValue());
                            }
                            else {
                                mult *= b.getKey().getOdds().get(b.getValue());
                                this.view.line("Odd: " + b.getKey().getOdds().get(b.getValue()) + "\n");
                            }
                        }
                        this.view.line("Multiplicador: " + mult + "\n");
                        this.insereMontante();
                        return;
                    }
                    else if (opcao2 == 0) {
                        return;
                    }
                }
            }
        }
    }

    private void insereMontante() {
        this.view.line("Insira o montante a apostar:");
        double montante = this.scan.nextDouble();
        if (montante > this.user.getSaldo()) {
            this.view.line("Saldo insuficiente!");
            return;
        }
        this.db.insereBoletim(this.user.getNomeutilizador(), montante, this.boletim);
        for (AbstractMap.Entry<Jogo, String> b : this.boletim) {
            this.db.seguirJogo(this.user.getNomeutilizador(), b.getKey().getId());
        }
        this.user.setSaldo(this.user.getSaldo() - montante);
        this.view.line("Boletim inserido com sucesso!");
        this.boletim.clear();
    }
}