/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rfilev
 */
class Acao{
    private String nomeAcao;
    private double valorUnitario;
    private double totalCotas;

    Acao(String nome, double valor, double cotas){
        nomeAcao=nome;
        valorUnitario=valor;
        totalCotas=cotas;
    }

    /**
     * @return the nomeAcao
     */
    public String getNomeAcao() {
        return nomeAcao;
    }

    /**
     * @param nomeAcao the nomeAcao to set
     */
    public void setNomeAcao(String nomeAcao) {
        this.nomeAcao = nomeAcao;
    }

    /**
     * @return the valorUnitario
     */
    public double getValorUnitario() {
        return valorUnitario;
    }

    /**
     * @param valorUnitario the valorUnitario to set
     */
    public void setValorUnitario(double valorUnitario) {
        this.valorUnitario = valorUnitario;
    }

    /**
     * @return the totalCotas
     */
    public double getTotalCotas() {
        return totalCotas;
    }

    /**
     * @param totalCotas the totalCotas to set
     */
    public void setTotalCotas(double totalCotas) {
        this.totalCotas = totalCotas;
    }
}
