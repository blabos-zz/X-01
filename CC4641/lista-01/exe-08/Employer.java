package org.blabos.lista1;

public class Employer {
    String      name;
    double      salary;
    double      day_overtimes;
    double      night_overtimes;
    int         dependents;
    int         absences;
    double      eventual_discounts;
    double      meals;
    double      vales; //???
    
    public Employer(String _name, double _salary, double _day_overtimes,
        double _night_overtimes, double _eventual_discounts, double _meals,
        double _vales, int _dependents, int _absences) {
        name                = _name;
        salary              = _salary;
        day_overtimes       = _day_overtimes;
        night_overtimes     = _night_overtimes;
        dependents          = _dependents;
        absences            = _absences;
        eventual_discounts  = _eventual_discounts;
        meals               = _meals;
        vales               = _vales;
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
        return salary * (day_overtimes + night_overtimes * 1.2) / 160;
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
