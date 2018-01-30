#pragma once
#include <string>

using namespace std;


/* --------------------------- */
/* LES CONSTANTES DU PROGRAMME */
/* --------------------------- */

const int	MAX_ITEM = 999,
			LONGUEUR_PRENOM = 23, LONGUEUR_NOM = 23, LONGUEUR_NUMTELE = 17, LONGUEUR_ITEMSLOUES = 3,
			LONGUEUR_ITEMTITRE = 65, LONGUEUR_NUMCIVIQUE = 9, LONGUEUR_RUE = 33, LONGUEUR_VILLE = 33,
			LONGUEUR_CODEPOSTAL = 9;

/* ---------------------------------------*/
/* LES STRUCTURES DE DONNÉES DU PROGRAMME */
/* ---------------------------------------*/

struct Item
{
	int numero;
	char titre[LONGUEUR_ITEMTITRE];
	unsigned int prix;
	time_t dateEtHeureLocation;
};

struct ListeDesItems
{
	int Cnt = 10;

	Item list[MAX_ITEM]  // valeurs par défaut si le fichier d'items n'a pas été utilisé.
		= {
			{1, "Vélo hybride", 25},
			{2, "Sac de vélo (22 à 30 litres)", 5},
			{3, "Casque de vélo", 3},
			{4, "Sacoches arrières (paire)", 6},
			{5, "Sacoche de guidon", 3},
			{6, "Porte-bagages arrière", 3},
			{7, "Casque d'escalade", 4},
			{8 , "Soulier d'escalade", 6},
			{9, "Sac de magnésie", 2},
			{10, "Bottes d'alpinisme", 12}
	};
}; 

struct Adresse
{
	char numeroCivique[LONGUEUR_NUMCIVIQUE];
	char rue[LONGUEUR_RUE];
	char ville[LONGUEUR_VILLE];
	char codePostal[LONGUEUR_CODEPOSTAL];
};

struct Client
{
	char prenom[LONGUEUR_PRENOM];
	char nom[LONGUEUR_NOM];
	char numeroTelephone[LONGUEUR_NUMTELE];
	Adresse adresse;
	int nombreItemsLoues;
	Item listeItemsLoues[LONGUEUR_ITEMSLOUES];
};


/* ---------------------------- */
/* LES PROTOTYPES DES FONCTIONS */
/* ---------------------------- */

void CopyStringTo(string &s, const unsigned int size, char to[]);
void LireString(const int size, char to[]);