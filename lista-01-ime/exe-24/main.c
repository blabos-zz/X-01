/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  24. Dizemos que um número natural n é palíndromo (4) se o 1o algarismo de
 *  n é igual ao seu último algarismo, o 2o algarismo de n é igual ao
 *  penúltimo algarismo, e assim sucessivamente.
 *
 *  Exemplos:
 *      567765 e 32423 são palíndromos.
 *      567675 não é palíndromo.
 *
 *  Dado um número natural n > 10 , verificar se n é palíndromo.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int power(int x, int n) {
	if (n > 0) return x * power(x, n-1);
	else return 1;
}

int how_many_digits(int a) {
    int d = 1;
    
    while (a /= 10) {
        d++;
    }
    
    return d;
}

int is_palindrome(int a) {
    int i, d, h;
    int first, last;    
    
    d = how_many_digits(a);
    h = d%2 + d/2;
    
    for (i = 1; i <= h; i++) {
	    first = (a / power(10, d-i)) % 10;
	    last  = (a % power(10, i)) / power(10, i-1);
	    
	    if (first != last) return 0;
	}
	
	return 1;
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n;
	
	printf("Enter the number: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	if (n < 10) {
	    printf("n must be >= 10\n");
	    return EXIT_FAILURE;
	}
	
	if (is_palindrome(n)) {
	    printf("%d is palindrome\n", n);
	}
	else {
	    printf("%d isn't palindrome\n", n);
	}
	
	return EXIT_SUCCESS;
}
