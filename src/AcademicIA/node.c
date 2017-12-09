#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct node{
    node_t*     previous;
    node_t*     next;
    void*       data;
};

node_t* node_new(void* data)
{
    if(data == NULL){
        perror("ERROR: at node_new: no data!\n");
        exit(EXIT_FAILURE);
    }
    node_t* node = malloc(sizeof(node_t));
    if(node == NULL){
        perror("ERROR: at node_new\n");
        exit(EXIT_FAILURE);
    }
    node->previous = NULL;
    node->next = NULL;
    node->data = data;
    return node;
}

void node_delete(node_t* node)
{
    if(node == NULL){
        perror("ERROR: at node_delete: NULL pointer!\n");
        exit(EXIT_FAILURE);
    }
    free(node);
    node = NULL;
    return;
}

// list-linker
void node_link(node_t* source, node_t* destine)
{
    if(source == NULL || destine == NULL){
        perror("ERROR: at node_link: ponteiros invalidos\n");
        exit(EXIT_FAILURE);
    }
    source->next = destine;
    destine->previous = source;
    return;
}

// list-unlinker
void node_unlink(node_t* node)
{
    if(node == NULL){
        perror("ERROR: at node_unlink: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    node->previous = NULL;
    node->next = NULL;
    node = NULL;
    return;
}

// GETTERS METHODS
// get next
node_t* node_get_next(node_t* node)
{
    if (node == NULL) {
        fprintf(stderr,"ERROR: at node_get_next: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return node->next;
}

// get previous
node_t* node_get_previous(node_t* node)
{
    if (node == NULL) {
        fprintf(stderr,"ERROR: at node_get_previous: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return node->previous;
}

// get data
void* node_get_data(node_t* node)
{
    if (node == NULL) {
        fprintf(stderr,"ERROR: at node_get_data: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return node->data;
}
