
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node;
struct node_list;

struct node {
	bool is_folder;
	char title[100];
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

void print_node_list(node_list *l) {
	if(l->succ != NULL) {
		printf("%s\n", l->no->title);
	}
}

void ls(node *n) {
	print_node_list(n->children);
}

void cd(node curr, char *dest) {
	
}

