#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
/*
Fonction init_LB
-------------------------

Une fonction qui initialise le LeaderBoard du jeu.
Si le LeaderBoard existe déjà, elle met à jour le nombre de joueurs existant sur Le board .

params:
	nbr_joueurs: le nombre de joueurs du jeu courant

*/
void init_LB(int nbr_joueurs)
{
	FILE *file;

	file = fopen("LeaderBoard.txt", "r+");

	char nbr_scores[3];

	// Si le fichier n'existe pas déjà, on doit le créer
	if (file == NULL)
	{
		file = fopen("LeaderBoard.txt", "w");
		sprintf(nbr_scores, "%d\n", nbr_joueurs);
		fputs(nbr_scores, file);
	}
	// Le fichier existe déjà, on lit la première ligne qui présente le nbr de scores, puis on l'ajoute le nombre de joueurs du jeu courant
	else
	{
		char nbr_total[3];

		// On lit la première ligne
		fgets(nbr_scores, 3, file);

		// On deplace le curseur du fichier jusqu'à la première ligne
		fseek(file, 0, 0);

		// On convertit le nbr_total pour un char * (string)
		sprintf(nbr_total, "%d\n", atoi(nbr_scores) + nbr_joueurs);

		// On ajoute le nouveau nombre total au fichier
		fputs(nbr_total, file);
	}

	fclose(file);
}

/*
Fonction get_scores_noms
------------------------
Une fonction qui recupère les noms et leurs scores du fichier LeaderBoard.txt

params:
	scores: La liste où on devra stocker les scores des joueurs
	names: La liste où on devra stocker leurs noms

returns:
	nbr_joueurs
*/
int get_scores_noms(int scores[15], char names[15][40])
{
	FILE *file;
	file = fopen("LeaderBoard.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Erreure lors de l'ouverture du fichier 'LeaderBaord.txt'\n");
		exit(2);
	}

	char line[30];
	fgets(line, 30, file);

	int nbr_scores = atoi(line);

	for (int i = 0; i < nbr_scores; i++)
	{
		fgets(line, 30, file);

		char *name;

		// On divise la ligne par 2. c'est a dire nom:score sera divisé en "nom" et "score"
		name = strtok(line, ":");
		// Le nom du joueur
		strcpy(names[i], name);

		name = strtok(NULL, ":");
		// Le score du joueur
		int score = atoi(name);
		scores[i] = score;
	}

	return nbr_scores;
}

/*
Fonction ajouter_score
----------------------

Fonction qui fait ajouter le score au fichier de LeaderBoard

params:
	score: Le score du joueur
	nom:   Le nom du joueur
*/
void ajouter_score(int score, char *nom)
{
	FILE *file;

	file = fopen("LeaderBoard.txt", "a");
	if (file == NULL)
	{
		fprintf(stderr, "Erreure lors de l'ouverture du fichier 'LeaderBoard.txt'\n");
		exit(2);
	}

	// On ecrit son nom dans le fichier
	fputs(nom, file);

	char ligne[30];

	// On convertit le score à un string
	sprintf(ligne, ":%d\n", score);

	// On ajoute le score au fichier
	fputs(ligne, file);

	fclose(file);
}

/*
Fonction sort_scores
--------------------
Une fonction qui fait trier les scores dans l'ordre décroissant. Elle fait trier leur nom egalement selon leurs scores

params:
	names: Une liste qui contient les noms du joueurs
	scores: Une liste qui contient leur scores

returns:
	nbr_joueurs
*/
int sort_scores(int scores[15], char names[15][40])
{
	// Recuperer les scores et les noms
	int nbr_scores = get_scores_noms(scores, names);

	for (int i = 0; i < nbr_scores; ++i)
	{
		for (int j = i + 1; j < nbr_scores; ++j)
		{
			if (scores[i] <= scores[j])
			{
				// Sauvegarder le score et le nom dans des variables temporaires
				int score = scores[i];
				char name[30];
				strcpy(name, names[i]);

				// Echanger les scores et le noms entre les indices i et j
				scores[i] = scores[j];
				strcpy(names[i], names[j]);

				// affecter les variables temporaires au score et nom d'indice j
				scores[j] = score;
				strcpy(names[j], name);
			}
		}
	}
	return nbr_scores;
}

