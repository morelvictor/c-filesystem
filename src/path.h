
#ifndef PATH_H
#define PATH_H

#include "parser.h"
#include "node.h"

struct path {
	enum { ABS, REL } type;
	w_index elem;
};

typedef struct path path;


node *pton(node *, path *);

#endif
