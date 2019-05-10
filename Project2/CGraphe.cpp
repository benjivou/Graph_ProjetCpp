#include "CGraphe.h"

CGraphe::CGraphe()
{
	uiGRANombreDeSommets = 0;
	uiGRANombreDArc = 0;
	ppSOMGRAListeSommets = (CSommet **)(malloc(sizeof(CSommet *)));
	

}

CGraphe::CGraphe(const char * pcFichier) {
	/* Etape 1 : récupération des données */
	CFichier *pFICDonnees = new CFichier(pcFichier);
	
	/* Etape 2 : Stockage des données de */
	uiGRANombreDArc = pFICDonnees->FICLire_NBArc();
	uiGRANombreDeSommets = pFICDonnees->FICLire_NBSommet();
	CStockageElement ** ppSTOListeDuGraph = pFICDonnees->FICLire_ppSTOFICStockage();

	/* Etape 3 : Generation de sommets */
	
	ppSOMGRAListeSommets = (CSommet **)malloc(sizeof(void *) * uiGRANombreDeSommets); // Création d'un tableau pour stocker les CSommets
	/* Stockage \ génération */
	for (unsigned int uiPos =  0; uiPos < uiGRANombreDeSommets ; uiPos++)
	{
		ppSOMGRAListeSommets[uiPos] = new CSommet(ppSTOListeDuGraph[uiPos]->iSTOLire_Sommet());
	}

	/* Etape 4 : Generation des Arcs */
	/* Deplacement dans la liste des sommets du CFichier*/
	for (unsigned int  uiPosSommet = 0; uiPosSommet < uiGRANombreDeSommets;  uiPosSommet++)
	{
		
		// Si on a bien des sommets dans ce sommet
		if (ppSTOListeDuGraph[uiPosSommet]->uiLire_NBCible() > 0)
		{
			// On rempli le sommet avec les arcs
			for (unsigned int uiPosArc = 0; uiPosArc < ppSTOListeDuGraph[uiPosSommet]->uiLire_NBCible(); uiPosArc++)
			{
				ppSOMGRAListeSommets[uiPosSommet];// TO-DO
			}
		}
	}
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

void CGraphe::GRAModifier_Sommet(CSommet sommet, unsigned int uiNouvelleValeur)
{
	sommet.SOMModifier_Numero(uiNouvelleValeur);
}

void CGraphe::GRASupprimer_Sommet(CSommet sommet)
{

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
