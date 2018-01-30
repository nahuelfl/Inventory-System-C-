/********************************************************************************
AUTEUR: Nahuel Londono
DATE: 16 mai
FICHIER: 420-B21-TP5-Londono-Nahuel
DESCRIPTION: Programme de gestion d’un club de location d’équipements de sport.
********************************************************************************/

/* ------------------------- */
/* LES #include DU PROGRAMME */
/* ------------------------- */

#include <conio.h>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <string>
#include "Affichage.h"
#include "Main.h"
#include "Clients.h"
#include "Items.h"

using namespace std;


/* ----------------------- */
/* LES FONCTIONS GÉNÉRALES */
/* ----------------------- */

// Copie les caractères de la string "s" dans le tableau de char "to" sans dépasser "size"
void CopyStringTo(string &s, const unsigned int size, char to[])
{
	unsigned int i;
	for (i = 0; (i < size - 1) && (i < s.size()); i++)
		to[i] = s[i];
	to[i] = 0;	//Valeur sentinelle
}

// Lire en entrée une string avec getline et transférer cette chaine dans le tableau de char "to" sans dépasser "size"
void LireString(const int size, char to[])
{
	string texte;
	getline(cin, texte);
	CopyStringTo(texte, size, to);
}


/* ---------------------- */
/* LA FONCTION PRINCIPALE */
/* ---------------------- */

void main(void)
{
	SetConsoleCP(1252); // À FAIRE: dans la fenêtre de la console : boutton de droite, propriété, font = LUCIDA CONSOLE
	SetConsoleOutputCP(1252);

	ListeDesItems items;
	Client client;

	Commandes choix;
	do
	{
		IU_AfficherMenuPrincipal();
		choix = IU_LectureChoixValideMenuPrincipal();

		switch (choix)
		{
		case ajouter: ajouter_Client(client); break;
		case afficher: afficher_Client(NombreDeClients()); break;
		case location: louer_Items(NombreDeClients()); break;
		case retour: retourner_Items(NombreDeClients()); break;
		case items_loues: lister_Items_Loues(); break;
		case clients_avec_retards: lister_Clients_Avec_Retard(); break;
		case quitter: IU_MessageDeFinDuProgramme(); break;
		case vider: ViderClients(); break;
		}
	} while (choix != quitter);


}

