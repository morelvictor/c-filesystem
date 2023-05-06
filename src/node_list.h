#ifndef NODE_LIST_H
#define NODE_LIST_H

#include "node.h"
#include <stdio.h>
#include <string.h>

struct node;

struct node_list {
	struct node *no;
	struct node_list *succ;
};

typedef struct node node;
typedef struct node_list node_list;

extern node_list *l_cons(node_list *, node *);
extern void free_node_list(node_list *);
extern node *l_remove(node_list **, node *);
extern node_list *l_add(node_list *, node *);
extern void print_node_list(node_list *);
extern node *get_node(node_list *, char *);
extern node *pop(node_list **);
extern size_t l_size(node_list *);

#endif
