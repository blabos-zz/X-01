/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rfilev
 */
public class OperacaoTrading {
    private String nomeAcao;
    private double valorUnitario;
    private double qtdeCotas;
    private double valorTotalOperacao;
    private int codOperacao;

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
     * @return the qtdeCotas
     */
    public double getQtdeCotas() {
        return qtdeCotas;
    }

    /**
     * @param qtdeCotas the qtdeCotas to set
     */
    public void setQtdeCotas(double qtdeCotas) {
        this.qtdeCotas = qtdeCotas;
    }

    /**
     * @return the totalCotas
     */
    public double getValorTotalOperacao() {
        return valorTotalOperacao;
    }

    /**
     * @param totalCotas the totalCotas to set
     */
    public void setValorTotalOperacao(double valorTotalOperacao) {
        this.valorTotalOperacao = valorTotalOperacao;
    }

    /**
     * @return the codOperacao
     */
    public int getCodOperacao() {
        return codOperacao;
    }

    /**
     * @param codOperacao the codOperacao to set
     */
    public void setCodOperacao(int codOperacao) {
        this.codOperacao = codOperacao;
    }


}
