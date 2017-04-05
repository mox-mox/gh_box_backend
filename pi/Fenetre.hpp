#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/main.h>
#include <gtkmm/notebook.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>
#include <gtkmm/table.h>
#include <gtkmm/alignment.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/spinbutton.h>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdio>
#include <gtkmm/radiobutton.h>
#include <sstream>
//#include <cstdint>
#include "message.hpp"	


using namespace std;


class Fenetre : public Gtk::Window {
    public :
    Fenetre();
    void modifierTitre(Gtk::Widget* page, int numPage);
	void modifierTexte();
	
        
    private :
	Message_interface arduino;
    Gtk::Notebook barreOnglets;
    Gtk::HButtonBox boiteBoutonsH;

	Gtk::Image plante1;
	Gtk::Image plante2;
	Gtk::Image plante3;
	Gtk::Image plante4;
	Gtk::Image attention_ph;
	Gtk::Image attention_ec;
	Gtk::Image validate;
	Gtk::Image validate2;
	Gtk::Image erreur;

	Gtk::VBox boiteV;
	Gtk::VBox acceuil_box;
	Gtk::VBox onGoingPlant1_box;
	Gtk::VBox onGoingPlant2V_box;
	Gtk::HBox onGoingPlant2H_box;
	Gtk::HBox onGoingPlant2H2_box;
	Gtk::VBox fonctionnement_box;
	Gtk::VBox newPlant1_box;
	Gtk::VBox newPlant2V_box;
	Gtk::VBox cancelPlantV_box;
	Gtk::HBox cancelPlantH_box;
	Gtk::HBox cancelPlantH2_box;
	Gtk::HBox newPlant2H_box;
	Gtk::HBox newPlant1_plant_box;
	Gtk::HBox newPlant2_plant_box;
	Gtk::HBox seedsOrder1_box;
	Gtk::HBox seedsOrder2_box;
	Gtk::HBox seedsOrder3_box;
	Gtk::VBox seedsOrder_box;
	Gtk::VBox phProblemV_box;
	Gtk::HBox phProblemH1_box;
	Gtk::HBox phProblemH2_box;
	Gtk::VBox ecProblemV_box;
	Gtk::HBox ecProblemH1_box;
	Gtk::HBox ecProblemH2_box;
	Gtk::VBox confirmationTomatoV_box;
	Gtk::HBox confirmationTomatoH_box;
	Gtk::VBox orderSuccessful_box;
	Gtk::VBox plantSuccessfulV_box;
	Gtk::HBox plantSuccessfulH_box;
	Gtk::VBox removeSuccessfulV_box;
	Gtk::HBox removeSuccessfulH_box;
	Gtk::HBox attenteplanteH_box;
	Gtk::VBox attenteplanteV_box;
	Gtk::HBox demoH1_box;
	Gtk::HBox demoH2_box;
	Gtk::HBox demoH3_box;
	Gtk::HBox demoH25_box;
	Gtk::HBox demoH35_box;
	Gtk::HBox demoH4_box;
	Gtk::HBox demoH5_box;
	Gtk::HBox demoH6_box;
	Gtk::VBox demoV_box;


	Gtk::Label label_newPlant1;
	Gtk::Label label_newPlant2;
	Gtk::Label label_fonctionnement;
	Gtk::Label label_onGoingPlant1;	
	Gtk::Label label_onGoingPlant2;
	Gtk::Label label_onGoingPlant2_2;
	Gtk::Label label_seedsOrder1;
	Gtk::Label label_seedsOrder2;
	Gtk::Label label_orderSuccessful;
	Gtk::Label label_confirmationTomato;
	Gtk::Label label_phProblem;
	Gtk::Label label_ecProblem;
	Gtk::Label label_plantSuccessful;
	Gtk::Label label_removeSuccessful;
	Gtk::Label label_cancelPlant;
	Gtk::Label label_attenteplante;
	Gtk::Label label_demo1;
	Gtk::Label label_demo2;
	Gtk::Label label_demo3;
	Gtk::Label label_demo25;
	Gtk::Label label_demo35;
	Gtk::Label label_demo4;
	Gtk::Label label_demo5;
	Gtk::Label label_demo6;


