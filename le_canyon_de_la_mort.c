#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#include "le_canyon_de_la_mort.h"
#include "menu.h"
#include "score.h"

/*
Fonction: cycliste_peut_avancer:
---------------------------------
gestion des deplacement du cycliste : savoir si on a touché le canyon ou non

param:
    (y, x): les coordonnees de la prochaine position du cycliste

returns:
    0 si le cycliste a touché le canyon, 1 sinon
*/
int cycliste_peut_avancer(int y, int x)
{
    int ch;
    // On recupere le caractere à la position (y, x)
    ch = mvinch(y, x);
    return (ch != CANYON); // Retourne 0 si le cycliste a touché le canyon, 1 sinon
}

/*
Fonction: initialiser_board:
----------------------------
On initialise les bords du canyon et on l'affiche pour la premiere fois

param:
    board : liste qui doit contenir la postion du canyon pour chaque ligne
*/
void initialiser_board(int board[2 * LINES])
{
    int y, x1, x2; // coordonnées des bords (y numéro de ligne, x numéro colonne)
    y = LINES;

    clear();

    // Le premier colonne est au milieu du terminal - la moitié du largeur specifi
    x1 = ((int)COLS / 2) - ((int)LARGEUR / 2);
    x2 = x1 + LARGEUR;

    // on rempli la liste avec les numéro de colonne des bords
    for (int i = 0; i < 2 * LINES; i = i + 2)
    {
        board[i] = x1;
        board[i + 1] = x2;
        mvaddch(y, x1, CANYON); // on affiche les bords pour chaque ligne
        mvaddch(y--, x2, CANYON);
    }
}

/*
Fonction: afficher_canyon
--------------------------
affichage du canyon apres chaque refraichissement

param:
    board: liste qui contient les precedentes positions du canyon
*/
void afficher_canyon(int board[2 * LINES], int difficulty)
{

    clear();

    int y = LINES - 1; // représente l'ordonnée d'une ligne du canyon
    int x1, x2;        // x1 et x2 représentent les (abscisses) bords du canyon

    /*Décallage des coordonnées des bords du canyon dans la liste
    de une ligne vers le bas; la dernièrre ligne disparait*/
    for (int i = 0; i < 2 * LINES - 2; i = i + 2)
    {

        x1 = board[i + 2];
        x2 = board[i + 3];
        board[i] = x1;     // Décallage des ordonnées de un vers le bas
        board[i + 1] = x2; // Décallage des ordonnées de un vers le bas
        // x2 = x1 + LARGEUR; // le second bord du canyon est espacé d'une longueur stockée dans 'LARGEUR'

        mvaddch(y, x1, CANYON);
        mvaddch(y--, x2, CANYON); // on decremente 'y' à la fin de chaque ligne
    }

    /*
    Ici on fait varier la largeur du canyon par rapport à la difficulté choisi.
    Difficulte = 1  ==> La laergeur reste le même, seul la position du canyon qui change par rapport au ligne précédant
    Difficulte = 2  ==> On fait un autre tirage aleatoire qui decide si on fait decrementer la largeur pour avoir largeur = LARGEUR/2
    Difficulte = 3  ==> On fait un autre tirage aleatoire qui decide si on fait decrementer la largeur pour avoir largeur = LARGEUR/4
    */
    int prob;
    prob = rand() % 3; // Tirage aléatoire avec trois issues pour les
                       // possibilités de la ligne suivantes du canyon

    // Le deuxieme tirage aleatoire
    int diff = rand() % 2;

    // Si la difficulté est moyenne
    if (difficulty == 1)
    {
        // Si le deuxieme tirage aleatoire = 0, on diminue la difference entre les canyons mais reste > LARGEUR / 2
        if (diff == 0)
        {
            if (x2 - x1 > MOYENNE + 2)
            {
                prob = 0;
                x1++;
                x2--;
            }
        }
        else
        {
            // Si le deuxieme tirage aleatoire = 1, on augmente la difference entre les canyons mais reste < LARGEUR initial
            if (x2 - x1 < LARGEUR)
            {
                prob = 0;
                x1--;
                x2++;
            }
        }
    }

    // Si la difficulté est difficile
    else if (difficulty == 2)
    {

        // Si le deuxieme tirage aleatoire = 0, on diminue la difference entre les canyons mais reste > LARGEUR / 4
        if (diff == 0)
        {
            if (x2 - x1 > DIFFICILE + 2)
            {
                prob = 0;
                x1++;
                x2--;
            }
        }
        else
        {
            // Si le deuxieme tirage aleatoire = 1, on augmente la difference entre les canyons mais reste < LARGEUR initial
            if (x2 - x1 < LARGEUR)
            {
                prob = 0;
                x1--;
                x2++;
            }
        }
    }

    /*Les trois issues possible pour les abcisses de la ligne suivante */
    if (prob == 0)
    {
        board[2 * LINES - 2] = x1; // on ne change pas les abcisses
        board[2 * LINES - 1] = x2;
        mvaddch(y, x1, CANYON);
        mvaddch(y, x2, CANYON);
    }
    else if (prob == 1)
    {
        board[2 * LINES - 2] = --x1; // on décalle de un vers la gauche
        board[2 * LINES - 1] = --x2; // on décalle de un vers la gauche
        mvaddch(y, x1, CANYON);
        mvaddch(y, x2, CANYON);
    }
    else
    {
        board[2 * LINES - 2] = ++x1; // on décalle de un vers la droite
        board[2 * LINES - 1] = ++x2; // on décalle de un vers la droite
        mvaddch(y, x1, CANYON);
        mvaddch(y, x2, CANYON);
    }
}

