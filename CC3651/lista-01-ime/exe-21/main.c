/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  21. (FIS 88) Qualquer número natural de quatro algarismos pode ser
 *  dividido em duas dezenas formadas pelos seus dois primeiros e dois últimos
 *  dígitos.
 *
 *  Exemplos:
 *      1297: 12 e 97.
 *      5314: 53 e 14.
 *  
 *  Escreva um programa que imprime todos os milhares (4 algarismos) cuja raiz
 *  quadrada seja a soma das dezenas formadas pela divisão acima.
 *
 *  Exemplo:
 *      raiz de 9801 = 99 = 98 + 01.
 *  
 *  Portanto 9801 é um dos números a ser impresso.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    int i, h, l;
    
    for (i = 1000; i <= 9999; i++) {
        h = i / 100;
        l = i % 100;
        
        if (((h + l)*(h + l)) == i) {
            printf("sqtr(%04d) = %02d = %02d + %02d\n", i, h + l, h, l);
        }
    }
	
	return EXIT_SUCCESS;
}
