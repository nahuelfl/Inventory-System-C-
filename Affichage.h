#pragma once
#include <string>
#include "Main.h"

using namespace std;

//CONSTANTES
const int TAB1 = 4, TAB2 = 26, TAB3 = 20, TAB4 = 6, TAB5 = 22;


//Actions que l'usager peut faire
enum Commandes { ajouter, afficher, location, retour, items_loues, clients_avec_retards, quitter, vider };


/* ---------------------------- */
/* LES PROTOTYPES DES FONCTIONS */
/* ---------------------------- */

//Fonctions en cas d'erreur d'Input
void IU_FlushTampons();
void IU_Bip();
void IU_Bip_DialogueErreur(string message);

//Fonctions spécifiques de l'affichage du programme
Commandes IU_LectureChoixValideMenuPrincipal();		//Lit le choix d'actions au menu principal
void IU_AfficherMenuPrincipal();	//Affiche le menu principal
void IU_AffichageCompagnie();		//Affiche le nom de la compagnie en haut de l'éxécutable
void IU_AffichageNbClients(int nbClients);	//Affiche le nombre de clients
void IU_Sousligne(int taille, int nbLignesLibres);		//Sousligne une string avec des charactères (-)
void IU_AffichageCaractères(char info[], const int LONGUEUR);	//Montre un tableau de caractères de la structure client
void IU_AfficherSousTitreAdresse();	//Affiche le sous titre "Adresse" 

//Fonctions plus larges d'affichage
void IU_AjouterClient(int numeroClient);	//Affichage de la première partie de l'action "ajouter un client"
void IU_AjouterClient2(string attribut);	//Affichage des différentes informations/attributs d'un client
void IU_AfficherClient();	
void IU_AfficherCompteEtNom(Client client, int noClient);
void IU_LouerClient(Client client, int noClient);
char IU_Question();
void IU_Items();
void IU_RetournerItems(Client client, int noClient);
void IU_MessageDeFinDuProgramme();