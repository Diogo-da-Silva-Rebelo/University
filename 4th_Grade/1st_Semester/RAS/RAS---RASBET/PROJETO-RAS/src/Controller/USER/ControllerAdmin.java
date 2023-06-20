package Controller.USER;

import DAO.USER.AdminDAO;
import Entidades.USER.Administrador;
import Entidades.USER.Jogo;

import java.util.List;


public class ControllerAdmin extends Controller {
    private final Administrador user;
    private final AdminDAO adminDAO;


    public ControllerAdmin(Administrador user, Controller controller) {
        super(controller);
        this.user = user;
        this.adminDAO = new AdminDAO(controller.getDb());
    }


    public void run() {
        int opcao = -1;
        while (opcao != 0) {
            this.view.adminMainMenu(this.user.getNomeutilizador());
            opcao = this.scanOption(0, 5);
            switch (opcao) {
                case 1: //consultar jogos
                    this.view.subheader("Jogos", this.user.getNomeutilizador());
                    String desporto = this.getDesporto();
                    if (desporto != null) {
                        List<Jogo> jogos = this.db.getJogos(desporto);
                        for (int i = 0; i < jogos.size(); i++) {
                            this.view.line((i + 1) + " - " + jogos.get(i).toString() + "\n");
                        }
                    }
                    break;

                case 2: //alterar estado de apostas
                    desporto = this.getDesporto();
                    if (desporto != null) {
                        List<Jogo> jogos = this.db.getJogos(desporto);
                        for (int i = 0; i < jogos.size(); i++) {
                            this.view.line((i + 1) + " - " + jogos.get(i).toString() + "\n");
                        }
                        this.view.line("Escolha um jogo");
                        int i = this.scanOption(1, jogos.size());

                        this.view.line("Deseja alterar para: \n 0 -> Vai Decorrer \n 1 -> Acabado \n  2 -> A correr \n 3 -> Suspenso \n ");
                        int estado = this.scanOption(0, 3);
                        this.adminDAO.alterarEstadoJogo(estado, jogos.get(i - 1));
                    }
                    break;

                case 3: //criar promocao
                    desporto = this.getDesporto();
                    if (desporto != null) {
                        List<Jogo> jogos = this.db.getJogos(desporto);
                        for (int i = 0; i < jogos.size(); i++) {
                            this.view.line((i + 1) + " - " + jogos.get(i).toString() + "\n");
                        }
                        this.view.line("Selecione o jogo: \n");
                        int i1 = this.scanOption(1, jogos.size());

                        this.view.line("Selecione a odd que deseja alterar: \n");
                        for (String odd : jogos.get(i1 - 1).getOdds().keySet()) {
                            this.view.line(odd);
                            this.view.line(jogos.get(i1 - 1).getOdds().get(odd).toString());

                        }
                        String key = this.scan.nextLine();

                        this.view.line("Altere a odd selecionada para a nova: ");
                        double oddalterada = this.scan.nextDouble();
                        this.scan.nextLine();


                        if (this.isPromocaoValida(oddalterada, jogos.get(i1 - 1).getOdds().get(key))) {
                            this.view.line("Deseja enviar notificação? (true/false)");
                            String notificacaobool = this.scan.nextLine();

                            if (notificacaobool.equalsIgnoreCase("s")) {
                                this.view.line("Para quem deseja enviar a notificação?");
                                String destinatarios = this.scan.nextLine();
                                this.view.line("Insira a notificação desejada: ");
                                String notificacao = this.scan.nextLine();

                                boolean check = this.adminDAO.criarPromo(oddalterada, jogos.get(i1 - 1).getId(), key);
                                if (check) {
                                    this.view.line("Promoção criada com sucesso");
                                    this.enviarNotificacoes(notificacao, destinatarios, this.user.getNomeutilizador());
                                }
                                else this.view.line("Erro ao criar promoção");
                            } else {
                                boolean check = this.adminDAO.criarPromo(oddalterada, jogos.get(i1 - 1).getId(), key);
                                if (check) this.view.line("Promoção criada com sucesso");
                                else this.view.line("Erro ao criar promoção");
                            }
                        } else {
                            this.view.line("Promoção inválida");
                        }
                    }
                    break;
                case 4: //enviar notificacoes
                    this.view.line("Para quem deseja enviar a notificação?");
                    String destinatarios = this.scan.nextLine();
                    if (destinatarios.equals("todos")) {
                        this.view.line("Insira a notificação desejada: ");
                        String notificacao = this.scan.nextLine();
                        this.enviarNotificacoes(notificacao, "todos", this.user.getNomeutilizador());
                        break;
                    }


                    this.view.line("Insira a notificação desejada: ");
                    String notificacao = this.scan.nextLine();
                    this.enviarNotificacoes(notificacao, destinatarios, this.user.getNomeutilizador());
                    break;

                case 0: //terminar sessão
                    this.db.logout(this.user.getNomeutilizador());
                    break;
                default:
                    this.view.line("Opção inválida!");
            }
        }
    }

    public boolean isPromocaoValida(double oddalterada, double odd) {
        return oddalterada > odd;
    }
}
