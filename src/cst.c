
#include "cst.h"

bool fail = false;

void failure() {
	fail = true;
}

bool get_fail() {
	return fail;
}

