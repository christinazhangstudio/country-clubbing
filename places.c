#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "places.h"
#include <math.h>

int main(int argc, char *argv[]) {
    char buffer[32] = {0};
    int option = 0;

    linked_list_t *ll = NULL;
    ll = NewLinkedList();

    printf("choose an option\n");
    printf("1: add a new place\n");
    printf("2: remove place from head\n");
    printf("3: remove place from tail\n");
    printf("4: print list of places\n");
    printf("5: remove place at index\n");
    printf("8: exit program and clean up\n");

    //printf("pointer to struct is 16 bytes %llu", sizeof(linked_list_node_t));

    bool inprogram = true;

    while(inprogram) {
        // fgets is safe and won't buffer overflow even if put in input size > 32
        // sscanf will read in up to 32 and puts in option 
        // the num contained by those 32 bytes 
        // so  0000000000000000000000000000001
        //      will be option = 1
        // and 00000000000000000000000000000001
        //      will be option = 0
        //      (loop back) option = 1
        // if you didn't want this unexpected edge case
        // can add length check
        if(fgets(buffer, sizeof(buffer), stdin)) {
            if(sscanf(buffer, "%d", &option) != 1) {    // this maybe causing mem leak...
                fprintf(stderr, "input pls\n");
                exit(1);
            }
            if (option < 0 || option > 8 ) {
                fprintf(stderr, "num pls\n");
                exit(1);
            }
        }

        printf("you chose %d\n", option);

        switch(option) {
            case 1:
                printf("chose to add a new place\n");
                linked_list_node_t *node = NULL;
                node = (linked_list_node_t*) malloc(sizeof(linked_list_node_t));
                
                printf("add some inputs for this new place\n");
                printf("hearts ♡ (1-5): ");
                // reusing buffer and option...
                if(fgets(buffer, sizeof(buffer), stdin)) {
                    if(sscanf(buffer, "%d", &option) != 1) {
                        fprintf(stderr, "input pls");
                        exit(1);
                    }
                    if (!(1 < option < 5)) { // this is warning, because "comparisons like 'X<=Y<=Z' do not have their mathematical meaning"
                    //if (option < 1 || option > 5)
                        fprintf(stderr, "num 1-5 pls\n");
                        exit(1);
                    }
                }

                printf("name: ");
                printf("visited(Tt/Ff): ");

                node->place = NewPlace(0, false, "e");
                node->next = NULL;  // this needs to be here or else throws non-nil garbage

                AddToEnd(ll, node);
                break;
            case 2:
                printf("chose to remove a place from head..\n");
                RemoveFromHead(ll);
                break;
            case 3:
                printf("chose to remove a place from tail..\n");
                RemoveFromTail(ll);
                break;
            case 4:
                printf("chose to print linked list...\n");
                //PrintAll(ll);
                
                break;
            case 8:
                printf("chose to exit program...\n");
                inprogram = false;
                break;
            default:
                continue;
        }
    }


    printf("here's list\n");
    linked_list_node_t *current = ll->head;
    while(current) {
        printf("%s\n", current->place->name);
        current = current->next;
    }

    // free everything
    printf("freeing..");
    while(ll->head) {
        RemoveFromHead(ll);
    }
    free(ll);

    return 0;
}

place_t* NewPlace(int prior, bool visited, char *name) {
    place_t *place = (place_t*) malloc(sizeof(place_t));
    if(!place) { fprintf(stderr, "out of mem\n"); exit(1337); }
    place->prior = prior;
    place->visited = visited;
    place->name = name;
    
    return place;
}

linked_list_t *NewLinkedList() {
    linked_list_t *list = (linked_list_t*) malloc(sizeof(linked_list_t));
    if(!list) { fprintf(stderr, "out of mem\n"); exit(1337); }
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void AddToHead(linked_list_t *ll, linked_list_node_t *node) {
    linked_list_node_t *prevHead = ll->head;
    ll->head = node;

    // everything else has to move
    if (prevHead != NULL) {
        for (linked_list_node_t *node = prevHead; node->next != NULL; node=node->next) {
            node->next = node->next->next;
            ll->tail = node->next;
        }
    }

    return;
}

void AddToEnd(linked_list_t *ll, linked_list_node_t *node) {
    if (ll->head == NULL) {
        ll->head = node;
        ll->tail = node;
        return;
    }
    linked_list_node_t *prevTail = ll->tail;
    prevTail->next = node;
    ll->tail = node;

    return;
}

void RemoveFromHead(linked_list_t *ll) {
    if (ll->head == NULL) {
        fprintf(stderr, "nothing to rem\n");
        return;
    }
    linked_list_node_t *prevHead = ll->head;
    ll->head = prevHead->next;

    free(prevHead->place);
    free(prevHead);

    return;
}

void RemoveFromTail(linked_list_t *ll) {
    if(ll->head == NULL) {
        fprintf(stderr, "nothing to rem\n");
        return;
    }

    // if we happen to be removing the head
    // (if it happens to be the same as tail)
    // need to make sure head is reset
    if(ll->head->next == NULL) {
        ll->head = NULL;
        ll->tail = NULL;
        free(ll->head->place);
        free(ll->head);
        return;
    }

    // get to the last node...
    // can do this as doubly linked list,
    // but this is a singly linked one,
    // so we'll just do this the long way...
    linked_list_node_t *current = ll->head;
    linked_list_node_t *lastNodeWithNext = NULL;
    while(current->next) {
        lastNodeWithNext = current;
        current = current->next;
    } 
    lastNodeWithNext->next = NULL; // and now wala it doesn't have a next
    ll->tail = lastNodeWithNext; // and it becomes the new tail
    
    free(current->place);   // current held the last tail
    free(current);

    return;
}

linked_list_node_t *GetNode(linked_list_t *ll, int index)
{
   linked_list_node_t *current = ll->head;
   if(index >= Length(ll)){
      fprintf(stderr,"out of range\n");
      return NULL;
   }
   for(int i = 0; i < index && current != NULL; i++){
      current = current->next;
   }
   return current;
}

int Length(linked_list_t *ll){
   int num = 0;
   for(linked_list_node_t *tmp = ll->head; tmp != NULL; tmp=tmp->next){
      num++;
   }
   return num;
}

void PrintAll(linked_list_t *ll) {
    // add padding through memset (just to use memset)


    // for(linked_list_node_t *tmp = ll->head; tmp != NULL; tmp=tmp->next) {
    //     printf("|%s|%s|", tmp->place->name, tmp->place->visited);
    //     printf(tmp)
    // }

    // add padding in a saner way
}