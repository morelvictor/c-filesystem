
#include "debug.h"

int fail = EXIT_SUCCESS;

void failure(int ret_code, char *msg) {
	fail = ret_code;
	fprintf(stderr, "\nError: %s\n", msg);
}

void err_read_file() {
	failure(READ_FILE, "Impossible de lire le fichier source");
}

void err_inval_cmd() {
	failure(INVAL_CMD, "Commande inconnue au bataillon");
}

void err_malloc_error() {
	failure(MALLOC_ERR, "Malloc error");
}

void err_no_dest() {
	failure(NO_DEST, "Fichier de destination inexistant");
}

void err_par_act() {
	failure(PAR_ACT, "La cible est un parent du noeud actuel");
}

void err_inval_type() {
	failure(INVAL_TYPE, "Type de noeud invalide");
}
void err_already_exist() {
	failure(ALREADY_EX, "Chemin déjà existant, choisissez un autre nom");
}

void err_par_dest() {
	failure(PAR_DEST, "La cible est un parent de la destination, c'est un problème");
}

void err_arg_err() {
	failure(ARG_ERR, "Mauvais nombre d'arguments dans la commande");
}

void err_edit_root() {
	failure(EDIT_ROOT, "Vous essayez de modifier la racine, c'est très grave");
}

int get_fail() {
	return fail;
}

