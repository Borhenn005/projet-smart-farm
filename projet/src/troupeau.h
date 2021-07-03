#ifndef TROUPEAU_H_INCLUDED
#define TROUPEAU_H_INCLUDED
#include <gtk/gtk.h>
#include <time.h>
#include "plantation.h"
typedef struct
{
    char name[30];
    char type[30];
    char genre[30];
    char id[30];
    DATE birth;


}troupeau;
//struct tm date;
void modifierTrou(char idf0[],troupeau nov);
void ajouter(troupeau p);
void affichage(GtkWidget *liste);
void supprimerTrou(troupeau tab[],int n,char value[],int *kappa);
int idmodifier(char idf0[]);
int alpha(char mot[]);
int maj(char mot[]);
void nombre(int *b,int *v,int *t);
void filtre();
void affichage1(GtkWidget *liste);
void affichage2(GtkWidget *liste);
int accepte(int j,int m, int a,struct tm date );
int verif(int j,int m, int a, struct tm date);



#endif // TROUPEAU_H_INCLUDED
