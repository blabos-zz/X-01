#include "sl_list.h"

#include <stdlib.h>
#include <stdio.h>


list_t* sll_new() {
    list_t* list        = (list_t*)malloc(sizeof(list_t));
    list->head          = (node_t*)malloc(sizeof(node_t));
    
    list->head->a       = 0;
    list->head->next    = NULL;
    
    return list;
}

void sll_del(list_t* list) {
    free(list->head);
    free(list);
}

void sll_print(list_t* list) {
    node_t* curr = list->head;
    
    if (curr->next == NULL) {
        printf("Empty list.\n");
    }
    
    while (curr = curr->next) {
        printf("%p: %d\n", curr, curr->a);
    }
}

void sll_insert(list_t* list, int num) {
    node_t* tmp = (node_t*)malloc(sizeof(node_t));

    if (tmp) {
        tmp->next = list->head->next;
        list->head->next = tmp;
        
        tmp->a = num;
    }
}

void sll_delete(list_t* list) {
    node_t* tmp = list->head;
    if (tmp->next == NULL) return;
    
    while (tmp->next->next) {
        tmp = tmp->next;
    }
    
    free(tmp->next);
    tmp->next = NULL;
}

