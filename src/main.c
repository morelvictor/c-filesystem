#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#include "parser.h"
#include "path.h"
#include "debug.h"

#define MAX_CHAR 500

void executor(node **, w_index *);

int main(int argc, char *argv[]) {

	assert(argc >= 2);
	FILE *file;

	/*
	 * On assigne sa valeur a file et si il y a une erreur de lecture on la signale et on arrete le programme
	 **/
	if((file = fopen(argv[1], "r")) == NULL) {
		err_read_file();
		return(get_fail());
	}

	char *current_line = malloc(MAX_CHAR * sizeof(char));
	assert(current_line != NULL);

	/*
	 * On crée le noeud racine
	 * et on attribue sa racine et son papa
	 **/
	node *current = cons_node(true, "", NULL, NULL, NULL);
	current->root = current;
	current->father = current;

	/*
	 * Pour chaque ligne
	 * on en fait un index par espace
	 * on execute sur l'index
	 **/
	while(fgets(current_line, MAX_CHAR, file) != NULL) {
		w_index *i = split_space(current_line);
		executor(&current, i);
		free_index(i);
		if(get_fail()) { 
			break;
		}
	}

	fclose(file);
	free_node(current->root);
	free(current_line);
	return get_fail();
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
