#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "equipement.h"

enum{
    EID,
    ENOM,
    EMARQUE,
    EMODEL,
    ESERIAL,
    EEMPLACEMENT,
    EDERNIERVERIF,
    ECOLUMNS,

};
/*----------------------------------------------------------------*/


void ajouter_equipemenet(equipement e){
    FILE *f;
    f = fopen("../DataBase/equipement.txt","a");
    fprintf(f,"%s %s %s %s %s %s %d/%d/%d\n",e.id,e.nom,e.marque,e.modele,e.serial,e.emplacement,e.dernierVerif.j,e.dernierVerif.m,e.dernierVerif.a);    
    fclose(f);
}


/*----------------------------------------------------------------*/


void modifier_equipement(equipement y){
    equipement e;
    FILE *f;
    FILE *g;
    f = fopen("../DataBase/equipement.txt","r");
    g = fopen("../DataBase/tmp.txt","a");
    while(fscanf(f,"%s %s %s %s %s %s %d/%d/%d\n",e.id,e.nom,e.marque,e.modele,e.serial,e.emplacement,&e.dernierVerif.j,&e.dernierVerif.m,&e.dernierVerif.a)!= EOF){
        if(strcmp(e.id,y.id) == 0){
            e = y;
        }
        fprintf(g,"%s %s %s %s %s %s %d/%d/%d\n",e.id,e.nom,e.marque,e.modele,e.serial,e.emplacement,e.dernierVerif.j,e.dernierVerif.m,e.dernierVerif.a);

    }
    fclose(f);
    fclose(g);
    remove("../DataBase/equipement.txt");
    rename("../DataBase/tmp.txt","../DataBase/equipement.txt");
}

/*----------------------------------------------------------------*/


void supprimer_equipement(char id[]){
    equipement e;
    FILE *f;
    FILE *g;
    f = fopen("../DataBase/equipement.txt","r");
    g = fopen("../DataBase/tmp.txt","a");
    while(fscanf(f,"%s %s %s %s %s %s %d/%d/%d\n",e.id,e.nom,e.marque,e.modele,e.serial,e.emplacement,&e.dernierVerif.j,&e.dernierVerif.m,&e.dernierVerif.a)!= EOF){
        if(strcmp(e.id,id) != 0){
            fprintf(g,"%s %s %s %s %s %s %d/%d/%d\n",e.id,e.nom,e.marque,e.modele,e.serial,e.emplacement,e.dernierVerif.j,e.dernierVerif.m,e.dernierVerif.a);
        }
    }
    fclose(f);
    fclose(g);
    remove("../DataBase/equipement.txt");
    rename("../DataBase/tmp.txt","../DataBase/equipement.txt");
}


/*----------------------------------------------------------------*/

void afficher_equipement(GtkWidget *liste){
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    
    char id[20];
    char nom[30];
    char marque[20];
    char model[20];
    char serial[30];
    char emplacement[30];
    date dernierVerif;
    char datee[50];
    FILE *f;
    store = NULL;
    store = gtk_tree_view_get_model(liste);

    if(store == NULL){
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" ID ",renderer,"text",EID,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Nom ",renderer,"text",ENOM,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Marque ",renderer,"text",EMARQUE,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Model ",renderer,"text",EMODEL,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Serial ",renderer,"text",ESERIAL,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Emplacement ",renderer,"text",EEMPLACEMENT,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Derniére Verification ",renderer,"text",EDERNIERVERIF,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

    }
	store = gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    
    
    	f = fopen("../DataBase/equipement.txt","r");
	if(f == NULL){
        	return;
    	}
	else{
        	while(fscanf(f,"%s %s %s %s %s %s %d/%d/%d\n",id,nom,marque,model,serial,emplacement,&dernierVerif.j,&dernierVerif.m,&dernierVerif.a)!= EOF){   
			sprintf(datee,"%d/%d/%d",dernierVerif.j,dernierVerif.m,dernierVerif.a);      		
			gtk_list_store_append(store,&iter);
            		gtk_list_store_set(store,&iter,EID,id,ENOM,nom,EMARQUE,marque,EMODEL,model,ESERIAL,serial,EEMPLACEMENT,emplacement,EDERNIERVERIF,datee,-1);
            		
        	}
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
        	fclose(f);
    	}
							
    
}


/*----------------------------------------------------------------*/

int idEquipExiste(char id[]){
  equipement e;
  FILE *f;
f=fopen("../DataBase/equipement.txt","r");
  if(f != NULL ){
	while(fscanf(f,"%s %s %s %s %s %s %d/%d/%d\n",e.id,e.nom,e.marque,e.modele,e.serial,e.emplacement,&e.dernierVerif.j,&e.dernierVerif.m,&e.dernierVerif.a)!= EOF){
      	if(strcmp(e.id,id) == 0){
        	return 1;
      	}
  	}
  }
fclose(f);
  return 0;

}

/*----------------------------------------------------------------*/

equipement find_equip(char id[]){
	equipement e;
  	FILE *f;
	f=fopen("../DataBase/equipement.txt","r");
  	if(f != NULL ){
	while(fscanf(f,"%s %s %s %s %s %s %d/%d/%d\n",e.id,e.nom,e.marque,e.modele,e.serial,e.emplacement,&e.dernierVerif.j,&e.dernierVerif.m,&e.dernierVerif.a)!= EOF){
      	if(strcmp(e.id,id) == 0){
        	return e;
      	}
  	}
  }
fclose(f);
  return ;

}

/*----------------------------------------------------------------*/
/*-----------------------------------------*/
/*
//fonction.c
void temperature_to_alarmante(capteur c)
{
FILE *f, *g;
f=fopen("temperature.txt","r");
g=fopen("alarmante.txt","w");
if(f==NULL||g==NULL)
{
	return;
}
else{
	while(fscanf(f,"%d %s %d %d %d %f\n",&(c.id),c.marque,&(c.jour),&(c.mois),&(c.annee),&(c.valeur))!=EOF)
	{
		if(c.valeur>40||c.valeur<0)
			fprintf(g,"%d %s %d %d %d %.2f\n",c.id,c.marque,c.jour,c.mois,c.annee,c.valeur);
	}
	fclose(f);
	fclose(g);
}
}

void valeur_alarmante(GtkWidget *liste)
{
capteur c;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;

FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID", renderer,"text",ID, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Marque", renderer,"text",MARQUE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Jour", renderer,"text",JOUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Mois", renderer,"text",MOIS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Annee", renderer,"text",ANNEE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Valeur", renderer,"text",VALEUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

store=gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_FLOAT);
f=fopen("alarmante.txt","r");
if(f==NULL)
{
	return;
}
else

{f = fopen("alarmante.txt","a+");
while(fscanf(f,"%d %s %d %d %d %f\n",&(c.id),c.marque,&(c.jour),&(c.mois),&(c.annee),&(c.valeur))!=EOF)
{
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,ID,(c.id),MARQUE,c.marque,JOUR,c.jour,MOIS,c.mois,ANNEE,c.annee,VALEUR,c.valeur,-1);
}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
}*/
