#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void free_node(node *n) {
	/*
	 * On enleve le node a liberer de la liste des enfant de son pere
	 * puis on free la liste des enfants
	 * puis le node
	 */
	l_remove(n->father->children, n);
	free_node_list(n->children);
	free(n);
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

node *get_node(node_list *l, char *title) {
	if(l == NULL)
		return NULL;
	if(strcmp(title, l->no->title)) {
		return l->no;
	} else {
		return get_node(l->succ, title);
	}
}

void ls(node *curr) {
	print_node_list(curr->children);
}

void cd(node *curr, w_index *i) {
	assert(i->size >= 1);
	
	puts("Error: cd not implemented");
	//exit(EXIT_FAILURE);
}

void pwd(node *curr) {
	puts("Error: pwd not implemented");
	//exit(EXIT_FAILURE);
}

void mkdir(node *curr, w_index *i) {
	assert(i->size >= 2);
	for(int x = 1; x < i->size; ++x) {
		
	}
	//exit(EXIT_FAILURE);
}

void touch(node *curr, w_index *i) {
	assert(i->size >= 2);
	puts("Error: touch not implemented");
	
	//exit(EXIT_FAILURE);
}

void rm(node *curr, w_index *i) {
	assert(i->size >= 2);
	puts("Error: rm not implemented");
	//exit(EXIT_FAILURE);
}

void cp(node *curr, w_index *i) {
	assert(i->size == 3);
	puts("Error: cp not implemented");
	//exit(EXIT_FAILURE);
}

void mv(node *curr, w_index *i) {
	assert(i->size == 3);
	puts("Error: mv not implemented");
	//exit(EXIT_FAILURE);
}

void print(node *curr) {
	puts("Error: print not implemented");
	//exit(EXIT_FAILURE);
}

