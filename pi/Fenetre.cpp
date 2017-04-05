222222
22222222222222222222222222222#include "Fenetre.hpp"

Fenetre::Fenetre() : 
	arduino(),
bouton_accueil_fonctionnement("Fonctionnement du système"), 
bouton_accueil_newPlant("Placer une nouvelle plante"),
bouton_accueil_onGoingPlant("Voir les plantes en cours"), 
bouton_accueil_seedsOrder("Commander de nouvelles pousses"),
bouton_fonctionnement_acceuil("Retour"),
bouton_newPlant1_acceuil("Retour"),
label_newPlant1("Placer une nouvelle plante"),
label_seedsOrder2("Quantité à commander"),
bouton_onGoingPlant2_acceuil("Retour"),
bouton1("Bienvenue chez GH | Box. Pour commencer à utiliser l'interface, cliquez sur ce bouton"),
bouton_cancelPlant("Annuler la plante en cours"),
bouton_orderSuccessful_acceuil("Retour à l'acceuil"),
label_orderSuccessful("Commande réussie, vous recevrez les pousses d'ici 6 jours ouvrés."),
bouton_onGoingPlant1_acceuil("Retour"),
bouton_newPlant2_acceuil("Retour"),
bouton_seedsOrder_acceuil("Retour"),
label_seedsOrder1("Liste des pousses"),
bouton_newPlant2_tomate("Choisir"),
bouton_newPlant2_basilic("Choisir"),
bouton_newPlant2_fraise("Choisir"),
bouton_newPlant2_salade("Choisir"),
bouton_seedsOrder_confirmation("Commander"),
bouton_confirmationTomato_acceuil("Annuler et retourner à l'accueil"),
bouton_confirmationTomato_dataCheck("Confirmer"),
bouton_phProblem_explicationPh("Explication"),
bouton_phProblem_acceuil("Annuler et retourner à l'acceuil"),
bouton_phProblem_confirmation("Continuer"),
bouton_ecProblem_explicationEC("Explication"),
bouton_ecProblem_acceuil("Annuler et retourner à l'acceuil"),
bouton_ecProblem_confirmation("Continuer"),
label_plantSuccessful("Insertion de la plante réussie, vous êtes un génie !"),
label_removeSuccessful("Retrait de la plante réussi, vous êtes un génie !"),
bouton_plantSuccessful_acceuil("Retour à l'acceuil"),
bouton_removeSuccessful_acceuil("Retour à l'acceuil"),
bouton_cancelPlant_confirmation("Confirmer"),
bouton_cancelPlant_acceuil("Annuler et retourner à l'acceuil"),
bouton_onGoingPlant2_cancelPlant("Enlever une plante du système"), 
boutonRadio1(groupe, "Plante 1"), 
boutonRadio2(groupe, "Plante 2"), 
boutonRadio3(groupe, "Plante 3"),
boutonRadio4(groupe, "Plante 4"),
bouton_attenteplante_accueil("Annuler et retourner à l'accueil"),
bouton_attenteplante_confirmation("Confirmer"),
bouton_demo_acceuil("Retour"),
bouton_demo_confirmation("Valider ces paramètres"),
label_demo1("Choisissez les paramètres de culture"),
label_demo2("Choisissez le temps d'allumage de la pompe (en minutes)"),
label_demo3("Choisissez le temps d'allumage des lumières (en heures)"),
label_demo25("Choisissez le temps entre 2 activations de la pompe (en minutes)"),
label_demo35("Choisissez le temps entre 2 allumages des lumières (en heures)"),
bouton_accueil_demo("Choisir les paramètres")
{
	jeanclaude = 3;
	resize(500, 285);
	set_position(Gtk::WIN_POS_CENTER);


	produit1_ec= arduino.get_ec()/10;
	//std::cout<<"++++++++++++++++ temp = "<<temp<<"+++++++++++++++++++++++++"<<std::endl;

	produit1_ph= arduino.get_ph()/10;
	//std::cout<<"++++++++++++++++ temp = "<<temp<<"+++++++++++++++++++++++++"<<std::endl;

	produit1_temperature= arduino.get_temperature()/10;
	//std::cout<<"++++++++++++++++ temp = "<<temp<<"+++++++++++++++++++++++++"<<std::endl;

	label_phProblem.set_line_wrap();
	label_phProblem.set_markup("Erreur de pH détectée, veuillez contrôler le niveau du pH et appuyer sur <b>Continuer</b> lorque le niveau  est mis à jour. Si vous souhaitez des explications sur cette manipulation, appuyez sur <b>Explication</b>");
	label_ecProblem.set_line_wrap();
	label_ecProblem.set_markup("Erreur d'electro-conductivité détectée, veuillez contrôler le niveau d'electro-conductivité et appuyer sur <b>Continuer</b> lorque le niveau  est mis à jour. Si vous souhaitez des explications sur cette manipulation, appuyez sur <b>Explication</b>");
	label_cancelPlant.set_line_wrap();
	label_cancelPlant.set_markup("Enlevez la plante du système puis appuyez sur <b>Confirmer</b>.\nSi vous souhaitez des explications sur cette manipulation, veuillez vous référer au lien <b>Youtube </b> suivant :\n https://www.youtube.com/watch?v=yhx3JIF7bGU\nPour annuler, appuyez sur <b>Annuler et retourner à l'acceuil</b>");
	label_fonctionnement.set_line_wrap();
	label_fonctionnement.set_markup("Ce système vous permet de faire pousser des fruits et légumes facilement et en peu de temps. Pour commencer, allez dans l'onglet <b> Placer une nouvelle plante </b> et insérez votre pousse dans la serre.\n Ci-dessous, vous trouverez des liens Youtube contenant des explications pour chaque manipulation à réaliser.\n\n Insertion d'une pousse dans le système : https://www.youtube.com/watch?v=yhx3JIF7bGU \n\n Mise à nour du niveau de PH : https://www.youtube.com/watch?v=yhx3JIF7bGU\n\n Mise à jour du niveau de nutriments : https://www.youtube.com/watch?v=yhx3JIF7bGU\n\n Récupérer une plante arrivée à maturité : https://www.youtube.com/watch?v=yhx3JIF7bGU");
	label_attenteplante.set_line_wrap();
	label_attenteplante.set_markup("Insérez votre pousse dans le système et appuyez sur <b>Confirmer </b>.\nSi vous souhaitez des explications sur cette manipulation, veuillez vous référer à ce lien : https://www.youtube.com/watch?v=yhx3JIF7bGU\n Pour annuler, appuyez sur <b>Annuler et retourner à l'accueil </b>");


	add(boiteV);
	add(acceuil_box);
	add(fonctionnement_box);
	add(newPlant1_box);
	add(newPlant2V_box);
	add(newPlant2H_box);
	add(newPlant1_plant_box);
	add(newPlant2_plant_box);
	add(onGoingPlant1_box);
	add(onGoingPlant2V_box);
	add(onGoingPlant2H_box);
	add(seedsOrder_box);
	add(seedsOrder1_box);
	add(seedsOrder2_box);
	add(seedsOrder3_box);
	add(spinbutton);
	add(orderSuccessful_box);
	add(confirmationTomatoV_box);
	add(confirmationTomatoH_box);
	add(phProblemV_box);
	add(phProblemH1_box);  
	add(phProblemH2_box);
	add(ecProblemV_box);
	add(ecProblemH1_box);  
	add(ecProblemH2_box);
	add(plantSuccessfulV_box);
	add(plantSuccessfulH_box);
	add(removeSuccessfulV_box);
	add(removeSuccessfulH_box);
	add(cancelPlantV_box);
	add(cancelPlantH_box);
	add(cancelPlantH2_box);
	add(onGoingPlant2H2_box);
	add(attenteplanteH_box);
	add(attenteplanteV_box);
	add(demoH1_box);
	add(demoH2_box);
	add(demoH25_box);
	add(demoH35_box);
	add(demoH3_box);
	add(demoV_box);

	spinbutton.set_range(0, 100);
	spinbutton.set_value(1);
	spinbutton.set_increments(1, 10);
	spinbutton.signal_changed().connect(sigc::mem_fun(*this, &Fenetre::on_spinbutton_changed));

	spin_pump_time.set_range(0, 100);
	spin_pump_time.set_value(1);
	spin_pump_time.set_increments(1, 10);
	spin_pump_time.signal_changed().connect(sigc::mem_fun(*this, &Fenetre::on_spin_pump_time_changed));

	spin_light_time.set_range(0, 100);
	spin_light_time.set_value(1);
	spin_light_time.set_increments(1, 10);
	spin_light_time.signal_changed().connect(sigc::mem_fun(*this, &Fenetre::on_spin_light_time_changed));

	spin_pump_intertime.set_range(0, 60);
	spin_pump_intertime.set_value(15);
	spin_pump_intertime.set_increments(1, 10);
	spin_pump_intertime.signal_changed().connect(sigc::mem_fun(*this, &Fenetre::on_spin_pump_intertime_changed());

	spin_light_intertime.set_range(0, 24);
	spin_light_intertime.set_value(24);
	spin_light_intertime.set_increments(1, 10);
	spin_light_intertime.signal_changed().connect(sigc::mem_fun(*this, &Fenetre::on_spin_light_intertime_changed));

	
	plante1.set("tomato.png");
	plante2.set("salade.png");
	plante3.set("fraise.png");
	plante4.set("basilic.png");
	attention_ph.set("attention.png");
	attention_ec.set("attention.png");
	validate.set("validate.png");
	validate2.set("validate.png");
	erreur.set("erreur.png");

	fonctionnement_box.pack_start(label_fonctionnement);
	fonctionnement_box.pack_start(bouton_fonctionnement_acceuil);

	newPlant1_box.pack_start(label_newPlant1);
	newPlant1_box.pack_start(newPlant1_plant_box);
	newPlant1_box.pack_start(newPlant2_plant_box);
	newPlant1_box.pack_start(bouton_newPlant1_acceuil);

	newPlant2H_box.pack_start(erreur);
	newPlant2H_box.pack_start(label_newPlant2);

	newPlant2V_box.pack_start(newPlant2H_box);
	newPlant2V_box.pack_start(bouton_cancelPlant);
	newPlant2V_box.pack_start(bouton_newPlant2_acceuil);

	onGoingPlant1_box.pack_start(label_onGoingPlant1);
	onGoingPlant1_box.pack_start(bouton_cancelPlant);
	onGoingPlant1_box.pack_start(bouton_onGoingPlant1_acceuil);
	
	onGoingPlant2H_box.pack_start(bouton_onGoingPlant2_acceuil);
	onGoingPlant2H_box.pack_start(bouton_onGoingPlant2_cancelPlant);
  
	onGoingPlant2H2_box.pack_start(label_onGoingPlant2);
	onGoingPlant2H2_box.pack_start(label_onGoingPlant2_2);

	onGoingPlant2V_box.pack_start(onGoingPlant2H2_box);
	onGoingPlant2V_box.pack_start(onGoingPlant2H_box);

	newPlant1_plant_box.pack_start(plante1);	
	newPlant1_plant_box.pack_start(plante2);
	newPlant1_plant_box.pack_start(plante3);
	newPlant1_plant_box.pack_start(plante4);

	newPlant2_plant_box.pack_start(bouton_newPlant2_tomate);
	newPlant2_plant_box.pack_start(bouton_newPlant2_salade);
	newPlant2_plant_box.pack_start(bouton_newPlant2_fraise);
	newPlant2_plant_box.pack_start(bouton_newPlant2_basilic);

	seedsOrder1_box.pack_start(label_seedsOrder1);
	seedsOrder1_box.pack_start(label_seedsOrder2);

	seedsOrder2_box.pack_start(listeDeroulante);
	seedsOrder2_box.pack_start(spinbutton);

	seedsOrder3_box.pack_start(bouton_seedsOrder_confirmation);
	seedsOrder3_box.pack_start(bouton_seedsOrder_acceuil);

	seedsOrder_box.pack_start(seedsOrder1_box);
	seedsOrder_box.pack_start(seedsOrder2_box);
	seedsOrder_box.pack_start(seedsOrder3_box);

	orderSuccessful_box.pack_start(label_orderSuccessful);
	orderSuccessful_box.pack_start(bouton_orderSuccessful_acceuil);

	confirmationTomatoH_box.pack_start(bouton_confirmationTomato_dataCheck);
	confirmationTomatoH_box.pack_start(bouton_confirmationTomato_acceuil);

	confirmationTomatoV_box.pack_start(label_confirmationTomato);
	confirmationTomatoV_box.pack_start(confirmationTomatoH_box);

	phProblemH1_box.pack_start(attention_ph);
	phProblemH1_box.pack_start(label_phProblem);

	phProblemH2_box.pack_start(bouton_phProblem_explicationPh);
	phProblemH2_box.pack_start(bouton_phProblem_confirmation);
	phProblemH2_box.pack_start(bouton_phProblem_acceuil);

	phProblemV_box.pack_start(phProblemH1_box);
	phProblemV_box.pack_start(phProblemH2_box);

	ecProblemH1_box.pack_start(attention_ec);
	ecProblemH1_box.pack_start(label_ecProblem);

	ecProblemH2_box.pack_start(bouton_ecProblem_explicationEC);
	ecProblemH2_box.pack_start(bouton_ecProblem_confirmation);
	ecProblemH2_box.pack_start(bouton_ecProblem_acceuil);

	ecProblemV_box.pack_start(ecProblemH1_box);
	ecProblemV_box.pack_start(ecProblemH2_box);

	plantSuccessfulH_box.pack_start(validate);
	plantSuccessfulH_box.pack_start(label_plantSuccessful);
	
	plantSuccessfulV_box.pack_start(plantSuccessfulH_box);
	plantSuccessfulV_box.pack_start(bouton_plantSuccessful_acceuil);

	removeSuccessfulH_box.pack_start(validate2);
	removeSuccessfulH_box.pack_start(label_removeSuccessful);
	
	removeSuccessfulV_box.pack_start(removeSuccessfulH_box);
	removeSuccessfulV_box.pack_start(bouton_removeSuccessful_acceuil);

	cancelPlantH_box.pack_start(bouton_cancelPlant_confirmation);
	cancelPlantH_box.pack_start(bouton_cancelPlant_acceuil);

	cancelPlantH2_box.pack_start(boutonRadio1);
	cancelPlantH2_box.pack_start(boutonRadio2);
	cancelPlantH2_box.pack_start(boutonRadio3);
	cancelPlantH2_box.pack_start(boutonRadio4);    

	cancelPlantV_box.pack_start(label_cancelPlant);
	cancelPlantV_box.pack_start(cancelPlantH2_box);
	cancelPlantV_box.pack_start(cancelPlantH_box);

	attenteplanteH_box.pack_start(bouton_attenteplante_accueil);
	attenteplanteH_box.pack_start(bouton_attenteplante_confirmation);

	attenteplanteV_box.pack_start(label_attenteplante);
	attenteplanteV_box.pack_start(attenteplanteH_box);

	demoH1_box.pack_start(label_demo2);
	demoH1_box.pack_start(spin_pump_time);

	demoH2_box.pack_start(label_demo3);
	demoH2_box.pack_start(spin_light_time);

	demoH25_box.pack_start(label_demo25);
	demoH25_box.pack_start(spin_pump_intertime);

	demoH35_box.pack_start(label_demo35);
	demoH35_box.pack_start(spin_light_intertime);

	demoH3_box.pack_start(bouton_demo_acceuil);
	demoH3_box.pack_start(bouton_demo_confirmation);

	demoV_box.pack_start(label_demo1);
	demoV_box.pack_start(demoH1_box);
	demoV_box.pack_start(demoH25_box);
	demoV_box.pack_start(demoH2_box);
	demoV_box.pack_start(demoH35_box);
	demoV_box.pack_start(demoH3_box);


	acceuil_box.pack_start(bouton_accueil_fonctionnement);
	acceuil_box.pack_start(bouton_accueil_newPlant);
	acceuil_box.pack_start(bouton_accueil_onGoingPlant);
	acceuil_box.pack_start(bouton_accueil_demo);
	acceuil_box.pack_start(bouton_accueil_seedsOrder);



	listeDeroulante.append("Tomates");
	listeDeroulante.append("Fraise");
	listeDeroulante.append("Basilic");
	listeDeroulante.append("Salade");
	listeDeroulante.set_active_text("Tomates");
	listeDeroulante.signal_changed().connect(sigc::mem_fun(*this, &Fenetre::afficher));

	boiteV.pack_start(boiteBoutonsH);
    /*
    * Création de la barre d'onglets
    * */

    //S'il y a trop d'onglets, nous pouvons naviguer à l'aide de flèche.
    barreOnglets.set_scrollable();
    //Ajouter un menu contextuel lors du clic-droit pour la navigation.
    barreOnglets.popup_enable();
    //Empêcher la barre d'avoir le focus.
    barreOnglets.set_can_focus(false);

    //Définir le groupe de la barre d'onglets (pour pouvoir échanger des onglets avec d'autres barre d'onglets).
    barreOnglets.set_group_name("Onglets");

    //Ajout d'une page
    //Ajout de l'onglet 0 avec "Bienvenue" écrit sur l'onglet.
    barreOnglets.append_page(bouton1, "Bienvenue");
    //bouton1.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::fileOpen));
    bouton1.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));

    //Ajout de l'onglet 1 avec "Accueil" écrit sur l'onglet.
    barreOnglets.append_page(acceuil_box, "Accueil");
    bouton_accueil_fonctionnement.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 2));
    //bouton_accueil_newPlant.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::compterligne));
    bouton_accueil_newPlant.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 3));
    bouton_accueil_onGoingPlant.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 4));
    bouton_accueil_seedsOrder.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 5));
    bouton_accueil_demo.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 15));
    bouton_accueil_onGoingPlant.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::onGoingPlant_setLabel));


    //Ajout de l'onglet 2 avec "Fonctionnement" écrit sur l'onglet.
    barreOnglets.append_page(fonctionnement_box, "Fonctionnement");
    //Cet onglet ne peut pas être réordonné, ni détaché.
    bouton_fonctionnement_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));

    //Ajout de l'onglet 3 avec "Nouvelle plante" écrit sur l'onglet.
    barreOnglets.append_page(newPlant1_box, "Nouvelle plante");
    bouton_newPlant2_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_newPlant1_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));

    bouton_newPlant2_tomate.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::confirmationProduit_setLabel), "Tomates"));   
    bouton_newPlant2_tomate.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 7));

    bouton_newPlant2_salade.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 7));
    bouton_newPlant2_salade.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::confirmationProduit_setLabel), "Salade"));

    bouton_newPlant2_fraise.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 7));
    bouton_newPlant2_fraise.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::confirmationProduit_setLabel), "Fraises"));

    bouton_newPlant2_basilic.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 7));
    bouton_newPlant2_basilic.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::confirmationProduit_setLabel), "Basilic"));

    bouton_cancelPlant.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 10));


    //Ajout de l'onglet 4 avec "Plante en cours" écrit sur l'onglet.
    barreOnglets.append_page(onGoingPlant2V_box, "Plante en cours");
    bouton_onGoingPlant1_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_onGoingPlant2_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_onGoingPlant2_newPlant.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 3));



    //Ajout de l'onglet 5 avec "Commande de pousses" écrit sur l'onglet.
    barreOnglets.append_page(seedsOrder_box, "Commande de pousses");
    bouton_seedsOrder_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_seedsOrder_confirmation.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 6));


    //Ajout de l'onglet 6 avec "Commande réussie" écrit sur l'onglet.
    barreOnglets.append_page(orderSuccessful_box, "Commande réussie");
    bouton_orderSuccessful_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));

    
    //Ajout de l'onglet 7 avec "Confirmation du choix de la plante" écrit sur l'onglet.
    barreOnglets.append_page(confirmationTomatoV_box, "Confirmation du choix de la plante");
    //cerr << compteur << endl;
    bouton_confirmationTomato_dataCheck.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 13));
    bouton_confirmationTomato_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));

    //bouton_confirmationTomato_dataCheck.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 11));


    //Ajout de l'onglet 8 avec "Problème de PH" écrit sur l'onglet.
    barreOnglets.append_page(phProblemV_box, "Problème de PH");
    bouton_phProblem_explicationPh.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 8));
    bouton_phProblem_confirmation.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 9));
    bouton_phProblem_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_phProblem_confirmation.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::setparametres), plantelulz));
    //bouton_phProblem_confirmation.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::onGoingPlant_setLabel));


    //Ajout de l'onglet 9 avec "Insertion réussie" écrit sur l'onglet.
    barreOnglets.append_page(plantSuccessfulV_box, "Insertion réussie");
    bouton_plantSuccessful_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    


    //Ajout de l'onglet 10 avec "Annulation d'une plante" écrit sur l'onglet.
    barreOnglets.append_page(cancelPlantV_box, "Annulation d'une plante");
    bouton_cancelPlant_confirmation.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::enleverPlante), plantelulz));
    bouton_cancelPlant_confirmation.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 14));
    bouton_cancelPlant_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));

    //Ajout de l'onglet 11 avec "Nouvelle plante" écrit sur l'onglet.
    barreOnglets.append_page(newPlant2V_box, "Nouvelle plante");
    bouton_onGoingPlant2_cancelPlant.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 10));
    //bouton_onGoingPlant2_cancelPlant.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::enleverPlante));

    //Ajout de l'onglet 12 avec "Problème d'electro-conductivité" écrit sur l'onglet.
    barreOnglets.append_page(ecProblemV_box, "Problème d'electro-conductivité");
    bouton_ecProblem_explicationEC.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 8));
    bouton_ecProblem_confirmation.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 9));
    bouton_ecProblem_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_ecProblem_confirmation.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::setparametres), plantelulz));
    //bouton_phProblem_confirmation.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::onGoingPlant_setLabel));

    //Ajout de l'onglet 13 avec "Attente d'une plante" écrit sur l'onglet.
    barreOnglets.append_page(attenteplanteV_box, "Attente d'une plante");
    bouton_attenteplante_accueil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_attenteplante_confirmation.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Fenetre::fileWrite), plantelulz));
    bouton_attenteplante_confirmation.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 9));


    //Ajout de l'onglet 14 avec "Retrait réussi" écrit sur l'onglet.
    barreOnglets.append_page(removeSuccessfulV_box, "Retrait réussi");
    bouton_removeSuccessful_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));

    //Ajout de l'onglet 15 avec "Parametres" écrit sur l'onglet.
    barreOnglets.append_page(demoV_box, "Paramètres");
    bouton_demo_acceuil.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
    bouton_demo_confirmation.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Fenetre::changerpage), 1));
 	

    barreOnglets.set_show_tabs(false);
    boiteV.pack_start(barreOnglets);
    /*
    * Création de la barre d'onglets
    * */
    barreOnglets.signal_switch_page().connect(sigc::mem_fun(*this, &Fenetre::modifierTitre));
    show_all();

}

