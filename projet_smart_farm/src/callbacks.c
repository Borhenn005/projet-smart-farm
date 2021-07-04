#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ouvrier.h"
#include "client.h"
#include "plantation.h"
#include "capteur.h"
#include "equipement.h"
#include "troupeau.h"
#include "user.h"

/*--------------------------  VARIABLE GLOBALE -------------------------------*/
char idDelOuv[20];
int x = 1;
int y = 0;
int w=2,ww =1;
int z = 1,zz=2;
struct tm h;
int xx=3;
int t[2]={0,0};
int zeta=-1;
int togg_acc = 1;
/*------------------------- INTERFACE DE LOGIN ------------------------------*/
void
on_seConnecter_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	
	GtkWidget *username;
	GtkWidget *pass;
	char userName[30],password[30];

	username = lookup_widget(objet,"username");
	pass = lookup_widget(objet,"password");	
	strcpy(userName,gtk_entry_get_text(GTK_ENTRY(username)));
	strcpy(password,gtk_entry_get_text(GTK_ENTRY(pass)));
	if(verif_user(userName,password)){
		window1 = lookup_widget(objet,"Login");
		window2 = create_menu ();
	  	gtk_widget_show (window2);
		gtk_widget_destroy(window1);		
	}
	else{
		GtkWidget *output;
		output = lookup_widget(objet,"outputLogin");
		GdkColor color;
		gdk_color_parse ("#f00", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
		gtk_label_set_text(GTK_LABEL(output),"Verifier Vos Données");	
		
	}

}


void
on_createAccount_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"Login");
	window2 = create_alerteSecurite ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}
void
on_confirmeCreateAccount_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{
	user u;	
	GtkWidget *username;
	GtkWidget *password;
	GtkWidget *rePass;
	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	username = lookup_widget(objet,"userName");
	password = lookup_widget(objet,"pass1");
	rePass = lookup_widget(objet,"pass2");
	output1 = lookup_widget(objet,"testPass1");
	output2 = lookup_widget(objet,"testPass2");
	output3 = lookup_widget(objet,"testUserAdd");
	char pass1[30],pass2[30];
	strcpy(u.username,gtk_entry_get_text(GTK_ENTRY(username)));
	strcpy(pass1,gtk_entry_get_text(GTK_ENTRY(password)));
	strcpy(pass2,gtk_entry_get_text(GTK_ENTRY(rePass)));
	u.role = togg_acc;
	int test = 0;
	if(strlen(u.username) != 0){
		test = 1;
		gtk_label_set_text(GTK_LABEL(output3),"✔️");			
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"❌");	
	}
	
	if(strcmp(pass1,pass2) == 0 && test){
		strcpy(u.password,pass1);
		addUser(u);	
		gtk_label_set_text(GTK_LABEL(output1),"✔️");
		gtk_label_set_text(GTK_LABEL(output2),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"❌");
		gtk_label_set_text(GTK_LABEL(output2),"❌");
	}

	
}


void
on_admin_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		togg_acc=1;
	}


void
on_employer_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		togg_acc=2;
	}


void
on_entrerKey_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *key;
	GtkWidget *output;
	GtkWidget *output1;
	char mot[30];
	key = lookup_widget(objet,"keyCreate");
	strcpy(mot,gtk_entry_get_text(GTK_ENTRY(key)));
	output1 = lookup_widget(objet,"testKey");
	if(strcmp(mot,"esprit2021") == 0){
			GtkWidget *window1;
			GtkWidget *window2;
			GtkWidget *window3;
			window1 = lookup_widget(objet,"alerteSecurite");
			window2 = create_createAccount ();
		  	gtk_widget_show (window2);
			gtk_widget_destroy(window1);
	}	
	else{
		gtk_label_set_text(GTK_LABEL(output1),"❌");
					
	}
}

void
on_backalerteLogin_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"alerteSecurite");
	window2 = create_Login ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_createaccountTologin_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"createAccount");
	window2 = create_Login ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}
/*------------------------------------ MENU -----------------------------------*/

void
on_toGesOuv_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"menu");
	window2 = create_GestionOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewOuv");
		
	afficher_ouvrier(treeview);
}


void
on_toGesClient_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *treeview;
	window1 = lookup_widget(objet,"menu");
	window2 = create_GesClient ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	treeview = lookup_widget(window2,"treeviewClient");	
	afficher_clients(treeview);
}


void
on_toGesCap_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"menu");
	window2 = create_gestionCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewCap");
	afficher_capteur(treeview);
}


void
on_toGesCal_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"menu");
	window2 = create_GesPlantation ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewPlant");
	afficher_plant(treeview);
}


void
on_toYearSeche_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
		GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"menu");
	window2 = create_windowAnSech ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toGesTrou_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"menu");
	window2 = create_Gestrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewTroup");	
	affichage(treeview);
}


void
on_toGesEqui_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"menu");
	window2 = create_GesEquipement ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewEqui");	
	afficher_equipement(treeview);
}


void
on_logout_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"menu");
	window2 = create_Login ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}

/*--------------------------------- GESTION DES CLIENTS ----------------------------------*/
void
on_goToAddClient_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesClient");
	window2 = create_addClient ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_goToEditClient_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesClient");
	window2 = create_editClient ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);


}


void
on_treeviewClient_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter Iter;
	gchar* id;
	char id_supp[20];	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&Iter,path)){
		gtk_tree_model_get(GTK_LIST_STORE(model),&Iter,0,&id,-1);
		
		strcpy(id_supp,id);
		supprimer_client(id_supp);	
		afficher_clients(treeview);
	}
	
}


void
on_homeClient_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesClient");
	window2 = create_menu ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_refreshTreeClient_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window;
	GtkWidget *window2;
	GtkWidget *treeview;
	window = lookup_widget(objet,"GesClient");
	window2 = create_GesClient ();
	gtk_widget_destroy(window);
	gtk_widget_show(window2);
	treeview = lookup_widget(window2,"treeviewClient");	
	afficher_clients(treeview);
}


void
on_goToDeleteClient_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *treeview;
	window1 = lookup_widget(objet,"GesClient");
	window2 = create_delClient ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	treeview = lookup_widget(window2,"treeviewClient");	
	afficher_clients(treeview);


}


void
on_backAddClient_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *treeview;
	window1 = lookup_widget(objet,"addClient");
	window2 = create_GesClient ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	treeview = lookup_widget(window2,"treeviewClient");	
	afficher_clients(treeview);

}


void
on_confirmeAddClient_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *input7;
	GtkWidget *input8;
	GtkWidget *input9;
	GtkWidget *input10;
	GtkWidget *output;
        GtkWidget *outputId;
	GtkWidget *outputcity;
	GtkWidget *outputadress;
        GtkWidget *outputPrenom;
	GtkWidget *outputNom;
	GtkWidget *outputNum;
	GtkWidget *outputdateee;
	GtkWidget *outputmaiil;
	Client c;
	input1 = lookup_widget(objet_graphique,"entryid");
	input2 = lookup_widget(objet_graphique,"entry_first_name_6");
	input3 = lookup_widget(objet_graphique,"entry_last_name_6");
	input4 = lookup_widget(objet_graphique,"spinbutton_day_6");
	input5 = lookup_widget(objet_graphique,"spinbutton_mouth_6");
	input6 = lookup_widget(objet_graphique,"spinbutton_year_6");
	input7 = lookup_widget(objet_graphique,"entry_email_6");
	input8 = lookup_widget(objet_graphique,"entry_adress_6");
	input9 = lookup_widget(objet_graphique,"entry_phone_number_6");
	input10 = lookup_widget(objet_graphique,"entry_city_6");

	strcpy(c.id,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(c.prenom,gtk_entry_get_text(GTK_ENTRY(input3)));

	c.dateNaissance.j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input4));
	c.dateNaissance.m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));
	c.dateNaissance.a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input6));

	strcpy(c.email,gtk_entry_get_text(GTK_ENTRY(input7)));
	strcpy(c.adresse,gtk_entry_get_text(GTK_ENTRY(input8)));
	strcpy(c.num,gtk_entry_get_text(GTK_ENTRY(input9)));
	strcpy(c.ville,gtk_entry_get_text(GTK_ENTRY(input10)));
	char texte[200];
        int test1,test2,test3,test4,test5,test6,test7,test8;
	
	/*----------- CONTROLE DE SAISIE --------------------*/
	test1 = idExiste(c.id);
	outputId = lookup_widget(objet_graphique,"idclientVerif");
	if(!test1){
		gtk_label_set_text(GTK_LABEL(outputId),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputId),"❌");
	}
        test2 = verifNameCl(c.nom);
	outputNom = lookup_widget(objet_graphique,"lalelnom");
	if(test2){
		gtk_label_set_text(GTK_LABEL(outputNom),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputNom),"❌");
	}

	/*-------------------------------------------------------*/
	test3= verifNameCl(c.prenom);
	outputPrenom = lookup_widget(objet_graphique,"lalelprenom");
	if(test3){
		gtk_label_set_text(GTK_LABEL(outputPrenom),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputPrenom),"❌");
	}

     	test4 = verifNameCl(c.adresse);
	outputadress = lookup_widget(objet_graphique,"laleladress");
	if(test4){
		gtk_label_set_text(GTK_LABEL(outputadress),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputadress),"❌");
	}

	/*-------------------------------------------------------*/
	test5= verifNameCl(c.ville);
	outputcity  = lookup_widget(objet_graphique,"lalelville");
	if(test5){
		gtk_label_set_text(GTK_LABEL(outputcity),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputcity),"❌");
	}
	test6 = verifNumCl(c.num);
	outputNum = lookup_widget(objet_graphique,"lalelnum");
	if(test6){
		gtk_label_set_text(GTK_LABEL(outputNum),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputNum),"❌");
	}
	test7 = verifier_date(c.dateNaissance.j,c.dateNaissance.m,c.dateNaissance.a);
	outputdateee = lookup_widget(objet_graphique,"dateNclieAdd");
	if(test7){
		gtk_label_set_text(GTK_LABEL(outputdateee),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputdateee),"❌");
	}
	
	if(!test1 && test2 && test3 && test4 && test5 && test6 && test7 ){
			
         	ajouter_client(c);
		sprintf(texte,"Votre Client a été ajouter avec succés\n");
		output = lookup_widget(objet_graphique,"resultaddCl");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);
		GtkWidget *success;
		success = create_successAdd ();
		gtk_widget_show(success);

		char reset[20];
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);			
		gtk_entry_set_text(GTK_ENTRY(input10),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input7),reset);
		gtk_entry_set_text(GTK_ENTRY(input8),reset);
		gtk_entry_set_text(GTK_ENTRY(input9),reset);

		gtk_spin_button_set_value(input4,1);
		gtk_spin_button_set_value(input5,1);
		gtk_spin_button_set_value(input6,2020);
	}
	else{
		sprintf(texte,"Vérifier vos donneés\n");
		output = lookup_widget(objet_graphique,"resultaddCl");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}
}


void
on_backDelClient_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *treeview;
	window1 = lookup_widget(objet,"delClient");
	window2 = create_GesClient ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	treeview = lookup_widget(window2,"treeviewClient");	
	afficher_clients(treeview);
}


void
on_delClientConfirm_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input;
	GtkWidget *output;
	char id[20];
	char texte[100];

	input = lookup_widget(objet_graphique,"entrysuppid");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input)));
	
	if(idExiste(id)){
		supprimer_client(id);		
		sprintf(texte,"Votre suppression à été effectué avec succés\n");
		output = lookup_widget(objet_graphique,"outputDelClient");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);    		
		gtk_label_set_text(GTK_LABEL(output),texte);
		
	}
	else{
		sprintf(texte,"ID NON EXISTANT\n");
		
		output = lookup_widget(objet_graphique,"outputDelClient");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);	
		
	}
}


void
on_backEditClient_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *treeview;
	window1 = lookup_widget(objet,"editClient");
	window2 = create_GesClient ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	treeview = lookup_widget(window2,"treeviewClient");	
	afficher_clients(treeview);
}


