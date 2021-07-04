#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "troupeau.h"
#include <gtk/gtk.h>
#include <time.h>
enum
{
	NOM,
	GENRE,
	TYPE,
	ID,
	EDATE,
	COLUMNS
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int idmodifier(char idf0[])
{
    FILE *f;
    char  nomt[30],nom1[30],nom2[30],idf[30];
    int d,m,a,choix,nb;
    f=fopen("../DataBase/projet.txt","r");
    if(f!=NULL)
    {


        int verif=0;
        
        while((fscanf(f,"%s %s %s %s %d %d %d\n",nomt,nom1,nom2,idf,&d,&m,&a)!=EOF)&&(verif==0))
        {
		if(strcmp(idf,idf0)==0)
		{	
			verif=1;
		}
	}
     fclose(f);
     return verif;
    }
}		



/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void modifierTrou(char idf0[],troupeau nov)
{
    troupeau tab[100];

    FILE *f;
    FILE *tem;
    char  nomt[30],nom1[30],nom2[30],idf[30];
    int d,m,a,choix,nb;
    f=fopen("../DataBase/projet.txt","r");

    if(f!=NULL)
    {


        int i;
        i=0;
        while(fscanf(f,"%s %s %s %s %d %d %d\n",nomt,nom1,nom2,idf,&d,&m,&a)!=EOF)
        {

            strcpy(tab[i].type,nomt);
            strcpy(tab[i].name,nom1);
            strcpy(tab[i].genre,nom2);
            tab[i].birth.jour=d;
            tab[i].birth.mois=m;
            tab[i].birth.annee=a;
            strcpy(tab[i].id,idf);
            i++;
        }
        nb=i;
        fclose(f);
        
       
        
        int var=0;
        int k=0;
        while((var==0)&&(k<nb))
        {
            if(strcmp(tab[k].id,idf0)==0)
            {

             /*  do
               {

                   printf("1-modifier type---\n");
                   printf("2-modifier nom---\n");
                   printf("3-modifier genre---\n");
                   printf("4-modifier date de naissance---\n");
                   printf("5-modifier le mois de naissance---\n");
                   printf("6-modifier l annee de naissance---\n");
                   printf("7-modifier tout les parametre---\n");
                   printf("donner votre choix de modification---: \n");
                   scanf("%d",&choix);
                   fflush(stdin);*/
              /* }while((choix<1)||(choix>7));
               switch(choix)
               {
                    case 1 :
                        printf("donner la nouvelle type : \n");
                        gets(typenew);*/
                        strcpy(tab[k].type,nov.type);
                       /* break;


                    case 2 :
                        printf("donner la nouvelle nom : \n");
                        gets(nomnew);*/
                        strcpy(tab[k].name,nov.name);
                    /*    break;
                    case 3 :
                        printf("donner la nouveau genre : \n");
                        gets(genrenew);*/
                        strcpy(tab[k].genre,nov.genre);
                     /*   break;
                    case 4 :
                        printf("donner la nouvelle date de naissance : ");
                        scanf("%d",&datenew);*/
                        tab[k].birth.jour=nov.birth.jour;
                        
                     /*   break;
                    case 5 :
                        printf("donner le nouveau mois de naissance : ");
                        scanf("%d",&moisnew);*/
                        tab[k].birth.mois=nov.birth.mois;
                     /*   fflush(stdin);
                        break;
                    case 6 :
                        printf("donner la nouvelle  annee de naissance : ");
                        scanf("%d",&anneenew);*/
                        tab[k].birth.annee=nov.birth.annee;
                      /*  fflush(stdin);
                        break;
                    case 7 :
                        printf("donner la nouvelle type : \n");
                        gets(typenew);
                        printf("donner la nouvelle nom : \n");
                        gets(nomnew);
                        printf("donner le nouveau genre : \n");
                        gets(genrenew);
                        printf("donner la nouvelle date de naissance : ");
                        scanf("%d",&datenew);
                        printf("donner le nouveau mois de naissance : ");
                        scanf("%d",&moisnew);
                        printf("donner la nouvelle  annee de naissance : ");
                        scanf("%d",&anneenew);
                        strcpy(tab[k].type,typenew);
                        strcpy(tab[k].name,nomnew);
                        strcpy(tab[k].genre,genrenew);
                        tab[k].birth.jour=datenew;
                        tab[k].birth.mois=moisnew;
                        tab[k].birth.annee=anneenew;
                        fflush(stdin);*/
			int q,l;
			char nbrch[10];
			q=strlen(idf0);
			for(l=1;l<q-1;l++)
			{
			nbrch[l-1]=idf0[l];
			}
			if(strcmp(tab[k].genre,"male")==0)
			{
			strcpy(tab[k].id,"M");
			}
			else
			{
			strcpy(tab[k].id,"F");
			}
			strcat(tab[k].id,nbrch);
	
	
			if(strcmp(tab[k].type,"brebi")==0)
			{
			strcat(tab[k].id,"B");
			}
			else
			{
			strcat(tab[k].id,"V"); 
			}
			FILE *i;
			i=fopen("../DataBase/idnouv.txt","w");
			fprintf(i,"%s",tab[k].id);
			fclose(i);  
              		 
                var=1;



            }
            else
                k++;


        }
        if(var==1)
        {   			
            tem=fopen("../DataBase/temp.txt","a+");
            for(i=0;i<nb;i++)
            {
                fprintf(tem,"%s %s %s %s %d %d %d\n",tab[i].type,tab[i].name,tab[i].genre,tab[i].id,tab[i].birth.jour,tab[i].birth.mois,tab[i].birth.annee);

            }
            fclose(tem);
            remove("../DataBase/projet.txt");
            rename("../DataBase/temp.txt","../DataBase/projet.txt");


        }
     //   else
          //  printf("l identifiant est n existe pas!!!!\n");




    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affichage(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter  iter;
    GtkListStore *store;
    
    FILE *f;
    char nom[30],genre[30],type[30],id[30];
    int d,m,a;
    char date[30];
    store=gtk_tree_view_get_model(liste);
    if(store==NULL)
    {
     	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("TYPE ",renderer,"text",TYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" NOM   ",renderer,"text",NOM,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("GENRE    ",renderer,"text",GENRE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("IDENTIFIANT    ",renderer,"text",ID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("DATE DE NAISSANCE    ",renderer,"text",EDATE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 	
	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

    	f=fopen("../DataBase/projet.txt","r");
    	if(f!=NULL)
    	{

        	while(fscanf(f,"%s %s %s %s %d %d %d\n",type,nom,genre,id,&d,&m,&a)!=EOF)
        	{
			//sprintf(idc,"%d",id);
		
			sprintf(date,"%d/%d/%d",d,m,a);
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,TYPE,type,NOM,nom,GENRE,genre,ID,id,EDATE,date,-1);
		}
           /* printf("type du troupeau %d : %s \n",nbr+1,type);
            printf("nom du troupeau %d : %s \n",nbr+1,nom);
            printf("genre du troupeau %d = %s \n",nbr+1,genre);
            printf("identifiant du troupeau %d : %d \n",nbr+1,id);
            printf("la date de naissance du troupeau %d : %d \n",nbr+1,d);
            printf("le mois de naissance du troupeau %d : %d \n",nbr+1,m);
            printf("l annee de naissance du troupeau %d : %d \n\n",nbr+1,a);

            nbr++;

        }
        printf("le nombre  de personne = %d \n",nbr);*/
        	fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
       	}
    	else
        //printf("imp!!!!!!!!");
	{
		return;
	}
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ajouter(troupeau p)
{
    FILE *f=fopen("../DataBase/projet.txt","a");
    int  nbr,m;
    char nbrch[30];
    FILE *l=fopen("../DataBase/para.txt","r");
    fscanf(l,"%d",&nbr);
    fclose(l);
    if(f!=NULL)
    {
	nbr++;
	sprintf(nbrch,"%d",nbr);
	
	
	
	if(strcmp(p.genre,"male")==0)
		strcpy(p.id,"M");
	else
		strcpy(p.id,"F");
	
	strcat(p.id,nbrch);
	
	
	if(strcmp(p.type,"brebi")==0)
		strcat(p.id,"B");
	else
		strcat(p.id,"V");      
        fprintf(f,"%s %s %s %s %d %d %d\n",p.type,p.name,p.genre,p.id,p.birth.jour,p.birth.mois,p.birth.annee);
        fclose(f);
	

    }
    
    FILE *r=fopen("../DataBase/para.txt","w");
    fprintf(r,"%d",nbr);
    fclose(r);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void supprimerTrou(troupeau tab[],int n,char value[],int *kapa)
{
    
    FILE *f,*tem;
    int i,j,verif,d,m,a,nbr;
    char nom[30],genre[30] ,type[30],idf[30],idff[30],ch[10];
    f=fopen("../DataBase/projet.txt","r");
    i=0;
    while(fscanf(f,"%s %s %s %s %d %d %d\n",type,nom,genre,idf,&d,&m,&a)!=EOF)
    {
        strcpy(tab[i].type,type);
        strcpy(tab[i].name,nom);
        strcpy(tab[i].genre,genre);
        strcpy(tab[i].id,idf);
        tab[i].birth.jour=d;
        tab[i].birth.mois=m;
        tab[i].birth.annee=a;
        i++;
    }
    nbr=i;
    fclose(f);
   // printf("donner l identifiant a supprimer: ");
  //  scanf("%d",&idf0);
  //  fflush(stdin);
    i=0;
    verif=0;
    while((i<nbr)&&(verif==0))
    {
        if(strcmp(tab[i].id,value)==0)
        {  
	    if(i!=nbr-1)
	    {
            for(j=i;j<nbr-1;j++)
            {
                strcpy(tab[j].type,tab[j+1].type);
		strcpy(tab[j].name,tab[j+1].name);
		strcpy(tab[j].genre,tab[j+1].genre);
		sprintf(ch,"%d",j+1);
		if(strcmp(tab[j+1].genre,"male")==0)
		strcpy(idff,"M");
		else
		strcpy(idff,"F");
		strcat(idff,ch);
		if(strcmp(tab[j+1].type,"brebi")==0)
		strcat(idff,"B");
		else
		strcat(idff,"V");
		strcpy(tab[j].id,idff);
		tab[j].birth.jour=tab[j+1].birth.jour;
		tab[j].birth.mois=tab[j+1].birth.mois;
		tab[j].birth.annee=tab[j+1].birth.annee;
            }

            nbr-=1;
            verif=1;
	    }
	    else
	    {
	     nbr-=1;
	     verif=1;
	    }
                
        }
        else
            i++;
	    

    }
    if(verif==1)
    {
        tem=fopen("../DataBase/temp.txt","a");
        for(i=0;i<nbr;i++)
        {
            
            fprintf(tem,"%s %s %s %s %d %d %d\n",tab[i].type,tab[i].name,tab[i].genre,tab[i].id,tab[i].birth.jour,tab[i].birth.mois,tab[i].birth.annee);

        }
        fclose(tem);
        FILE *r=fopen("../DataBase/para.txt","w");
        fprintf(r,"%d",nbr);
        fclose(r);
        remove("../DataBase/projet.txt");
        rename("../DataBase/temp.txt","../DataBase/projet.txt");
        *kapa=1;
    }
    else
	*kapa=0;


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int alpha(char mot[])
{
int var,k ,l,i=0;
var=0;
l=strlen(mot);
while((i<l)&&(var==0))
{
k=(int)mot[i];
if((k<65)||((k>90)&&(k<97))||(k>122))
{
var=1;
}
else
i++;
}
return var;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int maj(char mot[])
{
int var,k ,l,i=0;
var=0;
l=strlen(mot);
while((i<l)&&(var==0))
{
k=(int)mot[i];
if((k<48)||((k>57)&&(k<65))||(k>90))
{
var=1;
}
else
i++;
}
return var;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void nombre(int *b,int *v,int *t)
{
FILE *f,*n;
troupeau p;
f=fopen("../DataBase/projet.txt","r");
while(fscanf(f,"%s %s %s %s %d %d %d\n",p.type,p.name,p.genre,p.id,&p.birth.jour,&p.birth.mois,&p.birth.annee)!=EOF)
{
if(strcmp(p.type,"brebi")==0)
*b+=1;
else
if(strcmp(p.type,"veaux")==0)
*v+=1;
}
fclose(f);
n=fopen("../DataBase/para.txt","r");
fscanf(n,"%d",&*t);
fclose(n);

} 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void filtre()
{
FILE *f,*b,*v;
troupeau p;
f=fopen("../DataBase/projet.txt","r");
while(fscanf(f,"%s %s %s %s %d %d %d\n",p.type,p.name,p.genre,p.id,&p.birth.jour,&p.birth.mois,&p.birth.annee)!=EOF)
{
if(strcmp(p.type,"brebi")==0)
{
b=fopen("../DataBase/brebi.txt","a");
fprintf(b,"%s %s %s %s %d %d %d\n",p.type,p.name,p.genre,p.id,p.birth.jour,p.birth.mois,p.birth.annee);
fclose(b);
}
else
if(strcmp(p.type,"veaux")==0)
{
v=fopen("../DataBase/veaux.txt","a");
fprintf(v,"%s %s %s %s %d %d %d\n",p.type,p.name,p.genre,p.id,p.birth.jour,p.birth.mois,p.birth.annee);
fclose(v);
}
}
fclose(f);


}
//////////////////////////////////////////////////////////////////////////////////////
void affichage1(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter  iter;
    GtkListStore *store;
    
    FILE *f;
    char nom[30],genre[30],type[30],id[30];
    int d,m,a;
    char date[30];
    store=gtk_tree_view_get_model(liste);
    if(store==NULL)
    {
     	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("TYPE ",renderer,"text",TYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" NOM   ",renderer,"text",NOM,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("GENRE    ",renderer,"text",GENRE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("IDENTIFIANT    ",renderer,"text",ID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("DATE DE NAISSANCE   ",renderer,"text",EDATE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 	

	
	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);


    	f=fopen("../DataBase/brebi.txt","r");
    	if(f!=NULL)
    	{

        	while(fscanf(f,"%s %s %s %s %d %d %d\n",type,nom,genre,id,&d,&m,&a)!=EOF)
        	{
			//sprintf(idc,"%d",id);
		
			sprintf(date,"%d/%d/%d",d,m,a);
		
			//sprintf(mc,"%d",m);
			
			//sprintf(ac,"%d",a);
		
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,TYPE,type,NOM,nom,GENRE,genre,ID,id,EDATE,date,-1);
		}
           /* printf("type du troupeau %d : %s \n",nbr+1,type);
            printf("nom du troupeau %d : %s \n",nbr+1,nom);
            printf("genre du troupeau %d = %s \n",nbr+1,genre);
            printf("identifiant du troupeau %d : %d \n",nbr+1,id);
            printf("la date de naissance du troupeau %d : %d \n",nbr+1,d);
            printf("le mois de naissance du troupeau %d : %d \n",nbr+1,m);
            printf("l annee de naissance du troupeau %d : %d \n\n",nbr+1,a);

            nbr++;

        }
        printf("le nombre  de personne = %d \n",nbr);*/
        	fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
       	}
    	else
        //printf("imp!!!!!!!!");
	{
		return;
	}
   }
}
////////////////////////////////////////////////////////////////////////////////////////
void affichage2(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter  iter;
    GtkListStore *store;
    
    FILE *f;
    char nom[30],genre[30],type[30],id[30];
    int d,m,a;
    char date[30];
    store=gtk_tree_view_get_model(liste);
    if(store==NULL)
    {
     	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("TYPE ",renderer,"text",TYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" NOM   ",renderer,"text",NOM,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("GENRE    ",renderer,"text",GENRE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("IDENTIFIANT    ",renderer,"text",ID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("DATE DE NAISSANCE    ",renderer,"text",EDATE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 		store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);


    	f=fopen("../DataBase/veaux.txt","r");
    	if(f!=NULL)
    	{

        	while(fscanf(f,"%s %s %s %s %d %d %d\n",type,nom,genre,id,&d,&m,&a)!=EOF)
        	{
			//sprintf(idc,"%d",id);
			sprintf(date,"%d/%d/%d",d,m,a);
			
		
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,TYPE,type,NOM,nom,GENRE,genre,ID,id,EDATE,date,-1);
		}
           /* printf("type du troupeau %d : %s \n",nbr+1,type);
            printf("nom du troupeau %d : %s \n",nbr+1,nom);
            printf("genre du troupeau %d = %s \n",nbr+1,genre);
            printf("identifiant du troupeau %d : %d \n",nbr+1,id);
            printf("la date de naissance du troupeau %d : %d \n",nbr+1,d);
            printf("le mois de naissance du troupeau %d : %d \n",nbr+1,m);
            printf("l annee de naissance du troupeau %d : %d \n\n",nbr+1,a);

            nbr++;

        }
        printf("le nombre  de personne = %d \n",nbr);*/
        	fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
       	}
    	else
        //printf("imp!!!!!!!!");
	{
		return;
	}
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int accepte(int j,int m, int a,struct tm date)
{
    int x=0;
    if(a>date.tm_year+1900)
        x=1;
    else
        if((m>date.tm_mon+1)&&(a==date.tm_year+1900))
            x=1;
        else
            if((j>date.tm_mday)&&(m==date.tm_mon+1)&&(a==date.tm_year+1900))
                x=1;
    FILE *t;
    t=fopen("../DataBase/horloge.txt","a");
    fprintf(t,"%d %d  %d\n",date.tm_year+1900,date.tm_mon+1,date.tm_mday);
    fclose(t);
    return x;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verif(int j,int m, int a, struct tm date)
{
    int k;
    
    time_t temps;
   // struct tm date;

    // On récupère la date et l'heure actuelles.
    time(&temps);
    date=*localtime(&temps);

   
    k=accepte( j,m,a,date );
    


    return k;
}
///////////////////////////////////////////////////////////////////////









