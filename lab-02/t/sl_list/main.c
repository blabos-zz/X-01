#include <sl_list.h>
#include <stdlib.h>

int main(void) {
    list_t* list = sll_new();
    
    sll_insert(list, 1);
    sll_insert(list, 2);
    sll_insert(list, 3);
    sll_print(list);
    
    sll_delete(list);
    sll_delete(list);
    sll_delete(list);
    sll_delete(list);
    sll_print(list);
    
    sll_insert(list, 11);
    sll_insert(list, 12);
    sll_insert(list, 13);
    sll_print(list);
    
    sll_del(list);

    return 0;
}