void
on_consulterClient_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char id[10];
	GtkWidget *input1;
	input1 = lookup_widget(objet_graphique,"idclientEdit");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));

	char texte1[30],texte2[30],texte3[30],texte4[30],texte5[30],texte6[20];
	char outputmessage[100];
	GtkWidget *outputnom;
	GtkWidget *outputprenom;
	GtkWidget *outputemail;
	GtkWidget *outputville;
	GtkWidget *outputadresse;
	GtkWidget *outputnumtel;
	GtkWidget *output10;
	if(idExiste(id)==0){
		sprintf(outputmessage,"ID NON EXISTANT\n");
		output10 = lookup_widget(objet_graphique,"resultEditCl");
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{
		Client y;
		strcpy(y.nom,find_client(id).nom);
		strcpy(y.prenom,find_client(id).prenom);
		
		strcpy(y.email,find_client(id).email);
		strcpy(y.num,find_client(id).num);

		strcpy(y.ville,find_client(id).ville);
		strcpy(y.adresse,find_client(id).adresse);

		sprintf(outputmessage,"Tapez vos nouveau donnée puis cliquez sur enregistrer les modifications\n");
		output10 = lookup_widget(objet_graphique,"resultEditCl");
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);

		gdk_color_parse ("#0c8ae8", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
			
		sprintf(texte1,"%s",y.nom);
		outputnom = lookup_widget(objet_graphique,"fisrtnameClEdit");
    		gtk_entry_set_text(GTK_ENTRY(outputnom),texte1);

		sprintf(texte2,"%s",y.prenom);
		outputprenom = lookup_widget(objet_graphique,"lastnameClEdit");
    		gtk_entry_set_text(GTK_ENTRY(outputprenom),texte2);

		sprintf(texte3,"%s",y.email);
		outputemail = lookup_widget(objet_graphique,"entry_new_email");
    		gtk_entry_set_text(GTK_ENTRY(outputemail),texte3);

		sprintf(texte4,"%s",y.adresse);
		outputadresse = lookup_widget(objet_graphique,"entry_new_adress");
    		gtk_entry_set_text(GTK_ENTRY(outputadresse),texte4);
    		
		sprintf(texte5,"%s",y.num);
		outputnumtel = lookup_widget(objet_graphique,"entry_new_number");
    		gtk_entry_set_text(GTK_ENTRY(outputnumtel),texte5);

		

		sprintf(texte6,"%s",y.ville);
		outputville = lookup_widget(objet_graphique,"entry_new_city");
		gtk_entry_set_text(GTK_ENTRY(outputville),y.ville);
	}

}


void
on_confirmerEditClient_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input7;
	GtkWidget *input8;
	GtkWidget *input9;
	GtkWidget *input10;
	GtkWidget *output; 	 
	GtkWidget*outputNumm;
	GtkWidget *outputPrenomm; 
	GtkWidget *outputNomm;
	GtkWidget *outputadresss;
	GtkWidget *outputcityy;
	char id[10];
	input1 = lookup_widget(objet_graphique,"idclientEdit");

	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));
	
	char texte[200];
	if(idExiste(id) == 0){
		sprintf(texte,"ID non existant\n");
		output = lookup_widget(objet_graphique,"resultEditCl");
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}



	else{
		
		Client c;
		
		input2 = lookup_widget(objet_graphique,"fisrtnameClEdit");
		input3 = lookup_widget(objet_graphique,"lastnameClEdit");
		input7 = lookup_widget(objet_graphique,"entry_new_email");
		input8 = lookup_widget(objet_graphique,"entry_new_adress");
		input9 = lookup_widget(objet_graphique,"entry_new_number");
		input10 = lookup_widget(objet_graphique,"entry_new_city");

		strcpy(c.id,id);
		strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
		strcpy(c.prenom,gtk_entry_get_text(GTK_ENTRY(input3)));

		c.dateNaissance.j = find_client(c.id).dateNaissance.j;
		c.dateNaissance.m = find_client(c.id).dateNaissance.m;
		c.dateNaissance.a = find_client(c.id).dateNaissance.a;

		strcpy(c.email,gtk_entry_get_text(GTK_ENTRY(input7)));
		strcpy(c.adresse,gtk_entry_get_text(GTK_ENTRY(input8)));
		strcpy(c.num,gtk_entry_get_text(GTK_ENTRY(input9)));
		strcpy(c.ville,gtk_entry_get_text(GTK_ENTRY(input10)));

	int test1,test2,test3,test4,test5,test6;
	
	/*----------- CONTROLE DE SAISIE --------------------*/
	
        test1 = verifNameCl(c.nom);
	outputNomm = lookup_widget(objet_graphique,"lalelNOM");
	if(test1){
		gtk_label_set_text(GTK_LABEL(outputNomm),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputNomm),"❌");
	}

	/*-------------------------------------------------------*/
	test2= verifNameCl(c.prenom);
	outputPrenomm = lookup_widget(objet_graphique,"lalelPRENOMM");
	if(test2){
		gtk_label_set_text(GTK_LABEL(outputPrenomm),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputPrenomm),"❌");
	}

     	test3 = verifNameCl(c.adresse);
	outputadresss = lookup_widget(objet_graphique,"lalelADRESS");
	if(test3){
		gtk_label_set_text(GTK_LABEL(outputadresss),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputadresss),"❌");
	}

	/*-------------------------------------------------------*/
	test4= verifNameCl(c.ville);
	outputcityy  = lookup_widget(objet_graphique,"lalelVILLE");
	if(test4){
		gtk_label_set_text(GTK_LABEL(outputcityy),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputcityy),"❌");
	}
	test5 = verifNumCl(c.num);
	outputNumm = lookup_widget(objet_graphique,"lalelNUM");
	if(test5){
		gtk_label_set_text(GTK_LABEL(outputNumm),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputNumm),"❌");
	}
	
	if(test1 && test2 && test3 && test4 && test5 ){




		modifier_client(c);
		GtkWidget *dialog;
		dialog = create_SuccessEdit ();
		gtk_widget_show(dialog);
		sprintf(texte,"Votre Client a été modifier avec succés\n");
		output = lookup_widget(objet_graphique,"resultEditCl");
    		gtk_label_set_text(GTK_LABEL(output),texte);
		
		char reset[20];
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);			
		gtk_entry_set_text(GTK_ENTRY(input10),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input7),reset);
		gtk_entry_set_text(GTK_ENTRY(input8),reset);
		gtk_entry_set_text(GTK_ENTRY(input9),reset);
	} 
       }
}

/*---------------------------- POP_UP ----------------------------------*/
void
on_OksuccessDel_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window;
	window = lookup_widget(objet,"successDel");
	gtk_widget_destroy(window);
}


void
on_dontshowmessage_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_confirmeSuppPopup_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window;
	window = lookup_widget(objet,"alerteDel");
	gtk_widget_destroy(window);
	supprimer_ouvrier(idDelOuv);
	GtkWidget *window1;
	window1 = create_successDel ();
	gtk_widget_show(window1);
}


void
on_cancelDelPopup_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window;
	window = lookup_widget(objet,"alerteDel");
	gtk_widget_destroy(window);
}


void
on_OkSuccessEdit_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *dialog;
	dialog = lookup_widget(objet,"SuccessEdit");
	gtk_widget_destroy(dialog);
/*----------------Gestion De Troupeau-------------------*/
char id[10],inf[100];
GtkWidget *IntermedEditTrou;
GtkWidget *labelinf;
GtkWidget *labelmod;
GtkWidget *entry4;
GtkWidget *img9;
GtkWidget *img10;

FILE *f;
GdkColor color;


if(zeta==0)
{
IntermedEditTrou = create_IntermedEditTrou ();
gtk_widget_show (IntermedEditTrou);
labelinf=lookup_widget(IntermedEditTrou,"labelinf");
labelmod=lookup_widget(IntermedEditTrou,"labelmod");
entry4=lookup_widget(IntermedEditTrou,"entry4");
img9=lookup_widget(IntermedEditTrou,"img9");
img10=lookup_widget(IntermedEditTrou,"img10");
gtk_widget_hide(img9);
gtk_widget_hide(img10);
gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(entry4),5);
gtk_label_set_text(labelmod,"");
FILE *ff;
char id1[30];
f=fopen("../DataBase/id.txt","r");
fscanf(f,"%s",id);
fclose(f);
ff=fopen("../DataBase/idnouv.txt","r");
fscanf(ff,"%s",id1);
fclose(ff);
strcpy(inf,"vous avez modifier le troupeau d'ancien id: ");
strcat(inf,id);
strcat(inf," et de nouveau id: ");
strcat(inf,id1);
gdk_color_parse("blue",&color);
gtk_widget_modify_fg(labelinf,GTK_STATE_NORMAL,&color);
gtk_label_set_text(labelinf,inf);
}
else
{
gtk_widget_destroy(dialog);
}

}


void
on_okSuccessAdd_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *dialog;
	dialog = lookup_widget(objet,"successAdd");
	gtk_widget_destroy(dialog);
}

/*--------------------------------- GESTION DES OUVRIER ----------------------------------*/
void
on_homeGesOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GestionOuv");
	window2 = create_menu ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}

void
on_treeviewOuv_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter Iter;
	gchar* id;		
	char id_supp[20];	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	
	if(gtk_tree_model_get_iter(model,&Iter,path)){
		gtk_tree_model_get(GTK_LIST_STORE(model),&Iter,0,&id,-1);
		
		GtkWidget *window1;
		window1 = create_successDel ();
		gtk_widget_show(window1);
		strcpy(id_supp,id);
		supprimer_ouvrier(id_supp);
		afficher_ouvrier(treeview);
		
	
	}
}
void
on_goToAddOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GestionOuv");
	window2 = create_AddOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_goToEditOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GestionOuv");
	window2 = create_editOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_goToDelOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GestionOuv");
	window2 = create_DeleteOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_goToFichePres_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GestionOuv");
	window2 = create_fichepres ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_goToTauxAbsen_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GestionOuv");
	window2 = create_TauxAbsc ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toBestOuv_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GestionOuv");
	window2 = create_bestOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_refreshTreeOuv_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window;
	GtkWidget *treeview;
	window = lookup_widget(objet,"GestionOuv");	
	treeview = lookup_widget(window,"treeviewOuv");
		
	afficher_ouvrier(treeview);
}


void
on_radioFemmeOuv_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        x = 2;
    }
}


void
on_radioHommeOuv_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        x = 1;
    }
}


void
on_refreshAddOuv_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"AddOuv");
	window2 = create_AddOuv ();
	gtk_widget_hide(window1);
	gtk_widget_show(window2);
}


void
on_confirmerAddOuv_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
	
	GtkWidget *id;	
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *calendar1;
	GtkWidget *calendar2;
	GtkWidget *output;

	GtkWidget *outputId;
	GtkWidget *outputCin;
	GtkWidget *outputNum;
	GtkWidget *outputMode;
	GtkWidget *outputDateN;
	GtkWidget *outputDateR;
	GtkWidget *outputNom;
	GtkWidget *outputPrenom;
	GtkWidget *outputSal;
	int j,m,a;
	char sal[100];
	char reset[20];
	Ouvrier o;
	id = lookup_widget(objet,"id_Ouvadd");
	input1 = lookup_widget(objet,"cin_add");
	input2 = lookup_widget(objet,"nom_add");
	input3 = lookup_widget(objet,"prenom_add");
	input4 = lookup_widget(objet,"mode_add");
	input5 = lookup_widget(objet,"salaire_add");
	input6 = lookup_widget(objet,"numTel_add");
	calendar1 = lookup_widget(objet,"calendarNaissOuv");
	calendar2 = lookup_widget(objet,"calendarRecOuv");
	
	
		
	if (x == 1){
		strcpy(o.genre,"Homme");
	}
	else if(x == 2){
		strcpy(o.genre,"Femme");
	}
	
	strcpy(o.id,gtk_entry_get_text(GTK_ENTRY(id)));
	strcpy(o.cin,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(o.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(o.prenom,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(o.mode_emploi,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)));
	strcpy(sal,gtk_entry_get_text(GTK_ENTRY(input5)));
	o.salaire = (float) atoll(sal);
	strcpy(o.num_tel,gtk_entry_get_text(GTK_ENTRY(input6)));

	gtk_calendar_get_date(GTK_CALENDAR(calendar1),&a,&m,&j);
	o.dateNaiss.j = j;
	o.dateNaiss.m = m+1;
	o.dateNaiss.a = a;
	gtk_calendar_get_date(GTK_CALENDAR(calendar2),&a,&m,&j);

	o.DateRec.j = j;
	o.DateRec.m = m+1;
	o.DateRec.a = a;
	
	char texte[100];

	int test1,test2,test3,test4,test5,test6,test7,test8,test9;
	
	/*----------- CONTROLE DE SAISIE --------------------*/
	test1 = rechercher_ouv(o.id);
	outputId = lookup_widget(objet,"testIdAdd");
	if(!test1){
		gtk_label_set_text(GTK_LABEL(outputId),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputId),"❌");
	}
	/*-----------------------------------------------------*/
	test2 = verifNum(o.cin);
	outputCin = lookup_widget(objet,"testCinAdd");
	if(test2){
		gtk_label_set_text(GTK_LABEL(outputCin),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputCin),"❌");
	}
	/*------------------------------------------------------*/
	test3 = verifNum(o.num_tel);
	outputNum = lookup_widget(objet,"testNumTelAdd");
	if(test3){
		gtk_label_set_text(GTK_LABEL(outputNum),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputNum),"❌");
	}
	/*-------------------------------------------------------*/
	outputMode = lookup_widget(objet,"testModeAdd");
	if(strcmp(o.mode_emploi,"") == 0){
		gtk_label_set_text(GTK_LABEL(outputMode),"❌");		
		test4 = 0;
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputMode),"✔️");		
		test4 = 1;
	}
	/*-------------------------------------------------------*/
	test5 = verifDate(o.dateNaiss);
	outputDateN = lookup_widget(objet,"testDateNadd");
	if(test5){
		gtk_label_set_text(GTK_LABEL(outputDateN),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputDateN),"❌");
	}
	/*-------------------------------------------------------*/
	test6= verifDate(o.DateRec);
	outputDateR = lookup_widget(objet,"testDateRadd");
	if(test6){
		gtk_label_set_text(GTK_LABEL(outputDateR),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputDateR),"❌");
	}

	/*-------------------------------------------------------*/
	test7 = verifName(o.nom);
	outputNom = lookup_widget(objet,"testNomAdd");
	if(test7){
		gtk_label_set_text(GTK_LABEL(outputNom),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputNom),"❌");
	}

	/*-------------------------------------------------------*/
	test8 = verifName(o.prenom);
	outputPrenom = lookup_widget(objet,"testPrenAdd");
	if(test8){
		gtk_label_set_text(GTK_LABEL(outputPrenom),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputPrenom),"❌");
	}

	/*-------------------------------------------------------*/
	test9 = verifSal(sal);
	outputSal = lookup_widget(objet,"testSalAdd");
	if(test9){
		gtk_label_set_text(GTK_LABEL(outputSal),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(outputSal),"❌");
	}

	/*-------------------------------------------------------*/

	if(!test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8 && test9){
				
		ajouter_ouvrier(o);		
		sprintf(texte,"Votre ajout à été effectué avec succés\n");
		output = lookup_widget(objet,"output_add");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);

		GtkWidget *dialog;
		dialog = create_successAdd ();
		gtk_widget_show(dialog);
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(id),reset);
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);
		/*if(x == 2){
			gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton),0);
		}*/
		
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output = lookup_widget(objet,"output_add");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}


}


