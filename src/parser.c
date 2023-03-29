
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

struct w_index {
	size_t size;
	char **words;
};

typedef struct w_index w_index;

void free_index(w_index *pi) {
	for(size_t i = 0; i < pi->size; ++i) {
		free(pi->words[i]);
	}
	free(pi->words);
	free(pi);
}

void print_index(w_index *pi) {
	printf("nbr: %zu\n", pi->size);
	printf("words:\n");
	for(size_t i = 0; i < pi->size; ++i) {
		printf("%s\n", pi->words[i]);
	}
}

int nbr_words(bool (*f)(char), char *s) {
	int i = 0;
	char prev = '\0';
	for(size_t c = 0; s[c] != '\0'; ++c) {
		if(f(s[c]))
			i += 1;
	}
	return i;
}

int word_len(const char *w) {
	assert(isalpha(*w));
	int i = 0;
	
	for(size_t c = 0; isalpha(w[c]); ++c) {
		++i;
	}

	return i;
}

char *extract_word(const char *w, int *pl) {
	assert(isalpha(*w));
	*pl = word_len(w);
	char *c = malloc(*pl * sizeof(char));
	return memmove(c, w, *pl * sizeof(char));
}

char *next_word(bool (*f)(char), char *w) {
	char *c = w;
	while(f(*c) || *c == '\0') {
		if(*c == '\0')
			return NULL;
		++c;
	}
	return c;
}

w_index *cons_index(bool (*f)(char), char *s) {
	w_index *acc = malloc(sizeof(w_index));
	acc->size = nbr_words(f, s);
	acc -> words = malloc(acc->size * sizeof(char *));
	char *current = next_word(f, s);
	for(int i = 0; current != NULL && i < acc->size; ++i) {
		int pl = -1;
		acc -> words[i] = extract_word(current, &pl);
		current = next_word(f, current + pl);
	}
	return acc;
}

