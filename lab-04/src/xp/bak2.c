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

node_t* atom(char** str) {
    node_t* op1 = NULL;
    node_t* opr = NULL;
    
    printf("%s\n", *str);
    
    if (*(*str) == '(') {
        printf("1\n");
        ++(*str);
        op1 = atom(str);
    }
    else if (is_operand(*(*str))) {
        printf("2\n");
        op1 = new_node(*(*str));
        
        if (*((*str)+1) == ')') {
            printf("3\n");
            ++(*str);
            printf("===%c\n", op1->key);
            return op1;
        }
    }
    
    (*str)++;
    
    if (is_operator(*(*str))) {
        printf("4\n");
        opr = new_node(*(*str));
    }
    
    if (opr) {
        printf("5\n");
        ++(*str);
        opr->left = op1;
        opr->right = atom(str);
        return opr;
    }
    else {
        printf("6\n");
        return op1;
    }
} 

node_t* next_atom(node_t** root, char* str, int* pos) {
    node_t* op1 = NULL;
    node_t* op2 = NULL;
    node_t* opr = NULL;
    
    
        
    if (is_operand(str[*pos])) {
        printf("1\n");
        printf("--%c--\n", str[*pos]);
        op1 = new_node(str[*pos]);
    }
    else if (str[*pos] == '(') {
        printf("2\n");
        (*pos)++;
        op1 = next_atom(root, str, pos);
        (*pos)++;
        if (str[*pos] == ')') {
            return op1;
        }
    }
    else {
        printf("3\n");
        return NULL;
    }
    
    (*pos)++;
    
    if (is_operator(str[*pos])) {
        printf("4\n");
        opr = new_node(str[*pos]);
        //(*pos)++;
        //op2 = next_atom(root, str, pos);
    }
    else return NULL;
    
    (*pos)++;
    
    if (str[*pos]) {
        printf("5\n");
        op2 = next_atom(root, str, pos);
    }
    
    if (op2) {
        printf("7\n");
        (*root) = new_atom(op1, opr, op2);
        print_in(*root);
    } else {
        printf("8\n");
        if (*root) print_in(*root);
        return op1;
    }
    
    (*pos)++;
    if (str[*pos]) return next_atom(root, str, pos);
    else return NULL;
}

int main() {
    char* str = "(1+2)+(3+4)";
    int pos = 0;
    
    node_t* root;
    
    root = atom(&str);
    
    /*printf("%p\n", root);
    */
    print_in(root);
    
    return EXIT_SUCCESS;
}

