#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>


struct w_index {
	size_t size;
	char **words;
};

typedef struct w_index w_index;

extern void free_index(w_index *);
extern void print_index(w_index *);
extern w_index *cons_index(int (*)(int), char *);
extern w_index *split_space(char *);
extern w_index *splut_slash(char *);

#endif
