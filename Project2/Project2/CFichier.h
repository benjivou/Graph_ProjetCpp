/*	@brief Cette classe permet de r�cup�rer
*	les informations du fichier et apr�s les stocks
*	dans une matrice et garde le type dans un attribut
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "CException.h"
#ifndef CFICHIER_H
#define CFICHIER_H


#define MAX_LONGUEUR_LINE 80

#define MAX_TAILLE_ARG 20		// nombre de caractère dans 1 argument du fichier
/* Initialisation des balises à trouver dans le fichier */
#define NB_BALISE 4
#define TAILLE_BALISE_TYPE 1O
#define TAILLE_BALISE_NBLIGNES 10
#define TAILLE_BALISE_NBCOLONNES 8
#define TAILLE_BALISE_MATRICE 10

const char pcBaliseNbLignes[TAILLE_BALISE_NBLIGNES] = "NBSommets=";
const char pcBaliseNbColonnes[TAILLE_BALISE_NBCOLONNES] = "NBArcs=";
const char pcBaliseSommets[TAILLE_BALISE_MATRICE] = "Sommets=[";
const char pcBaliseArcs[TAILLE_BALISE_TYPE] = "Arcs=";
// regroupement
const int iLongueurBal[NB_BALISE] = { TAILLE_BALISE_TYPE,TAILLE_BALISE_NBLIGNES,TAILLE_BALISE_NBCOLONNES,TAILLE_BALISE_MATRICE };
const char *ppcTestBalise[NB_BALISE] = { pcBaliseType,pcBaliseNbLignes,pcBaliseNbColonnes,pcBaliseMatrice };
/* Message d'erreur */
#define CHEMIN_INVALID 11
#define BALISE_INVALID 12
#define TYPE_TROP_LONG 13
#define MAUVAIS_TYPE_MATRICE 14
#define TAILLE_MATRICE_INVALID 15
#define NOT_A_NUMBER 16
#define NOT_A_REEL 17
#define MATRICE_MAL_DECLARE 18
#define MATRICE_INITIALISATION_RATE 19


class CFichier
{
public:
	CFichier();
	CFichier(const char* adrcAdresse);
	~CFichier();

	// Getter
	double **FICLire_MTMppdrice() { return ppdStockage; };// inline
	int FICLire_NbLigne() { return ppdStockage->MTPLire_NbLigne(); } //inline
	int FICLire_NbColonne() { return ppdStockage->MTPLire_NbColonne(); } //inline
	char* FICLire_Type() { return pcType; }; // inline

	// Afficheur
	void FICAffiche_Contenu_Fich();	// affiche le contenu de la matrice

	
	
private:
	
	double **ppdStockage;
	unsigned int uiNbColonne;
	char pcType[MAX_TAILLE_ARG];

	unsigned int FICLongueur_De_Chaine(const char *);
	void FICEst_Un_Entier(const char* pcValeur);
	void FICEst_Un_Reel(const char* pcValeur);	// si la chaine n'est pas un nombre throw erreur
	char* FICTrouve_Premiere_Occurrence(char * pcLigne, char cSeparateur);
	int FICDemarre_Avec(const char* cPrefix, const char* cMot, int iLongueurPrefix);
	int FICCopie_String(char *pcSrc, char* pcDest);
	int FICStocke_Ligne_Dans_Matrice(char* pcLigne, double **pmStockage, unsigned int uiCurrentLigne);
};
#include "CFichier.cpp"
#endif // !CFICHIER_H
