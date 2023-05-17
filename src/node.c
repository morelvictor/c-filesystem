#include "node.h"

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
		err_malloc_error();
		exit(get_fail());
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

bool aux_h_c(node_list *l, char *s) {
	if(l == NULL) return false;
	if(!strcmp(l->no->title, s)) return true;
	return aux_h_c(l->succ, s);
}

bool has_child(node *n, char *s) {
	return aux_h_c(n->children, s);
}




// Copie les enfants et les enfants des enfants etc...
void copy_node(node *dest, node *origin) {
	node_list *o = origin->children;
	while(o != NULL) {
		node *new = cons_node(o->no->is_folder, o->no->title, o->no->root, dest, NULL);
		copy_node(new, o->no);
		o = o->succ;
	}
}



void p_aux_print(node_list *l) {
	if(l == NULL) return;
	printf("%s (%c) ", l->no->title, (l->no->is_folder ? 'D' : 'F'));
	p_aux_print(l->succ);
}


void rec_aux_print(node_list *l) {
	if(l == NULL) return;
	print_node(l->no);
	rec_aux_print(l->succ);
}

void print_node(node *node) {
	if(node == node->root) printf("/ ");
	else printf("%s ", node->title);
	printf("(%c), ", node->is_folder ? 'D' : 'F');
	if(node->root != node) {
		printf("pere: ");
		if(node->father == node->root) printf("/ ");
		else printf("%s ", node->father->title);
		printf(", ");
	}
	printf("%zu fils : ", l_size(node->children));
	p_aux_print(node->children);
	printf("\n");

	rec_aux_print(node->children);
}