void
on_backAddOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"AddOuv");
	window2 = create_GestionOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewOuv");
		
	afficher_ouvrier(treeview);
}


void
on_SuppOuv_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *input;
	GtkWidget *output;
	char id[20];
	char texte[100];

	input = lookup_widget(objet,"idOuv_del");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input)));
	
	if(rechercher_ouv(id)){
		strcpy(idDelOuv,id);	
		/*sprintf(texte,"Votre suppression à été effectué avec succés\n");
		output = lookup_widget(objet_graphique,"output_del");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);*/
		GtkWidget *attentionsupp;
		attentionsupp = create_alerteDel ();
		gtk_widget_show(attentionsupp);
		char reset[20];
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input),reset);
		
	}
	else{
		sprintf(texte,"ID NON EXISTANT\n");
		output = lookup_widget(objet,"output_del");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}
}


void
on_backDelOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"DeleteOuv");
	window2 = create_GestionOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewOuv");
		
	afficher_ouvrier(treeview);
}


void
on_consulterOuv_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char id[20];
	GtkWidget *ident;
	ident = lookup_widget(objet_graphique,"idEditOuv");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(ident)));

	char texte1[30],texte2[30],texte3[20],texte4[20],texte5[20],texte6[20];
	char outputmessage[100];
	GtkWidget *outputcin;
	GtkWidget *outputnom;
	GtkWidget *outputprenom;
	GtkWidget *outputmode;
	GtkWidget *outputsalaire;
	GtkWidget *outputnumtel;
	GtkWidget *output10;
	if(!rechercher_ouv(id)){
		sprintf(outputmessage,"ID NON EXISTANT\n");
		output10 = lookup_widget(objet_graphique,"output_editResult");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{
		Ouvrier y;
		strcpy(y.cin,find_ouv(id).cin);		
		strcpy(y.nom,find_ouv(id).nom);
		strcpy(y.prenom,find_ouv(id).prenom);
		y.salaire = find_ouv(id).salaire;
		strcpy(y.mode_emploi,find_ouv(id).mode_emploi);
		strcpy(y.num_tel,find_ouv(id).num_tel);
			
		sprintf(outputmessage,"Tapez vos nouveau donnée puis cliquez sur\n\tenregistrer les modifications\n");
		output10 = lookup_widget(objet_graphique,"output_editResult");
		GdkColor color;
		gdk_color_parse ("#0c8ae8", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);		

		sprintf(texte1,"%s",y.nom);
		outputnom = lookup_widget(objet_graphique,"nom_edit");
    		gtk_entry_set_text(GTK_ENTRY(outputnom),texte1);

		

		sprintf(texte2,"%s",y.prenom);
		outputprenom = lookup_widget(objet_graphique,"prenom_edit");
    		gtk_entry_set_text(GTK_ENTRY(outputprenom),texte2);


		outputmode = lookup_widget(objet_graphique,"mode_edit");
		gtk_combo_box_set_active(outputmode,1);
    		if(strcmp(find_ouv(id).mode_emploi,"Cadre") == 0 ){
			gtk_combo_box_set_active(outputmode,2);
		}
		else if(strcmp(find_ouv(id).mode_emploi,"Ouvrier") == 0){
			gtk_combo_box_set_active(outputmode,1);
		}
		else{
			gtk_combo_box_set_active(outputmode,3);
		}
		sprintf(texte4,"%s",y.num_tel);
		outputnumtel = lookup_widget(objet_graphique,"numTel_edit");
    		gtk_entry_set_text(GTK_ENTRY(outputnumtel),texte4);

		sprintf(texte5,"%.3f",y.salaire);
		outputsalaire = lookup_widget(objet_graphique,"salaire_edit");
    		gtk_entry_set_text(GTK_ENTRY(outputsalaire),texte5);

		sprintf(texte6,"%s",y.cin);
		outputcin = lookup_widget(objet_graphique,"cin_edit");
		gtk_entry_set_text(GTK_ENTRY(outputcin),texte6);	
		
	}
}


void
on_backEditOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"editOuv");
	window2 = create_GestionOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewOuv");
		
	afficher_ouvrier(treeview);
}

void
on_backFichePres_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"fichepres");
	window2 = create_GestionOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewOuv");
		
	afficher_ouvrier(treeview);
}

void
on_backTauxAbsen_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"TauxAbsc");
	window2 = create_GestionOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewOuv");
		
	afficher_ouvrier(treeview);
}
void
on_saveEditOuv_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *ident;
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	
	GtkWidget *outputNom;
	GtkWidget *outputPrenom;
	GtkWidget *outputCin;
	GtkWidget *outputNumTel;
	GtkWidget *outputmode;
	GtkWidget *outputSal;
	int test1,test2,test3,test4,test5,test6,test7;

	GtkWidget *output10;

	char id[20];
	char sal[20];
	char outputmessage[100];
	ident = lookup_widget(objet_graphique,"idEditOuv");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(ident)));
	if(!rechercher_ouv(id)){
		sprintf(outputmessage,"ID NON EXISTANT\n");
		output10 = lookup_widget(objet_graphique,"output_editResult");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{	
		Ouvrier y;
		strcpy(y.genre,find_ouv(id).genre);
		strcpy(y.id,id);

		y.dateNaiss.j = find_ouv(id).dateNaiss.j;
		y.dateNaiss.m = find_ouv(id).dateNaiss.m;
		y.dateNaiss.a = find_ouv(id).dateNaiss.a;

		y.DateRec.j = find_ouv(id).DateRec.j;
		y.DateRec.m = find_ouv(id).DateRec.m;
		y.DateRec.a = find_ouv(id).DateRec.a;

		input1 = lookup_widget(objet_graphique,"nom_edit");
		input2 = lookup_widget(objet_graphique,"prenom_edit");
		input3 = lookup_widget(objet_graphique,"cin_edit");
		input4 = lookup_widget(objet_graphique,"salaire_edit");
		input5 = lookup_widget(objet_graphique,"mode_edit");
		input6 = lookup_widget(objet_graphique,"numTel_edit");
		
		
		
		/*-----------------------------------------------------------*/

		strcpy(y.nom,gtk_entry_get_text(GTK_ENTRY(input1)));

		strcpy(y.prenom,gtk_entry_get_text(GTK_ENTRY(input2)));

		strcpy(y.cin,gtk_entry_get_text(GTK_ENTRY(input3)));

		strcpy(sal,gtk_entry_get_text(GTK_ENTRY(input4)));
		y.salaire = (float) atoll(sal);

		strcpy(y.mode_emploi,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input5)));
				
		strcpy(y.num_tel,gtk_entry_get_text(GTK_ENTRY(input6)));
		
		/*-------------------------------------------------------*/

		test1 = verifName(y.nom);
		outputNom = lookup_widget(objet_graphique,"nomEditTest");
		if(test1){
			gtk_label_set_text(GTK_LABEL(outputNom),"✔️");
		}
		else{
			gtk_label_set_text(GTK_LABEL(outputNom),"❌");
		}

		/*-------------------------------------------------------*/

		test2 = verifName(y.prenom);
		outputPrenom = lookup_widget(objet_graphique,"prenomEditTest");
		if(test2){
			gtk_label_set_text(GTK_LABEL(outputPrenom),"✔️");
		}
		else{
			gtk_label_set_text(GTK_LABEL(outputPrenom),"❌");
		}

		/*-------------------------------------------------------*/

		test3 = verifNum(y.cin);
		outputCin = lookup_widget(objet_graphique,"cinEditTest");
		if(test3){
			gtk_label_set_text(GTK_LABEL(outputCin),"✔️");
		}
		else{
			gtk_label_set_text(GTK_LABEL(outputCin),"❌");
		}

		/*-------------------------------------------------------*/

		test4 = verifNum(y.num_tel);
		outputNumTel = lookup_widget(objet_graphique,"NumTelEditTest");
		if(test4){
			gtk_label_set_text(GTK_LABEL(outputNumTel),"✔️");
		}
		else{
			gtk_label_set_text(GTK_LABEL(outputNumTel),"❌");
		}

		/*-------------------------------------------------------*/

		outputmode = lookup_widget(objet_graphique,"modeEditTest");
		if(strcmp(y.mode_emploi,"") == 0){
			gtk_label_set_text(GTK_LABEL(outputmode),"❌");		
			test5 = 0;
		}
		else{
			gtk_label_set_text(GTK_LABEL(outputmode),"✔️");		
			test5 = 1;
		}

		/*-------------------------------------------------------*/
		
		test6 = verifSal(sal);
		outputSal = lookup_widget(objet_graphique,"SalEditTest");
		if(test6){
			gtk_label_set_text(GTK_LABEL(outputSal),"✔️");
		}
		else{
			gtk_label_set_text(GTK_LABEL(outputSal),"❌");
		}
		/*-------------------------------------------------------*/

		if(test1 && test2 && test3 && test4 && test5 && test6){
			/*-----------------------------------------------------------*/
			modifier_ouvrier(y);
			sprintf(outputmessage,"*******");
			output10 = lookup_widget(objet_graphique,"output_editResult");
			GdkColor color;
			gdk_color_parse ("#000", &color);
			gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
	    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);
			
			char reset[20];
			sprintf(reset,"");
			gtk_entry_set_text(GTK_ENTRY(ident),reset);
			gtk_entry_set_text(GTK_ENTRY(input1),reset);
			gtk_entry_set_text(GTK_ENTRY(input2),reset);
			gtk_entry_set_text(GTK_ENTRY(input3),reset);
			gtk_entry_set_text(GTK_ENTRY(input4),reset);
			gtk_entry_set_text(GTK_ENTRY(input6),reset);
			gtk_combo_box_set_active(input5,0);	
			
			GtkWidget *successEdit;
			successEdit = create_SuccessEdit ();
			gtk_widget_show(successEdit);
		}
	}

}


void
on_refreshEditOuv_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"editOuv");
	window2 = create_editOuv ();
	gtk_widget_hide(window1);
	gtk_widget_show(window2);
}


void
on_SauvegardePres_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *input;
	GtkWidget *output;
	GtkWidget *inputDate;
	char id[20];
	char texte[200];
	int a,m,j;	
	input = lookup_widget(objet,"idpres");	
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input)));
	output = lookup_widget(objet,"outputpres");
	
	GtkWidget *cal;
	cal = lookup_widget(objet,"calendarpresence");

	gtk_calendar_get_date(GTK_CALENDAR(cal),
					     &a,
					     &m,
					     &j);
	date d;
	d.j = j;
	d.m=m+1;
	d.a = a;
	int testDate;
	testDate = verifDate(d);
	inputDate = lookup_widget(objet,"testDatePres");
	if(testDate){
		gtk_label_set_text(GTK_LABEL(inputDate),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(inputDate),"❌");
	}

	if(!rechercher_ouv(id)){
		sprintf(texte,"ID NON EXISTANT\n");
		

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}
	else if(!testDate){
		sprintf(texte,"Verifier vos données \n");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}	
	else{
		ajout_presence(id,j,m+1,a,y);
		sprintf(texte,"Votre sauvegarde à été effectué avec succés\n");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}
}


void
on_present_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        y = 1;
    }
}


void
on_absent_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        y = 0;
    }
}


