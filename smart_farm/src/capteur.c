#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "capteur.h"
#include <time.h>
#include <gtk/gtk.h>

enum
{
	EValeur,
	EEtat,
	ENomdecapteur,
	EReference,
	Eservice,
	EPrix,
	Edate,
	ECOLUMNS,
};
enum
{
	EDEF,
	ENOMBRE,
	COLUMNS
};

enum{
	VALEUR,
	NOM,
	REF,
	JOUR,
	MOIS,
	ANNEE,
	EECOLUMNS
};
void afficher_capteur(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char Valeur[20];
	char Nomdecapteur[20];
	char Reference[20]; 
	char service[20];
	char Prix[20];
	char Etat[20];
	int jourofcapteur;
	int moisofcapteur;
	int anneeofcapteur;
	store=NULL;
	FILE *f;
	
	store = gtk_tree_view_get_model(liste);

	if(store==NULL){
	renderer=gtk_cell_renderer_text_new();
   	column=gtk_tree_view_column_new_with_attributes("Marque",renderer,"text",ENomdecapteur,NULL);
   	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer=gtk_cell_renderer_text_new();
   	column=gtk_tree_view_column_new_with_attributes("Reference",renderer,"text",EReference,NULL);
   	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("service",renderer,"text",Eservice,NULL);
   	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer=gtk_cell_renderer_text_new();
   	column=gtk_tree_view_column_new_with_attributes("Prix",renderer,"text",EPrix,NULL);
   	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",EValeur,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Etat",renderer,"text",EEtat,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);




	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Date d'ajout",renderer,"text",Edate,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	store = gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    
	char text[50];
	f=fopen("../DataBase/capteur.txt","r");
 if(f!=NULL)
        {
	
         while(fscanf(f,"%s %s %s %s %s %s %d %d %d\n",Valeur,Nomdecapteur,Reference,service,Prix,Etat,&jourofcapteur,&moisofcapteur,&anneeofcapteur)!=EOF)
          {
	sprintf(text,"%d/%d/%d",jourofcapteur,moisofcapteur,anneeofcapteur);
		
           gtk_list_store_append(store,&iter);
           gtk_list_store_set(store,&iter,ENomdecapteur,Nomdecapteur,EReference,Reference,Eservice,service,EPrix,Prix,EEtat,Etat,EValeur,Valeur,Edate,text,-1);
          
        }
   fclose(f);
   gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
   g_object_unref(store);  
   }
}
}



void ajouter_capteur(capteur c){
    FILE *f;
    f=fopen("../DataBase/capteur.txt","a");
    if(f!=NULL){
        fprintf(f,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,c.jourofcapteur,c.moisofcapteur,c.anneeofcapteur);
    }
        fclose(f);
}

void modifier_capteur(capteur p){
    capteur c;
    FILE *f;
    FILE *g;
    f = fopen("../DataBase/capteur.txt","r");
    g = fopen("../DataBase/tmp.txt","a");
    while(fscanf(f,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,&c.jourofcapteur,&c.moisofcapteur,&c.anneeofcapteur) != EOF){
        if(strcmp(c.Reference,p.Reference) == 0){
            c = p;
        }
        fprintf(g,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,c.jourofcapteur,c.moisofcapteur,c.anneeofcapteur);
        
    }
    fclose(f);
    fclose(g);
    remove("../DataBase/capteur.txt");
    rename("../DataBase/tmp.txt","../DataBase/capteur.txt");
}

void supprimer_capteur(char ref[]){   
    capteur c;

    FILE *f1;
    FILE *f2;
    f1 = fopen("../DataBase/capteur.txt","r");
    f2 = fopen("../DataBase/tmp.txt","a");
    while(fscanf(f1,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,&c.jourofcapteur,&c.moisofcapteur,&c.anneeofcapteur)!=EOF){
        if(strcmp(c.Reference,ref)!=0){
            fprintf(f2,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,c.jourofcapteur,c.moisofcapteur,c.anneeofcapteur);
        }
    }
    fclose(f1);
    fclose(f2);
    remove("../DataBase/capteur.txt");
    rename("../DataBase/tmp.txt","../DataBase/capteur.txt");
    
}


int RefExist(char Reference[]){
    capteur c;
    FILE *f;
    f = fopen("../DataBase/capteur.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,&c.jourofcapteur,&c.moisofcapteur,&c.anneeofcapteur)!=EOF){
        	if(strcmp(c.Reference,Reference) == 0){
       		     return 1;
        	}
    	}
}
    fclose(f);
    return 0;
    

}

capteur find_cap(char ref[]){
    capteur c;
    FILE *f;
    f = fopen("../DataBase/capteur.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,&c.jourofcapteur,&c.moisofcapteur,&c.anneeofcapteur)!=EOF){
	if(strcmp(c.Reference,ref) == 0){
       		return c;    
        }
       		     
       }
}

    fclose(f);
    return ;
}

/*-----------------------------------------*/

