#ifndef __OUVRIER__H__
#define __OUVRIER__H__
typedef struct{
    int j;
    int m;
    int a;
}date;
typedef struct{
    char id[20];
    char nom[30];
    char prenom[30];
    char cin[20];
    date dateNaiss;
    date DateRec;
    char mode_emploi[20];
    float salaire;
    char genre[20];
    char num_tel[20];
}Ouvrier;

/*---------------------------------------------*/
void ajouter_ouvrier(Ouvrier o);
void supprimer_ouvrier(char cin[]);
void modifier_ouvrier(Ouvrier o);
void afficher_ouvrier(GtkWidget *liste);
/*-----------------------------------------------------*/


/*---------------------------------------------*/
int rechercher_ouv(char id[]);
Ouvrier find_ouv(char id[]);
void bestOuv(char id[],int year);
/*---------------------------------------------*/



/*-------------------- Taux d'absentéisme ----------------------*/
double calcul_taux(int m,int a);
void ajout_presence(char id[],int j,int m,int a,int e);



/*----------------  CONTROLE DE SAISIE ---------------*/
/*-------------------------------------*/
int verifDate(date d);
int verifNum(char c[]);
int verifName(char c[]);
int verifSal(char s[]);
/*-------------------------------------*/

#endif
