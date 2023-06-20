package Controller.USER;

import DAO.USER.EspecialistaDAO;
import Entidades.USER.Especialista;
import Entidades.USER.Jogo;

import java.util.LinkedHashMap;
import java.util.List;

public class ControllerEspecialista extends Controller {
    private final Especialista user;
    private final EspecialistaDAO db;
    public ControllerEspecialista(Especialista user, Controller controller) {
        this.user = user;
        this.view = controller.getView();
        this.scan = controller.getScan();
        this.db = new EspecialistaDAO(controller.getDb());
    }

    public void run() {
        int opcao = -1;
        while (opcao != 0) {
            this.view.especialistaMainMenu(this.user.getNomeutilizador());
            opcao = this.scan.nextInt();
            switch (opcao) {
                case 1 ->
                    // 1. Consultar Jogos
                        consultarJogos();
                case 2 ->
                    // 2. Inserir odd
                        inserirOdd();
                case 3 ->
                    // 3 Atualizar odd
                        atualizarOdd();
                case 0 -> this.db.logout(this.user.getNomeutilizador());
                default -> this.view.line("Opção inválida!");
            }
        }
    }

    void consultarJogos() {
        // 1.1 Escolhe um desporto
        this.view.subheader("Jogos", this.user.getNomeutilizador());
        String desporto = this.getDesporto();
        if (desporto != null) {
            List<Jogo> jogos = this.db.getJogos(desporto);
            for (int i = 0; i < jogos.size(); i++) {
                this.view.line((i + 1) + " - " + jogos.get(i).toString() + "\n");
            }
        }
    }

    void atualizarOdd() {
        // 3.1 Escolhe um desporto
        String desporto = this.getDesporto();


        // 3.2 Lista jogos do desporto
        List<Jogo> jogos = this.db.getJogos(desporto);
        List<String> menuJogos = this.getMenuJogos(jogos);
        this.view.optionsMenu(menuJogos.toArray(new String[0]));

        String idJogo = "";
        // 3.3 Input id jogo
        //Integer idJogo = -1;
        boolean existe = false;
        while(!existe) { // Caso nao exista, tenta novamente
            // 3.3.1 Scan Id Jogo
            this.view.line("Porfavor introduza o id do jogo que pretende alterar: ");
             idJogo = this.scan.nextLine();

            // 3.3.2 Verifica existencia idJogo
            for (Jogo j : jogos) {
                if (j.getId().equals(idJogo)) {
                    existe = true;
                    break;
                }
            }
        }
        // 3.4 Print odds
        LinkedHashMap<String, Double> odds = this.db.getOdds(idJogo);

        System.out.println(odds);

        // 3.5 Select odd to change
        this.view.line("Qual o prognostico que deseja alterar?");
        String prognostico = this.scan.nextLine();
        while(!odds.containsKey(prognostico)) {
            this.view.line("Prognostico invalido!");
            this.view.line("Qual o prognostico que deseja alterar?");
            prognostico = this.scan.nextLine();
        }

        // 3.6 Change odd
        this.view.line("Introduza nova odd para " + prognostico + ":");
        float newOdd = this.scan.nextFloat();
        this.db.atualizarOdd(newOdd,prognostico,idJogo);

        // 3.7 Confirmacao mudanca
        System.out.println("A odd foi alterada com sucesso!");
    }

    void inserirOdd() {
        // 2.1 Escolhe um desporto
        String desporto = this.getDesporto();
        if (desporto == null) return;
        // 2.2 Lista jogos (sem odd) do desporto
        List<Jogo> jogos = this.db.getJogosSemOdd(desporto);
        if(jogos.isEmpty()) {
            this.view.line("Nao ha jogos sem odds neste desporto...");
            return;
        }

        //
        List<String> menuJogos = this.getMenuJogos(jogos);
        this.view.optionsMenu(menuJogos.toArray(new String[0]));

        // 2.3 Input id jogo a inserir odd
        int idJogo = -1;
        boolean existe = false;
        while(!existe) { // Caso nao exista, tenta novamente
            // 2.3.1 Scan Id Jogo
            this.view.line("Porfavor introduza o id do jogo que pretende inserir odd: ");
            idJogo = this.scanOption(1, jogos.size());

            // 2.3.2 Verifica existencia idJogo
            for (Jogo j : jogos) {
                if (j.getId().equals(Integer.toString(idJogo))) {
                    existe = true;
                    break;
                }
            }
        }

        // 2.4 Insere odds
        this.view.line("Introduza <EquipaA>");
        String equipaA = this.scan.next();
        this.view.line("Introduza <OddA>");
        double oddA = this.scan.nextDouble();
        this.view.line("Introduza <OddEmpate>");
        double oddE = this.scan.nextDouble();
        this.view.line("Introduza <EquipaB>");
        String equipaB = this.scan.next();
        this.view.line("Introduza <OddB>");
        double oddB = this.scan.nextDouble();

        // Insert Equipa A
        this.db.inserirOdd(Integer.toString(idJogo),equipaA,oddA);
        // Insert Equipa B
        this.db.inserirOdd(Integer.toString(idJogo),equipaB,oddE);
        // Insert Empate
        this.db.inserirOdd(Integer.toString(idJogo),equipaA,oddB);

        this.view.line("Odds inseridas com sucesso!");
    }
}
