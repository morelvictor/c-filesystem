#ifndef PATH_H
#define PATH_H

#include "parser.h"
#include "node.h"

struct path {
	enum { ABS, REL } type;
	w_index *elem;
};

typedef struct path path;


extern void free_path(path *);

/**
 * Convert a path to a node if it exists
 * Exit if the desired path doesn't exist
 */
extern node *pton(node *, path *);

#endif
