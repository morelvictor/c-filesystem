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
			if(acc->is_folder) {
				*curr = acc;
			} else {
				err_inval_type();
			}
		} else {
			err_no_dest();
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


void mkdir(node **curr, w_index *i) {
	assert(i->size >= 2);
	for(int x = 1; x < i->size; ++x) {
		if(has_child(*curr, i->words[x])) {
			err_already_exist();
			break;
		}
		cons_node(true, i->words[x], (*curr)->root, (*curr), NULL);
	}
}

void touch(node **curr, w_index *i) {
	assert(i->size >= 2);
	for(int x = 1; x < i->size; ++x) {
		if(has_child(*curr, i->words[x])) {
			err_already_exist();
			break;
		}
		cons_node(false, i->words[x], (*curr)->root, (*curr), NULL);
	}
}

void rm(node **curr, w_index *i) {
	// il faut que la cible soit un enfant de current
	assert(i->size >= 2);
	node *n = pton(*curr, cons_path(i->words[1]));
	if(n != NULL) {
		//if(is_child(n, *curr)) {
		if(!is_child(*curr, n)) {
			l_remove(&n->father->children, n);
			free_node(n);
		} else {
			err_par_act();
		}
	} else {
		err_no_dest();
	}
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

void cp(node **curr, w_index *i) {
	assert(i->size == 3);
	node *origin = pton(*curr, cons_path(i->words[1]));
	if(origin == NULL) {
		err_no_dest();
	}
	
	path *cpy_path = cons_path(i->words[2]);
	char *cpy_title = cpy_path->index->words[cpy_path->index->size - 1];
	node *cpy_fath = pton(*curr, cons_papa(cpy_path));
	if(cpy_fath == NULL) {
		err_no_dest();
	} else if(!cpy_fath->is_folder) {
		err_inval_type();
	} else if(has_child(cpy_fath, cpy_title)) {
		err_already_exist();
	} else if(is_child(cpy_fath, origin)) {
		err_par_dest();
	} else {
		node* cpy = cons_node(true, cpy_title, (*curr)->root, cpy_fath, NULL);
		if(!origin->is_folder) cpy->is_folder = false;
	
		copy_node(cpy, origin);
	}
	
	free_path(cpy_path);
}

void mv(node **curr, w_index *i) {
	assert(i->size == 3);
	node *origin = pton(*curr, cons_path(i->words[1]));
	if(origin == NULL) {
		err_no_dest();
	}
	
	path *cpy_path = cons_path(i->words[2]);
	char *cpy_title = cpy_path->index->words[cpy_path->index->size - 1];
	node *cpy_fath = pton(*curr, cons_papa(cpy_path));
	if(cpy_fath == NULL) {
		err_no_dest();
	} else if(!cpy_fath->is_folder) {
		err_inval_type();
	} else if(has_child(cpy_fath, cpy_title)) {
		err_already_exist();
	} else if(is_child(cpy_fath, origin)) {
		err_par_dest();
	} else {
		l_remove(&origin->father->children, origin);
		cpy_fath->children = l_add(cpy_fath->children, origin);
	}

	free_path(cpy_path);
}

void p_aux_print(node_list *l) {
	if(l == NULL) return;
	printf("%s (%c) ", l->no->title, (l->no->is_folder ? 'D' : 'F'));
	p_aux_print(l->succ);
}

void aux_print(node *);

void rec_aux_print(node_list *l) {
	if(l == NULL) return;
	aux_print(l->no);
	rec_aux_print(l->succ);
}

void aux_print(node *node) {
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

void print(node **curr) {
	aux_print((*curr)->root);
}

