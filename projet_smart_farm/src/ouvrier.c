#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ouvrier.h"

enum{
	EID,
	EFULLN,
	EGENRE,
	ECIN,
	EDATENAISS,
	ENUMTEL,
	EMODEEMPLOI,
	EDATEREC,
	ESALAIRE,
	ECOLUMNS,
};

void ajouter_ouvrier(Ouvrier o){
    FILE *f;
    f = fopen("../DataBase/data.txt","a");
    if(f!= NULL){
        fprintf(f,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,o.dateNaiss.j,o.dateNaiss.m,o.dateNaiss.a,o.num_tel,o.mode_emploi,o.DateRec.j,o.DateRec.m,o.DateRec.a,o.salaire);
    }
    fclose(f);
}

void modifier_ouvrier(Ouvrier y){
    Ouvrier o;
    FILE *f;
    FILE *g;
    f = fopen("../DataBase/data.txt","r");
    g = fopen("../DataBase/tmp.txt","a");
    while(fscanf(f,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,&o.dateNaiss.j,&o.dateNaiss.m,&o.dateNaiss.a,o.num_tel,o.mode_emploi,&o.DateRec.j,&o.DateRec.m,&o.DateRec.a,&o.salaire) != EOF){
        if(strcmp(o.id,y.id) == 0){
            fprintf(g,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",y.id,y.nom,y.prenom,y.genre,y.cin,y.dateNaiss.j,y.dateNaiss.m,y.dateNaiss.a,y.num_tel,y.mode_emploi,y.DateRec.j,y.DateRec.m,y.DateRec.a,y.salaire);
        }
        else{
            fprintf(g,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,o.dateNaiss.j,o.dateNaiss.m,o.dateNaiss.a,o.num_tel,o.mode_emploi,o.DateRec.j,o.DateRec.m,o.DateRec.a,o.salaire);
        }
    }
    fclose(f);
    fclose(g);
    remove("../DataBase/data.txt");
    rename("../DataBase/tmp.txt","../DataBase/data.txt");
}

void supprimer_ouvrier(char id[]){
    Ouvrier o;
    FILE *f1;
    FILE *f2;
    f1 = fopen("../DataBase/data.txt","r");
    f2 = fopen("../DataBase/tmp.txt","a+");
    if(f1 != NULL && f2 != NULL){
        while(fscanf(f1,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,&o.dateNaiss.j,&o.dateNaiss.m,&o.dateNaiss.a,o.num_tel,o.mode_emploi,&o.DateRec.j,&o.DateRec.m,&o.DateRec.a,&o.salaire) != EOF){
        if(strcmp(o.id,id) != 0){
            fprintf(f2,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,o.dateNaiss.j,o.dateNaiss.m,o.dateNaiss.a,o.num_tel,o.mode_emploi,o.DateRec.j,o.DateRec.m,o.DateRec.a,o.salaire);
        }
    }
    fclose(f1);
    fclose(f2);
    remove("../DataBase/data.txt");
    rename("../DataBase/tmp.txt","../DataBase/data.txt");
    }
}

void afficher_ouvrier(GtkWidget *liste){
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    char id[20];
    char nom[30];
    char prenom[30];
    char cin[20];
int j,jj,m,mm,a,aa;
    char mode_emploi[20];
    float salaire;
    char genre[20];
    char num_tel[20];

    char sal[100];
    char date1[100];
    char date2[100];
    char fullName[60];
    FILE *f;
    store = NULL;
    store = gtk_tree_view_get_model(liste);

    if(store == NULL){
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID",renderer,"text",EID,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom&Prénom",renderer,"text",EFULLN,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Genre",renderer,"text",EGENRE,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("N° Cin",renderer,"text",ECIN,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de Naissance",renderer,"text",EDATENAISS,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numero Tel",renderer,"text",ENUMTEL,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mode d'emploi",renderer,"text",EMODEEMPLOI,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de Récrutement",renderer,"text",EDATEREC,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Salaire",renderer,"text",ESALAIRE,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


        

    }
	store = gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    
    
    	f = fopen("../DataBase/data.txt","r");
	if(f == NULL){
        	return;
    	}
	else{
        	while(fscanf(f,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",id,nom,prenom,genre,cin,&j,&m,&a,num_tel,mode_emploi,&jj,&mm,&aa,&salaire) != EOF){
			sprintf(sal,"%.3f",salaire);
			sprintf(date1,"%d/%d/%d",j,m,a);
			sprintf(date2,"%d/%d/%d",jj,mm,aa); 
			sprintf(fullName,"%s %s",nom,prenom);          		
			gtk_list_store_append(store,&iter);
            		gtk_list_store_set(store,&iter,EID,id,EFULLN,fullName,EGENRE,genre,ECIN,cin,EDATENAISS,date1,ENUMTEL,num_tel,EMODEEMPLOI,mode_emploi,EDATEREC,date2,ESALAIRE,sal,-1);
            		
        	}
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
        	fclose(f);
    	}
    
}

int rechercher_ouv(char id[]){
    Ouvrier o;
    FILE *f;
    f = fopen("../DataBase/data.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,&o.dateNaiss.j,&o.dateNaiss.m,&o.dateNaiss.a,o.num_tel,o.mode_emploi,&o.DateRec.j,&o.DateRec.m,&o.DateRec.a,&o.salaire) != EOF){
        	if(strcmp(o.id,id) == 0){
       		     return 1;
        	}
    	}
}
    fclose(f);
    return 0;
    

}


Ouvrier find_ouv(char id[]){
    Ouvrier o;
    FILE *f;
    f = fopen("../DataBase/data.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,&o.dateNaiss.j,&o.dateNaiss.m,&o.dateNaiss.a,o.num_tel,o.mode_emploi,&o.DateRec.j,&o.DateRec.m,&o.DateRec.a,&o.salaire) != EOF){
        	if(strcmp(o.id,id) == 0){
       		     return o;
        	}
    	}
}
    fclose(f);
    return;
}

