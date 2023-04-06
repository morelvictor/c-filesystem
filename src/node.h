#ifndef NODE_H
#define NODE_H

#include "parser.h"
#include <stdbool.h>

#define MAX_TITLE_LENGH 100

struct node;
struct node_list;


struct node {
	bool is_folder;
	char title[MAX_TITLE_LENGH];
	struct node *father;
	struct node *root;
	struct node_list *children;
};

struct node_list {
	struct node *no;
	struct node_list *succ;
};

typedef struct node node;
typedef struct node_list node_list;

extern void free_node_list(node_list *);
extern void free_node(node *);

extern node *cons_node(bool, char *, node *, node *, node_list *);

extern void ls(node *);
extern void cd(node *, w_index *);
extern void pwd(node *);
extern void mkdir(node *, w_index *);
extern void touch(node *, w_index *);
extern void rm(node *, w_index *);
extern void cp(node *, w_index *);
extern void mv(node *, w_index *);
extern void print(node *);

#endif