/*
Fonction UpdateLB
------------------
Une fonction qui fait reecrire le fichier LeaderBoard dans l'ordre decroissant (grand score -> petit score)

params:
	scores: Une liste des scores triées
	names: Une liste des noms triées selon leurs scores

*/
void UpdateLB(int scores[15], char names[15][40])
{
	// Trier les scores par ordre decroissant
	int nbr_scores = sort_scores(scores, names);

	if (nbr_scores > 10)
	{
		nbr_scores = 10;
	}

	FILE *file = fopen("LeaderBoard.txt", "w");
	char line[40];
	// On convertit le nbr de score à un string
	sprintf(line, "%d\n", nbr_scores);
	// On ajoute le nbr_score au fichier
	fputs(line, file);

	for (int i = 0; (i < nbr_scores && i <= 10); i++)
	{
		// On ecrit chaque nom et son score au fichier
		sprintf(line, "%s:%d\n", names[i], scores[i]);
		fputs(line, file);
	}
	fclose(file);
}

/*
Fonction affichier_all_scores
-----------------------------
Une fonction qui affiche les scores dans l'ordre + HallOfFame qui consiste aux score >= 1500 lignes
*/
void afficher_all_scores()
{
	// initialiser le menu
	WINDOW *score_win;
	WINDOW *score_win2;
	initscr();
	clear();
	noecho();
	cbreak();

	// la position initiale du window
	int startx = 20;
	int starty = 4;

	// rendre le curseur invisible
	curs_set(0);

	// Afficher le titre du tableau
	mvprintw(starty - 2, startx, "	LeaderBoard		");

	// initialiser le window des scores
	score_win = newwin(15, 40, starty, startx);

	// Afficher le titre du tableau HallOfFame
	mvprintw(starty - 2, startx * 4, "  Hall Of Fame (1500+ Lines)  ");

	// initialiser le window de Hall Of Fame
	score_win2 = newwin(15, 40, starty, startx * 4);

	keypad(score_win, TRUE);

	refresh();

	// initialiser les box
	int x, y, i;
	x = 2;
	y = 3;
	box(score_win, 0, 0);
	box(score_win2, 0, 0);

	// Initialiser les listes des noms et scores
	char names[15][40];
	int scores[15];

	UpdateLB(scores, names);

	FILE *file;

	file = fopen("LeaderBoard.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Erreure lors de l'ouverture du fichier 'LeaderBoard.txt'\n");
		exit(2);
	}

	char line[30];

	// Lire le nombre de joueurs depuis le fichier
	fgets(line, 30, file);
	int nbr_scores = atoi(line);

	for (int i = 0; i < nbr_scores; i++)
	{
		fgets(line, 30, file);

		char *name;

		// On divise la ligne par 2. c'est a dire nom:score sera divisé en "nom" et "score"
		name = strtok(line, ":");
		// Le nom du joueur
		strcpy(names[i], name);

		name = strtok(NULL, ":");
		// Le score du joueur
		int score = atoi(name);
		scores[i] = score;
	}

	// Afficher les titres des colonnes
	mvwprintw(score_win, 1, x, "   Name\t\tScore");
	mvwprintw(score_win, 2, x, "   -----\t\t-----");

	for (i = 0; i < nbr_scores; ++i)
	{
		// Afficher le nom du joueur et son score
		mvwprintw(score_win, y, x, "%d- %s", i+1, names[i]);
		mvwprintw(score_win, y, x + 23, "%d", scores[i]);
		++y;
	}

	wrefresh(score_win);

	/*

	HALL OF FAME

	*/

	// On reinitialise les variables de window
	int j = 0;
	x = 2;
	y = 3;

	// On affiche les titres des colonnes du tableau Hall Of Fame
	mvwprintw(score_win2, 1, x, "   Name\t\tScore");
	mvwprintw(score_win2, 2, x, "   -----\t\t-----");

	while (scores[j] >= 1500 && j < nbr_scores)
	{
		// On affiche les scores > 1500 et leur noms
		mvwprintw(score_win2, y++, x, "%d- %s", j+1, names[j]);
		mvwprintw(score_win2, y++, x + 23, "%d", scores[j]);
		j++;
	}

	wrefresh(score_win2);

	while (getch() != 'q')
		;

	endwin();
}
