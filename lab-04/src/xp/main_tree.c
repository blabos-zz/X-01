#include <stdlib.h>
#include <stdio.h>

#include "data.h"

int main(int argc, char** argv) {
    tnode_t* tree = make_parse_tree(argv[1]);
    
    print_in(tree);
    
    return EXIT_SUCCESS;
}
