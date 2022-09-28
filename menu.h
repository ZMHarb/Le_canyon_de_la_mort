#ifndef _MENU_H_
#define _MENU_H

#include <ncurses.h>

/*
Fonction get_difficulty
-----------------------
Une fonction qui recupère la difficultée voulue du jeu

returns:
	0 : Facile
	1: Moyenne
	2: Difficile
	3: Exit
*/
int get_difficulty();


/*
Fonction get_joueurs
--------------------
Une fonction qui recuprère le nombre de joueurs


returns:
	entier indiquant nombre de joueurs. (1 <= n <= 4)
*/
int get_joueurs();


/*
Fonction print_menu:
--------------------

Une fonction qui affiche le menu

params:
	menu_win: un pointeur vers le window du menu
	highlight: l'indice de highlight selon "choices"
*/
void print_menu(WINDOW *menu_win, int highlight, char *liste_choix[]);

#endif
