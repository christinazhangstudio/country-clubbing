#ifndef _linkedlist_h
#define _linkedlist_h

typedef struct place_t {
    int prior;
    bool visited;
    char *name;
    // no reason for this to be pointer
    // this is for fun
    //place_t *me;
} place_t;

typedef struct linked_list_node_t {
    place_t *place;
    struct linked_list_node_t *next;
} linked_list_node_t;

typedef struct linked_list_t {
    linked_list_node_t *head;
    linked_list_node_t *tail;
} linked_list_t;

place_t* NewPlace(int id, bool visited, char *name);

linked_list_t* NewLinkedList();

void FreeLinkedList(linked_list_t *ll);

void AddToEnd(linked_list_t *ll, linked_list_node_t *node);

void RemoveFromHead(linked_list_t *ll);

void RemoveFromTail(linked_list_t *ll);

place_t* GetPlace(linked_list_t *ll, int index);

void RemoveFromTail(linked_list_t *ll);

int Length(linked_list_t *ll);

#endif