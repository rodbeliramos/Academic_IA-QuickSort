#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

typedef struct node node_t;

// NODE FUNCTIONS
node_t*     node_new(void* data);
void        node_delete(node_t* node);

void        node_link(node_t* source, node_t* destine);
void        node_unlink(node_t* node);

//GETTERS METHODS
node_t*     node_get_next(node_t* node);
node_t*     node_get_previous(node_t* node);
void*       node_get_data(node_t* node);

#endif // NODE_H_INCLUDED
