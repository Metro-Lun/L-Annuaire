#pragma once
#include <stdio.h>
#define TAILLE_MAX 500

/** \file fonctions.h
* Ce fichier contient toutes les declarations des fonctions du projet. */

/* DEFINITION GLOBALE DE LA STRUCTURE */

/** Une ligne de l'annuaire. */
typedef struct {
    /** Nom du client */
    char* nom;
    /** Nom du client */
    char* prenom;
    /** Code postal du client */
    char* cp;
    /** Ville de residence du client */
    char* ville;
    /** Numero de telephone du client */
    char* tel;
    /** Adresse mail du client */
    char* mel;
    /** Metier/Profession du client */
    char* profession;
} ligne;

/* FONCTIONS DEMANDEES */

/** Fonction qui rajoute un client dans l'annuaire
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \param nom_p Nom du client
* \param prenom_p Prenom du client
* \param code_postal_p Code Postal du client
* \param ville_p Ville ou vit le client
* \param telephone_p Numero de telephone du client
* \param mel_p Adresse mail du client
* \param profession_p Metier pratique par le client */
void ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p); /* Jason GUGLIELMETTO */

/** Fonction qui cree un fichier texte contenant l'annuaire passe en parametre mais modifie sur une ligne.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \param mel_p Une adresse mail presente dans l'annuaire (celle a remplacer)
* \param nv_mel_p Une adresse mail qui remplacera celle du parametre precedent dans l'annuaire */
void modifier_mel_client(const char* nom_annuaire, const char* mel_p,const char* nv_mel_p); /* Mehdi BOURBON */

/** Fonction qui cree un fichier texte contenant l'annuaire passe en parametre mais modifie sur une ligne.
* La difference avec la fonction precedente est que celle-ci modifie une autre valeur que l'adresse mail.
*
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \param mel_p Une adresse mail presente dans l'annuaire (celle ou la valeur a remplacer se situe)
* \param nom_champ Nom du champ ou la valeur sera remplacee
* \param nv_valeur Valeur de remplacement */
void modifier_autres_que_mel_client(const char* nom_annuaire, const char* mel_p, const char* nom_champ,const char* nv_valeur); /* Mehdi BOURBON */

/** Fonction qui cree un fichier texte contenant l'annuaire passe en parametre mais avec un client en moins.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \param mel_p Une adresse mail presente dans l'annuaire correspondant au client a supprimer*/
void supprimer_client(const char* nom_annuaire, const char* mel_p); /* Jason GUGLIELMETTO */

/** Fonction qui cree un fichier texte contenant l'annuaire passe en parametre trie sur les noms.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse */
void trier_clients_par_nom(const char* nom_annuaire); /* Jason GUGLIELMETTO */

/** Fonction qui cree un fichier texte contenant les lignes de l'annuaire passe en parametre ou au moins un champ est vide.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse */
void filtrer_clients_donnees_manquantes(const char* nom_annuaire); /* Mehdi BOURBON */

/** Fonction qui cree un fichier texte contenant les lignes de l'annuaire remplissant une condition.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \param nom_champ Nom du champ concerne par la premiere chaine de caracteres
* \param val_chaine Chaine de caracteres faisant office de filtre */
void filtrer_un_champ(const char* nom_annuaire, const char* nom_champ, const char* val_chaine); /* Jason GUGLIELMETTO */

/** Fonction qui cree un fichier texte contenant les lignes de l'annuaire remplissant deux conditions.
* La difference avec la fonction precedente est que celle-ci possede deux contraintes au lieu d'une.
*
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \param nom_champ1 Nom du champ concerne par la premiere chaine de caracteres
* \param val_chaine1 Chaine de caracteres faisant office de filtre
* \param nom_champ1 Nom du champ concerne par la deuxieme chaine de caracteres
* \param val_chaine1 Chaine de caracteres faisant office de filtre */
void filtrer_combiner_deux_champs(const char* nom_annuaire, const char* nom_champ1, const char* val_chaine1, const char* nom_champ2, const char* val_chaine2); /* Mehdi BOURBON */

/* FONCTIONS SUPPLEMENTAIRES */

/** Fonction qui charge l'annuaire dans un tableau de lignes.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse */
ligne* charger_annuaire(const char* nom_annuaire);       /* Mehdi BOURBON */

/** Fonction qui compte le nombre de lignes d'un annuaire.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \retval cpt Entier egal au nombre de lignes de l'annuaire */
int compter_lignes_annuaire(const char* nom_annuaire);   /* Mehdi BOURBON */

/** Fonction qui verifie si un annuaire est valide.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \retval code Entier code de retour : 0 si aucun probleme, 1 si doublon de mails, 2 si mail manquant, 3 si les deux conditions precedentes sont reunies, -1 si erreur de chargement. */
int verifier_validite(const char* nom_annuaire); /* Mehdi BOURBON */

/** Fonction qui se charge de vider les champs de l'annuaire passe en parametre
* qui ne sont composes que d'espace ou de tabulations.
* \param ann Annuaire deja charge sous forme d'un tableau de lignes
* \param taille_annuaire La taille de l'annuaire en question
* \retval ann Le meme annuaire, mais les champs remplis uniquement d'espaces ou de tabulations sont vides */
ligne* retirer_trous(ligne* ann, int taille_annuaire); /* Mehdi BOURBON */

/** Fonction qui compte le nombre de lignes d'un annuaire.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse
* \retval cpt Entier egal au nombre de lignes de l'annuaire */
void rendre_valide(const char* nom_annuaire); /* Mehdi BOURBON */

/** Fonction qui affiche un annuaire dans la console.
* \param nom_annuaire Nom du fichier contenant l'annuaire, extension incluse */
void afficher_annuaire(const char* nom_annuaire);/* Jason GUGLIELMETTO */

/** Fonction qui cree un fichier ou l'on doit ajouter au fur et a mesure les informations des clients*/
void ecrire_nv_annuaire();  /* Jason GUGLIELMETTO */
