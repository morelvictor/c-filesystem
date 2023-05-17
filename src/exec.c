
#include "exec.h"


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

void pwd(node **curr) {
	pwd_in_line(curr);
	printf("\n");
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

void print(node **curr) {
	print_node((*curr)->root);
}


void executor(node **n, w_index *i) {
	if(i->size == 0)
		return;
	printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
	if(!strcmp(i->words[0], "ls")) {
		print_index_in_line(i);
		if(i->size == 1) {
			ls(n);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "cd")) {
		print_index_in_line(i);
		if(i->size <= 2) {
			cd(n, i);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "pwd")) {
		print_index_in_line(i);
		if(i->size == 1) {
			pwd(n);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "mkdir")) {
		print_index_in_line(i);
		if(i->size >= 2) {
			mkdir(n, i);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "touch")) {
		print_index_in_line(i);
		if(i->size >= 2) {
			touch(n, i);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "rm")) {
		print_index_in_line(i);
		if(i->size == 2) {
			rm(n, i);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "cp")) {
		print_index_in_line(i);
		if(i->size == 3) {
			cp(n, i);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "mv")) {
		print_index_in_line(i);
		if(i->size == 3) {
			mv(n, i);
		} else {
			err_arg_err();
		}
	} else if(!strcmp(i->words[0], "print")) {
		print_index_in_line(i);
		if(i->size == 1) {
			print(n);
		} else {
			err_arg_err();
		}
	} else {
		err_inval_cmd();
	}
}
