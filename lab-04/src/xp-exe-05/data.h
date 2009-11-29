/*
 * data.h
 *
 *  Created on: 28/11/2009
 *      Author: wesley
 */

#ifndef DATA_H_
#define DATA_H_

typedef enum {
    high_operator,      // Operadores * e /
    low_operator,       // Opreadores + e -
    open_parentesis,    // (
    close_parentesis,   // )
    operand,            // Dígitos de 0 a 9
    end_of_expression,  // Final da string
    unknown_token,      // Qualquer coisa desconhecida
    leaf                // Uma folha processada
} token_type_t;

typedef struct tnode_st {
    char                key;
    token_type_t        type;
    struct tnode_st*    left;
    struct tnode_st*    right;
} tnode_t;

typedef struct lnode_st {
    tnode_t*            data;
    struct lnode_st*    next;
    struct lnode_st*    prev;
} lnode_t;

typedef struct {
    int                 size;
    lnode_t*            nil;
} list_t;


#endif /* DATA_H_ */
