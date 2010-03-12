/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package bolsa1;

import java.util.ArrayList;

/**
 *
 * @author Mariana
 */
public interface Interface {

    public ArrayList consultarAcoes();
    public ResultadoDaVenda venderAcoes(MensagemDeVenda msg);
    public boolean comprarAcoes(String symbol, double valorCompra, double valorTotal);
    public ArrayList volumeNegociadoDia(String IdUsuario);
    public ArrayList consultaCarteira(String IdUsuario);

}
