/*	@brief Cette classe permet de récupérer
*	les informations du fichier et après les stocks
*	dans une matrice et garde le type dans un attribut
*/



#ifndef CFICHIER_H
#define CFICHIER_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CString.h"			// Méthodes de parser et traitement diverser sur les char *
#include "CStockageElement.h"	// contener pour stocker les données du graphe



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


/* Messages d'erreurs */
#define CHEMIN_INVALID 10
#define BALISE_INVALID 11
#define TYPE_TROP_LONG 12
#define GRAPH_VIDE 13
#define NOT_A_NUMBER 14
#define NOT_A_VALID_DIMENSION 15
#define MATRICE_MAL_DECLARE 16
#define MATRICE_INITIALISATION_RATE 17
#define CROCHET_MAL_PLACE 18
#define DECLARATION_LIGNE_COLONNE_INVALID 19
#define DECLARATION_DOUBLE_SOMMET 20
#define DECLARATION_SOMMET_NEXISTE_PAS 21
#define SOMMET_NEGATIF 34
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

	int* FICRecup_Ligne_Argument(char* pcLigne, const char ** ppcBaliseATrouver, unsigned int uiNBdeBalise);
	int FICSommet_Existe_T_Il(int iElement, int * piListe, unsigned int uiNBElement);
};
#include "CFichier.cpp"
#endif // !CFICHIER_H
