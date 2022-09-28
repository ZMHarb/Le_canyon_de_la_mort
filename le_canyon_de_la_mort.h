#ifndef _LE_CANYON_DE_LA_MORT_H_
#define _LE_CANYON_DE_LA_MORT_H_

#define CANYON '*'
#define CYCLISTE '^'
#define LARGEUR 20
#define FREQUENCE 50

#define MOYENNE LARGEUR/2
#define DIFFICILE LARGEUR/4

/*
Fonction: cycyliste_peut_avancer:
---------------------------------
gestion des deplacement du cycliste : savoir si on a touché le canyon ou non 

param:
    (y, x): les coordonnees de la prochaine position du cycliste

returns:
    0 si le cycliste a touché le canyon, 1 sinon
*/
int cycliste_peut_avancer(int y, int x);



/*
Fonction: initialiser_board:
---------------------------- 
On initialise les bords du canyon et on l'affiche pour la premiere fois

param:
    board : liste qui doit contenir la postion du canyon pour chaque ligne
*/
void initialiser_board(int board[LINES - 2]);



/*
Fonction: afficher_canyon
--------------------------
affichage du canyon apres chaque refraichissement 

param:
    board: liste qui contient les precedentes positions du canyon
*/
void afficher_canyon(int board[LINES - 2], int difficulty);



/*
Fonction: afficher_cycliste
----------------------------
affichage du cycliste par rapport aux coordonnees passées en entrée

param: 
    (y, x): les coordonnees de la prochaine position du cycliste
*/
void afficher_cycliste(int y, int x);


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
int game(int difficulty, char nom[30]);


#endif