void Fenetre::modifierTitre(Gtk::Widget* page, int numPage) {
    //Modifier le titre de la fenêtre selon l'onglet choisi.
	set_title(barreOnglets.get_tab_label_text(*barreOnglets.get_nth_page(numPage)));
}

void Fenetre::changerpage(int page) {
	if(page==1)
	{
		compterligne();
		cerr << "La valeur de compteur est : " << compteur << "\n";
		onGoingPlant_setLabel();

	}
	if(page==3)
	{
		if(compteur>3)
		{
			page = 4;
		}
	}

	cerr << "\npage : " << page << " et ec : " << produit1_ec;
	cerr << "\npage : " << page << " et ph : " << produit1_ph;
	if((( page == 3) || (page == 4)) && ((produit1_ph >= 7)||(produit1_ph <= 5 )))
	{
		page = 8;
	}

	if((( page == 3) || (page == 4)) && ((produit1_ec >= 15)||(produit1_ec <= 5 )))
	{
		page = 12;
	}


	barreOnglets.set_current_page (page);
	cerr << "La valeur de page est " << page << "\n";
    //  cerr << "La valeur de compteur est mdr : " << compteur << "\n";
}

void Fenetre::afficher() {
    //Affiche le texte sélectionné.
	Gtk::MessageDialog dialogue(*this, listeDeroulante.get_active_text());
}

