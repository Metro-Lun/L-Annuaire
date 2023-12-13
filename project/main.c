#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <windows.h> /* pour la fonction Sleep()*/

/** \file main.c */

/** Fonction principale. */
int main()
{
    char quit;                                                                                      /* variable servant à quitter à la fin */
    char demande[TAILLE_MAX];                                                                       /* variable servant à se déplacer dans les IF */
    char nomfichier[TAILLE_MAX];                                                                    /* variable commune */
    char nom_p[TAILLE_MAX],prenom_p[TAILLE_MAX],code_postal_p[TAILLE_MAX],ville_p[TAILLE_MAX];      /* variable principalement utilise par la fonction ajouter client */
    char telephone_p[TAILLE_MAX],mel_p[TAILLE_MAX],profession_p[TAILLE_MAX];                        /* variable principalement utilise par la fonction ajouter client */
    char champ1[TAILLE_MAX],val1[TAILLE_MAX],champ2[TAILLE_MAX],val2[TAILLE_MAX];                   /* variable principalement utilise par la fonction filtrer combiner 2 champs */
    char nv_mel_p[TAILLE_MAX],nom_champ[TAILLE_MAX],nv_valeur[TAILLE_MAX];                          /* variable principalement utilise par la fonction modification de données */
    FILE* contenu;

    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nBienvenue ! Cette application vous permet de gerer des annuaires.\n");
    printf("Vous pouvez creer de nouveaux annuaires ou bien en modifier d'autres deja existants.\n");
    printf("Il est possible de filtrer des donnees, de supprimer ou d'ajouter des lignes, mais egalement\n");
    printf("de trier des annuaires et bien sur, de les afficher.\n");

    choix:
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nQue souhaitez-vous faire ?\n");
    printf("1: Creer un annuaire\n");
    printf("2: Modifier un annuaire\n");
    printf("autre: Quitter le programme.\n");
    fgets(demande,TAILLE_MAX,stdin);
    demande[strcspn(demande,"\n")] = '\0';

    if(strcmp(demande,"1") == 0){
        printf("\nDebut de la creation de votre nouvel annuaire...\n");
        Sleep(1000);
        ecrire_nv_annuaire();
        printf("\nVotre nouvel annuaire vient d'etre cree ! : \n");

    } else if(strcmp(demande,"2")==0){
        goto fichier;

    } else {
        goto fin;
    }

    fichier:
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nVeuillez entrer le nom du fichier a modifier avec son extension. Taper Q pour quitter. : ");
    fgets(nomfichier,TAILLE_MAX,stdin);
    nomfichier[strcspn(nomfichier,"\n")] = '\0';
     if(!strcmp(nomfichier,"q") || !strcmp(nomfichier,"Q")) {
        goto fin;
    }

    contenu = fopen(nomfichier,"r");
    if(contenu == NULL){
        fclose(contenu);
        printf("\n\nERREUR : Le fichier precise n'existe pas !\n\n");
        goto fichier;
    } else {
        fclose(contenu); }

    opt:
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nA quelles options souhaitez-vous acceder ?\n");
    printf("1: Options de filtrage\n");
    printf("2: Options de modification\n");
    printf("3: Autres options (affichage d'annuaire, comptage de lignes)\n");
    printf("4: Changer d'annuaire\n");
    printf("5: Retourner en arriere\n");
    printf("autre: Quitter le programme.\n");
    fgets(demande,TAILLE_MAX,stdin);
    demande[strcspn(demande,"\n")] = '\0';

    if(strcmp(demande,"1")==0){
        goto fltr;
    } else if(strcmp(demande,"2")==0){
        goto mdf;
    } else if(strcmp(demande,"3")==0){
        goto atr;
    } else if(strcmp(demande,"4")==0){
        goto fichier;
    } else if(strcmp(demande,"5")==0){
        goto choix;
    } else {
        goto fin;  }

    fltr:
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nOptions de filtrage :\n");
    printf("1: Filtrer les clients avec des donnees manquantes\n");
    printf("2: Filtrer l'annuaire selon un champ\n");
    printf("3: Filtrer l'annuaire selon deux champs combines\n");
    printf("4: Retourner en arriere\n");
    printf("autre: Quitter le programme.\n");
    fgets(demande,TAILLE_MAX,stdin);
    demande[strcspn(demande,"\n")] = '\0';

    if(strcmp(demande,"1")==0){
        filtrer_clients_donnees_manquantes(nomfichier);
    } else if(strcmp(demande,"2")==0){
        /* le champ passé en paramètre doit être un champ de l'annuaire */
        do {
            printf("\nSur quel champ doit s'effectuer la recherche ? (nom,prenom,cp,ville,tel,mel,profession) : ");
            fgets(champ1,TAILLE_MAX,stdin);
            champ1[strcspn(champ1,"\n")] = '\0';
        }while(strcmp(champ1,"nom") && strcmp(champ1,"prenom") && strcmp(champ1,"cp") && strcmp(champ1,"ville") && strcmp(champ1,"tel") && strcmp(champ1,"mel") && strcmp(champ1,"profession"));

        /* la chaîne ne doit pas être vide */
        do {
            printf("\nQuelle valeur doit contenir ce champ ? : ");
            fgets(val1,TAILLE_MAX,stdin);
            val1[strcspn(val1,"\n")] = '\0';
        } while(!strlen(val1));

        filtrer_un_champ(nomfichier,champ1,val1);

    } else if(strcmp(demande,"3")==0){
        /* le champ passé en paramètre doit être un champ de l'annuaire */
        do {
            printf("\nSur quel premier champ doit s'effectuer la recherche ? (nom,prenom,cp,ville,tel,mel,profession) : ");
            fgets(champ1,TAILLE_MAX,stdin);
            champ1[strcspn(champ1,"\n")] = '\0';
        }while(strcmp(champ1,"nom") && strcmp(champ1,"prenom") && strcmp(champ1,"cp") && strcmp(champ1,"ville") && strcmp(champ1,"tel") && strcmp(champ1,"mel") && strcmp(champ1,"profession"));

        /* la chaîne ne doit pas être vide */
        do {
            printf("\nQuelle valeur doit contenir ce champ ? : ");
            fgets(val1,TAILLE_MAX,stdin);
            val1[strcspn(val1,"\n")] = '\0';
        }while(!strlen(val1));

        /* les deux champs passés en paramètre ne doivent pas être identiques */
        do {
            printf("\nSur quel champ filtrer en simultane ? (nom,prenom,cp,ville,tel,mel,profession) : ");
            fgets(champ2,TAILLE_MAX,stdin);
            champ2[strcspn(champ2,"\n")] = '\0';
        }while((strcmp(champ2,"nom") && strcmp(champ2,"prenom") && strcmp(champ2,"cp") && strcmp(champ2,"ville") && strcmp(champ2,"tel") && strcmp(champ2,"mel") && strcmp(champ2,"profession")) || !strcmp(champ1,champ2));

        /* la chaîne ne doit pas être vide */
        do {
            printf("\nQuelle valeur doit contenir ce champ ? : ");
            fgets(val2,TAILLE_MAX,stdin);
            val2[strcspn(val2,"\n")] = '\0';
        }while(!strlen(val2));

        filtrer_combiner_deux_champs(nomfichier, champ1, val1, champ2, val2);

    } else if(strcmp(demande,"4")==0){
        Sleep(1000);
        goto opt;

    } else {
        Sleep(1000);
        goto fin;
    }
    printf("\nC'est pret ! Consultez le repertoire de l'application.\n");
    Sleep(1000);
    goto fltr;

    mdf:
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nOptions de modification :\n");
    printf("1: Ajouter un client a l'annuaire\n");
    printf("2: Modifier d'autres donnees que le mail du client\n");
    printf("3: Modifier le mail d'un client de l'annuaire\n");
    printf("4: Supprimer un client de l'annuaire\n");
    printf("5: Trier l'annuaire par nom de client\n");
    printf("6: Retourner en arriere\n");
    printf("autre: Quitter le programme\n");
    fgets(demande,TAILLE_MAX,stdin);
    demande[strcspn(demande,"\n")] = '\0';

    if(strcmp(demande,"1")==0){
        printf("Veuillez donner le nom du client a inserer: ");
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

        ajouter_client(nomfichier,nom_p,prenom_p,code_postal_p,ville_p,telephone_p,mel_p,profession_p);

    } else if(strcmp(demande,"2")==0){
        /* la chaîne ne doit pas être vide */
        do {
            printf("\nVeuillez inscrire le mail du client dont les donnees sont a changer : ");
            fgets(mel_p,TAILLE_MAX,stdin);
            mel_p[strcspn(mel_p,"\n")] = '\0';
        } while(!strlen(mel_p));

        /* le champ passé en paramètre doit être un champ de l'annuaire */
        do {
            printf("\nSur quel premier champ doit s'effectuer la recherche ? (nom,prenom,cp,ville,tel,mel,profession) : ");
            fgets(nom_champ,TAILLE_MAX,stdin);
            nom_champ[strcspn(nom_champ,"\n")] = '\0';
        }while(strcmp(nom_champ,"nom") && strcmp(nom_champ,"prenom") && strcmp(nom_champ,"cp") && strcmp(nom_champ,"ville") && strcmp(nom_champ,"tel") && strcmp(nom_champ,"mel") && strcmp(nom_champ,"profession"));

        /* la chaîne ne doit pas être vide */
        do {
        printf("\nEcrire la nouvelle information : ");
        fgets(nv_valeur,TAILLE_MAX,stdin);
        nv_valeur[strcspn(nv_valeur,"\n")] = '\0';
        } while(!strlen(nv_valeur));

        modifier_autres_que_mel_client(nomfichier, mel_p, nom_champ, nv_valeur);

    } else if(strcmp(demande,"3")==0){
        /* la chaîne ne doit pas être vide */
        do {
            printf("\nInscrire le mail a remplacer : ");
            fgets(mel_p,TAILLE_MAX,stdin);
            mel_p[strcspn(mel_p,"\n")] = '\0';
        }while(!strlen(mel_p));

        /* la chaîne ne doit pas être vide */
        do {
            printf("\nInscrire le nouveau mail : ");
            fgets(nv_mel_p,TAILLE_MAX,stdin);
            nv_mel_p[strcspn(nv_mel_p,"\n")] = '\0';
        }while(!strlen(nv_mel_p));

        modifier_mel_client(nomfichier, mel_p, nv_mel_p);

    } else if(strcmp(demande,"4")==0){
        /* la chaîne ne doit pas être vide */
        do {
            printf("\nInscrire le mail du client a retirer :\n");
            fgets(mel_p,TAILLE_MAX,stdin);
            mel_p[strcspn(mel_p,"\n")] = '\0';
        } while(!strlen(mel_p));

        supprimer_client(nomfichier, mel_p);

    } else if(strcmp(demande,"5")==0){
        trier_clients_par_nom(nomfichier);

    } else if(strcmp(demande,"6")==0){
        Sleep(1000);
        goto opt;

    } else {
        Sleep(1000);
        goto fin;
    }
    Sleep(1000);
    goto mdf;

    atr:
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nAutres options :\n");
    printf("1: Afficher l'annuaire.\n");
    printf("2: Compter les lignes dans l'annuaire.\n");
    printf("3: Retour arriere.\n");
    printf("autre: Quitter le programme.\n");
    fgets(demande,TAILLE_MAX,stdin);
    demande[strcspn(demande,"\n")] = '\0';

    if(strcmp(demande,"1")==0){
        printf("Voici les donnees de l'annuaire :\n\n");
        afficher_annuaire(nomfichier);
    } else if(strcmp(demande,"2")==0){
        /* si lancé avec Code::Blocks, le chemin relatif de ces deux fichiers est à modifier */
        assert(compter_lignes_annuaire("fa.csv") == 7);
        assert(compter_lignes_annuaire("annuaire.csv") == 600);
        printf("\nLe fichier contient %d lignes.", compter_lignes_annuaire(nomfichier));
    } else if(strcmp(demande,"3")==0){
        Sleep(1000);
        goto opt;
    } else {
        Sleep(1000);
        goto fin;
    }
    Sleep(1000);
    goto atr;

    fin:
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("\nVous voici arrive a la fin du programme.");
    printf("\nPour quitter, tapez Q. : ");

    while(quit != 'Q' && quit != 'q') {
        scanf("%1c",&quit);
    }

    printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");
    printf("Sortie du programme...");
    printf("\n\n-----------------------------------------------------------------------------------------------------------------------\n");
    Sleep(4000);
    return 0;
}
