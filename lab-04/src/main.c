/*
 * main.c
 *
 *  Created on: 10/11/2009
 *      Author: blabos
 */
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    node_t* root = new_tree();
    node_t* node;
    node_t* n;
    int key = argc == 2 ? atoi(argv[1]) : 0;
    
    ins_node(&root, 5);
    ins_node(&root, 1);
    ins_node(&root, 3);
    ins_node(&root, 7);
    ins_node(&root, 9);
    ins_node(&root, 2);
    ins_node(&root, 4);
    ins_node(&root, 6);
    ins_node(&root, 8);
    ins_node(&root, 0);
    ins_node(&root, 10);
    
    printf("\nIN-OREDER\n");
    print_in(root, 0);
    
    node = find_node(root, key);
    
    if (node) {
        printf("Deletando Key %d\n", key);
        del_node(&root, node);
    }
    else printf("Key %d nao encontrada\n", key);
    
    printf("\nIN-OREDER\n");
    print_in(root, 0);
    
    
    return EXIT_SUCCESS;
}