void
on_ShowTaux_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *output;
	GtkWidget *month;
	GtkWidget *year;
	month = lookup_widget(objet,"absc_month");
	year  = lookup_widget(objet,"absc_year");
	int mois,annee;
	mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(month));
	annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(year));
	double result = calcul_taux(mois,annee)*100;
	char texte[200];
	char AllMonths[12][20];
	strcpy(AllMonths[0],"Janvier");
	strcpy(AllMonths[1],"Février");
	strcpy(AllMonths[2],"Mars");
	strcpy(AllMonths[3],"Avril");
	strcpy(AllMonths[4],"Mai");
	strcpy(AllMonths[5],"Juin");
	strcpy(AllMonths[6],"Juillet");
	strcpy(AllMonths[7],"Août");
	strcpy(AllMonths[8],"Septembre");
	strcpy(AllMonths[9],"Octobre");
	strcpy(AllMonths[10],"Novembre");
	strcpy(AllMonths[11],"Décembre");
	int x = 37;
	if (isnan(result)){
		sprintf(texte,"Le taux d'absentéisme des ouvriers pour %s %d est 0.00 %c",AllMonths[mois-1],annee,x);
		output = lookup_widget(objet,"output_taux");
		gtk_label_set_text(GTK_LABEL(output),texte);
	}
	else{
		sprintf(texte,"Le taux d'absentéisme des ouvriers pour %s %d est %.2lf %c",AllMonths[mois-1],annee,result,x);
		output = lookup_widget(objet,"output_taux");
		gtk_label_set_text(GTK_LABEL(output),texte);
	}
}

void
on_showBestOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *year;
	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	int annee;
	year = lookup_widget(objet,"yearBest");
	annee= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(year));
	char id[20] = "";
		

	bestOuv(id,annee);
	Ouvrier o;
	o = find_ouv(id);
	
	char texte1[20],texte2[70],texte3[20],texte4[20];
	strcpy(texte1,id);
	sprintf(texte2,"%s %s",o.nom,o.prenom);
	sprintf(texte3,"%s",o.genre);
	sprintf(texte4,"%s",o.mode_emploi);

	output1 = lookup_widget(objet,"bestId");
	//output2 = lookup_widget(objet,"bestNoPre");
	output3 = lookup_widget(objet,"bestGenre");
	output4 = lookup_widget(objet,"bestMode");

	gtk_label_set_text(GTK_LABEL(output1),texte1);
	//gtk_label_set_text(GTK_LABEL(output2),texte2);
	gtk_label_set_text(GTK_LABEL(output3),texte3);
	gtk_label_set_text(GTK_LABEL(output4),texte4);
	
}
/*---------------------------- GESTION DE CALENDRIER DE PLANTATION ----------------------------*/

void
on_refreshTreePlant_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{

}


void
on_treeviewPlant_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_toAddPlant_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesPlantation");
	window2 = create_addPlant ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toEditPlant_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesPlantation");
	window2 = create_editPlant ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_ToDelPlant_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesPlantation");
	window2 = create_delPlant ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_homePlant_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesPlantation");
	window2 = create_menu ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_confirmeAddPlant_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *output;

	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;
	GtkWidget *output6;
	input1=lookup_widget(objet_graphique,"idPlant");
	input2=lookup_widget(objet_graphique,"typePlant");
	input3=lookup_widget(objet_graphique,"nomplant");
	input4=lookup_widget(objet_graphique,"periodePlant");
	input5=lookup_widget(objet_graphique,"calendarPlantAjou");
	input6=lookup_widget(objet_graphique,"calendarRecAjou");
	Gestion_PLant G;
	strcpy(G.ID,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(G.Type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input2)));
	strcpy(G.Nom,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(G.per_plant,gtk_entry_get_text(GTK_ENTRY(input4)));
	int a,m,j;
	gtk_calendar_get_date(GTK_CALENDAR(input5),&a,&m,&j);

	G.D_plant.jour=j;
	G.D_plant.mois=m+1;
	G.D_plant.annee=a;
	gtk_calendar_get_date(GTK_CALENDAR(input6),&a,&m,&j);
	G.D_rec.jour=j;
	G.D_rec.mois=m+1;
	G.D_rec.annee=a;

	char text[100];
	char reset[20];
	int test1,test2=1,test3,test4,test5=1,test6;
	/*----------- CONTROLE DE SAISIE --------------------*/
	test1 = rechercher_id(G.ID);
	output1 = lookup_widget(objet_graphique,"IdPlantVerif");
	if(!test1){
		gtk_label_set_text(GTK_LABEL(output1),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"❌");
	}
	/*-----------------------------------------------------*/

	if(strcmp(G.Type,"") == 0){
		test2 = 0;	
	}
	output2 = lookup_widget(objet_graphique,"typePlanVerif");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"❌");
	}
	/*-----------------------------------------------------*/
	
	test3 = verifName(G.Nom);
	output3 = lookup_widget(objet_graphique,"NomPlanVerif");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"❌");
	}
	/*-----------------------------------------------------*/
	
	test4 = verifName(G.per_plant);
	output4 = lookup_widget(objet_graphique,"perPlanVerif");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"❌");
	}
	/*------------------------------------------------------*/
	output5 = lookup_widget(objet_graphique,"DatePlanVerif");
	
	/*------------------------------------------------------*/

	test6= verif2Dates(G.D_plant,G.D_rec);
	output6 = lookup_widget(objet_graphique,"DateReVerif");
	if(test6){
		gtk_label_set_text(GTK_LABEL(output6),"✔️");
		gtk_label_set_text(GTK_LABEL(output5),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output6),"❌");
		gtk_label_set_text(GTK_LABEL(output5),"❌");
	}

	/*---------------------------------------------------------*/

	if(!test1 && test2 && test3 && test4 && test5 && test6){
		ajouter_plantation(G);
		sprintf(text,"Votre ajout a été effectuer avec succés");
		output = lookup_widget(objet_graphique,"sortieadd");
		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
		gtk_label_set_text(GTK_LABEL(output),text);
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input4),reset);
		gtk_combo_box_set_active(input2,0);
	}
	else{
		sprintf(text,"ID déjà EXISTANT !");
		output = lookup_widget(objet_graphique,"sortieadd");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
		gtk_label_set_text(GTK_LABEL(output),text);
	}
	
}


void
on_backAddPlant_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"addPlant");
	window2 = create_GesPlantation ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewPlant");
	afficher_plant(treeview);
}


void
on_confirmeDelPlant_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char id[20];
	GtkWidget *id1;
	id1=lookup_widget(objet_graphique,"IdSupprim");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(id1)));

	GtkWidget *output;
	char text[100];
	char reset[100];

	if(rechercher_id(id)){
		supprimer(id);
		sprintf(text,"Votre suppression a été effectuer avec succés");
		output = lookup_widget(objet_graphique,"sortiemodsupp");
		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
		gtk_label_set_text(GTK_LABEL(output),text);
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(id1),reset);
	}
	else{
		sprintf(text,"ID NON EXISTANT !");
		output = lookup_widget(objet_graphique,"sortiemodsupp");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
		gtk_label_set_text(GTK_LABEL(output),text);
		
	}
}


void
on_backDelPlant_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"delPlant");
	window2 = create_GesPlantation ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewPlant");
	afficher_plant(treeview);
}


void
on_consultPlant_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char id[20];
	GtkWidget *input1;
	input1 = lookup_widget(objet_graphique,"IdModif");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));

	char texte1[30],texte2[30],texte3[20];
	char outputmessage[100];
	
	GtkWidget *outputnom;
	GtkWidget *outputtype;
	GtkWidget *outputperiode;
	
	GtkWidget *output10;
	if(rechercher_id(id)==0){
		sprintf(outputmessage,"ID n'existe pas\n");
		output10 = lookup_widget(objet_graphique,"OutputModif");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{
		Gestion_PLant G ;
		strcpy(G.Nom,find_plant(id).Nom);
		strcpy(G.Type,find_plant(id).Type);
		strcpy(G.per_plant,find_plant(id).per_plant);
		
			
		sprintf(outputmessage,"Tapez vos nouveau donnée puis cliquez sur\n\tenregistrer les modifications\n");
		output10 = lookup_widget(objet_graphique,"OutputModif");
		GdkColor color;
		gdk_color_parse ("#0c8ae8", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);		

		sprintf(texte1,"%s",G.Nom);
		outputnom = lookup_widget(objet_graphique,"NomModif");
    		gtk_entry_set_text(GTK_ENTRY(outputnom),texte1);

		

		sprintf(texte2,"%s",G.per_plant);
		outputperiode = lookup_widget(objet_graphique,"periodemodif");
    		gtk_entry_set_text(GTK_ENTRY(outputperiode),texte2);


		outputtype = lookup_widget(objet_graphique,"TypeModif");
		
    		if(strcmp(find_plant(id).Type,"cereales") == 0 ){
			gtk_combo_box_set_active(outputtype,1);
		}
		else if(strcmp(find_plant(id).Type,"legumes") == 0){
			gtk_combo_box_set_active(outputtype,2);
		}
		else{
			gtk_combo_box_set_active(outputtype,3);
		}
	}
}


void
on_saveEditPlant_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	

	GtkWidget *output10;

	char id[20];
	char periode[20];
	char outputmessage[100];
	input1 = lookup_widget(objet_graphique,"IdModif");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));
	if(rechercher_id(id)==0){
		sprintf(outputmessage,"ID n'existe pas\n");
		output10 = lookup_widget(objet_graphique,"OutputModif");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{	
		Gestion_PLant G;
		
		strcpy(G.ID,id);

		
		input2 = lookup_widget(objet_graphique,"NomModif");
		input3 = lookup_widget(objet_graphique,"TypeModif");
		input4 = lookup_widget(objet_graphique,"periodemodif");
		input5 = lookup_widget(objet_graphique,"calendarPlantMod");
		input6 = lookup_widget(objet_graphique,"calendarRecMod");
		
		GtkWidget *output2;
		GtkWidget *output3;
		GtkWidget *output4;
		GtkWidget *output5;
		GtkWidget *output6;
		
		strcpy(G.per_plant,gtk_entry_get_text(GTK_ENTRY(input4)));
		strcpy(G.Nom,gtk_entry_get_text(GTK_ENTRY(input2)));
		strcpy(G.Type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)));
		
			int a,m,j;
		gtk_calendar_get_date(GTK_CALENDAR(input5),&a,&m,&j);

		G.D_plant.jour=j;
		G.D_plant.mois=m+1;
		G.D_plant.annee=a;
		gtk_calendar_get_date(GTK_CALENDAR(input6),&a,&m,&j);
		G.D_rec.jour=j;
		G.D_rec.mois=m+1;
		G.D_rec.annee=a;
		
		int test1,test2=1,test3,test4,test5=1,test6;
	
	/*----------- CONTROLE DE SAISIE --------------------*/
	

	if(strcmp(G.Type,"") == 0){
		test2 = 0;	
	}
	output2 = lookup_widget(objet_graphique,"type_edit_test");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"❌");
	}
	/*-----------------------------------------------------*/
	
	test3 = verifName(G.Nom);
	output3 = lookup_widget(objet_graphique,"nom_edit_test");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"❌");
	}
	/*-----------------------------------------------------*/
	
	test4 = verifName(G.per_plant);
	output4 = lookup_widget(objet_graphique,"periode_edit_test");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"❌");
	}
	/*------------------------------------------------------*/
	output5 = lookup_widget(objet_graphique,"date_planta_edit_test");
	
	/*------------------------------------------------------*/

	test6= verif2Dates(G.D_plant,G.D_rec);
	output6 = lookup_widget(objet_graphique,"date_rec_edit_test");
	if(test6){
		gtk_label_set_text(GTK_LABEL(output6),"✔️");
		gtk_label_set_text(GTK_LABEL(output5),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output6),"❌");
		gtk_label_set_text(GTK_LABEL(output5),"❌");
	}
		if (test2 && test3 && test4 && test5 && test6){
			modifier(G);
			sprintf(outputmessage,"Votre modification a été effectué avec succés\n");
			output10 = lookup_widget(objet_graphique,"OutputModif");
			GdkColor color;
			gdk_color_parse ("#40e61a", &color);
			gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
	    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
			

			char reset[20];
			sprintf(reset,"");
			gtk_entry_set_text(GTK_ENTRY(input1),reset);
			gtk_entry_set_text(GTK_ENTRY(input2),reset);
			gtk_entry_set_text(GTK_ENTRY(input4),reset);
			//gtk_entry_set_text(GTK_ENTRY(input5),reset);
			//gtk_entry_set_text(GTK_ENTRY(input6),reset);
			gtk_combo_box_set_active(input3,0);
		
		}
		else {
			sprintf(outputmessage,"Vérifier vos données\n");
			output10 = lookup_widget(objet_graphique,"OutputModif");
			GdkColor color;
			gdk_color_parse ("#f00", &color);
			gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
	    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);
		     }
		
	}		
}


void
on_backEditPlant_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"editPlant");
	window2 = create_GesPlantation ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewPlant");
	afficher_plant(treeview);
}

/*--------------------------------- GESTION DES EQUIPEMENTS ----------------------------------*/

void
on_treeviewEqui_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	
}


