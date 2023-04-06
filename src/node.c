#include "node.h"

#include <stdio.h>
#include <stdlib.h>

void free_node_list(node_list *l) {
	if(l->succ != NULL) {
		free_node(l->no);
		free_node_list(l->succ);
		free(l);
	}
}

void remove_node(node *n, node_list *l) {
	
}

void free_node(node *n) {
	
}

node *cons_node(bool is_folder, char *title, node *root, node *father, node_list *children) {
	node *acc = malloc(sizeof(node));
	if(acc == NULL) {
		fprintf(stderr, "\nErreur: Impossible d'allouer la memoire pour créer un noeud");
		exit(EXIT_FAILURE);
	}
	acc->is_folder = is_folder;
	acc->root = root;
	acc->father = father;
	acc->children = children;

	size_t c = 0;
	while(c < 99 && title[c] != '\0') {
		acc->title[c] = title[c];
	}
	acc->title[c] = '\0';

	return acc;
}

void print_node_list(node_list *l) {
	if(l->succ != NULL) {
		printf("%s\n", l->no->title);
	}
}

void ls(node *current) {
	print_node_list(current->children);
}

void cd(node *curr, w_index *dest) {
	
}

