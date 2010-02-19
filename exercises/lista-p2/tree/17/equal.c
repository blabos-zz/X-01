/**
 * equal.c
 * 
 * 17 - Implemente uma função que compare se duas árvores binárias são iguais.
 *
 *  Created on: 23/11/2009
 *      Author: wesley
 */

struct node_st {
    int             key;
    struct node_st* left;
    struct node_st* right;
};

typedef struct node_st node_t;


/**
 * Dada duas sub-árvores quaisquer, dizemos que elas são iguais se as chaves
 * de suas raízes forem iguais e se as sub-árvores correspondentes (à direita
 * e à esquerda) de cada uma também forem iguais, ou seja, se cada nó desde a
 * raiz tiver a mesma chave e os mesmos filhos.
 */
int equal(node_t* t1, node_t* t2) {
    if (t1 && t2) {
        /**
         * Se ambos os nós são não-nulos, então verificamos se as chaves são
         * iguais e se as sub-árvores também são.
         */
        return (
            (t1->key == t2->key) &&
            equal(t1->left, t2->left) &&
            equal(t1->right, t2->right)
        );
    }
    else if (t1 || t2) {
        /**
         * Se somente um nó é não-nulo, então eles são necessariamente
         * diferentes.
         */
        return 0;
    }
    else {
        /**
         * Se os dois nós são nulos, então eles são idênticos.
         */
        return 1;
    }
}
