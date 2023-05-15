# C-filsystem

Un programme qui reproduit un terminal en C (seulement la gestion des fichiers et dossiers)



## Authors

- Victor Morel
- Ayman Khemakhem

## Installation

Vous devez avoir l'utilitaire `make` ainsi que `gcc`

```bash
  make build
  ./main <fichier d'instructions>
```
## Appendix

#### Limitations
- Une ligne fait au maximum 500 caractères

#### Ajouts
Nous avons décidé d'ajouter quelques fonctionnalités pour nous rapprocher le plus possible du comportement d'un vrai terminal. Elles sont listées ci-dessous:

- Les commandes `touch` et `mkdir` n'ont pas de limite d'arguments, par exemple la commande `mkdir bonjour a tous` créera trois dossier, "bonjour", "a", "tous".
- Nous avons autorisé l'utilisation du chemin "/" ainsi que l'utilisation de ".." en plein milieu d'un chemin
- Nous avons ajoutés un joli prompt comme si on était dans un véritable terminal
- La commande `ls` affiche d'un certaine couleur les fichiers et d'une autre les dossiers
- En cas d'erreur, aucune plus aucune commande n'est executée, la mémoire est vidée et un message d'erreur est imprimé dans `stderr` et un code erreur est retourné par le programme (voir `debug.h` pour les codes erreurs)

