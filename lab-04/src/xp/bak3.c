#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

int is_operand(char c) {
    return ((c >= '0') && (c <= '9'));
}

int is_operator(char c) {
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

int opgt(node_t* opr1, node_t* opr2) {
    if (is_operator(opr1->key) && is_operator(opr1->key)) {
        if (opr1->level != opr2->level) {
            return opr1->level > opr2->level;
        }
        else {
            if ((opr1->key == '*') || (opr1->key == '/')) {
                if ((opr2->key == '+') || (opr2->key == '-')) {
                    return 1;
                }
            }
            else {
                return 0;
            }
        }
    }
    else if (is_operator(opr1->key)) {
        return 1;
    }
    else {
        return 0;
    }
}

node_t* new_atom(node_t* op1, node_t* opr, node_t* op2) {
    opr->left = op1;
    opr->right = op2;
    
    return opr;
}

void print_expression(node_t* node) {
    if (node) {
        if (opgt(node, node->left)) {
            printf("(");
            print_expression(node->left);
            printf(")");
        }
        else
            print_expression(node->left);
        
        printf("%c", node->key);

        if (opgt(node, node->right)) {
            printf("(");
            print_expression(node->right);
            printf(")");
        }
        else
            print_expression(node->right);
    }
}

node_t* atom(char* str, int* pos, int* level) {
    if (str) {
        node_t* op1 = NULL;
        node_t* op2 = NULL;
        node_t* opr = NULL;

        char prev, curr, next;

        prev = *pos ? str[*pos - 1] : '\0';
        curr = str[*pos];
        next = *pos >= strlen(str) ? '\0' : str[*pos + 1];

        (*pos)++;
        if (curr == '(') {
            (*level)++;
            op1 = atom(str, pos, level);
        }
        else if (is_operand(curr)) {
            op1 = new_node(curr);
            op1->level = *level;
        }
        else {
            printf("Unexpected '%c' near column %d '%c%c%c' "
                "when looking for '(' or operand\n", curr, *pos, prev, curr, next);
            return NULL;
        }

        prev = *pos ? str[*pos - 1] : '\0';
        curr = str[*pos];
        next = *pos >= strlen(str) ? '\0' : str[*pos + 1];

        (*pos)++;
        if (is_operator(curr)) {
            opr = new_node(curr);
            opr->level = *level;

            opr->left = op1;
            opr->right = atom(str, pos, level);

            if (opr && opr->left && opr->right) {
                return opr;
            }
            else {
                return NULL;
            }
        }
        else if (curr == ')') {
            (*level)--;
            if (*level < 0) {
                printf("Unexpected ')' near column %d '%c%c%c'\n", *pos, prev, curr, next);
                return NULL;
            }
            else {
                return op1;
            }
        }
        else if (curr == '\0') {
            return op1;
        }
        else {
            printf("Unexpected '%c' near column %d '%c%c%c' "
                "when looking for ')' or operator\n", curr, *pos, prev, curr, next);
            return NULL;
        }
        
    }
    return NULL;
}


int main(int argc, char** argv) {
    int pos = 0;
    int level = 0;
    node_t* root = atom(argv[1], &pos, &level);
    print_in(root);
    print_expression(root);
    printf("\n");
    
    return EXIT_SUCCESS;
}

