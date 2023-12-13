#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

/** \file fonctions.c
* Ce fichier contient toutes les definitions des fonctions du projet. */

/* FONCTIONS DEMANDEES */

void ajouter_client(const char* nom_annuaire,const char* nom_p,const char* prenom_p,const char* code_postal_p,const char* ville_p,const char* telephone_p,const char* mel_p,const char* profession_p){

    ligne* ann;
    int i, taille_annuaire;
    FILE* resultat;

    /* à faire au début de toutes les fonctions, pour éviter de propager les erreurs */
    rendre_valide(nom_annuaire);

    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    resultat = fopen("resultat_ajouter_client.txt","w");

    /* si il y a une erreur avec le fichier de sortie, on le supprime et on quitte */
    if(resultat == NULL){
        fclose(resultat);
        remove("resultat_ajouter_client.txt");
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE);
    }

    for(i=0;i<taille_annuaire;i++)
    {
        fprintf(resultat, "%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }
        /* on ajoute le dernier client à la fin */
        fprintf(resultat, "%s,%s,%s,%s,%s,%s,%s",nom_p,prenom_p,code_postal_p,ville_p,telephone_p,mel_p,profession_p);

    free(ann);
    fclose(resultat);
}

void modifier_mel_client(const char* nom_annuaire, const char* mel_p, const char* nv_mel_p) {

    ligne* ann;
    int i, occ=0, taille_annuaire;

    FILE* resultat;

    rendre_valide(nom_annuaire);

    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    /* on gère les erreurs de champ vide*/
    if(!strlen(mel_p)){
        printf("\n\nERREUR : le mail à remplacer n'est pas precise !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }
    if(!strlen(nv_mel_p)){
        printf("\n\nERREUR : le mail à inserer n'est pas precise !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }

    resultat = fopen("resultat_modifier_mel.txt", "w");
    if(resultat == NULL){
        fclose(resultat);
        remove("resultat_modifier_mel.txt");
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE);
    }

    for(i=0;i<taille_annuaire;i++){

        /* on vérifie si le main qu'on veut insérer est déjà présent : on évite donc un doublon */
        if(!strcmp(ann[i].mel,nv_mel_p)){
           printf("\n\nERREUR : Le mail a inserer est deja present dans l'annuaire !\n\n");
           Sleep(60000);
           exit(EXIT_FAILURE);
        }

        /* on a trouvé le mail à remplacer */
        if(!strcmp(ann[i].mel,mel_p)) {
            fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,nv_mel_p,ann[i].profession);
            occ++;               /* occ vaudra à la fin le nombre de remplacements de mail, c'est-à-dire les occurrences de mel_p.
                                    si à la fin occ vaut 0 c'est que mel_p n'existait pas.*/
        } else {
            /* on ne l'a pas trouvé */
            fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
        }

        /* on libère tous les pointeurs pour chaque ligne */
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }

    /* si mel_p a été remplacé 0 fois c'est qu'il n'était pas présent dans l'annuaire */
    if(!occ){
        printf("\n\nERREUR : le mail a remplacer n'apparait pas une seule fois dans l'annuaire !\n\n");
        fclose(resultat);
        remove("resultat_modifier_mel.txt");
        Sleep(60000);
        exit(EXIT_FAILURE);
    }

    fclose(resultat);

    /* maintenant qu'on a libéré tous les sous-pointeurs, on libère le gros */
    free(ann);
}

void modifier_autres_que_mel_client(const char* nom_annuaire, const char* mel_p, const char* nom_champ,const char* nv_valeur){

    ligne* ann;
    int i, occ=0, taille_annuaire;

    FILE* resultat;

    rendre_valide(nom_annuaire);

    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    resultat = fopen("resultat_modifier_autres_que_mel.txt", "w");
    if(resultat == NULL){
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        fclose(resultat);
        remove("resultat_modifier_autres_que_mel.txt");
        Sleep(60000);
        exit(EXIT_FAILURE);  }

    if(!strlen(mel_p)){
        printf("\n\nERREUR : le mail à remplacer n'est pas precise !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }

    if(!strlen(nv_valeur)){
        printf("\n\nERREUR : le mail à inserer n'est pas precise !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }

    for(i=0;i<taille_annuaire;i++){

        if(!strcmp(ann[i].mel,mel_p)) {
            if(!strcmp(nom_champ,"nom")) {
            fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",nv_valeur,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
            } else if(!strcmp(nom_champ,"prenom")) {
                fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,nv_valeur,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
            } else if(!strcmp(nom_champ,"cp")) {
                fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,nv_valeur,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
            } else if(!strcmp(nom_champ,"ville")) {
                fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,nv_valeur,nv_valeur,ann[i].tel,ann[i].mel,ann[i].profession);
            } else if(!strcmp(nom_champ,"tel")) {
                fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,nv_valeur,ann[i].ville,nv_valeur,ann[i].mel,ann[i].profession);
            } else if(!strcmp(nom_champ,"profession")) {
                fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,nv_valeur,ann[i].ville,ann[i].tel,ann[i].mel,nv_valeur);
            } else {
                printf("\n\nERREUR : le nom de champ indique ne correspond pas a un champ de l'annuaire.\n\n");
                exit(EXIT_FAILURE);
            }
            occ++;

        } else {
            fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
        }
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }

    /* si aucune occurrence du mail, on ne peut rien faire */
    if(!occ){
        printf("\n\nERREUR : le mail a remplacer n'apparait pas une seule fois dans l'annuaire !\n\n");
        fclose(resultat);
        remove("resultat_modifier_autres_que_mel.txt");
        Sleep(60000);
        exit(EXIT_FAILURE);
    }

    fclose(resultat);
    free(ann);
}

void supprimer_client(const char* nom_annuaire, const char* mel_p){

    ligne* ann;
    int i, taille_annuaire;

    FILE* resultat;

    rendre_valide(nom_annuaire);

    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    resultat = fopen("resultat_supprimer_client.txt", "w");
    if(resultat == NULL){
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        fclose(resultat);
        remove("resultat_supprimer_client.txt");
        Sleep(60000);
        exit(EXIT_FAILURE);  }

    if(!strlen(mel_p)){
        printf("\n\nERREUR : le mail du client n'est pas precise !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }

    for(i=0;i<taille_annuaire; i++)
        {
            if(strcmp(ann[i].mel,mel_p)){
                fprintf(resultat, "%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
            }
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
        }
    free(ann);
    fclose(resultat);
}

void trier_clients_par_nom(const char* nom_annuaire){

    ligne* ann;
    ligne tmp;
    int n, i=0, ecart, j;

    FILE* resultat;

    rendre_valide(nom_annuaire);

    ann = charger_annuaire(nom_annuaire);
    n = compter_lignes_annuaire(nom_annuaire);
    ecart = n-1;
    j = ecart;

    resultat = fopen("resultat_trier_par_nom.txt","w");
    if(resultat == NULL){
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        fclose(resultat);
        remove("resultat_trier_par_nom.txt");
        Sleep(60000);
        exit(EXIT_FAILURE);  }

    while(j < n){
        if(strcmp(ann[i].nom, ann[j].nom) > 0){     /* si i > j alors on inverse les lignes */
            tmp = ann[i];
            ann[i] = ann[j];
            ann[j] = tmp;
        }
        i++;
        j++;
        if((j == n)&&(ecart != 0)){
            ecart--;
            j = ecart;
            i = 0;
        }
    }

    for(i = 0; i < n; i++){
        fprintf(resultat, "%s,%s,%s,%s,%s,%s,%s\n", ann[i].nom, ann[i].prenom, ann[i].cp, ann[i].ville, ann[i].tel, ann[i].mel, ann[i].profession);
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }

    free(ann);
    fclose(resultat);
}

void filtrer_clients_donnees_manquantes(const char* nom_annuaire) {

    ligne* ann;
    int i, taille_annuaire;

    FILE* resultat;

    rendre_valide(nom_annuaire);

    resultat = fopen("filtrer_clients_donnees_manquantes.txt","w");
    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    for(i=0;i<taille_annuaire;i++){
        if(!strcmp(ann[i].nom, "") || !strcmp(ann[i].prenom, "") || !strcmp(ann[i].cp, "") || !strcmp(ann[i].ville, "") || !strcmp(ann[i].tel, "") || !strcmp(ann[i].mel, "") || !strcmp(ann[i].profession, "")) {
            fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
        }
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }

    fclose(resultat);
    free(ann);
}

void filtrer_un_champ(const char* nom_annuaire, const char* nom_champ, const char* val_chaine) {

    ligne* ann;
    int i, j, taille_annuaire, cptval, valid;

    FILE* resultat;

    rendre_valide(nom_annuaire);

    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    if(!strlen(val_chaine)){
        printf("\n\nERREUR : il manque la valeur de recherche !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }

    resultat = fopen("resultat_filtrer_un_champ.txt", "w");
    if(resultat == NULL){
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        fclose(resultat);
        remove("resultat_filtrer_un_champ.txt");
        Sleep(60000);
        exit(EXIT_FAILURE);  }

    for(i=0;i<taille_annuaire;i++){

        valid = 0;
        cptval = 0;

        if(!strcmp(nom_champ,"nom")) {
            for(j=0;j<strlen(ann[i].nom);j++) {
                if(ann[i].nom[j] == val_chaine[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine)) {
                   valid = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ,"prenom")) {
            for(j=0;j<strlen(ann[i].prenom);j++) {
                if(ann[i].prenom[j] == val_chaine[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine)) {
                   valid = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ,"cp")) {
            for(j=0;j<strlen(ann[i].cp);j++) {
                if(ann[i].cp[j] == val_chaine[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine)) {
                   valid = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ,"ville")) {
            for(j=0;j<strlen(ann[i].ville);j++) {
                if(ann[i].ville[j] == val_chaine[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine)) {
                   valid = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ,"tel")) {
            for(j=0;j<strlen(ann[i].tel);j++) {
                if(ann[i].tel[j] == val_chaine[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine)) {
                   valid = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ,"mel")) {
            for(j=0;j<strlen(ann[i].mel);j++) {
                if(ann[i].mel[j] == val_chaine[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine)) {
                   valid = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ,"profession")) {
            for(j=0;j<strlen(ann[i].profession);j++) {
                if(ann[i].profession[j] == val_chaine[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine)) {
                   valid = 1;
                   break; }
            }
        } else {
            printf("\n\nERREUR : le nom de champ indique ne correspond pas a un champ de l'annuaire.\n\n");
            fclose(resultat);
            remove("resultat_filtrer_un_champ.txt");
            Sleep(60000);
            exit(EXIT_FAILURE);
        }

        if(valid == 1) fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }

    fclose(resultat);
    free(ann);
}

void filtrer_combiner_deux_champs(const char* nom_annuaire, const char* nom_champ1, const char* val_chaine1, const char* nom_champ2, const char* val_chaine2) {

    ligne* ann;
    int i, j, taille_annuaire, cptval, valid1, valid2;

    FILE* resultat;

    rendre_valide(nom_annuaire);

    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    if(!strlen(val_chaine1) || !strlen(val_chaine2)){
        printf("\n\nERREUR : il manque soit une soit deux valeurs de recherche !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }

    if(!strcmp(nom_champ1,nom_champ2)){
        printf("\n\nERREUR : les deux champs de recherche sont identiques !\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE); }

    resultat = fopen("resultat_filtrer_combiner_deux_champs.txt", "w");
    if(resultat == NULL){
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        fclose(resultat);
        remove("resultat_filtrer_combiner_deux_champs.txt");
        Sleep(60000);
        exit(EXIT_FAILURE);  }

    for(i=0;i<taille_annuaire;i++){

        valid1 = 0;
        valid2 = 0;
        cptval = 0;

        if(!strcmp(nom_champ1,"nom")) {
            for(j=0;j<strlen(ann[i].nom);j++) {
                if(ann[i].nom[j] == val_chaine1[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }

                if(cptval == strlen(val_chaine1)) {
                   valid1 = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ1,"prenom")) {
            for(j=0;j<strlen(ann[i].prenom);j++) {
                if(ann[i].prenom[j] == val_chaine1[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }

                if(cptval == strlen(val_chaine1)) {
                   valid1 = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ1,"cp")) {
            for(j=0;j<strlen(ann[i].cp);j++) {
                if(ann[i].cp[j] == val_chaine1[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine1)) {
                   valid1 = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ1,"ville")) {
            for(j=0;j<strlen(ann[i].ville);j++) {
                if(ann[i].ville[j] == val_chaine1[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }
                if(cptval == strlen(val_chaine1)) {
                   valid1 = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ1,"tel")) {
            for(j=0;j<strlen(ann[i].tel);j++) {
                if(ann[i].tel[j] == val_chaine1[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }

                if(cptval == strlen(val_chaine1)) {
                   valid1 = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ1,"mel")) {
            for(j=0;j<strlen(ann[i].mel);j++) {
                if(ann[i].mel[j] == val_chaine1[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }

                if(cptval == strlen(val_chaine1)) {
                   valid1 = 1;
                   break; }
            }
        } else if(!strcmp(nom_champ1,"profession")) {
            for(j=0;j<strlen(ann[i].profession);j++) {
                if(ann[i].profession[j] == val_chaine1[j]) {
                    cptval += 1;
                } else {
                    cptval = 0; }

                if(cptval == strlen(val_chaine1)) {
                   valid1 = 1;
                   break; }
            }
        } else {
            printf("\n\nERREUR : le premier nom de champ indique ne correspond pas a un champ de l'annuaire.\n\n");
            fclose(resultat);
            remove("resultat_filtrer_combiner_deux_champs.txt");
            Sleep(60000);
            exit(EXIT_FAILURE);
        }


        if(valid1 == 1) {
            if(!strcmp(nom_champ2,"nom")) {
                for(j=0;j<strlen(ann[i].nom);j++) {
                    if(ann[i].nom[j] == val_chaine2[j]) {
                        cptval += 1;
                    } else {
                        cptval = 0; }

                    if(cptval == strlen(val_chaine2)) {
                       valid2 = 1;
                       break; }
                }
            } else if(!strcmp(nom_champ2,"prenom") || !strcmp(nom_champ2,"prénom")) {
                for(j=0;j<strlen(ann[i].prenom);j++) {
                    if(ann[i].prenom[j] == val_chaine2[j]) {
                        cptval += 1;
                    } else {
                        cptval = 0; }

                    if(cptval == strlen(val_chaine2)) {
                       valid2 = 1;
                       break; }
                }
            } else if(!strcmp(nom_champ2,"cp")) {
                for(j=0;j<strlen(ann[i].cp);j++) {
                    if(ann[i].cp[j] == val_chaine2[j]) {
                        cptval += 1;
                    } else {
                        cptval = 0; }
                    if(cptval == strlen(val_chaine2)) {
                       valid2 = 1;
                       break; }
                }
            } else if(!strcmp(nom_champ2,"ville")) {
                for(j=0;j<strlen(ann[i].ville);j++) {
                    if(ann[i].ville[j] == val_chaine2[j]) {
                        cptval += 1;
                    } else {
                        cptval = 0; }
                    if(cptval == strlen(val_chaine2)) {
                       valid2 = 1;
                       break; }
                }
            } else if(!strcmp(nom_champ1,"tel")) {
                for(j=0;j<strlen(ann[i].tel);j++) {
                    if(ann[i].tel[j] == val_chaine2[j]) {
                        cptval += 1;
                    } else {
                        cptval = 0; }

                    if(cptval == strlen(val_chaine2)) {
                       valid2 = 1;
                       break; }
                }
            } else if(!strcmp(nom_champ2,"mel")) {
                for(j=0;j<strlen(ann[i].mel);j++) {
                    if(ann[i].mel[j] == val_chaine2[j]) {
                        cptval += 1;
                    } else {
                        cptval = 0; }

                    if(cptval == strlen(val_chaine2)) {
                       valid2 = 1;
                       break; }
                }
            } else if(!strcmp(nom_champ2,"profession")) {
                for(j=0;j<strlen(ann[i].profession);j++) {
                    if(ann[i].profession[j] == val_chaine2[j]) {
                        cptval += 1;
                    } else {
                        cptval = 0; }

                    if(cptval == strlen(val_chaine2)) {
                       valid2 = 1;
                       break; }
                }
            } else {
                printf("\n\nERREUR : le deuxieme nom de champ indique ne correspond pas a un champ de l'annuaire.\n\n");
                fclose(resultat);
                remove("resultat_filtrer_combiner_deux_champs.txt");
                Sleep(60000);
                exit(EXIT_FAILURE);
            }

        /* condition 1 validée et pas la 2 -> on regarde directement la ligne suivante */
        } else {
            continue;
        }

        if(valid1 == 1 && valid2 == 1) fprintf(resultat,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);

        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }

    fclose(resultat);
    free(ann);
}

/* FONCTIONS SUPPLEMENTAIRES */

ligne* charger_annuaire(const char * nom_annuaire) {

    int i=0, car=2, j, len=0, cpt = compter_lignes_annuaire(nom_annuaire); /* car est un int, il faut lire EOF (0 ou 1) */
    ligne* annuaire = (ligne*) calloc(cpt, sizeof(ligne));

    /* chaîne de caractères temporaire pour stocker les champs */
    char tmp[TAILLE_MAX];

    FILE* contenu;
    contenu = fopen(nom_annuaire,"r");

    while(!feof(contenu)) {

        annuaire = (ligne*) realloc(annuaire,(i+1)*sizeof(ligne));

        len = 0;
        for(j=0;;j++){
            car = fgetc(contenu);
            if(car == ',' || car == '\n' || car == EOF) break;
            len++;
            tmp[j] = (char) car;  }

        /* on alloue len+1 cases, dont une pour le '\0' */
        annuaire[i].nom = calloc(len+1, sizeof(char));

        /* on insère les éléments du string temporaire dans le pointeur final */
        for(j=0;j<len;j++) {
            annuaire[i].nom[j] = tmp[j];
        }
        /* en faisant attention au '\0' ! */
        annuaire[i].nom[len] = '\0';

        /* on recommence pour chaque champ en réutilisant le temporaire */
        len = 0;
        for(j=0;;j++){
            car = fgetc(contenu);
            if(car == ',' || car == '\n' || car == EOF) break;
            len++;
            tmp[j] = (char) car;  }

        annuaire[i].prenom = calloc(len+1, sizeof(char));

        for(j=0;j<len;j++) {
            annuaire[i].prenom[j] = tmp[j];
        }
        annuaire[i].prenom[len] = '\0';

        len = 0;
        for(j=0;;j++){
            car = fgetc(contenu);
            if(car == ',' || car == '\n' || car == EOF) break;
            len++;
            tmp[j] = (char) car;  }

        annuaire[i].cp = calloc(len+1, sizeof(char));

        for(j=0;j<len;j++) {
            annuaire[i].cp[j] = tmp[j];
        }
        annuaire[i].cp[len] = '\0';

        len = 0;
        for(j=0;;j++){
            car = fgetc(contenu);
            if(car == ',' || car == '\n' || car == EOF) break;
            len++;
            tmp[j] = (char) car;  }

        annuaire[i].ville = calloc(len+1, sizeof(char));

        for(j=0;j<len;j++) {
            annuaire[i].ville[j] = tmp[j];
        }
        annuaire[i].ville[len] = '\0';

        len = 0;
        for(j=0;;j++){
            car = fgetc(contenu);
            if(car == ',' || car == '\n' || car == EOF) break;
            len++;
            tmp[j] = (char) car;  }

        annuaire[i].tel = calloc(len+1, sizeof(char));

        for(j=0;j<len;j++) {
            annuaire[i].tel[j] = tmp[j];
        }
        annuaire[i].tel[len] = '\0';

        len = 0;
        for(j=0;;j++){
            car = fgetc(contenu);
            if(car == ',' || car == '\n' || car == EOF) break;
            len++;
            tmp[j] = (char) car;  }

        annuaire[i].mel = calloc(len+1, sizeof(char));

        for(j=0;j<len;j++) {
            annuaire[i].mel[j] = tmp[j];
        }
        annuaire[i].mel[len] = '\0';

        len = 0;
        for(j=0;;j++){
            car = fgetc(contenu);
            if(car == ',' || car == '\n' || car == EOF) break;
            len++;
            tmp[j] = (char) car;  }

        annuaire[i].profession = calloc(len+1, sizeof(char));

        for(j=0;j<len;j++) {
            annuaire[i].profession[j] = tmp[j];
        }
        annuaire[i].profession[len] = '\0';

        i++;

    }

    fclose(contenu);
    return annuaire;
}

void afficher_annuaire(const char* nom_annuaire) {

    ligne* ann;
    int i, taille_annuaire;
    ann = charger_annuaire(nom_annuaire);
    taille_annuaire = compter_lignes_annuaire(nom_annuaire);

    for(i=0;i<taille_annuaire;i++) {
        printf("%s - %s - %s - %s - %s - %s - %s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }

    free(ann);
}

int compter_lignes_annuaire(const char* nom_annuaire) {

    int cpt=0;
    char car=2;

    FILE* contenu;
    contenu = fopen(nom_annuaire,"r");

    while(!feof(contenu)) {
        car = fgetc(contenu);
        if(car == '\n' || car == EOF) cpt++;
    }

    fclose(contenu);

    /* l'annuaire se termine par un \n */
    return cpt-1;
}

int verifier_validite(const char* nom_annuaire) {

    ligne* ann = charger_annuaire(nom_annuaire);
    int taille_annuaire = compter_lignes_annuaire(nom_annuaire), i, j, code = 0;
    if(ann == NULL) {
        printf("\n\nERREUR de chargement ! \n\n");
        return -1;
    }

    /* verifier que deux adresses mail sont identiques */
    for(i=0;i<taille_annuaire;i++) {
        for(j=0;j<taille_annuaire;j++) {
            if(i != j && !strcmp(ann[i].mel,ann[j].mel)) {
                code = 1;
                break;
            }
        }
        if(code == 1) break;
    }

    /* verifier qu'un champ adresse mail est vide */
    for(i=0;i<taille_annuaire;i++) {
        if(!strlen(ann[i].mel)) {
            if(code == 1) {
                code = 3;
            } else if(code == 0) {
                code = 2;
            }
        }
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].mel);
        free(ann[i].profession);
    }
    free(ann);
    return code;
}

ligne* retirer_trous(ligne* ann, int taille_annuaire) {

    int i, j, esp;

    for(i=0;i<taille_annuaire;i++) {
        for(j=0;j<strlen(ann[i].nom);j++) {
            /* si espace ou tabulation alors true sinon false */
            if(ann[i].nom[j] == ' ' || ann[i].nom[j] == '\t') {
                esp = 1;
            } else {
                esp = 0;
                break;
            }
        }
        if(esp == 1) {
            /* on reparcourt le champ et on le vide */
            for(j=0;j<strlen(ann[i].nom);j++) {
                ann[i].nom[j] = '\0';
            }
        }

        /* on recommence avec tous les autres champs */
        for(j=0;j<strlen(ann[i].prenom);j++) {
            if(ann[i].prenom[j] == ' ' || ann[i].prenom[j] == '\t') {
                esp = 1;
            } else {
                esp = 0;
                break;
            }
        }
        if(esp == 1) {
            for(j=0;j<strlen(ann[i].prenom);j++) {
                ann[i].prenom[j] = '\0';
            }
        }

        for(j=0;j<strlen(ann[i].cp);j++) {
            if(ann[i].cp[j] == ' ' || ann[i].cp[j] == '\t') {
                esp = 1;
            } else {
                esp = 0;
                break;
            }
        }
        if(esp == 1) {
            for(j=0;j<strlen(ann[i].cp);j++) {
                ann[i].cp[j] = '\0';
            }
        }

        for(j=0;j<strlen(ann[i].ville);j++) {
            if(ann[i].ville[j] == ' ' || ann[i].ville[j] == '\t') {
                esp = 1;
            } else {
                esp = 0;
                break;
            }
        }
        if(esp == 1) {
            for(j=0;j<strlen(ann[i].ville);j++) {
                ann[i].ville[j] = '\0';
            }
        }

        for(j=0;j<strlen(ann[i].tel);j++) {
            if(ann[i].tel[j] == ' ' || ann[i].tel[j] == '\t') {
                esp = 1;
            } else {
                esp = 0;
                break;
            }
        }
        if(esp == 1) {
            for(j=0;j<strlen(ann[i].tel);j++) {
                ann[i].tel[j] = '\0';
            }
        }

        for(j=0;j<strlen(ann[i].mel);j++) {
            if(ann[i].mel[j] == ' ' || ann[i].mel[j] == '\t') {
                esp = 1;
            } else {
                esp = 0;
                break;
            }
        }
        if(esp == 1) {
            for(j=0;j<strlen(ann[i].mel);j++) {
                ann[i].mel[j] = '\0';
            }
        }

        for(j=0;j<strlen(ann[i].profession);j++) {
            if(ann[i].profession[j] == ' ' || ann[i].profession[j] == '\t') {
                esp = 1;
            } else {
                esp = 0;
                break;
            }
        }
        if(esp == 1) {
            for(j=0;j<strlen(ann[i].profession);j++) {
                ann[i].profession[j] = '\0';
            }
        }
    }

    return ann;
}

void rendre_valide(const char* nom_annuaire) {

    ligne* ann;
    int code, cpt, i, j;
    FILE* nv;

    ann = charger_annuaire(nom_annuaire);
    cpt = compter_lignes_annuaire(nom_annuaire);
    ann = retirer_trous(ann,cpt);

    /* si ouvert avec Code::Blocks, chemins relatifs à modifier */
    assert(verifier_validite("fa.csv") == 0);
    assert(verifier_validite("annuaire.csv") == 1);

    code = verifier_validite(nom_annuaire);

    nv = fopen(nom_annuaire,"w");
    if(nv == NULL){
        fclose(nv);
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        Sleep(60000);
        exit(EXIT_FAILURE);  }

    switch(code) {
        case 0 : break;
        case 1 :
            for(i=0;i<cpt;i++) {
                for(j=0;j<cpt;j++) {
                    if(i != j && !strcmp(ann[i].mel,ann[j].mel)) {
                        if(i < j && strcmp(ann[j].mel,"XXXX")) {
                            ann[j].mel = "XXXX";
                        }
                    }
                }
            }
            break;
        case 2 :
            for(i=0;i<cpt;i++) {
                if(!strlen(ann[i].mel)) {
                    ann[i].mel = "XXXX";
                }
            }
            break;
        case 3 :
            for(i=0;i<cpt;i++) {
                for(j=0;j<cpt;j++) {
                    if(i != j && (!strcmp(ann[i].mel,ann[j].mel))) {
                        if(i < j && strcmp(ann[j].mel,"XXXX")) {
                            ann[j].mel = "XXXX";  }
                    }
                }
            }

            for(i=0;i<cpt;i++) {
                if(!strlen(ann[i].mel)) {
                    ann[i].mel = "XXXX";
                }
            }
            break;
        default :
            printf("\n\nERREUR PROGRAMME : operation abandonnee\n\n");
            Sleep(60000);
            exit(EXIT_FAILURE);
    }

    for(i=0;i<cpt;i++) {
        if(strcmp(ann[i].mel,"XXXX") != 0) fprintf(nv,"%s,%s,%s,%s,%s,%s,%s\n",ann[i].nom,ann[i].prenom,ann[i].cp,ann[i].ville,ann[i].tel,ann[i].mel,ann[i].profession);
        free(ann[i].nom);
        free(ann[i].prenom);
        free(ann[i].cp);
        free(ann[i].ville);
        free(ann[i].tel);
        free(ann[i].profession);
    }

    free(ann);
    fclose(nv);
}

void ecrire_nv_annuaire(){
    char nom_p[TAILLE_MAX], prenom_p[TAILLE_MAX], code_postal_p[TAILLE_MAX], ville_p[TAILLE_MAX], telephone_p[TAILLE_MAX], mel_p[TAILLE_MAX], profession_p[TAILLE_MAX];
    int choix;

    FILE* resultat;
    resultat = fopen("nv_annuaire.csv","w");
    if(resultat == NULL){
        perror("\n\nERREUR FICHIER : operation abandonnee\n\n");
        fclose(resultat);
        remove("nv_annuaire.csv");
        Sleep(60000);
        exit(EXIT_FAILURE);  }

    debut:
        printf("\nInsertion d'un nouveau client :\n");

        printf("\nVeuillez donner le nom du client a inserer: ");
        fgets(nom_p,TAILLE_MAX,stdin);
        nom_p[strcspn(nom_p,"\n")] = '\0';

        printf("Veuillez donner son prenom : ");
        fgets(prenom_p,TAILLE_MAX,stdin);
        prenom_p[strcspn(prenom_p,"\n")] = '\0';

        printf("Veuillez donner le code postal de la ville ou il habite : ");
        fgets(code_postal_p,TAILLE_MAX,stdin);
        code_postal_p[strcspn(code_postal_p,"\n")] = '\0';

        printf("Veuillez donner sa ville de residence : ");
        fgets(ville_p,TAILLE_MAX,stdin);
        ville_p[strcspn(ville_p,"\n")] = '\0';

        printf("Veuillez donner son numero de telephone (avec de preference les champs separes par un point) : ");
        fgets(telephone_p,TAILLE_MAX,stdin);
        telephone_p[strcspn(telephone_p,"\n")] = '\0';

        printf("Veuillez donner son adresse mel : ");
        fgets(mel_p,TAILLE_MAX,stdin);
        mel_p[strcspn(mel_p,"\n")] = '\0';

        printf("Veuillez donner sa profession : ");
        fgets(profession_p,TAILLE_MAX,stdin);
        profession_p[strcspn(profession_p,"\n")] = '\0';

        fprintf(resultat, "%s,%s,%s,%s,%s,%s,%s\n", nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);

        printf("\nLe client a ete ajoute a l'annuaire.\nVoulez-vous ajouter un autre client? \n1: oui \nautre: non\n");
        scanf("%d",&choix);
        if (choix == 1) goto debut;

        fclose(resultat);

        rendre_valide("nv_annuaire.csv");
}
