/*	@brief Cette classe permet de r�cup�rer
*	les informations du fichier et apr�s les stocks
*	dans une matrice et garde le type dans un attribut
*/

#ifndef CFICHIER_H
#define CFICHIER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

<<<<<<< HEAD
#include "CStockageElement.h"	// contenaire pour stocker les données du graphe
#include "CString.h"			// Methodes de parser et traitement diverser sur les char *
=======
#include "CException.h"
#include "CStockageElement.h" // contenaire pour stocker les données du graphe
>>>>>>> parent of 16e47be... add CString


#define MAX_LONGUEUR_LINE 80
#define MAX_TAILLE_ARG 20		// nombre de caractère dans 1 argument du fichier
/* Initialisation des balises à trouver dans le fichier  */
/*Balise de Paramétrage*/
#define NB_BALISE 6


const char pcBaliseNbLignes[] = "NBSommets=";
const char pcBaliseNbColonnes[] = "NBArcs=";
const char pcBaliseSommets[] = "Sommets=[";
const char pcBaliseArcs[] = "Arcs=[";

// Balises de Sommets 
const char pcBaliseSommetNumero[] = "Numero=";

// Balises d'Arc
const char pcBaliseArcDebut[] = "Debut=";
const char pcBaliseArcFin[] = "Fin=";
// regroupement

const char *ppcTestBaliseParametrique[NB_BALISE] = { pcBaliseNbLignes,pcBaliseNbColonnes,pcBaliseSommets,pcBaliseSommetNumero,pcBaliseArcs,pcBaliseArcDebut};	// info de Ligne
const char *ppcTestBaliseSommet[] = { pcBaliseSommetNumero };						// info à récupérer pour une ligne de Sommet
const char *ppcTestBaliseArc[] = { pcBaliseArcDebut,pcBaliseArcFin };				// info à récupérer pour une ligne d'Arc


/* Message d'erreur */
#define CHEMIN_INVALID 11
#define BALISE_INVALID 12
#define TYPE_TROP_LONG 13
#define MAUVAIS_TYPE_MATRICE 14
#define GRAPH_VIDE 15
#define NOT_A_NUMBER 16
#define NOT_A_VALID_DIMENSION 17
#define MATRICE_MAL_DECLARE 18
#define MATRICE_INITIALISATION_RATE 19
#define CROCHET_MAL_PLACE 20
#define DECLARATION_LIGNE_COLONNE_INVALID 21
#define DECLARATION_DOUBLE_SOMMET 22
#define DECLARATION_SOMMET_NEXISTE_PAS 23

class CFichier
{
public:
	CFichier();
	CFichier(const char* adrcAdresse);
	~CFichier();

	// Getter
	CStockageElement **FICLire_ppSTOFICStockage() { return ppSTOFICStockage; };// inline
	unsigned int FICLire_NBSommet() { return uiFICNBSommet; }; // inline
	unsigned int FICLire_NBArc() { return uiFICNBArc; }; // inline


	// Afficheur
	void FICAffiche_Contenu_Fich();	// affiche le contenu de la matrice

	
	
private:
	
	CStockageElement ** ppSTOFICStockage;
	unsigned int uiFICNBSommet;
	unsigned int uiFICNBArc;

	unsigned int FICLongueur_De_Chaine(const char *);
	void FICEst_Un_Entier(const char* pcValeur);
	char* FICTrouve_Premiere_Occurrence(char * pcLigne, char cSeparateur);
	int FICDemarre_Avec(const char* cPrefix, const char* cMot, int iLongueurPrefix);
	int FICCopie_String(char *pcSrc, char* pcDest);
	int* FICRecup_Ligne_Argument(char* pcLigne, const char ** ppcBaliseATrouver, unsigned int uiNBdeBalise);
	int FICSommet_Existe_T_Il(int iElement, int * piListe, unsigned int uiNBElement);
};
#include "CFichier.cpp"
#endif // !CFICHIER_H
