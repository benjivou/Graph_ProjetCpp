#include "CStockageElement.h"


/**
*\brief Constructeur par défaut d'un stokage d'élément
*/
CStockageElement::CStockageElement()
{
	throw(STOCKAGE_VIDE);
}

/**
*\brief Constructeur de confort d'un stokage d'élément
*\param[in] iSommetCible Le sommet à stocker
*/
CStockageElement::CStockageElement(int iSommetCible)
{
	iSommet = iSommetCible;
	uiNBArcSortant = 0;
	piArcSortant = nullptr;
}

/**
*\brief Destructeur par défaut d'un stokage d'élément
*/
CStockageElement::~CStockageElement()
{
	if (piArcSortant != nullptr)
	{
		free(piArcSortant);
	}
}

/**
*\brief Méthode qui ajoute un arc
*\param[in] iSommetCible Le sommet à ajouter
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


/**
*\brief Méthode qui regarde si un élément existe dans la liste des arcs sortants
*\param[in] iElement le numéro du sommet à chercher dans la liste
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
*\brief Méthode qui affiche les arcs sortants d'un sommet
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
