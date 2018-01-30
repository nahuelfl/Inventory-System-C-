#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "cvm.h"
#include "Affichage.h"
#include "Main.h"
#include "Items.h"
#include <fstream>
#include "date.h"

int NombreDeClients()
{
	int nbClients, tailleFichier;

	fstream f;

	f.open("clients.dat", ios::in | ios::binary);
	if (f.is_open())
	{
		f.seekp(0, ios::end);
		tailleFichier = f.tellp();
		nbClients = tailleFichier / sizeof(Client);
		f.close();
	}
	else
	{
		f.open("clients.dat", ios::out | ios::binary);
		f.close();
		nbClients = 0;
	}

	return nbClients;
}

Client lectureInfoClient(Client client)
{
	string temp;

	IU_AjouterClient2("Prénom");
	LireString(LONGUEUR_PRENOM, client.prenom);

	IU_AjouterClient2("Nom");
	LireString(LONGUEUR_NOM, client.nom);

	IU_AjouterClient2("Numéro de téléphone");
	LireString(LONGUEUR_NUMTELE, client.numeroTelephone);

	IU_AfficherSousTitreAdresse();

	IU_AjouterClient2("Numéro civique");
	LireString(LONGUEUR_NUMCIVIQUE, client.adresse.numeroCivique);

	IU_AjouterClient2("Rue");
	LireString(LONGUEUR_RUE, client.adresse.rue);

	IU_AjouterClient2("Ville");
	LireString(LONGUEUR_VILLE, client.adresse.ville);

	IU_AjouterClient2("Code Postal");
	LireString(LONGUEUR_CODEPOSTAL, client.adresse.codePostal);

	return client;
}

void EcrireClientDansLeFichier(int numeroClient, Client &client)
{
	fstream f;
	f.open("clients.dat", ios::out | ios::in | ios::binary);
	f.seekp(numeroClient*(sizeof(Client)), ios::beg);
	f.write((char*)&client, sizeof(Client));
	f.close();
}

Client LireClientDansLeFichier(int numeroClient)
{
	Client client;

	fstream f;
	f.open("clients.dat", ios::in | ios::binary);
	f.seekp(numeroClient*(sizeof(Client)), ios::beg);
	f.read((char*)&client, sizeof(Client));
	f.close();

	return client;
}

int LireUnNoDeClient(int _nombreDeClients, int posY)
{
	int noClient;
	gotoxy(0, posY);
	cout << setw(TAB1) << right << " " << "Numéro du client : ";


	int x = wherex();
	int y = wherey();

	cin >> noClient;

	if (noClient <= _nombreDeClients && noClient > 0)
		noClient = noClient;
	else
	{
		gotoxy(x, y);

		if (cin.fail())
		{
			cout << "Numéro inexistant";
			cin.clear();
			IU_FlushTampons();
		}

		IU_Bip();
		IU_Bip_DialogueErreur("Le numéro du client est invalide");
		noClient = 0;
	}

	return noClient;
}

void ViderClients()
{
	fstream f;
	f.open("clients.dat", ios::out | ios::binary);
}

//----------------------------------Foctions Principales D'Actions----------------------------------------------//

void ajouter_Client(Client &client)
{
	int numeroClient = NombreDeClients() + 1;

	IU_AjouterClient(numeroClient);

	client = lectureInfoClient(client);

	client.nombreItemsLoues = 0;	//Initialisation du nombre de locations

	EcrireClientDansLeFichier(numeroClient - 1, client);
}

void afficher_Client(int nbClients)
{
	int noClient = LireUnNoDeClient(nbClients, 23);

	if (noClient != 0)
	{
		IU_AffichageCompagnie();
		IU_Sousligne(22,1);
		cout << setw(TAB1) << right << " " << "Informations personnelles (#" << noClient << ")" ;
		IU_Sousligne(26,1);

		Client client = LireClientDansLeFichier(noClient-1);

		IU_AjouterClient2("Prénom");
		IU_AffichageCaractères(client.prenom, LONGUEUR_PRENOM); 
		IU_AjouterClient2("Nom");
		IU_AffichageCaractères(client.nom, LONGUEUR_NOM); 
		IU_AjouterClient2("Numéro de téléphone");
		IU_AffichageCaractères(client.numeroTelephone, LONGUEUR_NUMTELE); 
		IU_AfficherSousTitreAdresse();
		IU_AjouterClient2("Numéro civique");
		IU_AffichageCaractères(client.adresse.numeroCivique, LONGUEUR_NUMCIVIQUE);
		IU_AjouterClient2("Rue");
		IU_AffichageCaractères(client.adresse.rue, LONGUEUR_RUE);
		IU_AjouterClient2("Ville");
		IU_AffichageCaractères(client.adresse.ville, LONGUEUR_VILLE);
		IU_AjouterClient2("Code Postal");
		IU_AffichageCaractères(client.adresse.codePostal, LONGUEUR_CODEPOSTAL);
		cout << endl;

		ItemsLoues(client);

		_getch();
	}
}



void lister_Clients_Avec_Retard()
{
	IU_AffichageCompagnie();

	cout << endl << endl << endl << endl;
	cout << "#" << setw(TAB1) << right << " " << "Prénom" << setw(TAB5) << right << " " << "Nom"
		<< setw(TAB5) << right << " " << "#Tel" << setw(TAB4) << right << " " << "NbJ"
		<< setw(TAB1) << right << " " << "Nb Items" << endl;

	IU_Sousligne(2, 0); cout << setw(TAB1-1) << right << " "; IU_Sousligne(7, 0);
	cout << setw(TAB5-1) << right << " "; IU_Sousligne(4, 0); cout << setw(TAB5) << right << " "; 
	IU_Sousligne(4, 0); cout << setw(TAB4-1) << right << " "; IU_Sousligne(4,0);
	cout << setw(3) << right << " "; IU_Sousligne(8, 0);


	for (int a = 0; a < NombreDeClients(); a++)
	{
		int nbItemsRetard = 0, nbJours = 0, nbJoursTemp = 0;
		Client client = LireClientDansLeFichier(a);

		for (int i = 0; i < client.nombreItemsLoues; i++)
		{

			if (DT_days_diff(client.listeItemsLoues[i].dateEtHeureLocation) > 0)
			{
				nbItemsRetard++;
			}

			nbJoursTemp = DT_days_diff(client.listeItemsLoues[i].dateEtHeureLocation);

			if (nbJoursTemp < nbJours)
				nbJours = nbJoursTemp;
		}

		if (nbItemsRetard > 0)
		{
			cout << endl << a << setw(TAB1 - 1) << right << " " << client.prenom
				<< setw(TAB5 - 1) << right << " " << client.nom
				<< setw(TAB5) << right << " " << client.numeroTelephone
				<< setw(TAB4 - 1) << right << " " << nbJours
				<< setw(3) << right << " " << nbItemsRetard;
		}
		
	}

	_getch();
}

//-------------------------------------------------------------------------------------------------------------//