void
on_homeEqui_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesEquipement");
	window2 = create_menu ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toAddEqui_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesEquipement");
	window2 = create_addEquipement ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toEditEqui_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesEquipement");
	window2 = create_editEquipement ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toDelEqui_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"GesEquipement");
	window2 = create_delEquipement ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_refreshTreeEqui_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{

}


void
on_backAddEquipe_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"addEquipement");
	window2 = create_GesEquipement ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewEqui");	
	afficher_equipement(treeview);
}


void
on_ConfirmeAddEqui_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *input7;
	GtkWidget *output;

	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;
	GtkWidget *output6;
	GtkWidget *output7;
	char texte[200];
	equipement e;
	input1 = lookup_widget(objet_graphique,"idequi");
	input2 = lookup_widget(objet_graphique,"nomequip");
	input3 = lookup_widget(objet_graphique,"marqueequi");
	input4 = lookup_widget(objet_graphique,"modeleequip");
	input5 = lookup_widget(objet_graphique,"serialequi");
	input6 = lookup_widget(objet_graphique,"calendarlastverif");
	input7 = lookup_widget(objet_graphique,"emplacementequip");
	int j,m,a;
	strcpy(e.id,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(e.marque,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(e.modele,gtk_entry_get_text(GTK_ENTRY(input4)));
	strcpy(e.serial,gtk_entry_get_text(GTK_ENTRY(input5)));
	strcpy(e.emplacement,gtk_entry_get_text(GTK_ENTRY(input7)));
	gtk_calendar_get_date(GTK_CALENDAR(input6),&a,&m,&j);
	e.dernierVerif.j = j;
	e.dernierVerif.m = m+1;
	e.dernierVerif.a = a;
	
	int test1,test2,test3,test4,test5,test6 = 1;
	/*---------------------------------------------------*/
	test1 = idEquipExiste(e.id);
	output1 = lookup_widget(objet_graphique,"idEquiVerif");
	if(!test1){
		gtk_label_set_text(GTK_LABEL(output1),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"❌");
	}
	/*---------------------------------------------------*/
	test2 = verifName(e.nom);
	output2 = lookup_widget(objet_graphique,"nomEquiVerif");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"❌");
	}
	/*---------------------------------------------------*/
	test3 = verifName(e.modele);
	output3 = lookup_widget(objet_graphique,"ModelEquiVerif");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"❌");
	}
	/*---------------------------------------------------*/
	test4 = verifName(e.marque);
	output4 = lookup_widget(objet_graphique,"SerEquiVerif");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"❌");
	}
	/*---------------------------------------------------*/
	test5 = verifName(e.emplacement);
	output5 = lookup_widget(objet_graphique,"emplacEquiVerif");
	if(test5){
		gtk_label_set_text(GTK_LABEL(output5),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output5),"❌");
	}
	/*---------------------------------------------------*/
	output6 = lookup_widget(objet_graphique,"MarqEquiVer");
	if(strcmp(e.serial,"") == 0){
		test6 = 0;	
	}
	if(test6){
		gtk_label_set_text(GTK_LABEL(output6),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output6),"❌");
	}
	/*---------------------------------------------------*/

	output7 = lookup_widget(objet_graphique,"lastVeriff");
	gtk_label_set_text(GTK_LABEL(output7),"✔️");
	
	/*------------------------------------------------------*/
	
	if(!test1 && test2 && test3 && test4 && test5 && test6){
		output = lookup_widget(objet_graphique,"resAddEqui");		
		GdkColor color;
		gdk_color_parse ("#7f0", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);		
		ajouter_equipemenet(e);		
		
		sprintf(texte,"Votre equipement a été ajouter avec succés\n");
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}
	else{
		output = lookup_widget(objet_graphique,"resAddEqui");		
		GdkColor color;
		gdk_color_parse ("#f00", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
		
		sprintf(texte,"Verifier Vos Données\n");
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}
}


void
on_backEditEquipe_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"editEquipement");
	window2 = create_GesEquipement ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewEqui");	
	afficher_equipement(treeview);	
}


void
on_consultEqui_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char id[20];
	GtkWidget *input1;
	input1 = lookup_widget(objet_graphique,"ideditequipem");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));

	char texte1[20],texte2[20],texte3[20],texte4[30],texte5[30],texte6[30];
	char outputmessage[100];
	GtkWidget *outputnom;
	GtkWidget *outputmarque;
	GtkWidget *outputmodel;
	GtkWidget *outputserial;
	GtkWidget *outputemplacement;
	GtkWidget *outputlastverif;
	
	GtkWidget *output10;
	if(idEquipExiste(id)==0){
		sprintf(outputmessage,"ID NON EXISTANT\n");
		output10 = lookup_widget(objet_graphique,"sortieeditequipe");
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{
		equipement e;
		strcpy(e.id,id);		
		strcpy(e.nom,find_equip(id).nom);
		strcpy(e.marque,find_equip(id).marque);
		
		strcpy(e.modele,find_equip(id).modele);
		strcpy(e.serial,find_equip(id).serial);
		strcpy(e.emplacement,find_equip(id).emplacement);
		

		sprintf(outputmessage,"Tapez vos nouveau donnée puis cliquez sur \n\t\tenregistrer les modifications\n");
		output10 = lookup_widget(objet_graphique,"sortieeditequipe");
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
			
		sprintf(texte1,"%s",e.nom);
		outputnom = lookup_widget(objet_graphique,"newnameeditequi");
    		gtk_entry_set_text(GTK_ENTRY(outputnom),texte1);

		sprintf(texte2,"%s",e.marque);
		outputmarque = lookup_widget(objet_graphique,"newmarqueequi");
    		gtk_entry_set_text(GTK_ENTRY(outputmarque),texte2);

		sprintf(texte3,"%s",e.modele);
		outputmodel = lookup_widget(objet_graphique,"newmodeleequip");
    		gtk_entry_set_text(GTK_ENTRY(outputmodel),texte3);

		sprintf(texte4,"%s",e.serial);
		outputserial = lookup_widget(objet_graphique,"newserialequipe");
    		gtk_entry_set_text(GTK_ENTRY(outputserial),texte4);
    		

		sprintf(texte6,"%s",e.emplacement);
		outputemplacement = lookup_widget(objet_graphique,"newemplacement");
    		gtk_entry_set_text(GTK_ENTRY(outputemplacement),texte6);

	}
}


void
on_saveEditEquipe_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *input7;
	GtkWidget *output;

	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;
	GtkWidget *output6;
	GtkWidget *output7;
	char texte[200];
	equipement e;
	input1 = lookup_widget(objet_graphique,"ideditequipem");
	input2 = lookup_widget(objet_graphique,"newnameeditequi");
	input3 = lookup_widget(objet_graphique,"newmarqueequi");
	input4 = lookup_widget(objet_graphique,"newmodeleequip");
	input5 = lookup_widget(objet_graphique,"newserialequipe");
	input6 = lookup_widget(objet_graphique,"newemplacement");	
	input7 = lookup_widget(objet_graphique,"calendarlastVerifedit");
	
	int j,m,a;
	strcpy(e.id,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(e.marque,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(e.modele,gtk_entry_get_text(GTK_ENTRY(input4)));
	strcpy(e.serial,gtk_entry_get_text(GTK_ENTRY(input5)));
	strcpy(e.emplacement,gtk_entry_get_text(GTK_ENTRY(input6)));

	gtk_calendar_get_date(GTK_CALENDAR(input7),&a,&m,&j);
	e.dernierVerif.j = j;
	e.dernierVerif.m = m+1;
	e.dernierVerif.a = a;
	
	int test1,test2,test3,test4,test5,test6 = 1;
	/*---------------------------------------------------*/
	test2 = verifName(e.nom);
	output2 = lookup_widget(objet_graphique,"nomequiTestEdit");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"❌");
	}
	/*---------------------------------------------------*/
	test3 = verifName(e.modele);
	output3 = lookup_widget(objet_graphique,"modelTestEdit");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"❌");
	}
	/*---------------------------------------------------*/
	test4 = verifName(e.marque);
	output4 = lookup_widget(objet_graphique,"marquequiTestEqui");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"❌");
	}
	/*---------------------------------------------------*/
	test5 = verifName(e.emplacement);
	output5 = lookup_widget(objet_graphique,"emplacEquiTesEdit");
	if(test5){
		gtk_label_set_text(GTK_LABEL(output5),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output5),"❌");
	}
	/*---------------------------------------------------*/
	output6 = lookup_widget(objet_graphique,"serialEquiTesEdit");
	if(strcmp(e.serial,"") == 0){
		test6 = 0;	
	}
	if(test6){
		gtk_label_set_text(GTK_LABEL(output6),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output6),"❌");
	}
	/*---------------------------------------------------*/

	output7 = lookup_widget(objet_graphique,"lastVerifEquiTest");
	gtk_label_set_text(GTK_LABEL(output7),"✔️");
	
	/*------------------------------------------------------*/
	
	if(test2 && test3 && test4 && test5 && test6){
		modifier_equipement(e);		
		output = lookup_widget(objet_graphique,"sortieeditequipe");
		sprintf(texte,"Votre equipement a été modifier avec succés\n");
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}
	else{
		output = lookup_widget(objet_graphique,"sortieeditequipe");
		sprintf(texte,"Verifier Vos Données\n");
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}
}


void
on_confirmDelEqui_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input;
	GtkWidget *output;
	char id[20];
	char texte[100];

	input = lookup_widget(objet_graphique,"idDelEqu");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input)));
	
	if(idEquipExiste(id)){
		supprimer_equipement(id);		
		sprintf(texte,"Votre suppression à été effectué avec succés\n");
		output = lookup_widget(objet_graphique,"resultdelequipement");
    		gtk_label_set_text(GTK_LABEL(output),texte);
		
	}
	else{
		sprintf(texte,"ID NON EXISTANT\n");
		output = lookup_widget(objet_graphique,"resultdelequipement");
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}
}


void
on_backDelEqui_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"delEquipement");
	window2 = create_GesEquipement ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewEqui");	
	afficher_equipement(treeview);
}

/*--------------------------------- GESTION DE CAPTEUR ----------------------------------*/


void
on_treeviewCap_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter Iter;
	gchar* nom;	
	gchar* Reference;

	char num_Reference[20];	
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	
	if(gtk_tree_model_get_iter(model,&Iter,path)){
		gtk_tree_model_get(GTK_LIST_STORE(model),&Iter,0,&nom,1,&Reference,-1);
		
		strcpy(num_Reference,Reference);
		supprimer_capteur(num_Reference);
		afficher_capteur(treeview);
	}
}


void
on_refreshTreeCap_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window;
	GtkWidget *window2;
	GtkWidget *treeview;
	window = lookup_widget(objet,"gestionCap");
	window2 = create_gestionCap ();
	gtk_widget_destroy(window);
	gtk_widget_show(window2);	
	treeview = lookup_widget(window2,"treeviewCap");	
	afficher_capteur(treeview);
}


void
on_toDelCap_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"gestionCap");
	window2 = create_DelCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toEditCap_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"gestionCap");
	window2 = create_EditCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_toAddCap_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"gestionCap");
	window2 = create_AddCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_homeCap_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"gestionCap");
	window2 = create_menu ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_backAddCap_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"AddCap");
	window2 = create_gestionCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewCap");
	afficher_capteur(treeview);
}


void
on_radiobuttonHumAdd_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        w = 2;
	}
}


void
on_radiobuttonTempAdd_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        w = 1;
	}
}


void
on_radiobuttonDefctAdd_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        ww = 2;
	}
}


void
on_radiobuttonFoncAdd_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
        ww = 1;
	}
}


void
on_confirmeAddCap_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *input8;
	GtkWidget *output;
	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;
	
	int p,o,i,u,l;
	

	char texte[200];

	capteur c;

	input1=lookup_widget(objet,"nomcapadd");
	input2=lookup_widget(objet,"refcapadd");
	input3=lookup_widget(objet,"vavaadd");
	input4=lookup_widget(objet,"spinbutton3");
	input5=lookup_widget(objet,"spinbutton1");
	input6=lookup_widget(objet,"spinbutton2");
	input8=lookup_widget(objet,"prixadd");
	
	


	if (w==1){
		strcpy(c.service,"Temperature");
	}
	else if(w==2){
		strcpy(c.service,"Humidité");
	}
	
	if(ww==1){
		strcpy(c.Etat,"Fonctionnel");
	}
	else if(ww==2){
		strcpy(c.Etat,"Defectueux");
	}
	
	
	strcpy(c.Nomdecapteur,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(c.Reference,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(c.Valeur,gtk_entry_get_text(GTK_ENTRY(input3)));
	c.jourofcapteur=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input4));
	c.moisofcapteur=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));
	c.anneeofcapteur=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input6));
	strcpy(c.Prix,gtk_entry_get_text(GTK_ENTRY(input8)));
	

	p=RefExist(c.Reference);
	output1 = lookup_widget(objet,"labelRe");
	if(!p){
	gtk_label_set_text(GTK_LABEL(output1),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"❌");
	}
	o=verifSal(c.Valeur);
	output2 = lookup_widget(objet,"labelValeur");
	if(o){
	gtk_label_set_text(GTK_LABEL(output2),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"❌");
	}

	i=verifSal(c.Prix);
	output3 = lookup_widget(objet,"labelPRIX");
	if(i){
	gtk_label_set_text(GTK_LABEL(output3),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"❌");
	}

	u=verifName(c.Nomdecapteur);
	output4 = lookup_widget(objet,"labelNo");
	if(u){
	gtk_label_set_text(GTK_LABEL(output4),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"❌");
	}

	l=verifier_date(c.jourofcapteur,c.moisofcapteur,c.anneeofcapteur);
	output5 = lookup_widget(objet,"labelDate");
	if(l){
	gtk_label_set_text(GTK_LABEL(output5),"✔️");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output5),"❌");
	}

	if(!p&&o&&i&&u&&l){
		ajouter_capteur(c);
		sprintf(texte,"Capteur ajouté avec succés");
		output = lookup_widget(objet,"outputaddcap");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);
	}
	else{		
		sprintf(texte,"Verfier vos données !");
		output = lookup_widget(objet,"outputaddcap");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}
}


