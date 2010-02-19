#include <stdlib.h>
#include <stdio.h>

#include "data.h"

int main(int argc, char** argv) {
    tnode_t* tree = make_parse_tree(argv[1]);
    
    if (tree) {
        printf("Expressão dada: %s\n", argv[1]);
        printf("Árvore correspondente:\n");
        print_in(tree);
        
        printf("Expressão gerada:\n");
        print_expr(tree);
        printf("\n");
    }
    else {
        printf("Expressão errada\n");
    }
    
    
    return EXIT_SUCCESS;
}
