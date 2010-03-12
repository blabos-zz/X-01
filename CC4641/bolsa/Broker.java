/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package bolsa1;

import java.util.ArrayList;

class Mensagem {
    String de;
    String para;
    String codigo;
};

class MensagemDeVenda extends Mensagem {
    String symbol;
    double valorMinimo;
    double quantidade;
};

class ResultadoDaVenda extends Mensagem {
    boolean deuCerto;
    double valorDeVenda;
    double quantidadeVendida;
};

/**
 *
 * @author Mariana
 */
public class Broker implements Interface {

    public ArrayList consultarAcoes() {
        return new ArrayList<String>();
    }

    public ResultadoDaVenda venderAcoes(MensagemDeVenda msg) {
        return new ResultadoDaVenda();
    }

    public boolean comprarAcoes(String symbol, double valorCompra, double valorTotal) {
        return false;
    }

    public ArrayList volumeNegociadoDia(String IdUsuario) {
        return new ArrayList<String>();
    }

    public ArrayList consultaCarteira(String IdUsuario) {
        return new ArrayList<String>();
    }

   
   

}
