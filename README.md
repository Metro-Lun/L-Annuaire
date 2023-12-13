# SAE S1.01 - BOURBON Mehdi, GUGLIELMETTO Jason - G4S1A
Ce dépôt contient les fichiers constituant notre SAÉ de C.

Il est retrouvable sur [la forge GitLab de l'IUT](https://forge.univ-lyon1.fr/p2205512/sae-s1.01_b.mehdi_g.jason).

## Sommaire
- [Description générale du projet](#description-générale-du-projet)
- [Pré-requis](#pré-requis)
- [Utilisation](#utilisation)
- [Auteurs du projet](#auteurs-du-projet)
- [Licence](#licence)

## Description générale du projet

Ce projet consiste en une application de gestion d'annuaires contenant des informations sur des clients d'une entreprise.
Ceci concerne la création d'un annuaire, sa modification, et sa sauvegarde.

Le projet a été codé en C sous Code::Blocks et respecte la norme C ANSI.

**ATTENTION :** lorsque le programme se termine lorsqu'il est lancé sur console, la fenêtre se ferme automatiquement. Il a donc été décidé de rajouter un temps d'attente d'environ 8 minutes à la fin du programme, et d'une minute en cas d'erreur et/ou d'abandon.

## Pré-requis

- Un ordinateur qui tourne (sous Windows de préférence)
- Le compilateur GNU GCC installé et placé dans le PATH si jamais vous souhaitez compiler en lignes de commande : [ce tutoriel](https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j) nous a permis de le faire
- L'IDE Code::Blocks (de préférence avec le compilateur pré-installé) pour ouvrir les fichiers code sous forme d'un projet global
- Les outils Doxygen et Graphviz paramétrés (optionnel)

## Utilisation

En dézippant l'archive, vous trouverez dans le répertoire de départ `sae-s1.01_b.mehdi_g.jason` deux raccourcis exécutables :

- `acces_documentation` qui ouvre une page web contenant la documentation de nos fonctions, faite avec Doxygen
- `acces_sae` qui lance l'application depuis le fichier `project/main.c`

C'est donc dans le répertoire de départ que les annuaires de sortie apparaîtront.

Vous trouverez également deux annuaires nous ayant permis de réaliser notre application.

Le 0 préfixant chaque fichier .bat sert à le retrouver plus facilement : ils se retrouvent en tête de liste dans le répertoire. Ainsi, pour lancer le programme, il suffit d'exécuter le second fichier.
Pour ouvrir le projet dans Code::Blocks, vous pouvez trouver les fichiers correspondants dans le répertoire `project`.

Pour éviter d'avoir à entrer un chemin relatif trop long vers votre annuaire, vous pouvez le placer dans le répertoire de départ.

**ATTENTION :** si vous lancez le projet depuis Code::Blocks, il faudra modifier les chemins relatifs des fichiers présents dans les assertions, ou bien changer les annuaires de répertoire.

__NB :__ si vous voulez compiler le programme à la main, il faudra exécuter cette commande :

```gcc -ansi -pedantic-errors -Wall -Werror project/*.c -o LE_NOM_DE_FICHIER_QUE_VOUS_SOUHAITEZ```

## Auteurs du projet

- Mehdi BOURBON - G4S1A
- Jason GUGLIELMETTO - G4S1A

__Note de Mehdi :__ Ayant configuré Git auparavant pour GitHub, et n'ayant rien modifié depuis, il m'arrive de push en tant que Metro-Lun, mais il s'agit bien de moi et pas d'une troisième personne.

## Licence

**GNU GPL 3.0**. Pour plus d'informations, consultez la [licence](LICENSE).
