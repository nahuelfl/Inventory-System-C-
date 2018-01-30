#pragma once
#include "Main.h"

/* ---------------------------- */
/* LES PROTOTYPES DES FONCTIONS */
/* ---------------------------- */

int NombreDeClients();	//Compte le nombredeClients et v�rifie que le fichier existe
Client lectureInfoClient(Client client);	//Lit l'info du client
void EcrireClientDansLeFichier(int numeroClient, Client &client);	//�crit l'info du client dans un fichier binaire
Client LireClientDansLeFichier(int numeroClient);	//Lit les clients qui se retrouvent d�j� dans le fichier
int LireUnNoDeClient(int _nombreDeClients, int posY);	//Lit un num�ro de client valide
void ViderClients();

//----Fonctions Principales D'Actions Pour Les Clients----//

void ajouter_Client(Client &client);	//Ajoute un client
void afficher_Client(int nbClients);	//Affiche l'info d'un client
void lister_Clients_Avec_Retard();		//Affiche les clients avec des items en retard