int verifPrix(char s[]){
    if(strlen(s) == 0){
        return 0;
    }
    else{
        int i,x;
        for(i=0;i<strlen(s);i++){
            x = s[i];
            if(x<48 || x >57){
                
                    return 0;
                
            }
        }
        return 1;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void defectuex()
{

    defect tab1[100];

    FILE *f,*d,*o;
    char mar[30];
    capteur c;
    int v,i=-1,max,min,k,ver,j,maxi=-1;
    f=fopen("../DataBase/capteur.txt","r");
    while(fscanf(f,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,&c.jourofcapteur,&c.moisofcapteur,&c.anneeofcapteur)!=EOF)
    {
          //  printf("service %s \n",c.service);
            v=(int)atoll(c.Valeur);
            //printf("%d\n",v);
            ver=0;
            if(strcmp(c.service,"Temperature")==0)
            {
                max=150;
                min=-55;
            }
            if(strcmp(c.service,"Humidite")==0)
            {
                max=80;
                min=-10;
            }




            //printf("max min %d %d \n",max,min);
            if((v<min)||(v>max)){

                if(i==-1)
                {
                    i=0;
                    strcpy(tab1[i].marquedef,c.Reference);
                    tab1[i].nombre=1;
                    ++i;
                }
                else
                {
                    for(k=0;k<=i;k++)
                    {
                        if(strcmp(tab1[k].marquedef,c.Reference)==0)
                        {
                            tab1[k].nombre+=1;
                            ver=1;
                        }
                    }
                    if(ver!=1)
                    {
                        strcpy(tab1[i].marquedef,c.Reference);
                        tab1[i].nombre=1;
                        ++i;

                    }
                }



            }








    }
    fclose(f);
    char y[30];
    int vari;
    for(j=0;j<i;j++)
    {
        for(k=j+1;k<i;k++)
        {
            if(tab1[k].nombre<tab1[j].nombre)
            {
                strcpy(y,tab1[j].marquedef);
                vari=tab1[j].nombre;
                strcpy(tab1[j].marquedef,tab1[k].marquedef);
                tab1[j].nombre=tab1[k].nombre;
                strcpy(tab1[k].marquedef,y);
                tab1[k].nombre=vari;


            }
        }
    }
    d=fopen("../DataBase/capteurdef.txt","a");
    for(j=i-1;j>=0;j--)
    {
        fprintf(d,"%s %d\n",tab1[j].marquedef,tab1[j].nombre);
    }
    fclose(d);


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficherdef(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter  iter;
    GtkListStore *store;
    defect d;
    char chd[30];
    FILE *f;
    store=gtk_tree_view_get_model(liste);
    if(store==NULL)
    {
     	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("LES MARQUES DES CAPTEURS DEFECTUEX ",renderer,"text",EDEF,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" NOMBRE  ",renderer,"text",ENOMBRE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	
 	
	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING);

    	f=fopen("../DataBase/capteurdef.txt","r");
    	if(f!=NULL)
    	{

        	while(fscanf(f,"%s %d\n",d.marquedef,&d.nombre)!=EOF)
        	{
			sprintf(chd,"%d",d.nombre);
			
		
			
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,EDEF,d.marquedef,ENOMBRE,chd,-1);
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


/*----------------------------------------------------------------------------------------*/
void capteur_alarmante(void)
{
FILE *f, *g;
capteur c;
int val;
f=fopen("../DataBase/capteur.txt","r");
g=fopen("../DataBase/alarmante.txt","a");
if(f==NULL||g==NULL)
{
	return;
}
else{
	while(fscanf(f,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,&(c.jourofcapteur),&(c.moisofcapteur),&(c.anneeofcapteur))!=EOF)
	{
		val = (int) atoll(c.Valeur);
		if(val>40||val<0)
			fprintf(g,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,c.jourofcapteur,c.moisofcapteur,c.anneeofcapteur);
	}
	fclose(f);
	fclose(g);
}
}

/*--------------------------------------------------------------------------------------*/

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
	column=gtk_tree_view_column_new_with_attributes(" Valeur", renderer,"text",VALEUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Nomdecapteur", renderer,"text",NOM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Reference", renderer,"text",REF, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	/*renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Service", renderer,"text",SER, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Prix", renderer,"text",PRIX, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);*/

        renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Jour", renderer,"text",JOUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
     renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Mois", renderer,"text",MOIS, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
     renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Année", renderer,"text",ANNEE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);




store=gtk_list_store_new(EECOLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
f=fopen("../DataBase/alarmante.txt","r");
if(f==NULL)
{
	return;
}
else

{f = fopen("../DataBase/alarmante.txt","a+");
while(fscanf(f,"%s %s %s %s %s %s %d %d %d\n",c.Valeur,c.Nomdecapteur,c.Reference,c.service,c.Prix,c.Etat,&(c.jourofcapteur),&(c.moisofcapteur),&(c.anneeofcapteur))!=EOF)
{
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,VALEUR,c.Valeur,NOM,c.Nomdecapteur,REF,c.Reference,JOUR,c.jourofcapteur,MOIS,c.moisofcapteur,ANNEE,c.anneeofcapteur,-1);
}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
}




