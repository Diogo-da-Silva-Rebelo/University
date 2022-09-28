package ficha4;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;


public class EncEficiente {
    private String clientName;
    private int clientTaxNumber;
    private String clientAddress;
    private int packageNumber;
    private LocalDate packageDate;
    private List<LinhaEncomenda> packages;

    public EncEficiente(){
        this.clientName = "";
        this.clientTaxNumber = -1;
        this.clientAddress = "";
        this.packageNumber = -1;
        this.packageDate = LocalDate.now();
        this.packages = new ArrayList<LinhaEncomenda>();
    }

    public EncEficiente(String clientName, int clientTaxNumber, String clientAddress,
                        int packageNumber, LocalDate packageDate, List<LinhaEncomenda> packages){
        this.clientName = clientName;
        this.clientTaxNumber = clientTaxNumber;
        this.clientAddress = clientAddress;
        this.packageNumber = packageNumber;
        this.packageDate = packageDate;
        this.setPackages(packages);
    }

    public EncEficiente(EncEficiente encEficiente){
        this.clientName = encEficiente.getClientName();
        this.clientTaxNumber = encEficiente.getClientTaxNumber();
        this.clientAddress = encEficiente.getClientAddress();
        this.packageNumber = encEficiente.getPackageNumber();
        this.packageDate = encEficiente.getPackageDate();
        this.setPackages(encEficiente.getPackages());
    }

    public String getClientName() {
        return this.clientName;
    }

    public void setClientName(String clientName) {
        this.clientName = clientName;
    }

    public int getClientTaxNumber(){
        return this.clientTaxNumber;
    }

    public void setClientTaxNumber(int clientTaxNumber){
        this.clientTaxNumber = clientTaxNumber;
    }

    public String getClientAddress() {
        return this.clientAddress;
    }

    public void setClientAddress(String clientAddress) {
        this.clientAddress = clientAddress;
    }

    public int getPackageNumber() {
        return this.packageNumber;
    }

    public void setPackageNumber(int packageNumber) {
        this.packageNumber = packageNumber;
    }

    public LocalDate getPackageDate() {
        return this.packageDate;
    }

    public void setPackageDate(LocalDate packageDate) {
        this.packageDate = packageDate;
    }

    public List<LinhaEncomenda> getPackages() {
        return this.packages;
    }

    public void setPackages(List<LinhaEncomenda> packages) {
        this.packages = new ArrayList<>();
        for (LinhaEncomenda l : packages)
            this.packages.add(l.clone());
    }

    public String toString() {
            final StringBuffer sbuffer = new StringBuffer("\tEncomenda {\n");
        sbuffer.append("\tClient Name: ").append(this.getClientName()).append("\n");
        sbuffer.append("\tClient Tax Number: ").append(this.getClientTaxNumber()).append("\n");
        sbuffer.append("\tClient Address: ").append(this.getClientAddress()).append("\n");
        sbuffer.append("\tDate: ").append(this.getPackageDate()).append("\n");
        sbuffer.append("\tPackages: ").append(this.getPackages().toString()).append("\n");
        sbuffer.append("\t}\n");
        return sbuffer.toString();
    }

    public EncEficiente clone(){
        return new EncEficiente(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof EncEficiente)) return false;
        EncEficiente that = (EncEficiente) o;
        return getClientTaxNumber() == that.getClientTaxNumber()
                && getPackageNumber() == that.getPackageNumber()
                && getClientName().equals(that.getClientName())
                && getClientAddress().equals(that.getClientAddress())
                && getPackageDate().equals(that.getPackageDate())
                && getPackages().equals(that.getPackages());
    }

    public double calculaValorTotal(){
        double sumTotal = 0;

        for (LinhaEncomenda l: this.getPackages())
            sumTotal += l.calculaValorLinhaEnc();
        return sumTotal;
    }

    public double calculaValorDesconto() {
        double sumOff = 0;

        for (LinhaEncomenda l: this.getPackages())
            sumOff += l.calculaValorDesconto();
        return sumOff;
    }

    public int numeroTotalProdutos(){
        int sumQuantity = 0;
        for (LinhaEncomenda l: this.getPackages())
            sumQuantity += l.getQuantidade();
        return sumQuantity;
    }

    public boolean existeProdutoEncomenda(String refProduto){
        for (LinhaEncomenda l: this.getPackages()){
            if (refProduto.equals(l.getReferencia()))
                return true;
        }
        return false;
    }

    public void adicionaLinha(LinhaEncomenda linha){
        this.getPackages().add(linha);
    }

    public void removeProduto(String codProd){
        this.getPackages().removeIf(line -> (codProd.equals(line.getReferencia())));
    }
}
