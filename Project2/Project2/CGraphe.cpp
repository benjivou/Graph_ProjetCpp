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

	unsigned int *puiBufferArc;		// recupére les arcs sortants etrentrant si besoin
	unsigned int uiBufferPosition;	// permet de remplir les arcs sortants

	/* Etape 3 : Generation de sommets */

	ppSOMGRAListeSommets = (CSommet **)malloc(sizeof(void *) * uiGRANombreDeSommets); // Création d'un tableau pour stocker les CSommets
	/* Stockage \ génération */
	for (unsigned int uiPos = 0; uiPos < uiGRANombreDeSommets; uiPos++)
	{
		ppSOMGRAListeSommets[uiPos] = new CSommet(ppSTOListeDuGraph[uiPos]->iSTOLire_Sommet());
	}

	/* Etape 4 : Generation des Arcs */
	/* Deplacement dans la liste des sommets du CFichier*/
	for (unsigned int uiPosSommet = 0; uiPosSommet < uiGRANombreDeSommets; uiPosSommet++)
	{

		// Si on a bien des arcs sortant 
		if (ppSTOListeDuGraph[uiPosSommet]->uiLire_NBCible() > 0)
		{
			uiBufferPosition = 0;
			// recuperation des sommets sortants
			puiBufferArc = ppSTOListeDuGraph[uiPosSommet]->piSTOLire_Cibles();

			// On rempli le sommet avec les arcs
			for (unsigned int uiPosArc = 0; uiPosArc < ppSTOListeDuGraph[uiPosSommet]->uiLire_NBCible(); uiPosArc++)
			{
				ppSOMGRAListeSommets[uiPosSommet]->SOMAjouter_Arc_Sortant(new CArc(puiBufferArc[uiPosArc])); // remplissage des sommet sortants 

				// On doit rechercher le sommet cible 
				while (ppSOMGRAListeSommets[uiBufferPosition]->SOMAfficher_Sommet() != puiBufferArc[uiPosArc]) ++uiBufferPosition;

				// On rempli le sommet cible
				ppSOMGRAListeSommets[uiBufferPosition]->SOMAjouter_Arc_Entrant(new CArc(puiBufferArc[ppSOMGRAListeSommets[uiPosSommet]->SOMLire_Numero()]));
			}
		}
	}
}

CGraphe::CGraphe(CGraphe & GRPParam)
{
	if (GRPParam.ppSOMGRAListeSommets != nullptr)
	{
		/* Etape 1 : Allocation de l'espace de CSommet*/
		ppSOMGRAListeSommets = (CSommet **)(malloc(sizeof(CSommet *) * GRPParam.GRALire_NbSommet());

		/* Etape 2: Recopie */
		for (unsigned int uiPosition = 0; uiPosition < GRPParam.GRALire_NbSommet(); uiPosition++)
		{
			ppSOMGRAListeSommets[uiPosition] = new CSommet(*GRPParam.ppSOMGRAListeSommets[uiPosition]); // construction par recopie
		}
		/* Etape 3 : Recopie des infos de graphe*/
		uiGRANombreDArc = GRPParam.uiGRANombreDArc;
		uiGRANombreDeSommets = GRPParam.uiGRANombreDeSommets;
	}
	else
	{
		GRPParam.ppSOMGRAListeSommets = nullptr;
		uiGRANombreDArc = 0;
		uiGRANombreDeSommets = 0;
	}

}

CGraphe::~CGraphe()
{
	for (unsigned int uiPos = 0; uiPos < uiGRANombreDeSommets; uiPos++)
	{
		delete ppSOMGRAListeSommets[uiPos];
	}
}

void CGraphe::GRAAfficher_Graphe()
{
	for (unsigned int uiPos = 0; uiPos < uiGRANombreDeSommets; uiPos++)
	{
		ppSOMGRAListeSommets[uiPos]->SOMAfficher_Sommet();
	}
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

	unsigned int uiPos = 0;
	if (GRAPresence_Sommet(uiAncienneValeur) > 0) // Si l'élément est bien présent
	{
		/* Etape 1 : Recherche du Sommet */
		while (ppSOMGRAListeSommets[uiPos]->SOMAfficher_Sommet() != uiAncienneValeur)uiPos++;  // Positionne le pointeur 

		/* Etape 2 : modification */
		ppSOMGRAListeSommets[uiPos]->SOMModifier_Numero(uiNouvelleValeur);
	}

}

void CGraphe::GRASupprimer_Sommet(unsigned int uiValeur)
{
	unsigned int uiPosNouvelle = 0;
	CSommet ** ppSOMBuffer;

	/* Etape 0 : L'élément existe - t - il?*/
	if (GRAPresence_Sommet(uiValeur)) // présence de lélément
	{
		/* Etape 1: Allocation de la nouvelle zone memoire */
		ppSOMBuffer = (CSommet **)malloc(sizeof(void*) * (uiGRANombreDeSommets - 1));

		/* Etape 2: Recopie */
		for (unsigned int uiPosAncienne = 0; uiPosAncienne < uiGRANombreDSommets; uiPosAncienne++)
		{
			/* Etape 2.1 : Element à supprimer*/
			if (ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_Numero() == uiValeur)
			{
				/*Etape 2.1.A : Retirer le nb d'arc de ce sommet du graphe */
				uiGRANombreDArc -= ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_ArcPartant();

				/* Etape 2.1.B : Retirer tous les Arcs partant et arrivant dans les autres CSommets */
				// Partant de uiValeur

				// Arrivant de uiValeur
				// TO-DO
			}
		}
		/* Etape 3: Sauvegarde des nouveaux paramétre et libération de l'ancienne chaine */
	}

}

unsigned int CGraphe::GRAPresence_Sommet(unsigned int uiValeur)
{
	unsigned int uiPos = 0;

	// positionnement 
	while (ppSOMGRAListeSommets[uiPos]->SOMLire_Numero() != uiValeur && uiGRANombreDeSommets > uiValeur)
	{
		uiPos++;
	}
	// Test
	return ppSOMGRAListeSommets[uiPos]->SOMLire_Numero() == uiValeur;
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
