/*
 * main.c
 *
 *  Created on: 08/11/2009
 *      Author: blabos
 */
#include "list.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    list_t* list = new_list();
    lnode_t lnode;
    tnode_t tnode1, tnode2, tnode3;
    tnode_t* tnode4;
    
    tnode1.key = '1';
    tnode1.left = tnode1.right = NULL;
    push(list, &tnode1);
    
    tnode2.key = '2';
    tnode2.left = tnode2.right = NULL;
    push(list, &tnode2);
    
    tnode3.key = '3';
    tnode3.left = tnode3.right = NULL;
    push(list, &tnode3);
    
    print_list(list);
    
    tnode4 = pop(list);
    
    printf("\n");
    print_list(list);
    
    printf("\n");
    print_tnode(tnode4);
    
    tnode4 = pop(list);
    
    printf("\n");
    print_list(list);
    
    printf("\n");
    print_tnode(tnode4);
    
    del_list(list);
    return EXIT_SUCCESS;
}
