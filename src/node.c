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

void ls(node *curr) {
	print_node_list(curr->children);
}

void cd(node *curr, w_index *dest) {
	puts("Error: cd not implemented");
	exit(EXIT_FAILURE);
}

void pwd(node *curr) {
	puts("Error: pwd not implemented");
	exit(EXIT_FAILURE);
}

void mkdir(node *curr, w_index *i) {
	puts("Error: mkdir not implemented");
	exit(EXIT_FAILURE);
}

void touch(node *curr, w_index *i) {
	puts("Error: touch not implemented");
	exit(EXIT_FAILURE);
}

void rm(node *curr, w_index *i) {
	puts("Error: rm not implemented");
	exit(EXIT_FAILURE);
}

void cp(node *curr, w_index *i) {
	puts("Error: cp not implemented");
	exit(EXIT_FAILURE);
}

void mv(node *curr, w_index *i) {
	puts("Error: mv not implemented");
	exit(EXIT_FAILURE);
}

void print(node *curr) {
	puts("Error: print not implemented");
	exit(EXIT_FAILURE);
}

