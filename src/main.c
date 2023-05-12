#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "node.h"
#include "parser.h"
#include "path.h"

#define MAX_CHAR 500

void executor(node **, w_index *);

int main(int argc, char *argv[]) {

	assert(argc >= 2);
	FILE *file;

	/*
	 * On assigne sa valeur a file et si il y a une erreur de lecture on la signale et on arrete le programme
	 **/
	if((file = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n", argv[1]);
		return(EXIT_FAILURE);
	}

	char *current_line = malloc(MAX_CHAR * sizeof(char));
	assert(current_line != NULL);

	/*
	 * On crée le noeud racine
	 * et on attribue sa racine et son papa
	 **/
	node *current = cons_node(true, "root", NULL, NULL, NULL);
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
	}

	fclose(file);
	free_node(current->root);
	free(current_line);

	return EXIT_SUCCESS;
}

void executor(node **n, w_index *i) {
	if(i->size == 0)
		return;
	if(!strcmp(i->words[0], "ls")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		ls(n);
	} else if(!strcmp(i->words[0], "cd")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		cd(n, i);
	} else if(!strcmp(i->words[0], "pwd")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		pwd(n);
	} else if(!strcmp(i->words[0], "mkdir")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		mkdir(n, i);
	} else if(!strcmp(i->words[0], "touch")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		touch(n, i);
	} else if(!strcmp(i->words[0], "rm")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		rm(n, i);
	} else if(!strcmp(i->words[0], "cp")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		cp(n, i);
	} else if(!strcmp(i->words[0], "mv")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		mv(n, i);
	} else if(!strcmp(i->words[0], "print")) {
		printf("\033[32;01mVictor-Ayman@Linux-desktop:\033[00m"); pwd_in_line(n); printf("$ ");
		print_index_in_line(i);
		print(n);
	} else {
		fprintf(stderr, "\nErreur: Commande inexistante %s\n", i->words[0]);
		exit(EXIT_FAILURE);
	}
}