void
on_consultCap_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char ref[20];
	GtkWidget *input1;
	input1 = lookup_widget(objet_graphique,"referenceedit");
	strcpy(ref,gtk_entry_get_text(GTK_ENTRY(input1)));

	char texte1[20],texte2[20],texte3[20],texte4[20];
	char outputmessage[100];
	GtkWidget *outputnom;
	GtkWidget *outputservice;
	GtkWidget *outputprix;
	GtkWidget *outputval;
	GtkWidget *output10;
	if(RefExist(ref)==0){
		sprintf(outputmessage,"Réference n'existe pas\n");
		output10 = lookup_widget(objet_graphique,"outputeditcap");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{
		capteur c;
		strcpy(c.Nomdecapteur,find_cap(ref).Nomdecapteur);
		strcpy(c.Valeur,find_cap(ref).Valeur);
		strcpy(c.service,find_cap(ref).service);
		
			
		sprintf(outputmessage,"Tapez vos nouveau donnée puis cliquez sur\n\tenregistrer les modifications\n");
		output10 = lookup_widget(objet_graphique,"outputeditcap");
		GdkColor color;
		gdk_color_parse ("#0c8ae8", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);		

		sprintf(texte1,"%s",c.Nomdecapteur);
		outputnom = lookup_widget(objet_graphique,"nameedit");
    		gtk_entry_set_text(GTK_ENTRY(outputnom),texte1);

		sprintf(texte2,"%s",c.Valeur);
		outputval = lookup_widget(objet_graphique,"valeuredit");
    		gtk_entry_set_text(GTK_ENTRY(outputval),texte2);

	}
}


void
on_radiobuttonTempEdit_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
	        z= 2;
	}
}


void
on_radiobuttonFonctEdit_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
	        zz= 1;
	}
}


void
on_radiobuttonHumEdit_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
	        z= 2;
	}
}


void
on_radiobuttonDefecEdit_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
	        zz=2;
	}
}


void
on_backEditCap_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"EditCap");
	window2 = create_gestionCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewCap");
	afficher_capteur(treeview);
}


void
on_saveEditCap_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *input4;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	

	GtkWidget *output10;
	int o,u;

	char ref[20];

	char outputmessage[100];
	input1 = lookup_widget(objet_graphique,"referenceedit");
	strcpy(ref,gtk_entry_get_text(GTK_ENTRY(input1)));
	if(!RefExist(ref)){
		sprintf(outputmessage,"Reference n'existe pas\n");
		output10 = lookup_widget(objet_graphique,"outputeditcap");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
	}
	else{	
		capteur c;
		strcpy(c.Reference,ref);

		input1 = lookup_widget(objet_graphique,"nameedit");
		input4 = lookup_widget(objet_graphique,"valeuredit");
		

		if (z==1){
		strcpy(c.service,"Temperature");
}
		else if(z==2){
		strcpy(c.service,"Humidité");
}
		
		
		if(zz==1){
		strcpy(c.Etat,"Fonctionnel");
		}
		else if(zz==2){
			strcpy(c.Etat,"Defectueux");
		}

		
		
		strcpy(c.Nomdecapteur,gtk_entry_get_text(GTK_ENTRY(input1)));
		strcpy(c.Valeur,gtk_entry_get_text(GTK_ENTRY(input4)));

		c.jourofcapteur = find_cap(ref).jourofcapteur;
		c.moisofcapteur = find_cap(ref).moisofcapteur;
		c.anneeofcapteur = find_cap(ref).anneeofcapteur;
		strcpy(c.Prix,find_cap(ref).Prix);
		o=verifSal(c.Valeur);
		output2 = lookup_widget(objet_graphique,"labelVal");
		if(o){
		gtk_label_set_text(GTK_LABEL(output2),"✔️");
		}
		else{
			gtk_label_set_text(GTK_LABEL(output2),"❌");
		}

		u=verifName(c.Nomdecapteur);
		output4 = lookup_widget(objet_graphique,"labelNom");
		if(u){
		gtk_label_set_text(GTK_LABEL(output4),"✔️");
		}
		else{
			gtk_label_set_text(GTK_LABEL(output4),"❌");
		}
		if(o  && u){
		
		modifier_capteur(c);
		sprintf(outputmessage,"Votre modification a été effectué avec succés\n");
		output10 = lookup_widget(objet_graphique,"outputeditcap");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output10, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output10),outputmessage);	
		

		char reset[20];
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input4),reset);
		}
		
		
	}	
}


void
on_ConfirmDelCap_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *input;
	GtkWidget *output;
	char ref[20];
	char texte[100];

	input = lookup_widget(objet_graphique,"referencedelcap");
	strcpy(ref,gtk_entry_get_text(GTK_ENTRY(input)));
	
	if(RefExist(ref)){
		supprimer_capteur(ref);		
		sprintf(texte,"Votre suppression à été effectué avec succés\n");
		output = lookup_widget(objet_graphique,"outputsuppcap");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);
		char reset[20];
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input),reset);
		
	}
	else{
		sprintf(texte,"Reference  n'existe pas\n");
		output = lookup_widget(objet_graphique,"outputsuppcap");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}
}


void
on_backDelCap_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"DelCap");
	window2 = create_gestionCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewCap");
	afficher_capteur(treeview);
}

/*--------------------------------- GESTION DE TROUPEAUX ----------------------------------*/
void
on_backAddTrou_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"addTrou");
	window2 = create_Gestrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewTroup");	
	affichage(treeview);
}


void
on_ConfirmAddTrou_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
troupeau p;
int *d,*m,*a;
GtkWidget *combotype;
GtkWidget *img1;
GtkWidget *img2;
GtkWidget *img3;
GtkWidget *img4;
GtkWidget *img5;
GtkWidget *img6;
GtkWidget *img15;
GtkWidget *img16;
GtkWidget *l1;
GtkWidget *combo1;
GtkWidget *entrynom;
GtkWidget *labelajouter;
GtkWidget *calendar1;
GtkWidget *type;
GtkWidget *nom;
GtkWidget *genre;
GtkWidget *ajoutoui;
GtkWidget *windowtroupeaux;
GtkWidget *buttonajoutetroupeaux;
GdkColor color;
GdkColor color1;
GdkColor color2;
d=&p.birth.jour;
m=&p.birth.mois;
a=&p.birth.annee;
int x,s;

buttonajoutetroupeaux=lookup_widget(objet_graphique,"buttonajoutetroupeaux");
windowtroupeaux=lookup_widget(objet_graphique,"windowtroupeaux");
type=lookup_widget(objet_graphique,"type");
l1=lookup_widget(objet_graphique,"l1");
img1=lookup_widget(objet_graphique,"img1");
img2=lookup_widget(objet_graphique,"img2");
img3=lookup_widget(objet_graphique,"img3");
img4=lookup_widget(objet_graphique,"img4");
img5=lookup_widget(objet_graphique,"img5");
img6=lookup_widget(objet_graphique,"img6");
img15=lookup_widget(objet_graphique,"img15");
img16=lookup_widget(objet_graphique,"img16");
nom=lookup_widget(objet_graphique,"nom");
genre=lookup_widget(objet_graphique,"genre");
combotype=lookup_widget(objet_graphique,"combotype");
combo1=lookup_widget(objet_graphique,"combo1");
entrynom=lookup_widget(objet_graphique,"entrynom");
labelajouter=lookup_widget(objet_graphique,"labelajouter");
calendar1=lookup_widget(objet_graphique,"calendar1");
gtk_calendar_get_date(calendar1,a,m,d);
++*m;
s=verif( p.birth.jour,p.birth.mois,p.birth.annee, h);
FILE *t;
t=fopen("horloge.txt","a");
fprintf(t,"%d\n%d %d %d \n",s,d,m,a);
fclose(t);
strcpy(p.name,gtk_entry_get_text(GTK_ENTRY(entrynom)));
strcpy(p.genre,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo1)));
strcpy(p.id,gtk_entry_get_text(GTK_ENTRY(entrynom)));
strcpy(p.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combotype)));




if(s==1)
{
gtk_label_set_markup(GTK_LABEL(l1),"<span  foreground='#f90922'> *verifier la date!!! </span>");
/*gdk_color_parse("#ff0000",&color2);
gtk_widget_modify_bg(buttonajoutetroupeaux,GTK_STATE_NORMAL,&color2);*/
gtk_widget_show(img15);
gtk_widget_hide(img16);
}
else
{
gtk_label_set_text(GTK_LABEL(l1),"");
gtk_widget_hide(img15);
gtk_widget_show(img16);
}


if(strcmp(p.type,"./")==0)
{
gtk_label_set_markup(GTK_LABEL(type),"<span  foreground='#f90922'> *le champ type est vide!!! </span>");
/*gdk_color_parse("#ff0000",&color2);
gtk_widget_modify_bg(buttonajoutetroupeaux,GTK_STATE_NORMAL,&color2);*/
gtk_widget_show(img1);
gtk_widget_hide(img2);
}
else
{
gtk_label_set_text(GTK_LABEL(type),"");
gtk_widget_hide(img1);
gtk_widget_show(img2);
}

if(strcmp(p.genre,"./")==0)
{
gtk_label_set_markup(GTK_LABEL(genre),"<span  foreground='#f90922'> *le champ genre est vide!!! </span>");
/*gdk_color_parse("#ff0000",&color2);
gtk_widget_modify_bg(buttonajoutetroupeaux,GTK_STATE_NORMAL,&color2);*/
gtk_widget_show(img5);
gtk_widget_hide(img6);
}
else
{
gtk_label_set_text(GTK_LABEL(genre),"");
gtk_widget_show(img6);
gtk_widget_hide(img5);
}
if(strlen(p.name)==0)
{
gtk_label_set_markup(GTK_LABEL(nom),"<span  foreground='#f90922'> *le champ nom est vide!!! </span>");
/*gdk_color_parse("#ff0000",&color2);
gtk_widget_modify_bg(buttonajoutetroupeaux,GTK_STATE_NORMAL,&color2);*/
gtk_widget_show(img3);
gtk_widget_hide(img4);
}
else

{
x=alpha(p.name);
if(x==1)
{
gtk_label_set_markup(GTK_LABEL(nom),"<span  foreground='#f90922'> *entrer des alphabets!!! </span>");
/*gdk_color_parse("#ff0000",&color2);
gtk_widget_modify_bg(buttonajoutetroupeaux,GTK_STATE_NORMAL,&color2);*/
gtk_widget_show(img3);
gtk_widget_hide(img4);
}
else
{
gtk_label_set_text(GTK_LABEL(nom),"");
gtk_widget_show(img4);
gtk_widget_hide(img3);
}

}





if((strcmp(p.type,"./")!=0)&&(strcmp(p.genre,"./")!=0)&&(strlen(p.name)!=0)&&(x==0)&&(s==0))
{
gtk_widget_hide(img2);
gtk_widget_hide(img4);
gtk_widget_hide(img6);
ajouter(p);

ajoutoui = create_successAdd ();
gtk_widget_show (ajoutoui);
//////////////////////////////////////////////////////////////////////


GdkColor color;






gtk_widget_hide(img1);
gtk_widget_hide(img2);
gtk_widget_hide(img3);
gtk_widget_hide(img4);
gtk_widget_hide(img5);
gtk_widget_hide(img6);
gtk_widget_hide(img15);
gtk_widget_hide(img16);
gtk_label_set_text(GTK_LABEL(type),"");
gtk_label_set_text(GTK_LABEL(nom),"");
gtk_label_set_text(GTK_LABEL(genre),"");
gtk_label_set_text(GTK_LABEL(l1),"");

int n;
char ac[30];
char ab[30];
FILE *a;
FILE *aa;
a=fopen("../DataBase/nombre.txt","r");
fscanf(a,"%d",&n);
fclose(a);
n++;
aa=fopen("../DataBase/nombre.txt","w");
fprintf(aa,"%d",n);
fclose(aa);
sprintf(ac,"%d",n);
strcpy(ab,"vous avez ajoutee");
strcat(ab,ac);
strcat(ab," troupeau.");
gdk_color_parse("blue",&color);
gtk_widget_modify_fg(labelajouter,GTK_STATE_NORMAL,&color);




gtk_label_set_text(GTK_LABEL(labelajouter),ab);
gtk_combo_box_set_active(combotype,0);
gtk_combo_box_set_active(combo1,0);
gtk_entry_set_text(entrynom,"");



}





}


