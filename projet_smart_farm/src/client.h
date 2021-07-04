#ifndef __CLIENT__H__
#define __CLIENT__H__
typedef struct{
    int j;
    int m;
    int a;
}Date;
typedef struct{
    char id[10];
    char nom[30];
    char prenom[30];
    char email[30];
    char adresse[30];
    char num[30];
    Date dateNaissance;
    char ville[20];
}Client;

typedef struct
{
  int anne;
  float moy,somm;
}ct;
int anneseche();
/*--------------------- CRUD -------------------*/
void afficher_clients(GtkWidget *liste);
void ajouter_client(Client c);
void supprimer_client(char id[]);
int verif_client(char id[]);
void modifier_client(Client c);
int idExiste(char id[]);
int verifNameCl(char c[]);
int verifier_date(int j,int m,int a);
Client find_client(char id[]);
int verifNumCl(char c[]);

#endif

