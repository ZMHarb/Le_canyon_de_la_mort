#ifndef _SCORE_H_
#define _SCORE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Fonction init_LB
-------------------------

Une fonction qui initialise le LeaderBoard du jeu. 
Si le LeaderBoard existe déjà, elle met à jour le nombre de joueurs existant sur Le board .

params:
	nbr_joueurs: le nombre de joueurs du jeu courant

*/
void init_LB(int nbr_joueurs);


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
int get_scores_noms(int scores[15], char names[15][40]);


/*
Fonction ajouter_score
----------------------

Fonction qui fait ajouter le score au fichier de LeaderBoard

params:
	score: Le score du joueur
	nom:   Le nom du joueur 
*/
void ajouter_score(int score, char *nom);


/*
Fonction sort_scores
--------------------
Une fonction qui fait trier les scores dans l'ordre décroissant. Elle fait trier leur nom egalement selon leurs scores

params:
	names: Une liste qui contient les noms du joueurs
	scores: Une liste qui contient leur scores
	nbr_joueurs: Le nombre total des joueurs (scores)

returns:
    nbr_joueurs
*/
int sort_scores(int scores[15], char names[15][30]);


/*
Fonction UpdateLB
------------------
Une fonction qui fait reecrire le fichier LeaderBoard dans l'ordre decroissant (grand score -> petit score)

params:
	scores: Une liste des scores triées
	names: Une liste des noms triées selon leurs scores
*/
void UpdateLB(int scores[15], char names[15][40]);

/*
Fonction affichier_all_scores
-----------------------------
Une fonction qui affiche les scores dans l'ordre + HallOfFame qui consiste aux score >= 1500 lignes
*/
void afficher_all_scores();

#endif
