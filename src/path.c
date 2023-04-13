
#include "path.h"

#include <assert.h>
#include "parser.h"


void free_path(path *p) {
	free_index(p->index);
	free(p);
}

node *pton(node *curr, path *p) {
	assert(p != NULL);
	node *now = curr;
	if(p->type == ABS) {
		now = curr->root;
	}
	for(int i = 0; i < p->index->size; ++i) {
		if((now = get_node(curr->children, p->index->words[i])) == NULL)
		return NULL;
	}
	free_path(p);
	return now;
}

path *cons_path(char *s) {
	path *acc = malloc(sizeof(path));
	acc->type = *s == '/' ? ABS: REL;
	acc->index = split_slash(s);
	return acc;
}
