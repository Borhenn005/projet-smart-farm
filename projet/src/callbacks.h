#include <gtk/gtk.h>

/*------------------------- INTERFACE DE LOGIN ------------------------------*/

void
on_seConnecter_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_createAccount_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

/*------------------------------------ MENU -----------------------------------*/

void
on_toGesOuv_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toGesClient_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toGesCap_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toGesCal_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toYearSeche_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toGesTrou_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toGesEqui_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_logout_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data);

/*--------------------------------- GESTION DES CLIENTS ----------------------------------*/

void
on_goToAddClient_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_goToEditClient_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeviewClient_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_homeClient_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_refreshTreeClient_clicked           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_goToDeleteClient_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backAddClient_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_confirmeAddClient_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backDelClient_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_delClientConfirm_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backEditClient_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_consulterClient_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_confirmerEditClient_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

/*---------------------------- POP_UP ----------------------------------*/

void
on_OksuccessDel_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_dontshowmessage_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_confirmeSuppPopup_clicked           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_cancelDelPopup_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_OkSuccessEdit_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_okSuccessAdd_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

/*--------------------------------- GESTION DES OUVRIERS ----------------------------------*/


void
on_homeGesOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeviewOuv_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_goToAddOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_goToEditOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_goToDelOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_goToFichePres_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_goToTauxAbsen_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toBestOuv_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_refreshTreeOuv_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_radioFemmeOuv_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioHommeOuv_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_refreshAddOuv_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_confirmerAddOuv_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backAddOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_SuppOuv_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backDelOuv_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_consulterOuv_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backEditOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_saveEditOuv_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_refreshEditOuv_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_SauvegardePres_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backFichePres_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_present_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_absent_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_backTauxAbsen_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ShowTaux_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);


/*--------------------------------- GESTION DE PLANTATION ----------------------------------*/
void
on_refreshTreePlant_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeviewPlant_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_toAddPlant_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toEditPlant_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ToDelPlant_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_homePlant_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_confirmeAddPlant_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backAddPlant_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_confirmeDelPlant_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backDelPlant_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_consultPlant_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_saveEditPlant_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backEditPlant_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

/*--------------------------------- GESTION DES EQUIPEMENTS ----------------------------------*/

void
on_treeviewEqui_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_homeEqui_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toAddEqui_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toEditEqui_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toDelEqui_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_refreshTreeEqui_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backAddEquipe_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ConfirmeAddEqui_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backEditEquipe_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_consultEqui_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_saveEditEquipe_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_confirmDelEqui_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backDelEqui_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data);


/*--------------------------------- GESTION DE CAPTEUR ----------------------------------*/
void
on_treeviewCap_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_refreshTreeCap_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toDelCap_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toEditCap_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toAddCap_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_homeCap_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backAddCap_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_radiobuttonHumAdd_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonTempAdd_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonDefctAdd_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonFoncAdd_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_confirmeAddCap_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_consultCap_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_radiobuttonTempEdit_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonFonctEdit_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonHumEdit_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonDefecEdit_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_backEditCap_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_saveEditCap_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ConfirmDelCap_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backDelCap_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

/*--------------------------------- GESTION DE TROUPEAUX ----------------------------------*/

void
on_backAddTrou_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ConfirmAddTrou_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_treeviewTroup_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_toAddTrou_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toInterEditTrou_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toDelTrou_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_brebiGes_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_veauxGes_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_homeTrou_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_refreshTreeTroup_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_toNumberTrou_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_confirmDelsupptrou_clicked          (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_ToEditTrou_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_RetourInterEditGes_clicked          (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_saveEditTrou_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_RetourInterModifTrou_clicked        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_confirmNombreTrou_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_BackNombreGesTrou_clicked           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_totaleType_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_brebiType_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_veauxType_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_backDelTrou_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_okType_clicked                      (GtkButton       *objet,
                                        gpointer         user_data);

void
on_oppmod_clicked                      (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_oppsupp_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_anuller_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_confirmeCreateAccount_clicked       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_admin_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_employer_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_entrerKey_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backalerteLogin_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_createaccountTologin_clicked        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_showBestOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);




void
on_capAlarm_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_toCapDef_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backDefToGesCapp_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backcapAlar_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_backBestOuv_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_TbuttonAfficheAnSech_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_backAnneeSeche_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);
