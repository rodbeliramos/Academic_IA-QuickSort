#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

struct doubly_linked_list_struct{
    node_t*     head;
    node_t*     tail;
    uint16_t    list_size;
};

dll_t* dll_new(void)
{
    dll_t* dll = malloc(sizeof(dll_t));
    if(dll == NULL){
        perror("ERROR: at dll_create");
        exit(EXIT_FAILURE);
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->list_size = 0;
    return dll;
}

void dll_delete(dll_t* dll){
    free(dll);
    return;
}

void dll_add_head(dll_t* dll, node_t* node)
{
    if(dll == NULL || node == NULL){
        perror("ERROR: at dll_add_head");
        exit(EXIT_FAILURE);
    }
    if(dll_is_empty(dll)){
        dll->head = node;
        dll->tail = node;
        dll->list_size++;
        node_unlink(node);
    } else {
        node_unlink(node);
        node_link(node,dll_get_head(dll));
        dll->head = node;
        dll->list_size++;
    }
}

void* dll_remove_head(dll_t* dll)
{
    if(dll == NULL){
        perror("ERROR: at dll_remove_head");
        exit(EXIT_FAILURE);
    }
    void* data;
    node_t* node = dll_get_head(dll);
    node_t* next = node_get_next(node);
    node_unlink(node);
    dll->head = next;
    dll->list_size--;
    if(node == NULL){
        return NULL;
    }else{
        data = node_get_data(node);
    }
    return data;
}

void dll_add_tail(dll_t* dll, node_t* node)
{
    if(dll == NULL || node == NULL){
        perror("ERROR: at dll_add_tail");
        exit(EXIT_FAILURE);
    }
    if(dll_is_empty(dll)){
        dll->head = node;
        dll->tail = node;
        dll->list_size++;
        node_unlink(node);
    } else {
        node_unlink(node);
        node_link(dll_get_tail(dll), node);
        dll->tail = node;
        dll->list_size++;
    }
}

void* dll_remove_tail(dll_t* dll)
{
    if(dll == NULL){
        perror("ERROR: at dll_remove_head");
        exit(EXIT_FAILURE);
    }
    void* data;
    node_t* node = dll_get_tail(dll);
    node_t* previous = node_get_previous(node);
    node_unlink(node);
    dll->tail = previous;
    dll->list_size--;
    if(node == NULL){
        return NULL;
    }else{
        data = node_get_data(node);
    }
    return data;
}

void* dll_remove_between(dll_t* dll, node_t* node)
{
    if(dll == NULL){
        perror("ERROR: at dll_remove_between");
        exit(EXIT_FAILURE);
    }
    void* data;
    node_t* previous = node_get_previous(node);
    node_t* next = node_get_next(node);
    node_unlink(node);
    node_link(previous, next);
    dll->list_size--;
    if(node == NULL){
        return NULL;
    }else{
        data = node_get_data(node);
    }
    return data;

}

void* dll_take_node_at_pos(dll_t* dll, uint16_t position)
{
    if(dll == NULL){
        perror("ERROR: at dll_take_node_at_pos");
        exit(EXIT_FAILURE);
    }
    if(position>dll_get_list_size(dll)){
        perror("ERROR: at dll_take_node_at_pos: position out of range.");
        exit(EXIT_FAILURE);
    }
    uint16_t i;
    node_t* node = dll_get_head(dll);
    for(i=0;i<position;i++){
        node = node_get_next(node);
    }
    return node;
}

//  GETTERS METHODS
void* dll_get_head(dll_t* dll)
{
    if(dll == NULL){
        perror("ERROR: at dll_get_head");
        exit(EXIT_FAILURE);
    }
    return dll->head;
}

void* dll_get_tail(dll_t* dll)
{
    if(dll == NULL){
        perror("ERROR: at dll_get_tail");
        exit(EXIT_FAILURE);
    }
    return dll->tail;
}

uint16_t dll_get_list_size(dll_t* dll)
{
    return dll->list_size;
}

uint8_t dll_is_empty(dll_t* dll)
{
    if(dll_get_list_size(dll) == 0)
        return 1;
    else
        return 0;
}

void dll_print(dll_t* dll){
    if(dll == NULL){
        perror("ERROR: at dll_print");
        exit(EXIT_FAILURE);
    }
    uint16_t i;
    node_t* node = dll_get_head(dll);

    puts("---Lista:---");
    for(i=0;i<dll_get_list_size(dll);i++){
        printf("%s\n",(char*)node_get_data(node));
        node = node_get_next(node);
    }
    free(node);
    puts("---\\Lista:---");
    return;
}

