#ifndef SINGLE_LINKED_LIST
#define SINGLE_LINKED_LIST

struct st_node {
    int a;
    struct st_node* next;
};

typedef struct st_node node_t;

typedef struct {
    node_t* head;
} list_t;


list_t* sll_new();
void sll_del(list_t* list);
void sll_print(list_t* list);
void sll_insert(list_t* list, int num);
void sll_delete(list_t* list);

#endif

