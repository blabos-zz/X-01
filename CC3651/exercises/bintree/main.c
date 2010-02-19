/*
 * main.c
 *
 *  Created on: 10/11/2009
 *      Author: blabos
 */
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    node_t* root = NULL;
    
    insert(&root, 5);
    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 9);
    insert(&root, 2);
    insert(&root, 4);
    insert(&root, 6);
    insert(&root, 8);
    insert(&root, 0);
    
    printf("\nIN-OREDER\n");
    print_in(root, 0);
    
    printf("\nPRE-OREDER\n");
    print_pre(root, 0);
    
    printf("\nPOS-OREDER\n");
    print_pos(root, 0);
    
    return EXIT_SUCCESS;
}