/*
Fonction: afficher_cycliste
----------------------------
affichage du cycliste par rapport aux coordonnees passées en entrée

param:
    (y, x): les coordonnees de la prochaine position du cycliste
*/
void afficher_cycliste(int y, int x)
{
    mvaddch(y, x, CYCLISTE);
}

/*
Fonction: game
--------------
La fonction initiale capable de lancer le jeu

params:
    difficulty: Le niveau de difficulté choisi par le joueur    
    nom: Le nom du joueur

returns:
    lignes: Nombre de lignes parcourus
*/
int game(int difficulty, char nom[30])
{

    // initialiser ncurses
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    cbreak();
    noecho();

    // Rendre le curseur invisible
    curs_set(FALSE);

    /* Déclaration des variables utilisées dans le jeu*/

    // coordonnées du cycliste
    int y_cycliste, x_cycliste;

    // le caractere lu
    int ch;

    // boolean qui indique si le jeu a fini
    int game_over = 0;

    // les lignes parcourues
    int lignes = 0;

    clear();
    mvprintw(LINES /2 , COLS/3, "Au tour de '%s'. Tapez 'Entrée' Pour commencer ...", nom);
    while (getch() != 10);

    // Initialiser Le board du jeu
    int board[2 * LINES];
    initialiser_board(board);

    /* initialisation des coordonnées du cycliste*/
    y_cycliste = LINES - 1;
    x_cycliste = (int)COLS / 2;

    // afficher le cycliste à la position (y, x)
    afficher_cycliste(y_cycliste, x_cycliste);

    ch = getch();
    // Le jeu s'arrete lorsque le joueur presse la touche "q"
    while ((ch != 'q') && (ch != 'Q'))
    {
        while ((!game_over))
        {
            // on affiche le canyon
            afficher_canyon(board, difficulty);

            // On affiche le cycliste aux bonnes coordonnées
            afficher_cycliste(y_cycliste, x_cycliste);

            /*Gestion des touches du joueur */
            ch = getch();
            switch (ch)
            {
            case KEY_LEFT: // Gestion flèche de gauche
                // si le cycliste n'est pas au bord à gauche
                if ((x_cycliste > 0))
                {
                    // on verifie si le cycliste peut se décaller vers la gauche
                    if (cycliste_peut_avancer(y_cycliste, x_cycliste - 1))
                    {
                        // on diminue de 'un' l'abcisse du cycliste
                        afficher_cycliste(y_cycliste, --x_cycliste);
                    }
                    else
                    {
                        // Sinon on marque l'endtoit où il touche le canyon
                        mvaddch(y_cycliste, x_cycliste, ' ');
                        mvaddch(y_cycliste, x_cycliste-1, 'X');
                        // le jeu s'arrête
                        game_over = 1;
                    }
                }
                break;
            case KEY_RIGHT: // Gestion flèche de droite
                // Si le cycliste n'est pas au bord à droite
                if ((x_cycliste < COLS - 1))
                {
                    // si le cycliste peut se décaller vers la droite :
                    if (cycliste_peut_avancer(y_cycliste, x_cycliste + 1))
                    {
                        // on augmente de 'un' l'abcisse du cycliste
                        afficher_cycliste(y_cycliste, ++x_cycliste);
                    }
                    else
                    {
                        // Sinon on marque l'endtoit où il touche le canyon
                        mvaddch(y_cycliste, x_cycliste, ' ');
                        mvaddch(y_cycliste, x_cycliste+1, 'X');
                        // le jeu s'arrête
                        game_over = 1;
                    }
                }
                break;
            default: // si aucune flèche est pressée, le cycliste continue tout droit
                // on verifie que le cycliste ne recontera pas un canyon devant lui
                if (cycliste_peut_avancer(y_cycliste - 1, x_cycliste))
                {
                    afficher_cycliste(y_cycliste, x_cycliste);
                }
                else
                {
                    // On marque l'endroit où le cycliste a touché le  canyon
                    move(LINES-1, 0);
                    clrtoeol();
                    refresh();
                    mvaddch(y_cycliste, x_cycliste, ' ');
                    mvaddch(y_cycliste, board[2], CANYON);
                    mvaddch(y_cycliste, board[3], CANYON);
                    mvaddch(y_cycliste, x_cycliste, 'X');
                    // le jeu s'arrête
                    game_over = 1;
                }
                break;
            }
            refresh();
            usleep(1E6 * (1. / FREQUENCE));
            move(LINES, (int)COLS / 2);
            lignes++;
        }
        refresh();
        // quand le jeu est fini, on change la position du souris jusqu'a le coin sud-ouest pour afficher le resultat
        move(LINES - 1, 0);
        nodelay(stdscr, FALSE);
        // on indique le score parcourue
        printw("Vous avez parcouru: %d. Pressez 'q' pour sortir ...", lignes);
        // On attend que l'utilisateur presse la lettre 'q'
        ch = getch();
    }
    refresh();

    return lignes;
}

int main()
{
    // initialiser srand() pour le tirage aleatoire apres
    time_t t;
    srand((unsigned)time(&t));

    // Avoir le niveau de difficulté voulu
    int difficulty = get_difficulty();

    // Si on choisit "Exit", on entre pas dans le jeu
    if (difficulty != 3)
    {
        // Avoir le nbr de joueurs voulu
        int nbr_joueurs = get_joueurs();

        char nom_joueurs[nbr_joueurs][30];

        for (int i = 0; i < nbr_joueurs; i++)
        {
            printf("Entrez le nom de joueur %d: ", i + 1);
            scanf("%s", nom_joueurs[i]);
        }

        for (int i = 0; i < nbr_joueurs; i++)
        {
            int score;
            score = game(difficulty, nom_joueurs[i]);
            init_LB(1);
            ajouter_score(score, nom_joueurs[i]);
        }
        refresh();
        endwin();
        afficher_all_scores();
    }

    return 0;
}
