
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
		if(!strcmp(p->index->words[i], ".."))
			now = now->father;
		else if((now = get_node(now->children, p->index->words[i])) == NULL)
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

path *cons_papa(path *p) {
  w_index *i = sub_index(p->index, 0, p->index->size-1);
  path *acc = malloc(sizeof(path));
  acc->index = i;
  acc->type = p->type;
  return acc;
}
