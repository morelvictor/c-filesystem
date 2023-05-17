#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "path.h"
#include "debug.h"
#include "parser.h"
#include "node_list.h"

#define MAX_TITLE_LENGH 100

struct node_list;

struct node {
	bool is_folder;
	char title[MAX_TITLE_LENGH];
	struct node *father;
	struct node *root;
	struct node_list *children;
};

typedef struct node node;
typedef struct node_list node_list;

extern void free_node(node *);

extern node *cons_node(bool, char *, node *, node *, node_list *);
extern bool is_child(node *, node *);
extern bool has_child(node *, char *);
extern void copy_node(node *, node *);
extern void print_node(node *);



#endif
