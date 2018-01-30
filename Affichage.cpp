#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "cvm.h"
#include "Main.h"
#include "Affichage.h"
#include "Clients.h"
#include "date.h"
#include "Items.h"


using namespace std;

//VARIABLES
int nbItems = 0;

/* ----------------------------------------- */
/* LES FONCTIONS TRÈS GÉNÉRALES DU PROGRAMME */
/* ----------------------------------------- */

void IU_FlushTampons() // pour vider les 2 tampons 
{
	cin.ignore(cin.rdbuf()->in_avail()); // vide le tampon du cin
	while (_kbhit()) _getch(); // vide l'autre tampon
}

// FONCTIONS GÉNÉRALES POUR LE SIGNALEMENT D'ERREURS

void IU_Bip() { cout << "\a"; }

void IU_Bip_DialogueErreur(string message)
{
	IU_Bip();
	MessageBoxA(NULL, message.c_str(), "ERREUR", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);
}

void IU_AffichageCompagnie()
{
	ListeDesItems listeItems;

	clrscr();
	cout << setw(TAB1) << right << " " << "Location CVM" << "  (" << listeItems.Cnt << " items)";
}

void IU_AffichageNbClients(int nbClients)
{
	cout << setw(TAB2) << right << " " << nbClients << " client";
	if (nbClients != 1)
		cout << "s";
	cout << " présentement";
}

void IU_Sousligne(int taille, int nbLignesLibres)
{
	if (nbLignesLibres != 0)
	{
		cout << endl << setw(TAB1) << right << " ";
	}

	cout << setfill('-') << setw(taille) << " ";

	if (nbLignesLibres == 1)
		cout << endl << endl;
	else if (nbLignesLibres == 2)
		cout << endl << endl << endl;
		
	cout << setfill(' ');
}


void IU_AffichageCaractères(char info[], const int LONGUEUR)
{
	int i = 0;

	while (info[i] != 0 && i < LONGUEUR)
	{
		cout << info[i];
		i++;
	}

	cout << endl;
}

void IU_AfficherSousTitreAdresse()
{
	cout << endl
		<< setw(TAB1) << right << " " << "Adresse";
	
	IU_Sousligne(8,1);
}

void IU_AfficherMenuPrincipal()
{
	IU_AffichageCompagnie();
	IU_AffichageNbClients(NombreDeClients());
	IU_Sousligne(22,2);

	cout << setw(TAB1) << right << " " << "1. Ajouter un client" << endl << endl
		 << setw(TAB1) << right << " " << "2. Afficher le dossier d'un client" << endl << endl
		 << setw(TAB1) << right << " " << "3. Location d'items" << endl << endl
		 << setw(TAB1) << right << " " << "4. Retour d'items" << endl << endl
		 << setw(TAB1) << right << " " << "5. Items loués" << endl << endl
		 << setw(TAB1) << right << " " << "6. Clients avec des retards" << endl << endl
		 << setw(TAB1) << right << " " << "7. Quitter" << endl << endl << endl;
}

Commandes IU_LectureChoixValideMenuPrincipal()
{
	Commandes choix = quitter;		//Commande par défaut

	cout << setw(TAB1) << right << " " << "Entrez votre choix: ";

	bool choixValide = false;	//Valeur par défaut (il est mieux de rester dans la boucle en cas de condition non réflechie)
	int tempChoix = 0;
	do
	{
		int x = wherex();
		int y = wherey();

		tempChoix = _getche();

		if (tempChoix > 48 && tempChoix < 57 || tempChoix == 102)	//L'intervalle de caractères 48 à 56 équivaut aux chiffres 1 à 7 du clavier
			choixValide = true;
		else
			gotoxy(x, y);
	} while (choixValide == false);

	switch (tempChoix)
	{
	case 49: choix = ajouter; break;
	case 50: choix = afficher; break;
	case 51: choix = location; break;
	case 52: choix = retour; break;
	case 53: choix = items_loues; break;
	case 54: choix = clients_avec_retards; break;
	case 55: choix = quitter; break;
	case 102: choix = vider; break;
	}							//Le case 56 soit le choix #7 (quitter) n'est pas mentionné puisqu'il est par défaut

	return choix;
}

void IU_AjouterClient(int numeroClient)
{

	IU_AffichageCompagnie();
	IU_Sousligne(22,2);
	cout << setw(TAB1) << right << " " << "Création du client #" << numeroClient << endl << endl << endl
		 << setw(TAB1) << right << " " << "Informations personnelles";
	IU_Sousligne(26,1);
		 
}

void IU_AjouterClient2(string attribut)
{
	cout << setw(TAB1) << right << " " << setw(TAB3) << left << attribut << ": ";
}

void IU_AfficherClient()
{
	IU_AffichageCompagnie();

	cout << setw(TAB1) << right << " " << "Informations personnelles" << endl;
	IU_Sousligne(26,1);
}


void IU_AfficherCompteEtNom(Client client, int noClient)
{
	cout << setw(TAB1) << right << " " << "(#" << noClient << ")   Cpte de M. (Mme): ";
	int y = wherey();
	IU_AffichageCaractères(client.nom, LONGUEUR_NOM);
	gotoxy(0, y);
}

void IU_LouerClient(Client client, int noClient)
{
	IU_AffichageCompagnie();
	IU_AfficherCompteEtNom(client, noClient);
	IU_Sousligne(24,1);
}

char IU_Question()
{
	char reponse;
	cout << setw(TAB1) << right << " " << "Désirez-vous louer un item ? (O/N) : ";
	reponse = _getch();
	reponse = toupper(reponse);

	return reponse;
}

void IU_Items()
{

}

void IU_RetournerItems(Client client, int noClient)
{
	IU_AffichageCompagnie();
	IU_Sousligne(24,2);
	cout << setw(TAB1) << right << " " << "Date actuelle: ";
	cout << DT_format_date(DT_now()) << " - " << DT_format_heure(DT_now()) << endl << endl << endl << endl;
	IU_AfficherCompteEtNom(client, noClient);
	cout << endl << endl << endl;
	ItemsLoues(client);
	cout << endl << endl << endl << endl << endl;
}

void IU_MessageDeFinDuProgramme()
{
	clrscr();
	string auRevoir = "A U    R E V O I R";

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n"
		<< setw(((120 - auRevoir.size()) / 2) + auRevoir.size()) << right << auRevoir << endl;

	Sleep(1000);
}