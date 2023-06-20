package Controller.USER;

import DAO.USER.TecnicoDAO;
import Entidades.USER.Jogo;
import Entidades.USER.PedidoAjuda;
import Entidades.USER.Tecnico;

import java.util.*;

public class ControllerTecnico extends Controller {
    private final Tecnico user;
    private final TecnicoDAO db;
    public ControllerTecnico(Tecnico user, Controller controller) {
        this.user = user;
        this.view = controller.getView();
        this.scan = controller.getScan();
        this.db = new TecnicoDAO(controller.getDb());
    }

    public void run() {
        int opcao = -1;
        while (opcao != 0) {
            this.view.TecnicoMainMenu(this.user.getNomeutilizador());
            opcao = this.scanOption(0,3);
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
                case 2: //responder a pedidos
                    List<PedidoAjuda> pedidos = this.db.getPedidos();
                    for (int i = 0; i < pedidos.size(); i++) {
                        this.view.line((i+1) + " - " + pedidos.get(i).getTexto());
                    }
                    this.view.line("Escolha um pedido" );
                    int i = this.scanOption(1, pedidos.size());
                    this.view.line("Escreva a resposta ao pedido:");
                    String resposta = this.scan.nextLine();

                    if (this.db.responderPedido(resposta, pedidos.get(i-1),this.user.getNomeutilizador())) {
                        String notificacao = "O seu pedido de ajuda foi respondido com sucesso, aceda ao mesmo através da sua area de notificações";
                        String destinatarios = pedidos.get(i-1).getIdUtilizador();
                        this.enviarNotificacoes(notificacao,destinatarios,this.user.getNomeutilizador());
                    } else {
                        this.view.line("Erro ao responder pedido!");
                    }
                    break;
                case 0:
                    this.db.logout(this.user.getNomeutilizador());
                    break;
                default:
                    this.view.line("Opção inválida!");
            }
        }
    }
}