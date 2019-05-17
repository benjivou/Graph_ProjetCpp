#include "CStockageElement.h"


/**
*\brief Constructeur par d�faut d'un stokage d'�l�ment
*/
CStockageElement::CStockageElement()
{
	throw(STOCKAGE_VIDE);
}

/**
*\brief Constructeur de confort d'un stokage d'�l�ment
*\param[in] iSommetCible Le sommet � stocker
*/
CStockageElement::CStockageElement(int iSommetCible)
{
	iSommet = iSommetCible;
	uiNBArcSortant = 0;
	piArcSortant = nullptr;
}

/**
*\brief Destructeur par d�faut d'un stokage d'�l�ment
*/
CStockageElement::~CStockageElement()
{
	if (piArcSortant != nullptr)
	{
		free(piArcSortant);
	}
}

/**
*\brief M�thode qui ajoute un arc
*\param[in] iSommetCible Le sommet � ajouter
*/
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
	 * Etape 2 : Ajout de l'�lement
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


/**
*\brief M�thode qui regarde si un �l�ment existe dans la liste des arcs sortants
*\param[in] iElement le num�ro du sommet � chercher dans la liste
*/
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

/**
*\brief M�thode qui affiche les arcs sortants d'un sommet
*/
void CStockageElement::STOAfficher_Stockage()
{
	cout << "Le Sommet : " << iSommet << " est la source de :";
	for (unsigned int  uiPosition = 0; uiPosition < uiNBArcSortant; uiPosition++)
	{
		cout << piArcSortant[uiPosition];
		if (uiPosition < uiNBArcSortant - 1) cout << ", ";

	}
	cout << "." << endl;
}