void Fenetre::on_spinbutton_changed()
{
	int value = spinbutton.get_value_as_int();
}

void Fenetre::on_spin_pump_time_changed()
{
	int value = spin_pump_time.get_value_as_int();
}

void Fenetre::on_spin_light_time_changed()
{
	int value = spin_light_time.get_value_as_int();
}

void Fenetre::on_spin_pump_intertime_changed()
{
	int value = spin_light_intertime.get_value_as_int();
}

void Fenetre::on_spin_light_intertime_changed()
{
	int value = spin_light_intertime.get_value_as_int();
}



void Fenetre::compterligne()
{
	compteur = 0;
	ifstream fichier("test.txt", ios::in);
    if(fichier)  // si l'ouverture a réussi
    {       
    	cerr << "Ouverture fichier réussie !" << endl;
    	string ligne;
            while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu" 
            {
            	compteur++;

            }
        }
    else  // sinon
    {
    	cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    cerr << "La valeur de compteur est : " << compteur << "\n";
}

void Fenetre::fileWrite(string produit)
{
	compteur = 0;
	produit = plantelulz;
	ifstream fichier("test.txt", ios::in);
    if(fichier)  // si l'ouverture a réussi
    {       
    	cerr << "Ouverture fichier réussie !" << endl;
    	string ligne;
        	while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu" 
        	{
        		compteur++;
        		cerr << compteur;
        	}
        	fichier.close();
        }
    else  // sinon
    {
    	cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    ofstream file("test.txt", ios::out | ios::app);
    if(file)
    {
    	if(compteur<4)
    	{
    		cerr << "ça marche" << endl;
    		cerr << "produit : " << produit << endl;
    		cerr << compteur << endl;
    		file << produit << endl;
    		file.close(); 
    	}
    	else
    	{   
    		cerr << "ça marche pas" << endl;
    		label_confirmationTomato.set_markup("Vous avez déja 4 plantes dans votre système");
    	}
    }

    else  // sinon
    {
    	cerr << "Impossible d'ouvrir le fichier 1!" << endl;
    }

    setparametres(produit);


}

void Fenetre::enleverPlante(string produit)
{

	compteur = 0;   
	ifstream file("test.txt", ios::in);
	ofstream file1("test1.txt", ios::out | ios::app);
	if(boutonRadio1.get_active())
	{
		produit=boutonRadio1.get_label();
		cerr << "bouton1 actif" ;
	}
	if(boutonRadio2.get_active())
	{
		produit=boutonRadio2.get_label();
		cerr << "bouton2 actif" ;
	}
	if(boutonRadio3.get_active())
	{
		produit=boutonRadio3.get_label();
		cerr << "bouton3 actif" ;
	}
	if(boutonRadio4.get_active())
	{
		produit=boutonRadio4.get_label();
		cerr << "boutonRadio4 actif" ;
	}


	if(file && file1)
	{   
		string ligne;
        while(getline(file, ligne))  // tant que l'on peut mettre la ligne dans "contenu" 
        {
        	cerr << "Ligne :" << ligne << endl;
        	cerr << "Produit :" << produit << endl;
            //cerr << ligne << endl;
        	if(strcmp(produit.c_str(), ligne.c_str()) == 0)
        	{
        		cerr << "c'est la meme";
        	}
        	else
        	{
        		cerr << "ligne dans boucle : " << ligne;
        		file1 << ligne << endl;
        	}

        } 

        file.close();
        file1.close();

        if( std::remove( "test.txt" ) == 0 )
        	cerr << "remove successful";
        else
        	cerr << "erreur de remove";

        if( std::rename( "test1.txt","test.txt" ) == 0 )
        	cerr << "rename successful";
        else
        	cerr << "erreur de rename";
    }
    
    else  // sinon
    {
    	cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    barreOnglets.set_current_page (1);
}



void Fenetre::confirmationProduit_setLabel(string produit)
{
	label_confirmationTomato.set_markup("Vous avez choisi de faire pousser des <b>" + produit + "</b>. Voulez-vous continuer?");
	plantelulz = produit;
	cerr << plantelulz << endl;
}

void Fenetre::onGoingPlant_setLabel()
{
  	ifstream fichier("test.txt", ios::in);  // on ouvre en lecture
    if(fichier)  // si l'ouverture a fonctionné
    {
    	string ligne;
    	string bigligne;
    	string bigline2;
    	int compteur = 0;
    	temperature = ToString(produit1_temperature);
    	PH = ToString(produit1_ph);
    	EC = ToString(produit1_ec);

    	bigline2 = "\n\n Temperature : " + temperature + "\n Electro-conductivité : " + EC +"\n PH : "  + PH;

        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {
        	cerr << "dans le while";
        	compteur++;
        	cerr << "dans le while : compteur est : " << compteur;;
        	bigligne = bigligne + "\n" + ligne;
        	if(compteur==1)
        	{
        		cerr << "compteur dans while est 1";
        		boutonRadio1.set_label(ligne);
        	}
        	if(compteur==2)
        	{
        		cerr << "compteur dans while est 2";
        		boutonRadio2.set_label(ligne);
        	}
        	if(compteur==3)
        	{
        		cerr << "compteur dans while est 3";
        		boutonRadio3.set_label(ligne);
        	}
        	if(compteur==4)
        	{
        		cerr << "compteur dans while est 4";
        		boutonRadio4.set_label(ligne);
        	}


        }

        if(compteur==0)
    	{
    		boutonRadio1.set_label("Non utilisé");
    		boutonRadio2.set_label("Non utilisé");
    		boutonRadio3.set_label("Non utilisé");
    		boutonRadio4.set_label("Non utilisé");
    	}
        if(compteur==1)
    	{
    		boutonRadio4.set_label("Non utilisé");
    		boutonRadio3.set_label("Non utilisé");
    		boutonRadio2.set_label("Non utilisé");
    	}
    	if(compteur==2)
    	{
    		boutonRadio4.set_label("Non utilisé");
    		boutonRadio3.set_label("Non utilisé");
    	}
    	if(compteur==3)
    	{
    		boutonRadio4.set_label("Non utilisé");
    	}



        if(compteur==0)
        {
        	label_onGoingPlant1.set_markup("Pas de plante dans le systèmes");
        	label_onGoingPlant2.set_markup("Pas de plante dans le systèmes");
            //label_onGoingPlant2.set_markup("Vous n'avez aucune plante en cours"),
        }
        if(compteur>0)
        {     
        	label_onGoingPlant1.set_markup("Vous faites déja pousser ces différents produits :\n <b>" + bigligne + "</b>");
        	label_onGoingPlant2.set_markup("Vous faites déja pousser ces différents produits :\n <b>" + bigligne + "</b>");
        	//label_onGoingPlant2_2.set_markup("Vous faites déja pousser ces différents produits :\n <b>" + bigligne + "</b>");
        	label_onGoingPlant2_2.set_markup("Voici les paramètres actuels du système :\n <b>" + bigline2 + "</b>");

        }
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

}


void Fenetre::setparametres(string produit)
{
	compteur1 = -1;
	produit = plantelulz;
	cerr << "setparametres";
	ifstream fichier("test.txt", ios::in);
    if(fichier)  // si l'ouverture a réussi
    {       
    	cerr << "Ouverture fichier réussie !" << endl;
    	string ligne;
        	while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu" 
        	{
        		compteur1++;
        		cerr << "compteur vaut  dans boucle" << compteur1;
        	}
        	if(compteur1==0)
        	{
        		cerr << "compteur vaut 0";
       			cerr << "produit : " << produit;
        		if(strcmp(produit.c_str(), "Tomates") == 0)
        		{
        			cerr << "compteur == 0 et tomates" << endl;
        			produit1_ph = arduino.get_ph()/10;;
        			produit1_temperature= arduino.get_temperature()/10;
        			produit1_ec = arduino.get_ec()/10;;
        			produit1_temps_pousse = 30*24;	
        		}
        		if(strcmp(produit.c_str(), "Salade") == 0)
        		{
        			cerr << "compteur == 0 et salade" << endl;
        			produit1_ph = arduino.get_ph()/10;;
        			produit1_temperature= arduino.get_temperature()/10;
        			produit1_ec = arduino.get_ec()/10;;
        			produit1_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Fraises") == 0)
        		{
        			cerr << "compteur == 0 et fraise" << endl;
        			produit1_ph = arduino.get_ph()/10;;
        			produit1_temperature= arduino.get_temperature()/10;
        			produit1_ec = arduino.get_ec()/10;;
        			produit1_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Basilic") == 0)
        		{
        			cerr << "compteur == 0 et basilic" << endl;
        			produit1_ph = arduino.get_ph()/10;;
        			produit1_temperature= arduino.get_temperature()/10;
        			produit1_ec = arduino.get_ec()/10;;
        			produit1_temps_pousse = 30*24;
        		}
        	}
        	if(compteur1==1)
        	{
        		cerr << "compteur vaut 1";
        		cerr << "produit : " << produit;
        		if(strcmp(produit.c_str(), "Tomates") == 0)
        		{
        			cerr << "compteur == 1 et tomates" << endl;
        			produit2_ph = arduino.get_ph()/10;;
        			produit2_temperature= arduino.get_temperature()/10;
        			produit2_ec = arduino.get_ec()/10;;
        			produit2_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Salade") == 0)
        		{
        			produit2_ph = arduino.get_ph()/10;;
        			produit2_temperature= arduino.get_temperature()/10;
        			produit2_ec = arduino.get_ec()/10;;
        			produit2_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Fraises") == 0)
        		{
        			produit2_ph = arduino.get_ph()/10;;
        			produit2_temperature= arduino.get_temperature()/10;
        			produit2_ec = arduino.get_ec()/10;;
        			produit2_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Basilic") == 0)
        		{
        			produit2_ph = arduino.get_ph()/10;;
        			produit2_temperature= arduino.get_temperature()/10;
        			produit2_ec = arduino.get_ec()/10;;
        			produit2_temps_pousse = 30*24;
        		}
        	}
        	if(compteur1==2)
        	{
        		cerr << "compteur vaut 2";
        		cerr << "produit : " << produit;
        		if(strcmp(produit.c_str(), "Tomates") == 0)
        		{
        			produit3_ph = arduino.get_ph()/10;;
        			produit3_temperature= arduino.get_temperature()/10;
        			produit3_ec = arduino.get_ec()/10;;
        			produit3_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Salade") == 0)
        		{
        			produit3_ph = arduino.get_ph()/10;;
        			produit3_temperature= arduino.get_temperature()/10;
        			produit3_ec = arduino.get_ec()/10;;
        			produit3_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Fraises") == 0)
        		{
        			produit3_ph = arduino.get_ph()/10;;
        			produit3_temperature= arduino.get_temperature()/10;
        			produit3_ec = arduino.get_ec()/10;;
        			produit3_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Basilic") == 0)
        		{
        			produit3_ph = arduino.get_ph()/10;;
        			produit3_temperature= arduino.get_temperature()/10;
        			produit3_ec = arduino.get_ec()/10;;
        			produit3_temps_pousse = 30*24;
        		}
        	}
        	if(compteur1==3)
        	{
        		cerr << "compteur vaut 3";
        		cerr << "produit : " << produit;
        		if(strcmp(produit.c_str(), "Tomates") == 0)
        		{
        			produit4_ph = arduino.get_ph()/10;;
        			produit4_temperature= arduino.get_temperature()/10;
        			produit4_ec = arduino.get_ec()/10;;
        			produit4_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Salade") == 0)
        		{
        			produit4_ph = arduino.get_ph()/10;;
        			produit4_temperature= arduino.get_temperature()/10;
        			produit4_ec = arduino.get_ec()/10;;
        			produit4_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Fraises") == 0)
        		{
        			produit4_ph = arduino.get_ph()/10;;
        			produit4_temperature= arduino.get_temperature()/10;
        			produit4_ec = arduino.get_ec()/10;;
        			produit4_temps_pousse = 30*24;
        		}
        		if(strcmp(produit.c_str(), "Basilic") == 0)
        		{
        			produit4_ph = arduino.get_ph()/10;;
        			produit4_temperature= arduino.get_temperature()/10;
        			produit4_ec = arduino.get_ec()/10;;
        			produit4_temps_pousse = 30*24;
        		}
        	}
        }
    	else  // sinon
    	{
    	cerr << "Impossible d'ouvrir le fichier 2!" << endl;
    	}
    cerr << "Produit1EC : " << produit1_ec << endl;
    cerr << "Produit1ph : " << produit1_ph << endl;
    cerr << "Produit1temp : " << produit1_temperature << endl;
}

string Fenetre::ToString(int T)
{
    stringstream stream;
    stream << T;
    return stream.str();
}
