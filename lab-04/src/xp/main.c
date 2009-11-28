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

node_t* new_atom(node_t* op1, node_t* opr, node_t* op2) {
    opr->left = op1;
    opr->right = op2;
    
    return opr;
}

node_t* atom(char** str, int* level) {
    node_t* op1 = NULL;
    node_t* opr = NULL;
    char next;
    
    printf("'%s'\n", *str);
    
    if (*(*str) == '(') {
        printf("1\n");
        (*level)++;
        next = *(*str + 1);
        
        if ((next != '(') && !is_operand(next)) {
            printf("Esperava ( ou operando mas encotrei '%c' apos '%c'\n", next, **str);
        }
        
        ++(*str);
        op1 = atom(str, level);
    }
    else if (is_operand(*(*str))) {
        printf("2\n");
        op1 = new_node(*(*str));
        
        next = *(*str + 1);
        if ((next != ')') && (!is_operator(next)) && (next != '\0')) {
            printf("Esperava operador ou ) mas encotrei '%c' apos '%c'\n", next, **str);
        }
        else if ((next == '\0') && *level) {
            printf(") sobrando\n");
        }
        
        if (next == ')') {
            printf("3\n");
            (*level)--;
            printf("LEVEL: %d\n", *level);
            if (*level < 0) {
                printf("Encontrei ) sem ( depois de '%c'\n", **str);
            }
            ++(*str);
            printf("===%c\n", op1->key);
            return op1;
        }
    }
    
    (*str)++;
    
    if (is_operator(*(*str))) {
        printf("4\n");
        next = *(*str + 1);
        if ((next != '(') && !is_operand(next)) {
            printf("Esperava operando ou ( mas encotrei '%c' apos '%c'\n", next, **str);
        }
        opr = new_node(*(*str));
    }
    
    if (opr) {
        printf("5\n");
        ++(*str);
        opr->left = op1;
        opr->right = atom(str, level);
        return opr;
    }
    else {
        printf("6\n");
        return op1;
    }
}


int main() {
    char* str = "(";
    int level = 0;
    
    node_t* root;
    
    root = atom(&str, &level);
    
    /*printf("%p\n", root);
    */
    print_in(root);
    
    return EXIT_SUCCESS;
}

