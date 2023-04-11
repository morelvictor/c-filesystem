
#include "node_list.h"

node_list *l_cons(node_list *succ, node *n) {
	node_list *acc = malloc(sizeof(node));
	acc->succ = succ;
	acc->no = n;
	return acc;
}

void free_node_list(node_list *l) {
	if(l != NULL) {
		free_node(l->no);
		free_node_list(l->succ);
		free(l);
	}
}

node_list *l_remove(node_list *l, node *n) {
	if(l->no == n) {
		return l->succ;
	} else {
		l->succ = l_remove(l->succ, n);
		return l;
	}
}

node_list *l_add(node_list *l, node *n) {
	return l_cons(l, n);
}

