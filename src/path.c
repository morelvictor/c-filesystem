
#include "path.h"

#include <assert.h>


void free_path(path *p) {
	free_index(p->elem);
	free(p);
}

node *pton(node *curr, path *p) {
	node *now = curr;
	if(p->type == ABS) {
		now = curr->root;
	}
	for(int i = 0; i < p->elem->size; ++i) {
		if((now = get_node(curr->children, p->elem->words[i])) == NULL)
			return NULL;
	}
	return now;
}

