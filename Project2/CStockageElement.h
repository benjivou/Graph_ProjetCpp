#ifndef CSTOCK
#define CSTOCK
/*
 *\brief L'objectif est d'avoir une boite d'�l�ments permettant de cr�er un sommet et ses arcs sortants
 * utiliser cette classe permet de garder une �volutivit� pour le code du 3�me projet
 */

#include"CException.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

/* Message d'Erreur*/
#define CETTE_ELEMENT_EXISTE_DEJA 30
#define ERREUR_REALLOC 31
#define STOCKAGE_VIDE 32
class CStockageElement
{
private:
	int  iSommet;
	int* piArcSortant;
	unsigned int uiNBArcSortant;

public:
	CStockageElement();				// throw erreur car inutile
	CStockageElement(int iSommet);
	~CStockageElement();

	int STOLire_Sommet() { return iSommet; };
	int* STOLire_Cibles() { return piArcSortant; };
	unsigned int Lire_NBCible() { return uiNBArcSortant; };

	void STOAjouter_Arc(int iSommetCible);
	void STOExiste_T_Il(int iElement);	// permet de savoir si la cible de l'arc existe

	void STOAfficher_Stockage();
};
#endif // !CSTOCK