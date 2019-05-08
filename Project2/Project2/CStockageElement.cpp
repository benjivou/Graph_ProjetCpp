#include "CStockageElement.h"



CStockageElement::CStockageElement()
{
	throw(STOCKAGE_VIDE);
}

CStockageElement::CStockageElement(int iSommetCible)
{
	iSommet = iSommetCible;
	uiNBArcSortant = 0;
	piArcSortant == nullptr;
}


CStockageElement::~CStockageElement()
{
	if (piArcSortant != nullptr)
	{
		free(piArcSortant);
	}
}

void CStockageElement::STOAjouter_Arc(int iSommetCible)
{
	/*
	 * Etape 1 : Check si la cible n'existe pas deja
	 */
	try
	{
		STOExiste_T_Il(iSommetCible);
	}
	catch (CException EXCe)	
	{
		throw(EXCe);
	}
	/*
	 * Etape 2 : Ajout de l'élement
	 */
	if ((++uiNBArcSortant) == 1)
	{
		piArcSortant = (int *)malloc(sizeof(int) * uiNBArcSortant);
	}
	else
	{
		piArcSortant = (int * )realloc( piArcSortant, sizeof(int) * uiNBArcSortant);
	}
	
	// Erreur : Allocation memoire 
	if (piArcSortant == nullptr) throw(new CException(ERREUR_REALLOC));
	
	// Remplissage 
	piArcSortant[uiNBArcSortant - 1] = iSommetCible;
}

void CStockageElement::STOExiste_T_Il(int iElement)
{
	for (unsigned int  uiPosition = 0; uiPosition < uiNBArcSortant; uiPosition++)
	{
		if (iElement == piArcSortant[uiPosition])
		{
			throw(new CException(CETTE_ELEMENT_EXISTE_DEJA));
		}
	}
}
