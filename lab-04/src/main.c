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
    
    ins_node(&root, 16);
    ins_node(&root, 8);
    ins_node(&root, 24);
    ins_node(&root, 4);
    ins_node(&root, 12);
    ins_node(&root, 20);
    ins_node(&root, 28);
    ins_node(&root, 2);
    ins_node(&root, 6);
    ins_node(&root, 10);
    ins_node(&root, 14);
    ins_node(&root, 18);
    ins_node(&root, 22);
    ins_node(&root, 26);
    ins_node(&root, 30);
    ins_node(&root, 1);
    ins_node(&root, 3);
    ins_node(&root, 5);
    ins_node(&root, 7);
    ins_node(&root, 9);
    ins_node(&root, 11);
    ins_node(&root, 13);
    ins_node(&root, 15);
    ins_node(&root, 17);
    ins_node(&root, 19);
    ins_node(&root, 21);
    ins_node(&root, 23);
    ins_node(&root, 25);
    ins_node(&root, 27);
    ins_node(&root, 29);
    ins_node(&root, 31);
    
    printf("\nIN-OREDER\n");
    print_in(root);
    
    srand(0);
    int num;
    while(count_nodes(root)) {
        num = 1 + rand() % 31;
        printf("Removendo %d\n", num);
        del_node(&root, num);
        printf("\nIN-OREDER\n");
        print_in(root);
        printf("\n---------\n");
    }
    
    /*del_node(&root, 1);
    printf("\nIN-OREDER\n");
    print_in(root);
    printf("\n---------\n");
    
    del_node(&root, 2);
    printf("\nIN-OREDER\n");
    print_in(root);
    printf("\n---------\n");
    
    del_node(&root, 3);
    printf("\nIN-OREDER\n");
    print_in(root);
    printf("\n---------\n");
    
    del_node(&root, 4);
    printf("\nIN-OREDER\n");
    print_in(root);
    printf("\n---------\n");
    
    del_node(&root, 5);
    printf("\nIN-OREDER\n");
    print_in(root);
    printf("\n---------\n");
    
    del_node(&root, 6);
    printf("\nIN-OREDER\n");
    print_in(root);
    printf("\n---------\n");
    
    del_node(&root, 7);
    printf("\nIN-OREDER\n");
    print_in(root);
    printf("\n---------\n");*/
    
    return EXIT_SUCCESS;
}
