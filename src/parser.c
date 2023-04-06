
#include "parser.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

void free_index(w_index *pi) {
	for(size_t i = 0; i < pi->size; ++i) {
		free(pi->words[i]);
	}
	free(pi->words);
	free(pi);
}

void print_index(w_index *pi) {
	//printf("nbr: %zu\n", pi->size);
	//printf("words:\n");
	for(size_t i = 0; i < pi->size; ++i) {
		printf("%s\n", pi->words[i]);
	}
}

/* Origine de mon malheur*/
int nbr_words(int (*f)(int), char *s) {
	int i = 0;
	bool pre_s = true;
	
	for(size_t c = 0; s[c] != '\0'; ++c) {
		if(pre_s && !f(s[c]))
			++i;
		pre_s = f(s[c]);
	}
	return i;
}

int word_len(int(*f)(int), const char *w) {
	assert(isalpha(*w) || !f(*w));
	int i = 0;
	
	for(size_t c = 0; (isalpha(w[c]) || !f(w[c])) && w[c] != '\0' ; ++c) {
		++i;
	}
	return i;
}

char *extract_word(int(*f)(int), const char *w, int *pl) {
	assert(isalpha(*w) || !f(*w));
	*pl = word_len(f, w);
	char *c = malloc(*pl * sizeof(char));
	return memmove(c, w, *pl * sizeof(char));
}

char *next_word(int (*f)(int), char *w) {
	char *c = w;
	while(f(*c) || *c == '\0') {
		if(*c == '\0')
			return NULL;
		++c;
	}
	return c;
}

w_index *cons_index(int (*f)(int), char *s) {
	w_index *acc = malloc(sizeof(w_index));
	acc->size = nbr_words(f, s);
	acc -> words = malloc(acc->size * sizeof(char *));
	char *current = next_word(f, s);
	for(int i = 0; current != NULL && i < acc->size; ++i) {
		int pl = -1;
		acc -> words[i] = extract_word(f, current, &pl);
		current = next_word(f, current + pl);
	}
	return acc;
}

int is_slash(int c) {
	return c == '/';
}

/*
 * Soucis de parsage pour
 * "Td/Cours/td" -> ["Td", "Cours"]
 */
w_index *split_slash(char *s) {
	return cons_index(is_slash, s);
}

w_index *split_space(char *s) {
	return cons_index(isspace, s);
}



