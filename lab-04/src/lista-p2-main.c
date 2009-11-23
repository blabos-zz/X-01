#include <stdlib.h>
#include <stdio.h>

#include "lista-p2.h"

int main(void) {
    node_t* r1 = new_tree();
    node_t* r2 = new_tree();
    
    ins_node(&r1, 2);
    ins_node(&r1, 1);
    //ins_node(&r1, 3);
    
    ins_node(&r2, 2);
    ins_node(&r2, 1);
    ins_node(&r2, 3);
    
    print_in(r1);
    print_in(r2);
    
    if (equal(r1, r2)) {
        printf("Iguais\n");
    }
    else {
        printf("Diferentes\n");
    }
    
    return EXIT_SUCCESS;
}

