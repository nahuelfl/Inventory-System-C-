#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>

#include "console.h"

using namespace std;

void cvm_SetColor(cvm_color c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cvm_ResetColor()
{
	cvm_SetColor(BLANC);
}

// Temps équivaut au temps de défilement des lettres en milliseconde
// Donc si on veut aucun défilement on met la valeur 0.

void Console_CenterTxt(string texte, unsigned int Temps, cvm_color couleur)
{
	cvm_SetColor(couleur);
	//texte = Console_FormatTxt(texte);
	cout << setw ( ( 80 - texte.size() ) / 2 ) << left << "";

	for ( unsigned int i = 0 ; i < texte.size() ; i++ )	//Défiler
	{
		cout << texte[i];
		Sleep(Temps);
	}
}

// Le deuxième argument est le temps de défilement des lettres en milliseconde.

void Console_DefilTxt(string texte, unsigned int Temps, cvm_color couleur)
{
	cvm_SetColor(couleur);
	//texte = Console_FormatTxt(texte);
	for (unsigned int i(0); i<texte.size(); i++)	//Défiler
	{
		cout << texte[i];
		Sleep(Temps);
	}
}