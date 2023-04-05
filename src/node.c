#include "node.h"

#include <stdio.h>
#include <stdlib.h>

void free_node_list(node_list *l) {
	free_node(l->no);
	free_node_list(l->succ);
	free(l);
}

void remove_node(node *n, node_list *l) {
	
}

void free_node(node *n) {
	
}

void print_node_list(node_list *l) {
	if(l->succ != NULL) {
		printf("%s\n", l->no->title);
	}
}

void ls(node *current) {
	print_node_list(current->children);
}

void cd(node *curr, char *dest) {
	
}

