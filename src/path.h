#ifndef PATH_H
#define PATH_H

#include "parser.h"
#include "node.h"

#include <assert.h>
#include "parser.h"

struct path {
	enum { ABS, REL } type;
	w_index *index;
};

typedef struct path path;
typedef struct node node;

extern void free_path(path *);

/**
 * Convert a path to a node if it exists
 * Exit if the desired path doesn't exist
 */
extern node *pton(node *, path *);
extern path *cons_path(char *);
extern path *cons_papa(path *);

#endif
