#pragma once

#include <string>
using namespace std;

enum cvm_color
{
	BLANC = 0x07,
	JAUNE = 0x0e,
	ROUGE = 0x0c,
	VERT = 0x0a,
	BLEU = 0x09,
	CYAN = 0x0b,
	ROSE = 0x0d,
	NOIR = 0x00
};

void cvm_SetColor(cvm_color c);
void cvm_ResetColor();

void Console_CenterTxt(string texte, unsigned int Temps = 0, cvm_color couleur = BLANC);
void Console_DefilTxt(string texte, unsigned int Temps = 0, cvm_color couleur = BLANC);