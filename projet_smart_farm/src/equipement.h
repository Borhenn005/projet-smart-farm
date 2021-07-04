#ifndef __EQUIPEMENT__H__
#define __EQUIPEMENT__H__
#include "ouvrier.h"
typedef struct{
    char id[20];
    char nom[20];
    char marque[20];
    char modele[20];
    char serial[30];
    char emplacement[30];
    date dernierVerif;


}equipement;



void ajouter_equipemenet(equipement e);
void modifier_equipement(equipement e);
void supprimer_equipement(char id[]);
void afficher_equipement(GtkWidget *liste);
/*
void temperature_to_alarmante(capteur c);
void valeur_alarmante(GtkWidget *liste);
*/
int idEquipExiste(char id[]);
equipement find_equip(char id[]);
#endif
