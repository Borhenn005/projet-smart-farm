/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
  GtkWidget *Login;
  GtkWidget *createAccount;
  GtkWidget *menu;
/*-------- GESTION DE CLIENT --------*/
  GtkWidget *GesClient;
  GtkWidget *addClient;
  GtkWidget *delClient;
  GtkWidget *editClient;
/*-------- POP UP --------*/
  GtkWidget *successDel;
  GtkWidget *alerteDel;
  GtkWidget *SuccessEdit;
  GtkWidget *successAdd;

  GtkWidget *alerteSecurite;
/*-------- GESTION DES OUVRIER --------*/
  GtkWidget *GestionOuv;
  GtkWidget *AddOuv;
  GtkWidget *DeleteOuv;
  GtkWidget *editOuv;
  GtkWidget *fichepres;
  GtkWidget *TauxAbsc;
  GtkWidget *bestOuv;
/*-------- GESTION DE PLANTATION --------*/
  GtkWidget *GesPlantation;
  GtkWidget *addPlant;
  GtkWidget *delPlant;
  GtkWidget *editPlant;
/*-------- GESTION DES EQUIPEMENTS --------*/
  GtkWidget *GesEquipement;
  GtkWidget *addEquipement;
  GtkWidget *editEquipement;
  GtkWidget *delEquipement;
/*-------- GESTION DE CAPTEUR --------*/
  GtkWidget *gestionCap;
  GtkWidget *AddCap;
  GtkWidget *EditCap;
  GtkWidget *DelCap;
/*-------- GESTION DE TROUPEAUX --------*/
  GtkWidget *addTrou;
  GtkWidget *Gestrou;
  GtkWidget *DelTrou;
  GtkWidget *IntermedEditTrou;
  GtkWidget *editTrou;
  GtkWidget *NumberTrou;
  GtkWidget *typeinf;
  GtkWidget *capDeff;
  GtkWidget *capAlarmante;
  GtkWidget *windowAnSech;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory ("../pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  Login = create_Login ();
  gtk_widget_show (Login);

  /*menu = create_menu ();
  gtk_widget_show (menu);*/

/*-------- GESTION DE CLIENT --------*/

  /*GesClient = create_GesClient ();
  gtk_widget_show (GesClient);
  addClient = create_addClient ();
  gtk_widget_show (addClient);
  delClient = create_delClient ();
  gtk_widget_show (delClient);
  editClient = create_editClient ();
  gtk_widget_show (editClient);*/

/*-------- POP UP --------*/

  /*successDel = create_successDel ();
  gtk_widget_show (successDel);
  alerteDel = create_alerteDel ();
  gtk_widget_show (alerteDel);
  SuccessEdit = create_SuccessEdit ();
  gtk_widget_show (SuccessEdit);
  successAdd = create_successAdd ();
  gtk_widget_show (successAdd);*/

/*-------- GESTION DES OUVRIERS --------*/

/*  GestionOuv = create_GestionOuv ();
  gtk_widget_show (GestionOuv);
  AddOuv = create_AddOuv ();
  gtk_widget_show (AddOuv);
  DeleteOuv = create_DeleteOuv ();
  gtk_widget_show (DeleteOuv);
  editOuv = create_editOuv ();
  gtk_widget_show (editOuv);
  fichepres = create_fichepres ();
  gtk_widget_show (fichepres);
  TauxAbsc = create_TauxAbsc ();
  gtk_widget_show (TauxAbsc);
  bestOuv = create_bestOuv ();
  gtk_widget_show (bestOuv);
*/

/*-------- GESTION DE PLANTATION --------*/

/*
  GesPlantation = create_GesPlantation ();
  gtk_widget_show (GesPlantation);
  addPlant = create_addPlant ();
  gtk_widget_show (addPlant);
  delPlant = create_delPlant ();
  gtk_widget_show (delPlant);
  editPlant = create_editPlant ();
  gtk_widget_show (editPlant);
*/
/*-------- GESTION DES EQUIPEMENTS --------*/
/*
  GesEquipement = create_GesEquipement ();
  gtk_widget_show (GesEquipement);
  addEquipement = create_addEquipement ();
  gtk_widget_show (addEquipement);
  editEquipement = create_editEquipement ();
  gtk_widget_show (editEquipement);
  delEquipement = create_delEquipement ();
  gtk_widget_show (delEquipement);
*/
/*-------- GESTION DE CAPTEUR --------*/
/*
  gestionCap = create_gestionCap ();
  gtk_widget_show (gestionCap);
  AddCap = create_AddCap ();
  gtk_widget_show (AddCap);
  EditCap = create_EditCap ();
  gtk_widget_show (EditCap);
  DelCap = create_DelCap ();
  gtk_widget_show (DelCap);
  capDeff = create_capDeff ();
  gtk_widget_show (capDeff);
  capAlarmante = create_capAlarmante ();
  gtk_widget_show (capAlarmante);


*/
  
/*-------- GESTION DE TROUPEAUX --------*/
/*
  addTrou = create_addTrou ();
  gtk_widget_show (addTrou);
  Gestrou = create_Gestrou ();
  gtk_widget_show (Gestrou);
  DelTrou = create_DelTrou ();
  gtk_widget_show (DelTrou);
  IntermedEditTrou = create_IntermedEditTrou ();
  gtk_widget_show (IntermedEditTrou);
  editTrou = create_editTrou ();
  gtk_widget_show (editTrou);
  NumberTrou = create_NumberTrou ();
  gtk_widget_show (NumberTrou);
  typeinf=create_typeinf();
  gtk_widget_show(typeinf);

*/
/*
  createAccount = create_createAccount ();
  gtk_widget_show (createAccount);
  alerteSecurite = create_alerteSecurite ();
  gtk_widget_show (alerteSecurite);

 windowAnSech = create_windowAnSech ();
  gtk_widget_show (windowAnSech);
*/
  gtk_main();
  return 0;
}
