#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "path.h"
#include "cst.h"
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

extern void ls(node **);
extern void cd(node **, w_index *);
extern void pwd(node **);
extern void pwd_in_line(node **);
extern void mkdir(node **, w_index *);
extern void touch(node **, w_index *);
extern void rm(node **, w_index *);
extern void cp(node **, w_index *);
extern void mv(node **, w_index *);
extern void print(node **);

#endif