/*------------------------ Taux d'absentéisme ----------------------------*/

double calcul_taux(int m,int a){
    FILE *f;
    double nbre_seance = 0;
    double nbre_absence = 0;
    char id[20];
    int jj,aa,mm,res;
    double result;
    f = fopen("../DataBase/absenteisme.txt","r");
    if(f != NULL){
        while(fscanf(f,"%s %d %d %d %d\n",id,&jj,&mm,&aa,&res) != EOF){
            if(mm == m && aa == a){
                nbre_seance ++;
                if(res == 0){
                    nbre_absence ++;
                }
            }
        }
    }
    fclose(f);
    return (nbre_absence/nbre_seance);
}
void ajout_presence(char id[],int j,int m,int a,int e){
    FILE *f,*g;
    char ID[20];
    int jj,aa,mm,pres,test = 0;
    f = fopen("../DataBase/absenteisme.txt","r");
    g = fopen("../DataBase/temp.txt","a");
    if(f != NULL){
        while(fscanf(f,"%s %d %d %d %d\n",ID,&jj,&mm,&aa,&pres) != EOF){
            if((strcmp(ID,id) == 0) && (jj == j) && (m = mm) && (aa == a)){
                fprintf(g,"%s %d %d %d %d\n",id,j,m,a,e);
                test = 1;
            }
            else{
                fprintf(g,"%s %d %d %d %d\n",ID,jj,mm,aa,pres);
            }
        }
        if(test == 0){
            fprintf(g,"%s %d %d %d %d\n",id,j,m,a,e);
        }
        
    }
    fclose(f);
    fclose(g);
    remove("../DataBase/absenteisme.txt");
    rename("../DataBase/temp.txt","../DataBase/absenteisme.txt");
}
void bestOuv(char id[],int year){
    Ouvrier o;
    FILE *f,*g;
    char liste_id[1000][20];
    int n = 0;
    int max = 0;
    int nbre_jour=0;
    char ident[20];
    int jj,aa,mm,pres;
    f = fopen("../DataBase/data.txt","r");
    if(f != NULL && g != NULL){
        while(fscanf(f,"%s %s %s %s %s %d/%d/%d %s %s %d/%d/%d %f\n",o.id,o.nom,o.prenom,o.genre,o.cin,&o.dateNaiss.j,&o.dateNaiss.m,&o.dateNaiss.a,o.num_tel,o.mode_emploi,&o.DateRec.j,&o.DateRec.m,&o.DateRec.a,&o.salaire) != EOF){
            strcpy(liste_id[n],o.id);
            ++n;
        }
	fclose(f);
        int i;
        for(i = 0;i<n;i++){
            g = fopen("../DataBase/absenteisme.txt","r");
            nbre_jour = 0;
            while(fscanf(g,"%s %d %d %d %d\n",ident,&jj,&mm,&aa,&pres) != EOF){
                if(strcmp(liste_id[i],ident) == 0 && (year == aa)){
                    if(pres == 1){
                        nbre_jour ++;
                    }
                }
            }
            if(nbre_jour > max){
                max = nbre_jour;
                strcpy(id,liste_id[i]);
            }
            fclose(g);
        }
    }
    
}
/*-------------------------------------- CONTROLE DE SAISIE --------------------------------------*/
/*-------------------------------------*/
int verifDate(date d){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int j,m,a;
    j = tm.tm_mday;
    m =  tm.tm_mon + 1;
    a =  tm.tm_year + 1900;

    if(d.a < a){
        return 1;
    }
    else if(d.a == a){
        if(d.m < m){
            return 1;
        }
        else if(d.m == m){
            if(d.j > j){
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
/*-------------------------------------*/
int verifNum(char c[]){
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
/*-------------------------------------*/
int verifName(char c[]){
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
/*-----------------------------------------*/

int verifSal(char s[]){
    if(strlen(s) == 0){
        return 0;
    }
    else{
        int i,x;
        for(i=0;i<strlen(s);i++){
            x = s[i];
            if(x<48 || x >57){
                if(x != 46){
                    return 0;
                }
            }
        }
        return 1;
    }
}

