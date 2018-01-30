#pragma once
#include "Main.h"

/* ---------------------------- */
/* LES PROTOTYPES DES FONCTIONS */
/* ---------------------------- */

void listerItems();
void ItemsLoues(Client client);
void VerificationNoItem();
int calculFraisRetard();

//----Fonctions Principales D'Actions Pour Des Items----//

void louer_Items(int nbClients);
void retourner_Items(int nbClients);
void lister_Items_Loues();