#ifndef __PLANTATION__H__
#define __PLANTATION__H__
typedef struct {
    int jour;
    int mois;
    int annee;
}DATE;
typedef struct {
    char ID[20];
    char Type[20] ;
    char Nom[20];
    char per_plant[20];
    DATE D_plant;
    DATE D_rec;
    char Ren[20];

}Gestion_PLant;
void afficher_type(char type[]);

/* --------------------------------------- */
void ajouter_plantation(Gestion_PLant P);
void afficher_plant(GtkWidget *liste);
void supprimer(char id[]);
void modifier(Gestion_PLant P);
void afficher_plantation(void);
int rechercher_id(char id[]);
int verif2Dates(DATE d1, DATE d2);
Gestion_PLant find_plant(char id[]);

/* --------------------------------------- */





#endif
