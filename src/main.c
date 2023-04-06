#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"
#include "parser.h"

#define MAX_CHAR 500

int main(int argc, char *argv[]) {
	assert(argc >= 2);
	FILE *file;
	
	/*
	 * On assigne sa valeur a file et si il y a une erreur de lecture on la signale et on arrete le programme
	 **/
	if((file = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n\x1b[1;31mErreur: Impossible de lire le fichier %s\n", argv[1]);
		return(EXIT_FAILURE);
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
		print_index(split_space(current_line));
	}
	
	fclose(file);

	return EXIT_SUCCESS;
}

