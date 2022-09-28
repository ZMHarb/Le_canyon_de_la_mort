#include <stdio.h>
#include <ncurses.h>

#include "menu.h"

#define n_choices 4

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
int get_difficulty()
{

	// Les choix de differents niveau du menu
	char *choix_niveau[] = {
		"Facile",
		"Moyenne",
		"Difficile",
		"Exit",
	};

	// initialiser le menu
	WINDOW *menu_win;

	// initialiser les differents variables utilisés
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();

	noecho();
	cbreak();

	int startx = COLS / 3;
	int starty = 4;

	curs_set(0);

	mvprintw(starty - 2, COLS / 3, "Choisir le niveau de difficulté:");
	mvprintw(starty - 1, COLS / 3, " (Tapez 'entrée' pour choisir)");

	menu_win = newwin(10, 30, starty, startx);

	keypad(menu_win, TRUE);

	refresh();

	// afficher le menu
	print_menu(menu_win, highlight, choix_niveau);

	// tant qu'on a pas encore choisi parmi le menu
	while (choice == 0)
	{
		c = wgetch(menu_win);

		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case KEY_ENTER:
		case 10:
			choice = highlight;
			break;
		default:
			refresh();
			break;
		}
		print_menu(menu_win, highlight, choix_niveau);
	}
	refresh();
	endwin();
	return choice - 1;
}

/*
Fonction get_joueurs
--------------------
Une fonction qui recuprère le nombre de joueurs


returns:
	entier indiquant nombre de joueurs. (1 <= n <= 4)
*/
int get_joueurs()
{

	char *choix_joeurs[] = {
		"1 joueur",
		"2 joueurs",
		"3 joueurs",
		"4 joueurs"};

	// initialiser le menu
	WINDOW *menu_win;

	// initialiser les differents variables utilisés
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();

	noecho();
	cbreak();

	int startx = COLS / 3;
	int starty = 4;

	curs_set(0);

	mvprintw(starty - 2, COLS / 3, "Choisir le nombre de joueurs voulus:");
	mvprintw(starty - 1, COLS / 3, " (Tapez 'entrée' pour choisir)");

	menu_win = newwin(10, 30, starty, startx);

	keypad(menu_win, TRUE);

	refresh();

	// afficher le menu
	print_menu(menu_win, highlight, choix_joeurs);

	// tant qu'on a pas encore choisi parmi le menu
	while (choice == 0)
	{
		c = wgetch(menu_win);

		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case KEY_ENTER:
		case 10:
			choice = highlight;
			break;
		default:
			refresh();
			break;
		}
		print_menu(menu_win, highlight, choix_joeurs);
	}
	refresh();
	endwin();
	return choice;
}

/*
Fonction print_menu:
--------------------

Une fonction qui affiche le menu

params:
	menu_win: un pointeur vers le window du menu
	highlight: l'indice de highlight selon "choix_niveau"
*/
void print_menu(WINDOW *menu_win, int highlight, char *liste_choix[])
{
	int x, y, i;
	x = 2;
	y = 2;
	box(menu_win, 0, 0);

	for (i = 0; i < n_choices; ++i)

	{
		if (highlight == i + 1)
		{
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", liste_choix[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
		{
			mvwprintw(menu_win, y, x, "%s", liste_choix[i]);
		}
		++y;
	}
	wrefresh(menu_win);
}