void
on_treeviewTroup_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;

GdkColor color;
GtkWidget *alerteopp;
GtkWidget *opplab;
char mot[50];

char id0[30];
gchar *id;
FILE *f;
f=fopen("../DataBase/id.txt","w");

GtkTreeModel *model=gtk_tree_view_get_model(treeview);
if(gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,3,&id,-1);
strcpy(id0,id);
fprintf(f,"%s",id0);
fclose(f);
strcpy(mot,"Choisir l'opération sur le troupeau d'id :");
strcat(mot,id0);

alerteopp = create_alerteopp ();
gtk_widget_show (alerteopp);
opplab=lookup_widget(alerteopp,"opplab");
gdk_color_parse("black",&color);
gtk_widget_modify_fg(opplab,GTK_STATE_NORMAL,&color);
gtk_label_set_text(opplab,mot);



}


}


void
on_toAddTrou_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"Gestrou");
	window2 = create_addTrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *combotype;
	GtkWidget *entrynom;
	GtkWidget *combo1;
	GtkWidget *type;
	GtkWidget *nom;
	GtkWidget *genre;
	GtkWidget *img1;
	GtkWidget *img2;
	GtkWidget *img3;
	GtkWidget *img4;
	GtkWidget *img5;
	GtkWidget *img6;
	GtkWidget *l1;
	GtkWidget *img15;
	GtkWidget *img16;

	
	
	combotype=lookup_widget(window2,"combotype");
	combo1=lookup_widget(window2,"combo1");
	entrynom=lookup_widget(window2,"entrynom");
	gtk_combo_box_set_active(combotype,0);
	gtk_combo_box_set_active(combo1,0);
	gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(entrynom),10);
	type=lookup_widget(window2,"type");
	nom=lookup_widget(window2,"nom");
	genre=lookup_widget(window2,"genre");
	img1=lookup_widget(window2,"img1");
	img2=lookup_widget(window2,"img2");
	img3=lookup_widget(window2,"img3");
	img4=lookup_widget(window2,"img4");
	img5=lookup_widget(window2,"img5");
	img6=lookup_widget(window2,"img6");
	l1=lookup_widget(window2,"l1");
	img15=lookup_widget(window2,"img15");
	img16=lookup_widget(window2,"img16");
	gtk_widget_hide(img1);
	gtk_widget_hide(img2);
	gtk_widget_hide(img3);
	gtk_widget_hide(img4);
	gtk_widget_hide(img5);
	gtk_widget_hide(img6);
	gtk_widget_hide(img15);
	gtk_widget_hide(img16);
	gtk_label_set_text(GTK_LABEL(type),"");
	gtk_label_set_text(GTK_LABEL(nom),"");
	gtk_label_set_text(GTK_LABEL(genre),"");
	gtk_label_set_text(GTK_LABEL(l1),"");

}


void
on_toInterEditTrou_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"Gestrou");
	window2 = create_IntermedEditTrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *entry4;
	GtkWidget *labelmod;
	GtkWidget *labelinf;
	GtkWidget *img9;
	GtkWidget *img10;

	
	entry4=lookup_widget(window2 ,"entry4");
	labelmod=lookup_widget(window2 ,"labelmod");
	labelinf=lookup_widget(window2 ,"labelinf");
	img9=lookup_widget(window2 ,"img9");
	img10=lookup_widget(window2 ,"img10");
	gtk_widget_hide(img9);
	gtk_widget_hide(img10);
	gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(entry4),5);
	gtk_entry_set_text(GTK_ENTRY(entry4),"");
	gtk_label_set_text(GTK_LABEL(labelmod),"");
	gtk_label_set_text(GTK_LABEL(labelinf),"");
}


void
on_toDelTrou_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"Gestrou");
	window2 = create_DelTrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *entry3;
	GtkWidget *labelsup;
	GtkWidget *labelsup2;
	GtkWidget *img11;



	
	entry3=lookup_widget(window2,"entry3");
	labelsup=lookup_widget(window2,"labelsup");
	labelsup2=lookup_widget(window2,"labelsup2");
	img11=lookup_widget(window2,"img11");
	gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(entry3),5);
	gtk_entry_set_text(GTK_ENTRY(entry3),"");
	gtk_label_set_text(GTK_LABEL(labelsup),"");
	gtk_label_set_text(GTK_LABEL(labelsup2),"");
	gtk_widget_hide(img11);

}


void
on_brebiGes_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active (togglebutton))
t[0]=1;
else
t[0]=0;

}


void
on_veauxGes_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active (togglebutton))
t[1]=1;
else
t[1]=0;

}


void
on_homeTrou_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"Gestrou");
	window2 = create_menu ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	zeta=-1;
}


void
on_refreshTreeTroup_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
FILE *f;

GtkWidget *window1;
GtkWidget *treeview1;
window1=lookup_widget(objet,"Gestrou");
gtk_widget_destroy(window1);
window1=create_Gestrou();
gtk_widget_show(window1);
treeview1=lookup_widget(window1,"treeviewTroup");
filtre();
if((t[0]==1)&&(t[1]==1))
affichage(treeview1);
else
if(t[0]==1)
affichage1(treeview1);
else
if(t[1]==1)
affichage2(treeview1);
else
if((t[0]==0)&&(t[1]==0))
affichage(treeview1);


remove("../DataBase/brebi.txt");
remove("../DataBase/veaux.txt");

f=fopen("../DataBase/tab.txt","w");
fprintf(f,"%d %d ",t[0],t[1]);
fclose(f);

t[0]=0;
t[1]=0;


}


void
on_toNumberTrou_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"Gestrou");
	window2 = create_NumberTrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);

	
	
	GtkWidget *totaleType;
	totaleType=lookup_widget(window2 ,"totaleType");

	gtk_toggle_button_set_active (totaleType,"TRUE");

}


void
on_confirmDelsupptrou_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
int *kappa,a,y;
char value[10],idt[100];
a=0;
kappa=&a;
troupeau tab[100];
GtkWidget *labelsup;
GtkWidget *labelsup2;
GtkWidget *entry3;
GtkWidget *img11;
GtkWidget *alerte;
GtkWidget *lab;
GdkColor color;
GtkWidget *alerteDel;
int x;

GtkWidget *windowsuppmod;
GdkColor color1;
GdkColor color2;
GdkColor color3;

img11=lookup_widget(objet_graphique,"img11");
labelsup=lookup_widget(objet_graphique,"labelsup");
labelsup2=lookup_widget(objet_graphique,"labelsup2");
entry3=lookup_widget(objet_graphique,"entry3");
windowsuppmod=lookup_widget(objet_graphique,"DelTrou");
strcpy(value,gtk_entry_get_text(GTK_ENTRY(entry3)));
y=maj(value);
if(strcmp(value,"")==0)
{
gtk_label_set_markup(GTK_LABEL(labelsup),"<span  foreground='#f90922'> *le champ est vide!!! </span>");
gtk_widget_show(img11);
}
else
if(y==1)
{
gtk_label_set_markup(GTK_LABEL(labelsup),"<span  foreground='#f90922'> *entrer des MAJUSCULE et des chiffres!!! </span>");
gtk_widget_show(img11);
}
else
if((y!=1)&&(strcmp(value,"")!=0))
{
x=idmodifier(value);
if(x==1)
{
/*gtk_widget_destroy(windowsuppmod);
alerte = create_alerte ();
gtk_widget_show (alerte);
lab=lookup_widget(alerte,"lab");
strcpy(idt,value);
strcat(idt," ?");
GdkColor color3;
gdk_color_parse("black",&color3);
gtk_widget_modify_fg(lab,GTK_STATE_NORMAL,&color3);
gtk_label_set_text(lab,idt);
FILE *t;
t=fopen("id.txt","w");
fprintf(t,"%s",value);
fclose(t);*/
supprimerTrou( tab,100,value,kappa);





}
else
{
gtk_label_set_markup(GTK_LABEL(labelsup),"<span  foreground='#f90922'> *l'id n'existe pas!!! </span>");

}

}

}


void
on_ToEditTrou_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char idf0[30];
	int x,y;
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *img9;
	GtkWidget *img10;
	GdkColor color1;
	GdkColor color2;
	GtkWidget *entry4;
	GtkWidget *labelmod;
	GtkWidget *modifierid;
	
	
	img9=lookup_widget(objet_graphique,"img9");
	img10=lookup_widget(objet_graphique,"img10");
	modifierid=lookup_widget(objet_graphique,"modifierid");
	window1 = lookup_widget(objet_graphique,"IntermedEditTrou");
	labelmod=lookup_widget(objet_graphique,"labelmod");
	entry4=lookup_widget(objet_graphique,"entry4");
	y=maj(gtk_entry_get_text(GTK_ENTRY(entry4)));
	if(strcmp("",gtk_entry_get_text(GTK_ENTRY(entry4)))==0)
	{
	gtk_label_set_markup(GTK_LABEL(labelmod),"<span  foreground='#f90922'> *le champ est vide!!! </span>");
	gtk_widget_show(img9);
	gtk_widget_hide(img10);
	}
	else
	if(y==1)
	{
	gtk_label_set_markup(GTK_LABEL(labelmod),"<span  foreground='#f90922'> *entrer des MAJUSCULE et des chiffres!!! </span>");
	gtk_widget_show(img9);
	gtk_widget_hide(img10);
	}
	else
	if((y!=1)&&(strcmp("",gtk_entry_get_text(GTK_ENTRY(entry4)))!=0))
	{
	strcpy(idf0,gtk_entry_get_text(GTK_ENTRY(entry4)));
	x=idmodifier(idf0);
	if(x==1)
	{
	gtk_widget_destroy(window1);
	window2 = create_editTrou ();
  	gtk_widget_show (window2);
	GtkWidget *entry2;
	GtkWidget *combobox3;
	GtkWidget *combobox4;
	GtkWidget *calendar2;
	GtkWidget *labelnomt;
	GtkWidget *img7;
	GtkWidget *img8;
	GtkWidget *img20;
	GtkWidget *img21;
	GtkWidget *l2;
	l2=lookup_widget(window2,"l2");
	img20=lookup_widget(window2,"img20");
	img21=lookup_widget(window2,"img21");
	img7=lookup_widget(window2,"img7");
	img8=lookup_widget(window2,"img8");
	labelnomt=lookup_widget(window2,"labelnomt");
	entry2=lookup_widget(window2,"entry2");
	combobox3=lookup_widget(window2,"combobox3");
	combobox4=lookup_widget(window2,"combobox4");
	calendar2=lookup_widget(window2,"calendar2");
	gtk_label_set_text(GTK_LABEL(labelnomt),"");
	gtk_label_set_text(GTK_LABEL(l2),"");
	gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(entry2),10);
	gtk_widget_hide(img7);
	gtk_widget_hide(img8);
	gtk_widget_hide(img20);
	gtk_widget_hide(img21);
	FILE *f;
	troupeau t;
	char  nomt[30],nom1[30],nom2[30],idf[30];
	int d,m,a;
	f=fopen("../DataBase/projet.txt","r");
	if(f!=NULL)
	    {


		
		while(fscanf(f,"%s %s %s %s %d %d %d\n",nomt,nom1,nom2,idf,&d,&m,&a)!=EOF)
		{
		    	if(strcmp(idf0,idf)==0)
			{
			
		    		strcpy(t.type,nomt);
		    		strcpy(t.name,nom1);
		    		strcpy(t.genre,nom2);
		    		t.birth.jour=d;
		    		t.birth.mois=m;
		    		t.birth.annee=a;
				FILE *e;
				e=fopen("../DataBase/id.txt","w");
				fprintf(e,"%s",idf0);
				fclose(e);
		    	}	
		    
		}
		
		fclose(f);
	     }
	gtk_entry_set_text(GTK_ENTRY(entry2),t.name);
	if(strcmp(t.type,"brebi")==0)
	{
	gtk_combo_box_set_active(combobox4,0);

	}
	if(strcmp(t.type,"veaux")==0)
	{
	gtk_combo_box_set_active(combobox4,1);
	}
	if(strcmp(t.genre,"male")==0)
	{
	gtk_combo_box_set_active(combobox3,0);
	}
	if(strcmp(t.genre,"female")==0)
	{
	gtk_combo_box_set_active(combobox3,1);
	}
	gtk_calendar_select_day(calendar2,t.birth.jour);
	gtk_calendar_select_month(calendar2,t.birth.mois-1,t.birth.annee);
	zeta=0;

	}
	else
	{
	gtk_label_set_markup(GTK_LABEL(labelmod),"<span  foreground='#f90922'> *l'id n'existe pas!!! </span>");
	gtk_widget_show(img9);
	gtk_widget_hide(img10);
	}

	}

}


