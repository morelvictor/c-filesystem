#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "path.h"

void free_node(node *n) {
	/*
	 * On enleve le node a liberer de la liste des enfant de son pere
	 * puis on free la liste des enfants
	 * puis le node
	 */
	if(n == NULL)
		return;
	if(n->children != NULL) {
		free_node_list(n->children);
	}
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

	if(acc->father != NULL) {
		acc->father->children = l_add(acc->father->children, acc);
	}
	acc->children = children;


	size_t c = 0;
	while(c < 99 && title[c] != '\0') {
		acc->title[c] = title[c];
		++c;
	}
	acc->title[c] = '\0';

	return acc;
}

void ls(node **curr) {
	print_node_list((*curr)->children);
}

void cd(node **curr, w_index *i) {
	assert(i->size >= 1);
	if(i->size == 1) {
		*curr = (*curr)->root;
	} else {
		node *acc = pton(*curr, cons_path(i->words[1]));
		if(acc != NULL) {
			*curr = acc;
		} else {
			puts("Cd: repertoire inexistant");
			exit(EXIT_FAILURE);
		}
	}
}

void pwd(node **curr) {
	printf("Nom: %s\n", (*curr)->title);
}

void mkdir(node **curr, w_index *i) {
	assert(i->size >= 2);
	for(int x = 1; x < i->size; ++x) {
		cons_node(true, i->words[x], (*curr)->root, (*curr), NULL);
	}
}

void touch(node **curr, w_index *i) {
	assert(i->size >= 2);
	for(int x = 1; x < i->size; ++x) {
		cons_node(false, i->words[x], (*curr)->root, (*curr), NULL);
	}
}

void rm(node **curr, w_index *i) {
	assert(i->size >= 2);
	puts("Error: rm not implemented");
	//exit(EXIT_FAILURE);
	/* 
	if(n->father != NULL) {
		l_remove(&n->father->children, n);
	}
	 * */
}

void cp(node **curr, w_index *i) {
	assert(i->size == 3);
	puts("Error: cp not implemented");
	//exit(EXIT_FAILURE);
}

void mv(node **curr, w_index *i) {
	assert(i->size == 3);
	puts("Error: mv not implemented");
	//exit(EXIT_FAILURE);
}

void print(node **curr) {
	puts("Error: print not implemented");
	//exit(EXIT_FAILURE);
}

