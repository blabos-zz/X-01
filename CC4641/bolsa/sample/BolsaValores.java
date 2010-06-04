
import java.util.ArrayList;

/**
 *
 * @author rfilev
 * Abril/2010 - revisao Maio/2010
 * Classe base para o desenvolvimento da classe bolsa de valores.
 */

/**
 *
 * @author rfilev
 * OBS. PODE SER NECESSARIO (DEPENDENDO DE SUA PROGRAMACAO) TROCAR A CLASSE ACAO
 * DE LOCAL. FACA A MUDANCA QUE JULGAR NECESSARIO - PENSO QUE UMA DISCUSSAO NO
 * FORUM VENHA A CALHAR.
 */


public class BolsaValores {

    private ArrayList listaAcoes;
    public int opCompra=1;
    public int opVenda=2;
    public int erroProc=-1;

    BolsaValores(){
        listaAcoes=null;
        listaAcoes.add(new Acao("VALE5",43.50,50000.00));
        listaAcoes.add(new Acao("PETR4",30.10,600000.00));
        listaAcoes.add(new Acao("AMBV4",172.00,1000000.00));
        listaAcoes.add(new Acao("ELET6",14.30,1000000.00));
        listaAcoes.add(new Acao("ITSA4",14.80,10.00));
        listaAcoes.add(new Acao("TAMM4",27.49,100.00));
        listaAcoes.add(new Acao("USIM5",90.30,400000.00));
        listaAcoes.add(new Acao("CSNA3",10.30,200000.00));
        listaAcoes.add(new Acao("EMBR3",20.10,300000.00));
        listaAcoes.add(new Acao("ITAUB4",36.11,250000.00));
    }

    public int acaoListadaPregao(String codAcao){

        Acao acaoTemp=null;
        for(int i=0;i<listaAcoes.size();i++){
            acaoTemp=(Acao)listaAcoes.get(i);
            if(acaoTemp.getNomeAcao().equalsIgnoreCase(codAcao)){
                return i;
            }
        }
        return erroProc;
    }

    /**
     *
     * MÉTODO INFORMA A QUANTIDADE O CODIGO DA ACAO, VALOR UNITARIO E TOTAL
     * DE COTAS DISPONIVEIS NO MERCADO
     *
     * NOTE QUE O METODO RETORNA UM VETOR DE OBJETOS DO TIPO ACAO.     *
     */
    public ArrayList informaAcoesPregao(){
        return listaAcoes;
    }

    public  OperacaoTrading negociaAcao(int idBroker, String codAcao, int operacao, double valorCota, double valorOperacao){
       OperacaoTrading opTrading=null;
       Acao acaoTemp=null;
       if(operacao==opCompra){
            if(acaoListadaPregao(codAcao)>erroProc){
                acaoTemp =(Acao) listaAcoes.get(acaoListadaPregao(codAcao));//este objeto está referenciando algo que pode ser acessado por diversos objetos! Como protege-lo?
                opTrading.setNomeAcao(codAcao);
                opTrading.setValorUnitario(acaoTemp.getValorUnitario());
                if(opTrading.getValorUnitario()<=valorCota){
                    if(opTrading.getQtdeCotas()< (valorOperacao/valorCota)){
                        opTrading.setQtdeCotas((valorOperacao/valorCota));
                        acaoTemp.setTotalCotas(acaoTemp.getTotalCotas()-opTrading.getQtdeCotas());
                        opTrading.setCodOperacao(opCompra);
                        opTrading.setValorTotalOperacao(acaoTemp.getValorUnitario()*((valorOperacao/valorCota)));
                        
                    }
                   
                    }
                }
            }
       else{//operacao de venda
            //else compra-se todo o mercado
                    
                if(acaoListadaPregao(codAcao)>erroProc){
                    acaoTemp =(Acao) listaAcoes.get(acaoListadaPregao(codAcao));
                    if(acaoTemp.getValorUnitario()<=valorCota){
                        //o mercado sempre compra toda a acao caso o preco esteja abaixo do mercado.
                        opTrading.setValorTotalOperacao(valorOperacao);
                        opTrading.setQtdeCotas(valorOperacao/valorCota);
                        opTrading.setNomeAcao(codAcao);
                        opTrading.setCodOperacao(opVenda);
                        opTrading.setValorUnitario(valorCota);


                    }
                }  
       }


         return opTrading;
       }      


}
