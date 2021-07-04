#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "client.h"

enum
{
  EID,
  EFIRSTNAME,
  ELASTNAME,
  EDATEN,
  EEMAIL,
  EADRESS,
  ECITY,
  ENUM,
  ECOLUMNS,
};
/*----------------------------------------------------------------*/
void ajouter_client(Client c){

FILE *f;
f=fopen("../DataBase/Clients.txt","a+");

if(f!=NULL){
   fprintf(f,"%s %s %s %d %d %d %s %s %s %s\n",c.id,c.nom,c.prenom,c.dateNaissance.j,c.dateNaissance.m,c.dateNaissance.a,c.email,c.adresse,c.ville,c.num);
   }
fclose(f);
}

/*---------------------------------------------------------------------*/

void supprimer_client(char id[])
{
Client c;
char id1[10];
char username[30],password[30];
FILE *f,*g;
f=fopen("../DataBase/Clients.txt","r");
g=fopen("../DataBase/tmp.txt","a+");

while(fscanf(f,"%s %s %s %d %d %d %s %s %s %s\n",c.id,c.nom,c.prenom,&c.dateNaissance.j,&c.dateNaissance.m,&c.dateNaissance.a,c.email,c.adresse,c.ville,c.num)!=EOF){
     if(strcmp(id,c.id)!=0){
        fprintf(g,"%s %s %s %d %d %d %s %s %s %s\n",c.id,c.nom,c.prenom,c.dateNaissance.j,c.dateNaissance.m,c.dateNaissance.a,c.email,c.adresse,c.ville,c.num);
      } 
   }

fclose(f);
fclose(g);
remove("../DataBase/Clients.txt");
rename("../DataBase/tmp.txt","../DataBase/Clients.txt");
}

/*---------------------------------------------------------------------*/

void modifier_client(Client c)
{
Client y;
FILE *f,*g;
f=fopen("../DataBase/Clients.txt","r");
g=fopen("../DataBase/tmp.txt","a+");
while(fscanf(f,"%s %s %s %d %d %d %s %s %s %s\n",y.id,y.nom,y.prenom,&y.dateNaissance.j,&y.dateNaissance.m,&y.dateNaissance.a,y.email,y.adresse,y.ville,y.num)!=EOF){
  if(strcmp(c.id,y.id)==0){
       y=c;
    } 
    fprintf(g,"%s %s %s %d %d %d %s %s %s %s\n",y.id,y.nom,y.prenom,y.dateNaissance.j,y.dateNaissance.m,y.dateNaissance.a,y.email,y.adresse,y.ville,y.num);
   }
fclose(f);
fclose(g);
remove("../DataBase/Clients.txt");
rename("../DataBase/tmp.txt","../DataBase/Clients.txt");
}  
/*-----------------------------------------------------*/
int idExiste(char id[]){
  Client c;
  FILE *f;
  f=fopen("../DataBase/Clients.txt","r");
  while(fscanf(f,"%s %s %s %d %d %d %s %s %s %s\n",c.id,c.nom,c.prenom,&c.dateNaissance.j,&c.dateNaissance.m,&c.dateNaissance.a,c.email,c.adresse,c.ville,c.num)!=EOF){
      if(strcmp(c.id,id) == 0){
        return 1;
      }
  }
  return 0;

}
int verifier_date(int j,int m,int a){
    if(m == 4 || m == 6 || m == 9 || m == 11){
        if(j>30){
            return 0;
        }
        else{
            return 1;
        }
    }
    if(m==2){
        if(a % 4 == 0){
            if(j>29){
                return 0;
            }
            else{
                return 1;
            }
        }
       else{
           if(j>28){
                return 0;
            }
            else{
                return 1;
            }
       }
   }
    return 1;
}
/*-----------------------------------------------------------------*/
Client find_client(char id[]){
	Client c;
    	FILE *f;
    	f = fopen("../DataBase/Clients.txt","r");
    	if(f != NULL){
    		while(fscanf(f,"%s %s %s %d %d %d %s %s %s %s\n",c.id,c.nom,c.prenom,&c.dateNaissance.j,&c.dateNaissance.m,&c.dateNaissance.a,c.email,c.adresse,c.ville,c.num) != EOF){
        		if(strcmp(c.id,id) == 0){
       		     		return c;
        		}
    		}
	}
    fclose(f);
    return;
}
/*-------------------------------------------------------------------------------*/

