/*
- Usar TCP/IP;
- Dispositivos:
    - termómetro (indica a temperatura atual)
    - controlo de temp-alvo (indica o limiar da ativação da caldeira)
    - relé (controla a caldeira (liga e desliga) e aguarda indicação de mudança de estado via método off)
    - metodo off deve bloquear caso o estado fornecido seja idêntico ao atual do sistema.
 */
package PraticaTestes.Teste17;

interface Controlador {
    void temperatura(int centigrados);
    // medidor indica temperatura actual
    void limiar(int centigrados);
    // utilizador indica limiar de activao
    boolean on_off(boolean estadoatual) throws InterruptedException; // caldeira pergunta se estado mudou
}