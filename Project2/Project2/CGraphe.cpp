#include "CGraphe.h"

CGraphe::CGraphe()
{
	uiGRANombreDeSommets = 0;
	uiGRANombreDArc = 0;
	ppSOMGRAListeSommets = (CSommet **)(malloc(sizeof(CSommet *)));
	ppSOMGRAListeSommets[0] = (CSommet*)malloc(sizeof(CSommet)*(UITAILLEDEFAULT + 1));

}

CGraphe::CGraphe(CGraphe & GRPParam)
{
	if (GRPParam.ppSOMGRAListeSommets != nullptr)
	{
		ppSOMGRAListeSommets = (CSommet **)(malloc(sizeof(CSommet *)));
		ppSOMGRAListeSommets[0] = (CSommet*)malloc(sizeof(CSommet)*(uiGRANombreDeSommets + 1));

		for (unsigned int uiBoucle1 = 0; uiBoucle1 < uiGRANombreDeSommets+1; uiBoucle1++)
		{
			ppSOMGRAListeSommets[0][uiBoucle1] = GRPParam.ppSOMGRAListeSommets[0][uiBoucle1];
		}
	}
	else { GRPParam.ppSOMGRAListeSommets = nullptr; }

}

CGraphe::~CGraphe()
{
	free(ppSOMGRAListeSommets[0]);
	free(ppSOMGRAListeSommets);
}

void CGraphe::GRAAfficher_Graphe()
{
}

void CGraphe::GRAAjouter_Sommet(unsigned int uiValeur)
{
	CSommet *sommet = new CSommet(uiValeur);
	ppSOMGRAListeSommets[0][uiGRANombreDeSommets] = *sommet;
	ppSOMGRAListeSommets[0] = (CSommet*)realloc(ppSOMGRAListeSommets[0], (uiGRANombreDeSommets + 1) * sizeof(CSommet));
	uiGRANombreDeSommets++;
}

void CGraphe::GRAModifier_Sommet(unsigned int uiAncienneValeur, unsigned int uiNouvelleValeur)
{
	for (unsigned int uiBoucle; uiBoucle < uiGRANombreDeSommets; uiBoucle++)
	{
		if (ppSOMGRAListeSommets[0][uiBoucle].SOMLire_Numero() == uiAncienneValeur)
			ppSOMGRAListeSommets[0][uiBoucle].SOMModifier_Numero(uiAncienneValeur);
	}


	//sommet.SOMModifier_Numero(uiNouvelleValeur);
}

void CGraphe::GRASupprimer_Sommet(unsigned int uiValeur)
{
	unsigned int uiCurseurAncienTab = 0;
	unsigned int uiCurseurNouveauTab = 0;


	CSommet ppSOMGRAListeSommets = (CSommet **)(malloc(sizeof(CSommet *)));
	ppSOMGRAListeSommets[0] = (CSommet*)malloc(sizeof(CSommet)*(UITAILLEDEFAULT + 1));

}

unsigned int CGraphe::GRAPresence_Sommet(unsigned int uiValeur)
{
	return 0;
}

void CGraphe::GRAAjouter_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
}

void CGraphe::GRAModifier_Arc(unsigned int uiAncienDepart, unsigned int uiAncienArrivee, unsigned int uiNouveauDepart, unsigned int uiNouvelleArrivee)
{
}

void CGraphe::GRASupprimer_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
}

unsigned int CGraphe::GRAPresence_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
	return 0;
}
