#include "lista-p2.h"
#include <stdio.h>


/**
 * Dada duas sub-árvores quaisquer, dizemos que elas são iguais se as chaves
 * de suas raízes são iguais e se cada sub-árvore (à direita e à esquerda)
 * também são iguais.
 */
int equal(node_t* t1, node_t* t2) {
    if (t1 && t2) {
        return (
            (t1->key == t2->key) &&
            equal(t1->left, t2->left) &&
            equal(t1->right, t2->right)
        );
    }
    else if (t1 || t2) {
        return 0;
    }
    else {
        return 1;
    }
}

