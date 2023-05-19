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

void set_title(node *no, char *title) {
	size_t c = 0;
	while(c < 99 && title[c] != '\0') {
		no->title[c] = title[c];
		++c;
	}
	no->title[c] = '\0';
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

	set_title(acc, title);
	
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
		return true;
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


void print_node(node *n, int depth) {
	if(n == n->root){
		    printf(".\n");
	}  
	print_aux(n->children, depth+1);
}

void print_aux(node_list *l, int depth){
	if(l == NULL){
		return;
	}
	if(l -> succ == NULL){
		for(int i = 0; i < depth-1; i++) {
        	printf("     ");
    	}
		printf("└────");
	}
	else{
		for(int i = 0; i < depth-1; i++) {
        	printf("     ");
    	}
		printf("├────");
	}
	if(l->no->is_folder){
		printf("\033[34;01m%s/\033[00m\n", l->no->title);
	}
	else{
		printf("%s\n", l->no->title);
	}	
	print_node(l->no, depth);
	print_aux(l->succ, depth);
}