/*-------------------------------------*/
int verifNameCl(char c[]){
    if(strlen(c) == 0){
        return 0;
    }
    else{
        int i,x;
        for(i=0;i<strlen(c);i++){
            x= c[i];
            if(x<65 || x>122 || (x>90 && x < 97)){
                return 0;
            }
        }
        return 1;
    }
}
/*-------------------------------------*/
int verifNumCl(char c[]){
    if(strlen(c) != 8){
        return 0;
    }
    else{
        int i,x;
        for(i=0;i<8;i++){
            x = c[i];
            if(x>57 || x<48){
                return 0;
            }
        }
	return 1;
    }
}
/*-------------------------------------------------------------------------------*/

void afficher_clients(GtkWidget *liste){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char id[10];
	char nom[30];
	char prenom[30];
	char email[30];
	char adresse[30];
	char num[30];
	Date dateNaissance;
	char ville[20];

	char date[50];
	store=NULL;
	FILE  *f;
	store=gtk_tree_view_get_model(liste);

  	if(store==NULL){
	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes(" Id ",renderer,"text",EID,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes("   NOM   ",renderer,"text",EFIRSTNAME,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes(" Prénom ",renderer,"text",ELASTNAME,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes(" Date de Naissance ",renderer,"text",EDATEN,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes(" Email ",renderer,"text",EEMAIL,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes(" Adresse ",renderer,"text",EADRESS,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes(" Ville ",renderer,"text",ECITY,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	   
	   renderer=gtk_cell_renderer_text_new();
	   column=gtk_tree_view_column_new_with_attributes(" Numéro du téléphone ",renderer,"text",ENUM,NULL);
	   gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

   		store=gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

f=fopen("../DataBase/Clients.txt","r");

     if(f!=NULL)
        {
         while(fscanf(f,"%s %s %s %d %d %d %s %s %s %s\n",id,nom,prenom,&dateNaissance.j,&dateNaissance.m,&dateNaissance.a,email,adresse,ville,num)!=EOF){
		sprintf(date,"%d/%d/%d",dateNaissance.j,dateNaissance.m,dateNaissance.a);
           gtk_list_store_append(store,&iter);
           gtk_list_store_set(store,&iter,EID,id,EFIRSTNAME,nom,ELASTNAME,prenom,EDATEN,date,EEMAIL,email,EADRESS,adresse,ECITY,ville,ENUM,num,-1);
          }
        }
   fclose(f);
   gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
   g_object_unref(store);  
   }
}



int anneseche()
{
    FILE *f=NULL;
    ct at;
    int n1,n2,n3,annee;
    float hum;
    int t[90000];
    int i=0,x=0,j=1,min=0;
    int n[20];
    int anne[20];
    float somm[20];
    float moy[20];

    f=fopen("humid.txt","r");
if(f!=NULL)
      {
         while(fscanf(f,"%d %d %d %d %f\n",&n1,&n2,&n3,&annee,&hum)!=NULL)
            {
               t[i]=annee;
            i++;
            }
      i=0;
fclose(f);
 f=fopen("humid.txt","r");

         while(fscanf(f,"%d %d %d %d %f\n",&n1,&n2,&n3,&annee,&hum)!=NULL)
            {

               if (t[i]!=t[i+1])
                 {   anne[x]=annee;
                     n[x]=j;
                     x++;

                    j=1;

                 }
               else
                 {
                   j++;
                 }
              somm[x]+=hum;

              i++;
             }
    }
      fclose(f);

     for(i=0;i<x;i++)
     {
        moy[i]=(somm[i]/n[i]);

     }
       for (i=0;i<x;i++)
        {
         if(moy[i]<moy[min])
          {
            min=i;
          }
        }
     at.moy=moy[min];
     at.somm=somm[min];
     at.anne=anne[min];
return anne[min];

}




