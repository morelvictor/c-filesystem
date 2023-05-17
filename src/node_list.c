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

node *pop(node_list **head) {
	node *retval = NULL;
	node_list * next_node = NULL;

	if (*head == NULL) {
		return NULL;
	}

	next_node = (*head)->succ;
	retval = (*head)->no;
	free(*head);
	*head = next_node;

	return retval;
}

node *l_remove(node_list **head, node *val) {
	node_list *previous, *current;

	if (*head == NULL) {
		return NULL;
	}

	if ((*head)->no == val) {
		return pop(head);
	}

	previous = *head;
	current = (*head)->succ;
	while (current) {
		if (current->no == val) {
			previous->succ = current->succ;
			free(current);
			return val;
		}

		previous = current;
		current  = current->succ;
	}
	return NULL;
}

node_list *l_add(node_list *l, node *n) {
	return l_cons(l, n);
}

node *get_node(node_list *l, char *title) {
	if(l == NULL)
		return NULL;
	if(!strcmp(title, l->no->title)) {
		return l->no;
	} else {
		return get_node(l->succ, title);
	}
}

void print_node_list(node_list *l) {
	if(l == NULL) {
		printf("\n");
	} else {
		printf("%s ", l->no->title);
		print_node_list(l->succ);
	}
}

size_t size_aux(node_list *l, size_t acc) {
	if(l == NULL) return acc;
	return size_aux(l->succ, acc+1);
}

size_t l_size(node_list *l) {
	return size_aux(l, 0);
}
