#ifndef CST_H
#define CST_H

#define READ_FILE  1
#define INVAL_CMD  2
#define MALLOC_ERR 3
#define NO_DEST    4
#define PAR_ACT    5
#define INVAL_TYPE 6
#define ALREADY_EX 7
#define PAR_DEST   8
#define ARG_ERR    9
#define EDIT_ROOT  666

#include <stdio.h>
#include "parser.h"

extern int fail;
extern void failure(int, char *);
extern void err_read_file();
extern void err_inval_cmd();
extern void err_malloc_error();
extern void err_no_dest();
extern void err_par_act();
extern void err_inval_type();
extern void err_already_exist();
extern void err_par_dest();
extern void err_arg_err();
extern void err_edit_root();
extern int get_fail();

#endif
