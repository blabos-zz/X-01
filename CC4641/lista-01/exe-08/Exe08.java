import org.blabos.lista1.Employer;
import java.io.*;

public class Exe08 {
    private Employer[] employers;
    
    public static void main(String args[]) throws Exception {
        Exe08 exe = new Exe08();
        
        
        exe.init();
        exe.show();
    }
    
    private void init() {
        BufferedReader stdin
            = new BufferedReader(new InputStreamReader(System.in));
        
        String input;
        int nfunc;
        
        System.out.print("Digite a quantidade de funcionarios: ");
        try {
            input = stdin.readLine();
            nfunc = Integer.parseInt(input);
        }
        catch (Exception e) {
            System.err.println("Warning: n func invalido. Usando 3");
            nfunc = 3;
        }
        
        employers = new Employer[nfunc];
        
        String name             = "";
        double salary           = 0.0;
        double day_overtimes    = 0.0;
        double night_overtimes  = 0.0;
        double discounts        = 0.0;
        double meals            = 0.0;
        double vales            = 0.0;
        int dependents          = 0;
        int absences            = 0;
        
        for (int i = 0; i < employers.length; i++) {
            try {
                System.out.print("Nome:              ");
                name = stdin.readLine();
                
                System.out.print("Salario:           ");
                salary = Double.parseDouble(stdin.readLine());
                
                System.out.print("Horas Ex Diurnas:  ");
                day_overtimes = Double.parseDouble(stdin.readLine());
                
                System.out.print("Horas Ex Noturnas: ");
                night_overtimes = Double.parseDouble(stdin.readLine());
                
                System.out.print("Dependentes:       ");
                dependents = Integer.parseInt(stdin.readLine());
                
                System.out.print("Faltas:            ");
                dependents = Integer.parseInt(stdin.readLine());
                
                System.out.print("Descontos:         ");
                discounts = Double.parseDouble(stdin.readLine());
                
                System.out.print("Comida:            ");
                meals = Double.parseDouble(stdin.readLine());
                
                System.out.print("Vales:             ");
                vales = Double.parseDouble(stdin.readLine());
            }
            catch (Exception e) {
                System.err.println("Voce digitou besteira, se lascou!!!");
                System.exit(-1);
            }
                
            employers[i] = new Employer(
                name,
                salary,
                day_overtimes,
                night_overtimes,
                discounts,
                meals,
                vales,
                dependents,
                absences
            );
        }
    }
    
    private void show() {
        System.out.println("\nLista de funcionarios:");
        for (int i = 0; i < employers.length; i++) {
            System.out.println("\nFuncionário " + i + ":" );
            System.out.println("Nome:            " + employers[i].name() );
            System.out.println("Salario:         " + employers[i].salary() );
            System.out.println("Horas Extras:    " + employers[i].all_overtimes() );
            System.out.println("Salario Familia: " + employers[i].family_salary() );
            System.out.println("Salario Bruto:   " + employers[i].brute_salary() );
            System.out.println("Descontos:       " + employers[i].all_discounts() );
            System.out.println("Salario Liquido: " + employers[i].brute_salary() );
        }
    }
};


