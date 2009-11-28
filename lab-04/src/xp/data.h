/*
 * data.h
 *
 *  Created on: 28/11/2009
 *      Author: wesley
 */

#ifndef DATA_H_
#define DATA_H_

typedef struct tnode_st {
    char                key;
    char                type;
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
