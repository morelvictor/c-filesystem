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
	node_list *l = (*curr)->children;

	if(l == NULL) {
		printf("\n");
	} else {
		while(l != NULL){
			if(l->no->is_folder){
				printf("\033[35;01m%s\033[00m ", l->no->title);
			}
			else{
				printf("%s ", l->no->title);
			}
			l = l->succ;
		}
	}
	printf("\n");
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
    pwd_in_line(curr);
    printf("\n");
}

void pwd_in_line(node **curr) {
    node_list *acc = NULL;
    node *tmp = *curr;
    while (tmp->father != tmp) {
        acc = l_add(acc, tmp);
        tmp = tmp->father;
    }
    printf("\033[34;01m/\033[00m");
    while(acc != NULL){
        printf("\033[34;01m%s/\033[00m", acc->no->title);
		  node_list *prec = acc;
        acc = acc->succ;
		  free(prec);
    }
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

bool is_child(node *child, node *father) {
	if(child == child->root)
		return false;
	if(father == child->root)
		return true;
	if(father == child->father)
		return true;
	if(father == child)
		return false;
	return is_child(child->father, father);
}

void rm(node **curr, w_index *i) {
	// il faut que la cible soit un enfant de current
	assert(i->size >= 2);
	node *n = pton(*curr, cons_path(i->words[1]));
	if(n != NULL) {
		if(is_child(n, *curr)) {
			l_remove(&n->father->children, n);
			free_node(n);
		} else {
			puts("rm: dossier/fichier n'est pas un enfant de l'actuel");
			exit(EXIT_FAILURE);
		}
	} else {
		puts("rm: dossier/fichier inexistant");
		exit(EXIT_FAILURE);
	}
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

