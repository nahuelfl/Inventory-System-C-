#include < windows.h >

// --- Prototypes des fonctions

void clrscr(void);          // effacer l'écran de sortie
void clreol(void);          // effacer le reste de la ligne courante
void clreoscr(void);        // effacer le reste de l'écran de sortie
void gotoxy(int x,int y);   // placer le curseur à la colonne x et à la ligne y  ( l'origine est (0,0) )
int wherex(void);           // retourner la colonne courante 
int wherey(void);           // retourner la ligne courante