void
on_RetourInterEditGes_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"IntermedEditTrou");
	window2 = create_Gestrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewTroup");	
	affichage(treeview);
}


void
on_saveEditTrou_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	troupeau p;
	FILE *f;
	int *d,*m,*a;
	char id[10],inf[100];
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *combobox3;
	GtkWidget *entry2;
	GtkWidget *entry4;
	GtkWidget *combobox4;
	GtkWidget *calendar2;
	GtkWidget *labelnomt;
	GtkWidget *labelinf;
	GtkWidget *img7;
	GtkWidget *img8;
	GtkWidget *img20;
	GtkWidget *img21;
	GtkWidget *l2;
	GdkColor color;
	GdkColor color1;
	GdkColor color2;
	GtkWidget *labelmod;
	
	int y,s;
	d=&p.birth.jour;
	m=&p.birth.mois;
	a=&p.birth.annee;

	f=fopen("../DataBase/id.txt","r");
	fscanf(f,"%s",id);
	fclose(f);
	img20=lookup_widget(objet_graphique,"img20");
	img21=lookup_widget(objet_graphique,"img21");
	l2=lookup_widget(objet_graphique,"l2");
	img7=lookup_widget(objet_graphique,"img7");
	img8=lookup_widget(objet_graphique,"img8");
	calendar2=lookup_widget(objet_graphique,"calendar2");
	combobox3=lookup_widget(objet_graphique,"combobox3");
	combobox4=lookup_widget(objet_graphique,"combobox4");
	labelnomt=lookup_widget(objet_graphique,"labelnomt");
	entry2=lookup_widget(objet_graphique,"entry2");
	strcpy(p.name,gtk_entry_get_text(GTK_ENTRY(entry2)));
	strcpy(p.genre,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox3)));
	strcpy(p.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox4)));
	gtk_calendar_get_date(calendar2,a,m,d);
	++*m;
	s=verif( p.birth.jour,p.birth.mois,p.birth.annee, h);
	y=alpha(p.name);
	if(s==1)
	{
	gtk_label_set_markup(GTK_LABEL(l2),"<span  foreground='#f90922'> *verifier la date!!! </span>");
	gtk_widget_show(img21);
	gtk_widget_hide(img20);
	}
	else
	{
	gtk_label_set_text(GTK_LABEL(l2),"");
	gtk_widget_hide(img21);
	gtk_widget_show(img20);
	}

	if(strcmp(p.name,"")==0)
	{

	gtk_label_set_markup(GTK_LABEL(labelnomt),"<span  foreground='#f90922'> *le champ nom est vide!!! </span>");
	gtk_widget_show(img7);
	gtk_widget_hide(img8);
	}
	else
	{
	if(y==1)
	{
	gtk_label_set_markup(GTK_LABEL(labelnomt),"<span  foreground='#f90922'> *entrer des alphabets!!! </span>");
	gtk_widget_show(img7);
	gtk_widget_hide(img8);
	}
	else
	{
	gtk_widget_hide(img7);
	gtk_widget_show(img8);
	gtk_label_set_text(labelnomt,"");
	}
	}
	
	if((y!=1)&&(s==0))
	{
	


	
	modifierTrou( id, p);

	window1 = lookup_widget(objet_graphique,"editTrou");
	gtk_widget_destroy(window1);
	window2 = create_SuccessEdit ();
        gtk_widget_show (window2);

	



	}

}


void
on_RetourInterModifTrou_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"editTrou");
	
	//gtk_widget_destroy(window1);
/////////////////////////////////////////////////////////////////////////////////////////

GtkWidget *entry4;
GtkWidget *labelmod;
GtkWidget *labelinf;
GtkWidget *img9;
GtkWidget *img10;




if(zeta==0)
{


gtk_widget_destroy(window1);
window2 = create_IntermedEditTrou ();
gtk_widget_show (window2);
entry4=lookup_widget(window2,"entry4");
labelmod=lookup_widget(window2,"labelmod");
labelinf=lookup_widget(window2,"labelinf");
img9=lookup_widget(window2,"img9");
img10=lookup_widget(window2,"img10");
gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(entry4),5);
gtk_entry_set_text(GTK_ENTRY(entry4),"");
gtk_label_set_text(GTK_LABEL(labelmod),"");
gtk_label_set_text(GTK_LABEL(labelinf),"");
gtk_widget_hide(img9);
gtk_widget_hide(img10);
}

if(zeta==1)
{
gtk_widget_destroy(window1);
}






}


void
on_confirmNombreTrou_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *window1;
GtkWidget *typeinf;
GtkWidget *tpi;
GdkColor color;
window1=lookup_widget(objet_graphique,"NumberTrou");

int *b,*v,*t,a=0,e=0,c=0;
char inf[50],rec[10];
b=&a;
v=&e;
t=&c;
nombre(b,v,t);
if(xx==1)
{
gtk_widget_destroy(window1);
typeinf=create_typeinf();
gtk_widget_show(typeinf);
tpi=lookup_widget(typeinf,"tpi");
sprintf(rec,"%d",a);
strcpy(inf,"Le nombre de brebis est: ");
strcat(inf,rec);
gdk_color_parse("black",&color);
gtk_widget_modify_fg(tpi,GTK_STATE_NORMAL,&color);
gtk_label_set_text(tpi,inf);


} 
else
if(xx==2)
{
gtk_widget_destroy(window1);
typeinf=create_typeinf();
gtk_widget_show(typeinf);
tpi=lookup_widget(typeinf,"tpi");
sprintf(rec,"%d",e);
strcpy(inf,"Le nombre de veaux est: ");
strcat(inf,rec);
gdk_color_parse("black",&color);
gtk_widget_modify_fg(tpi,GTK_STATE_NORMAL,&color);
gtk_label_set_text(tpi,inf);
}
else
if(xx==3)
{
gtk_widget_destroy(window1);
typeinf=create_typeinf();
gtk_widget_show(typeinf);
tpi=lookup_widget(typeinf,"tpi");
sprintf(rec,"%d",c);
strcpy(inf,"Le nombre totale du troupeaux est: ");
strcat(inf,rec);
gdk_color_parse("black",&color);
gtk_widget_modify_fg(tpi,GTK_STATE_NORMAL,&color);
gtk_label_set_text(tpi,inf);
}
xx=3;


}


void
on_BackNombreGesTrou_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"NumberTrou");
	window2 = create_Gestrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewTroup");	
	affichage(treeview);
}


void
on_totaleType_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
xx=3;

}


void
on_brebiType_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
xx=1;
}


void
on_veauxType_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
xx=2;

}


void
on_backDelTrou_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"DelTrou");
	window2 = create_Gestrou ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;	
	treeview = lookup_widget(window2,"treeviewTroup");	
	affichage(treeview);
}


void
on_okType_clicked                      (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *window1 ;
GtkWidget *typeinf;
GtkWidget *totaleType;
typeinf=lookup_widget(objet,"typeinf");
gtk_widget_destroy(typeinf);
window1 = create_NumberTrou ();
gtk_widget_show (window1);
totaleType=lookup_widget(window1 ,"totaleType");
gtk_toggle_button_set_active (totaleType,"TRUE");

}


void
on_oppmod_clicked                      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
char idf0[30];
GtkWidget *alerteopp;
alerteopp=lookup_widget(objet_graphique,"alerteopp");
gtk_widget_destroy(alerteopp);
GtkWidget *editTrou;
FILE *k;
k=fopen("../DataBase/id.txt","r");
fscanf(k,"%s",idf0);
fclose(k);
//modifiertroupeaux=lookup_widget(objet_graphique,"modifiertroupeaux");
editTrou = create_editTrou ();
gtk_widget_show (editTrou);
GtkWidget *entry2;
GtkWidget *combobox3;
GtkWidget *combobox4;
GtkWidget *calendar2;
GtkWidget *labelnomt;
GtkWidget *img7;
GtkWidget *img8;
GtkWidget *img20;
GtkWidget *img21;
GtkWidget *l2;
l2=lookup_widget(editTrou,"l2");
img20=lookup_widget(editTrou,"img20");
img21=lookup_widget(editTrou,"img21");
img7=lookup_widget(editTrou,"img7");
img8=lookup_widget(editTrou,"img8");
labelnomt=lookup_widget(editTrou,"labelnomt");
entry2=lookup_widget(editTrou,"entry2");
combobox3=lookup_widget(editTrou,"combobox3");
combobox4=lookup_widget(editTrou,"combobox4");
calendar2=lookup_widget(editTrou,"calendar2");
gtk_label_set_text(GTK_LABEL(labelnomt),"");
gtk_label_set_text(GTK_LABEL(l2),"");
gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(entry2),10);
gtk_widget_hide(img7);
gtk_widget_hide(img8);
gtk_widget_hide(img20);
gtk_widget_hide(img21);
FILE *f;
troupeau t;
char  nomt[30],nom1[30],nom2[30],idf[30];
int d,m,a;
f=fopen("../DataBase/projet.txt","r");
if(f!=NULL)
    {


        
        while(fscanf(f,"%s %s %s %s %d %d %d\n",nomt,nom1,nom2,idf,&d,&m,&a)!=EOF)
        {
	    	if(strcmp(idf0,idf)==0)
		{
		
            		strcpy(t.type,nomt);
            		strcpy(t.name,nom1);
            		strcpy(t.genre,nom2);
            		t.birth.jour=d;
            		t.birth.mois=m;
            		t.birth.annee=a;
			FILE *e;
			e=fopen("../DataBase/id.txt","w");
			fprintf(e,"%s",idf0);
			fclose(e);
            	}	
            
        }
        
        fclose(f);
     }
gtk_entry_set_text(GTK_ENTRY(entry2),t.name);
if(strcmp(t.type,"brebi")==0)
{
gtk_combo_box_set_active(combobox4,0);

}
if(strcmp(t.type,"veaux")==0)
{
gtk_combo_box_set_active(combobox4,1);
}
if(strcmp(t.genre,"male")==0)
{
gtk_combo_box_set_active(combobox3,0);
}
if(strcmp(t.genre,"female")==0)
{
gtk_combo_box_set_active(combobox3,1);
}
gtk_calendar_select_day(calendar2,t.birth.jour);
gtk_calendar_select_month(calendar2,t.birth.mois-1,t.birth.annee);
zeta=1;


}


void
on_oppsupp_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *window1;
//GtkWidget *fin;
GtkWidget *alerteopp;
GdkColor color;






int *k,a=0;
char id0[10];
troupeau tab[100];
k=&a;
alerteopp=lookup_widget(objet_graphique,"alerteopp");
gtk_widget_destroy(alerteopp);
FILE *f;
f=fopen("../DataBase/id.txt","r");
fscanf(f,"%s",id0);
fclose(f);
supprimerTrou(tab,100,id0,k);
window1 = create_successDel ();
gtk_widget_show (window1 );
/*fin=lookup_widget(suppfin,"fin");
gdk_color_parse("black",&color);
gtk_widget_modify_fg(fin,GTK_STATE_NORMAL,&color);
gtk_label_set_text(fin,id0);*/


}


void
on_anuller_clicked                     (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *alerteopp;
alerteopp=lookup_widget(objet,"alerteopp");
gtk_widget_destroy(alerteopp);


}


void
on_capAlarm_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"gestionCap");
	window2 = create_capAlarmante ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);


	GtkWidget *treeview;

	treeview=lookup_widget(window2,"treeviewAlar");
	capteur_alarmante();
	valeur_alarmante(treeview);
	remove("../DataBase/alarmante.txt");
}




void
on_toCapDef_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *treeviewDefect;
	window1 = lookup_widget(objet,"gestionCap");
	window2 = create_capDeff ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	treeviewDefect=lookup_widget(window2,"treeviewDefect");
	defectuex();
	afficherdef(treeviewDefect);
	remove("../DataBase/capteurdef.txt");
}


void
on_backDefToGesCapp_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"capDeff");
	window2 = create_gestionCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewCap");
	afficher_capteur(treeview);
}


void
on_backcapAlar_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"capAlarmante");
	window2 = create_gestionCap ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
	GtkWidget *treeview;
	treeview = lookup_widget(window2,"treeviewCap");
	afficher_capteur(treeview);
}


void
on_backBestOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"bestOuv");
	window2 = create_GestionOuv ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}


void
on_TbuttonAfficheAnSech_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{ 
    GtkWidget *ansech1;
    gchar *str;  
    int a;
    a=anneseche();
    str = g_strdup_printf ("%d",a);
    ansech1 = lookup_widget(objet_graphique,"textviewAnseche") ;
    gtk_label_set_text(GTK_LABEL(ansech1),str);
    g_free (str);

}

void
on_backAnneeSeche_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(objet,"windowAnSech");
	window2 = create_menu ();
  	gtk_widget_show (window2);
	gtk_widget_destroy(window1);
}

