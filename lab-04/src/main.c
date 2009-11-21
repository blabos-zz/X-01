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
    
    printf("size: %d\n", count_nodes(root));
    printf("leaf: %d\n", count_leaves(root));
    
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
    
    printf("size: %d\n", count_nodes(root));
    printf("leaf: %d\n", count_leaves(root));
    
    printf("\nIN-OREDER\n");
    print_in(root);
    
    del_node(&root, 7);
    del_node(&root, 8);
    
    printf("\nIN-OREDER\n");
    print_in(root);
    
    printf("size: %d\n", count_nodes(root));
    printf("leaf: %d\n", count_leaves(root));
    
    return EXIT_SUCCESS;
}
