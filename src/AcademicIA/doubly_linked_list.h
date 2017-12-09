#ifndef DOUBLY_LINKED_LIST_H_INCLUDED
#define DOUBLY_LINKED_LIST_H_INCLUDED

#include <stdint.h>
#include "node.h"

typedef struct doubly_linked_list_struct dll_t;

// DOUBLY LINKED LIST FUNCTIONS
dll_t*      dll_new(void);
void        dll_delete(dll_t* dll);

void        dll_add_head(dll_t* dll, node_t* node);
void*       dll_remove_head(dll_t* dll);

void        dll_add_tail(dll_t* dll, node_t* node);
void*       dll_remove_tail(dll_t* dll);

void*       dll_remove_between(dll_t* dll, node_t* node);
//void*       dll_take_node_at_pos(dll_t* dll, int position);

// GETTERS METHODS
void*       dll_get_head(dll_t* dll);
void*       dll_get_tail(dll_t* dll);

uint16_t    dll_get_list_size(dll_t* dll);
uint8_t     dll_is_empty(dll_t* dll);
void        dll_print(dll_t* dll);


#endif // DOUBLY_LINKED_LIST_H_INCLUDED
