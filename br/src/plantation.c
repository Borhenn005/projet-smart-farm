#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "plantation.h"

enum
{
	EID,
	ENOM,
	ETYPE,
	EPERIODE,
	EDATEP,
	EDATER,
	ECOLUMNS,
};


void ajouter_plantation(Gestion_PLant G)
{
    FILE *f;
    f = fopen("../DataBase/DATA_plant.txt","a");
    fprintf(f,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,G.D_plant.jour,G.D_plant.mois,G.D_plant.annee,G.D_rec.jour,G.D_rec.mois,G.D_rec.annee );
 
    fclose(f);

}
/*-----------------------------------------------------*/
void modifier(Gestion_PLant P)
{
    Gestion_PLant G ;
    FILE *f,*f_temp;
    f=fopen("../DataBase/DATA_plant.txt","r");
    f_temp=fopen("../DataBase/fichAux.txt","a");
    if((f != NULL)&&(f_temp != NULL)){
    while (fscanf(f,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,&G.D_plant.jour,&G.D_plant.mois,&G.D_plant.annee,&G.D_rec.jour,&G.D_rec.mois,&G.D_rec.annee)!=EOF)
    {
    if(strcmp(G.ID,P.ID)==0){

        G=P;

    }
    fprintf(f_temp,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,G.D_plant.jour,G.D_plant.mois,G.D_plant.annee,G.D_rec.jour,G.D_rec.mois,G.D_rec.annee );
    }
    fclose(f);
    fclose(f_temp);
    }
    remove("../DataBase/DATA_plant.txt");
    rename("../DataBase/fichAux.txt","../DataBase/DATA_plant.txt");
}
/*--------------------------------------------------------*/
void supprimer(char id[] ){
    Gestion_PLant G;
    FILE *f,*f_temp;
    f=fopen("../DataBase/DATA_plant.txt","r");
    f_temp=fopen("../DataBase/fichAux.txt","a");
    if((f != NULL)&&(f_temp != NULL)){
        while (fscanf(f,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,&G.D_plant.jour,&G.D_plant.mois,&G.D_plant.annee,&G.D_rec.jour,&G.D_rec.mois,&G.D_rec.annee)!=EOF){
        if(strcmp(G.ID,id)!=0){
            fprintf(f_temp,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,G.D_plant.jour,G.D_plant.mois,G.D_plant.annee,G.D_rec.jour,G.D_rec.mois,G.D_rec.annee);
        }
        
        }
        fclose(f);
        fclose(f_temp);
    }
        remove("../DataBase/DATA_plant.txt");
        rename("../DataBase/fichAux.txt","../DataBase/DATA_plant.txt");
}

/*----------------------------------------------------------*/
void afficher_plant(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter  iter;
    GtkListStore *store;
    Gestion_PLant G;
    FILE *f;
    char dc1[50],dc2[50];
    
    store=gtk_tree_view_get_model(liste);
    if(store==NULL)
    {
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("ID",renderer,"text",EID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	

     	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("TYPE",renderer,"text",ETYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("NOM",renderer,"text",ENOM,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Periode de Plantation",renderer,"text",EPERIODE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Date de Plantation",renderer,"text",EDATEP,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Date de Récolte",renderer,"text",EDATER,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 	
	
	store=gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);


    	f=fopen("../DataBase/DATA_plant.txt","r");
    	if(f!=NULL)
    	{

        	while (fscanf(f,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,&G.D_plant.jour,&G.D_plant.mois,&G.D_plant.annee,&G.D_rec.jour,&G.D_rec.mois,&G.D_rec.annee)!=EOF){
			sprintf(dc1,"%d/%d/%d",G.D_plant.jour,G.D_plant.mois,G.D_plant.annee);
			sprintf(dc2,"%d/%d/%d",G.D_rec.jour,G.D_rec.mois,G.D_rec.annee);
		
			
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,EID,G.ID,ETYPE,G.Type,ENOM,G.Nom,EPERIODE,G.per_plant,EDATEP,dc1,EDATER,dc2,-1);
		}
           
        	fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
       	}
    	else
       
	{
		return;
	}
   }
}
/*----------------------------------------------------------*/
int rechercher_id(char id[]){
    Gestion_PLant G;
    FILE *f;
    f = fopen("../DataBase/DATA_plant.txt","r");
    if(f != NULL){
	while (fscanf(f,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,&G.D_plant.jour,&G.D_plant.mois,&G.D_plant.annee,&G.D_rec.jour,&G.D_rec.mois,&G.D_rec.annee)!=EOF){
        if(strcmp(G.ID,id)==0){
            return 1;
        }
    }
}
	fclose(f);
    	return 0;
    

}

/*-------------------------------------*/

Gestion_PLant find_plant(char id[]){
    Gestion_PLant G;
    FILE *f;
    f = fopen("../DataBase/DATA_plant.txt","r");
    if(f != NULL){
    	while (fscanf(f,"%s %s %s %s %d %d %d %d %d %d\n",G.ID,G.Type,G.Nom,G.per_plant,&G.D_plant.jour,&G.D_plant.mois,&G.D_plant.annee,&G.D_rec.jour,&G.D_rec.mois,&G.D_rec.annee)!=EOF){
        	if(strcmp(G.ID,id) == 0){
       		     return G;
        	}
    	}
}
    fclose(f);
    return;
}


/*-------------------------------------*/
int verif2Dates(DATE d1, DATE d2){

    if(d1.annee < d2.annee){
        return 1;
    }
    else if(d1.annee == d2.annee){
        if(d1.mois < d2.mois){
            return 1;
        }
        else if(d1.mois == d2.mois){
            if(d1.jour >= d2.jour){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}
