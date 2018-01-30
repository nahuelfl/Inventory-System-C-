#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "cvm.h"
#include "Affichage.h"
#include "Main.h"
#include "Clients.h"
#include "date.h"
#include "console.h"

void listerItems()
{
	ListeDesItems listeItems;

	//Console_DefilTxt

	for (int i = 0; i < listeItems.Cnt; i++)
	{
		cvm_SetColor(ROUGE);

		cout << setw(TAB4) << right << listeItems.list[i].numero << ")"
			 << setw(TAB1) << right << listeItems.list[i].prix << "$  "
			 << listeItems.list[i].titre << endl;
	}
	cout << endl << endl;
	cvm_ResetColor();
}


void ItemsLoues(Client client)
{ 
	ListeDesItems listeItems;

	cout << setw(TAB1) << right << " " << "Liste des items loués (Max " << LONGUEUR_ITEMSLOUES << ")";
	IU_Sousligne(30,1);


	if (client.nombreItemsLoues == 0)
		cout << setw(TAB1) << right << " " << "Aucun";
	else
	{
		for (int i = 0; i < client.nombreItemsLoues; i++)
		{
			cout << setw(TAB1) << right << " " << i + 1 << ". " 
				 << DT_format_date(client.listeItemsLoues[i].dateEtHeureLocation)
				 << " - " << DT_format_heure(client.listeItemsLoues[i].dateEtHeureLocation)
				 << "(" << DT_days_diff(client.listeItemsLoues[i].dateEtHeureLocation) << "j à " 
				 << client.listeItemsLoues[i].prix << "$)  " << client.listeItemsLoues[i].titre << endl;
		}
	}
}

int VerificationNoItem()
{
	ListeDesItems liste;

	int posX = wherex(),
		posY = wherey();
	int noItem;

	do
	{
		gotoxy(posX, posY);
		noItem = _getch();

		switch (noItem)
		{
			case 48: noItem = 0; break;
			case 49: noItem = 1; break;
			case 50: noItem = 2; break;
			case 51: noItem = 3; break;
			case 52: noItem = 4; break;
			case 53: noItem = 5; break;
			case 54: noItem = 6; break;
			case 55: noItem = 7; break;
			case 56: noItem = 8; break;
			case 57: noItem = 9; break;
			case 58: noItem = 10; break;
		}

		if (noItem == 0)
		{
			cout << noItem;
			IU_Bip();
			IU_Bip_DialogueErreur("Le numéro de l'item doit être entre 1 et 10 \n (Touche Escape pour quitter)");
		}

	} while (noItem <= 0 && noItem > liste.Cnt && noItem != 27);

	if (noItem == 27)
	{
		gotoxy(posX, posY);
		cout << setw(50) << setfill(' ');
	}

	if (noItem != 0 && noItem != 27)
	{
		cout << noItem;
		_getch();
	}

	return noItem;
}

void EcrireItemsLoues(Client &client, int noClient, int noItem)
{
	ListeDesItems listeItems;

	client.listeItemsLoues[client.nombreItemsLoues] = listeItems.list[noItem - 1];
	client.listeItemsLoues[client.nombreItemsLoues].dateEtHeureLocation = DT_now();
	client.nombreItemsLoues++;
	EcrireClientDansLeFichier(noClient - 1, client);
	
}

float calculFraisRetard(Client client)
{
	float fraisRetard = 0.00;

	for (int i = 0; i < client.nombreItemsLoues; i++)
		fraisRetard += ( DT_days_diff(client.listeItemsLoues[i].dateEtHeureLocation) ) * client.listeItemsLoues[i].prix ;

	return fraisRetard;
}

//----------------------------------Foctions Principales D'Actions----------------------------------------------//

void louer_Items(int nbClients)
{
	char reponse;
	int noClient = LireUnNoDeClient(nbClients, 23);
	bool locationEffectuee = false;


	if (noClient != 0)
	{
		int noItem;
		ListeDesItems listeItems;
		Client client = LireClientDansLeFichier(noClient-1);
		IU_LouerClient(client, noClient);
		listerItems();

		do
		{
			int posXListe = wherex();
			int posYListe = wherey();
			reponse = ' ';

			ItemsLoues(client);
			cout << endl << endl << endl << endl << endl;

			if (client.nombreItemsLoues == LONGUEUR_ITEMSLOUES)
			{
				cout << setw(TAB1) << right << " " << "Le maximum de trois locations est déjà atteint! ";
				Sleep(1000);
				break;
			}

			do
			{
				int posY = wherey();
				gotoxy(0, posY);
				reponse = IU_Question();
			} while (reponse != 'O' && reponse != 'N');

			cout << reponse;

			if (reponse == 'N')
				break;

			cout << setw(TAB2) << right << "Item #: ";
			
			noItem = VerificationNoItem();
			
			if (noItem != 27)
			{
				EcrireItemsLoues(client, noClient, noItem);
				locationEffectuee = true;
			}
			
			gotoxy(posXListe, posYListe);
			clreoscr();
			gotoxy(posXListe, posYListe);

		} while (reponse == 'O');

		if (locationEffectuee == true)
		{
			gotoxy(0, 24);
			cout << "\t\t\t\t\t\t\t\t\t\t";
			gotoxy(0, 24);
			cout << setw(TAB1) << right << " " << "Locations enregistrées! ";
			Sleep(1000);
		}
	}
}

void retourner_Items(int nbClients)
{
	int noClient = LireUnNoDeClient(nbClients, 23);

	if (noClient != 0)
	{
		Client client = LireClientDansLeFichier(noClient-1);
		IU_RetournerItems(client, noClient);


		cout << setw(TAB1) << right << " " << "Des frais de retard de " 
			 << fixed << setprecision(2) << calculFraisRetard(client) << "$ seront appliqués";

		for (int i = 0; i < client.nombreItemsLoues; i++)
			client.listeItemsLoues[i] = { };

		client.nombreItemsLoues = 0;
		EcrireClientDansLeFichier(noClient - 1, client);
		_getch();
	}
	
}

void lister_Items_Loues()
{
	IU_AffichageCompagnie();
	IU_Sousligne(24, 2);

	cout << setw(TAB1) << right << " " << "Date actuelle: "
		<< DT_format_date(DT_now()) << " - " << DT_format_heure(DT_now()) << endl << endl
		<< setw(TAB1) << right << " " << "#Item  Date    Heure     Titre de l'item" << endl;
	
	cout << setw(TAB1) << right << " "; IU_Sousligne(6, 0); cout << " "; IU_Sousligne(5, 0); cout << "   "; 
	IU_Sousligne(6, 0); cout << "    "; IU_Sousligne(16, 0);

	for (int i=0; i < NombreDeClients(); i++)
	{
		Client client = LireClientDansLeFichier(i);

		for (int i = 0; i < client.nombreItemsLoues; i++)
		{
			cout << endl << setw(TAB1) << right << " " << client.listeItemsLoues[i].numero
				<< setw(TAB1) << right << " " << DT_format_date(client.listeItemsLoues[i].dateEtHeureLocation) << "  "
				<< DT_format_heure(client.listeItemsLoues[i].dateEtHeureLocation)
				<< setw(TAB1) << right << " " << client.listeItemsLoues[i].titre;
		}
	}

	_getch();
}