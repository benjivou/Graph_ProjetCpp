#include"CException.h"
#include <stdlib.h>
/*
 *\brief L'objectif est d'avoir une boite d'éléments permettant de créer un sommet et ses arcs sortants
 * utiliser cette classe permet de garder une évolutivité pour le code du 3ème projet
 */

#ifndef CSTOCK
#define CSTOCK


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

	int iSTOLire_Sommet() { return iSommet; };
	int* piSTOLire_Cibles() { return piArcSortant; };
	unsigned int uiLire_NBCible() { return uiNBArcSortant; };

	void STOAjouter_Arc(int iSommetCible);
	void STOExiste_T_Il(int iElement);	// permet de savoir si la cible de l'arc existe

};
#endif // !CSTOCK