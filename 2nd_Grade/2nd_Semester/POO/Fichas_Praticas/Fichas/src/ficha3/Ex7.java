package ficha3;

//Coloquei aqui apenas por organização, a classe já estava implementada no package 4.
/*********************************************************************************/
/** DISCLAIMER: Este código foi criado e alterado durante as aulas práticas      */
/** de POO. Representa uma solução em construção, com base na matéria leccionada */
/** até ao momento da sua elaboração, e resulta da discussão e experimentação    */
/** durante as aulas. Como tal, não deverá ser visto como uma solução canónica,  */
/** ou mesmo acabada. É disponibilizado para auxiliar o processo de estudo.      */
/** Os alunos são encorajados a testar adequadamente o código fornecido e a      */
/** procurar soluções alternativas, à  medida que forem adquirindo mais          */
/** conhecimentos de POO.                                                        */
/*********************************************************************************/

/**
 * Representacao de Linha de Encomenda
 *
 * @author MaterialPOO
 * @version 20180312
 * @version 20200317
 * @version 20210323
 */

public class Ex7 {
    private String referencia;
    private String descricao;
    private double preco;
    private int quantidade;
    private double imposto;
    private double desconto;

    public Ex7() {
        this.referencia = "n/a";
        this.descricao = "n/a";
        this.preco = 0;
        this.quantidade = 0;
        this.imposto = 0;
        this.desconto = 0;
    }

    public Ex7(String referencia, String descricao, double preco,
               int quantidade, double imposto, double desconto) {
        this.referencia = referencia;
        this.descricao = descricao;
        this.preco = preco;
        this.quantidade = quantidade;
        this.imposto = imposto;
        this.desconto = desconto;
    }

    public Ex7(Ex7 linha) {
        this.referencia = linha.getReferencia();
        this.descricao = linha.getDescricao();
        this.preco = linha.getPreco();
        this.quantidade = linha.getQuantidade();
        this.imposto = linha.getImposto();
        this.desconto = linha.getDesconto();
    }

    /**
     * B)
     */
    public double calculaValorLinhaEnc() {
        double valor = this.getQuantidade() * this.getPreco();
        valor -= valor* this.getDesconto();
        valor *= 1+ this.getImposto();
        return valor;
    }

    /**
     * C)
     */
    public double calculaValorDesconto() {
        double valor = this.getQuantidade() * this.getPreco();
        valor *= this.getImposto(); //e.g. imposto = 1.06
        return this.calculaValorLinhaEnc()-valor;
    }

    public String getReferencia() {
        return this.referencia;
    }

    public void setReferencia(String referencia) {
        this.referencia = referencia;
    }

    public String getDescricao() {
        return this.descricao;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public double getPreco() {
        return this.preco;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }

    public int getQuantidade() {
        return this.quantidade;
    }

    public void setQuantidade(int quantidade) {
        this.quantidade = quantidade;
    }

    public double getImposto() {
        return this.imposto;
    }

    public void setImposto(double imposto) {
        this.imposto = imposto;
    }

    public double getDesconto() {
        return this.desconto;
    }

    public void setDesconto(double desconto) {
        this.desconto = desconto;
    }

    public Ex7 clone() {
        return new Ex7(this);
    }

    public boolean equals(Object obj) {
        if(obj==this) return true;
        if(obj==null || obj.getClass() != this.getClass()) return false;
        Ex7 le = (Ex7) obj;
        return le.getReferencia().equals(this.getReferencia()) &&
                le.getDescricao().equals(this.getDescricao()) &&
                le.getPreco() == this.getPreco();
    }

    public String toString() {
        StringBuilder sb = new StringBuilder("\tDados Encomenda {\n");
        sb.append("\tReferencia: ").append(this.getReferencia()).append("\n");
        sb.append("\tDescrição: ").append(this.getDescricao()).append("\n");
        sb.append("\tPreço: ").append(this.getPreco()).append("\n");
        sb.append("\tQuantidade: ").append(this.getQuantidade()).append("\n");
        sb.append("\tImposto: ").append(this.getImposto()).append("\n");
        sb.append("\tDesconto: ").append(this.getDesconto()).append("\n");
        sb.append("\t}\n");
        return sb.toString();
    }

}