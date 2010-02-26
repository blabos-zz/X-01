public class Exe08 {
    public static void main(String args[]) {
        Employer e = new Employer();
        
        System.out.println("Nome:            " + e.name() );
        System.out.println("Salario:         " + e.salary() );
        System.out.println("Horas Extras:    " + e.all_overtimes() );
        System.out.println("Salario Familia: " + e.family_salary() );
        System.out.println("Salario Bruto:   " + e.brute_salary() );
        System.out.println("Descontos:       " + e.all_discounts() );
        System.out.println("Salario Liquido: " + e.brute_salary() );
    }
};

class Employer {
    String      name;
    double      salary;
    double      day_overtimes;
    double      nigth_overtimes;
    int         dependents;
    int         absences;
    double      eventual_discounts;
    double      meals;
    double      vales; //???
    
    public Employer() {
        name                = "Blabos de Blebe";
        salary              = 10000.0;
        day_overtimes       = 20;
        nigth_overtimes     = 10;
        dependents          = 9;
        absences            = 10;
        eventual_discounts  = 30;
        meals               = 200;
        vales               = 300;
    }
    
    public String name() {
        return name;
    }
    
    public double salary() {
        return salary;
    }
    
    public double received_salary() {
        return brute_salary() - all_discounts();
    }
    
    public double all_overtimes() {
        return salary * (day_overtimes + nigth_overtimes * 1.2) / 160;
    }
    
    public double family_salary() {
        return dependents * 0.05 * 550;
    }
    
    public double brute_salary() {
        return salary + all_overtimes() + family_salary();
    }
    
    public double all_discounts() {
        return (
            0.8 * salary +                          // INAMPS
            salary * absences / 160 +               // Faltas
            meals + vales + eventual_discounts +    // Comida, vales e outros
            0.08 * brute_salary()                   // IR
        );
    }
};
