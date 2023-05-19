#ifndef EXEC_H
#define EXEC_H

#include "node.h"
#include "parser.h"
#include "debug.h"

extern void executor(node **n, w_index *i);

/*extern void ls(node **);
extern void cd(node **, w_index *);
extern void pwd(node **);
extern void pwd_in_line(node **);
extern void mkdir(node **, w_index *);
extern void touch(node **, w_index *);
extern void rm(node **, w_index *);
extern void cp(node **, w_index *);
extern void mv(node **, w_index *);
extern void print(node *);
*/
#endif