	Gtk::Button bouton_accueil_fonctionnement;
	Gtk::Button bouton_accueil_newPlant;
	Gtk::Button bouton_accueil_onGoingPlant;
	Gtk::Button bouton_accueil_seedsOrder;
	Gtk::Button bouton_accueil_demo;
	Gtk::Button bouton_demo_acceuil;
	Gtk::Button bouton_demo_confirmation;
    Gtk::Button bouton1;
	Gtk::Button bouton_fonctionnement_acceuil;
	Gtk::Button bouton_cancelPlant;
	Gtk::Button bouton_onGoingPlant1_acceuil;
	Gtk::Button bouton_onGoingPlant2_acceuil;
	Gtk::Button bouton_newPlant1_acceuil;
	Gtk::Button bouton_newPlant2_tomate;
	Gtk::Button bouton_newPlant2_salade;
	Gtk::Button bouton_newPlant2_fraise;
	Gtk::Button bouton_newPlant2_basilic;
	Gtk::Button bouton_seedsOrder_confirmation;
	Gtk::Button bouton_newPlant2_acceuil;
	Gtk::Button bouton_seedsOrder_acceuil;
	Gtk::Button bouton_confirmationTomato_acceuil;
	Gtk::Button bouton_confirmationTomato_dataCheck;
	Gtk::Button bouton_phProblem_explicationPh;
	Gtk::Button bouton_phProblem_acceuil;
	Gtk::Button bouton_phProblem_confirmation;
	Gtk::Button bouton_ecProblem_explicationEC;
	Gtk::Button bouton_ecProblem_acceuil;
	Gtk::Button bouton_ecProblem_confirmation;
	Gtk::Button bouton_onGoingPlant2_newPlant;	
	Gtk::Button bouton_orderSuccessful_acceuil;
	Gtk::Button bouton_plantSuccessful_acceuil;
	Gtk::Button bouton_removeSuccessful_acceuil;
	Gtk::Button bouton_cancelPlant_acceuil;
	Gtk::Button bouton_cancelPlant_confirmation;
	Gtk::RadioButtonGroup groupe; //Création d'un groupe.
    Gtk::RadioButton boutonRadio1, boutonRadio2, boutonRadio3, boutonRadio4; //Création de boutons radio.
	Gtk::Button bouton_onGoingPlant2_cancelPlant;
	Gtk::Button bouton_attenteplante_accueil;
	Gtk::Button bouton_attenteplante_confirmation;
	Gtk::SpinButton spinbutton; //Bouton compteur
	Gtk::SpinButton spin_pump_time; //Bouton compteur
	Gtk::SpinButton spin_light_time; //Bouton compteur
	Gtk::SpinButton spin_pump_intertime; //Bouton compteur
	Gtk::SpinButton spin_light_intertime; //Bouton compteur
	Gtk::SpinButton spin_ph; //Bouton compteur
	Gtk::SpinButton spin_ec; //Bouton compteur
	Gtk::SpinButton spin_temp; //Bouton compteur
	//Gtk::SpinButton spinbutton; //Bouton compteur
	//Gtk::SpinButton spinbutton; //Bouton compteur


	Gtk::ComboBoxText listeDeroulante;
	//string label_cancelPlant;



	string plantelulz;
	int compteur;
	int compteur1;
	int jeanclaude;


	double produit1_ph;
	uint32_t produit1_temperature;
	float produit1_ec;

	double ph_voulu;
	int temp_voulu;
	float ec_voulu;

	uint32_t produit1_temps_pousse;

	string temperature;
	string PH;
	string EC;

	void changerpage(int page);
	void set_current_page (int page_number);
	void afficher();
	void on_spinbutton_changed();
	void on_spin_pump_time_changed();
	void on_spin_light_time_changed();
	void on_spin_pump_intertime_changed();
	void on_spin_light_intertime_changed();
	void fileWrite(string produit);
	void confirmationProduit_setLabel(string produit);
	void onGoingPlant_setLabel();
	void compterligne();
	void enleverPlante(string produit);
	void setparametres(string produit);
	void on_spin_temp_changed();
	void on_spin_ec_changed();
	void on_spin_ph_changed();
	string ToString(int T);
	string ToStringd(double T);
	string ToStringf(float T);

};

#endif
