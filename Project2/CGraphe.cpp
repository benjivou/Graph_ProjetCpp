
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
			puiBufferArc = (unsigned int *)ppSTOListeDuGraph[uiPosSommet]->piSTOLire_Cibles();

			// On rempli le sommet avec les arcs
			for (unsigned int uiPosArc = 0; uiPosArc < ppSTOListeDuGraph[uiPosSommet]->uiLire_NBCible(); uiPosArc++)
			{
				ppSOMGRAListeSommets[uiPosSommet]->SOMAjouter_Arc_Sortant(new CArc(puiBufferArc[uiPosArc])); // remplissage des sommet sortants 

				// On doit rechercher le sommet cible 
				while (ppSOMGRAListeSommets[uiBufferPosition]->SOMLire_Numero() != puiBufferArc[uiPosArc]) ++uiBufferPosition;

				// On rempli le sommet cible
				ppSOMGRAListeSommets[uiBufferPosition]->SOMAjouter_Arc_Arrivant(new CArc(puiBufferArc[ppSOMGRAListeSommets[uiPosSommet]->SOMLire_Numero()]));
			}
		}
	}
}

CGraphe::CGraphe(CGraphe & GRPParam)
{
	if (GRPParam.ppSOMGRAListeSommets != nullptr)
	{
		/* Etape 1 : Allocation de l'espace de CSommet*/
		ppSOMGRAListeSommets = (CSommet **)(malloc(sizeof(CSommet *) * GRPParam.GRALire_NbSommet()));

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
	cout << "NB ARC: " << uiGRANombreDArc << endl;
	cout << "NB Sommet: " << uiGRANombreDeSommets << endl;
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
	if (GRAPresence_Sommet(uiAncienneValeur) > 0) // Si lélément est bien présent
	{
		/* Etape 1 : Recherche du Sommet */
		while (ppSOMGRAListeSommets[uiPos]->SOMLire_Numero() != uiAncienneValeur)uiPos++;  // Positionne le pointeur 

		/* Etape 2 : modification */
		ppSOMGRAListeSommets[uiPos]->SOMModifier_Numero(uiNouvelleValeur);
	}

}

void CGraphe::GRASupprimer_Sommet(unsigned int uiValeur)
{
	unsigned int uiPosNouvelle = 0;
	CSommet ** ppSOMBuffer;
	CArc ** ppARCBufferCible;
	/* Etape 0 : L'élément existe - t - il?*/
	if (GRAPresence_Sommet(uiValeur) > -1) // présence de lélément
	{
		/* Etape 1: Allocation de la nouvelle zone memoire */
		ppSOMBuffer = (CSommet **)malloc(sizeof(void*) * (uiGRANombreDeSommets - 1));

		/* Etape 2: Recopie */
		for (unsigned int uiPosAncienne = 0; uiPosAncienne < uiGRANombreDeSommets; uiPosAncienne++)
		{
			/* Etape 2.1 : Element à supprimer*/
			if (ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_Numero() == uiValeur)
			{
				/*Etape 2.1.A : Retirer le nb d'arc de ce sommet du graphe */
				uiGRANombreDArc -= ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_TaillePartant();

				/* Etape 2.1.B : Retirer tous les Arcs partant et arrivant dans les autres CSommets */
				ppARCBufferCible = ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_ArcArrivant();
				// Partant de uiValeur
				for (unsigned int uiPos = 0; uiPos < ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_TailleArrivant(); uiPos++)
				{

					GRASupprimer_Arc(ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_Numero(), ppARCBufferCible[0]->ARCLire_Destination());

				}
				ppARCBufferCible = ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_ArcPartant();
				// Arrivant a uiValeur
				for (unsigned int uiPos = 0; uiPos < ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_TaillePartant(); uiPos++)
				{
					GRASupprimer_Arc(ppARCBufferCible[0]->ARCLire_Destination(), ppSOMGRAListeSommets[uiPosAncienne]->SOMLire_Numero());
				}

				/* Etape 2.1.C : Libéré le sommet */
				delete ppSOMGRAListeSommets[uiPosAncienne];
			}
			/* Etape 2.2 : Recopie */
			else
			{
				ppSOMBuffer[uiPosNouvelle] = ppSOMGRAListeSommets[uiPosAncienne];
				uiPosNouvelle++;
			}
		}
		/* Etape 3: Sauvegarde des nouveaux paramétre et libération de l'ancienne chaine */
		uiGRANombreDeSommets = uiPosNouvelle;
	}

}

/* \brief Si le sommet existe, on retourne sa position dans le tableau*/
int CGraphe::GRAPresence_Sommet(unsigned int uiValeur)
{
	int iPositionValeur = -1;
	unsigned int uiPos = 0;

	// positionnement 
	while (iPositionValeur < 0 && uiGRANombreDeSommets > uiValeur)
	{
		ppSOMGRAListeSommets[uiPos]->SOMLire_Numero() != uiValeur ? uiPos++ : iPositionValeur = uiPos;
	}

	return iPositionValeur;
}

void CGraphe::GRAAjouter_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
	/* Recuperation des position de depart des */
	int iPosDepart = GRAPresence_Sommet(uiDepart);
	int iPosArrive = GRAPresence_Sommet(uiArrivee);

	/* Les sommets existent-t-ils?*/
	if (iPosArrive > -1 && iPosDepart > -1)
	{
		/* Ajout des arcs*/
		ppSOMGRAListeSommets[iPosDepart]->SOMAjouter_Arc_Sortant(new CArc(uiArrivee));
		ppSOMGRAListeSommets[iPosArrive]->SOMAjouter_Arc_Arrivant(new CArc(uiDepart));
	}
}

void CGraphe::GRAModifier_Arc(unsigned int uiAncienDepart, unsigned int uiAncienArrivee, unsigned int uiNouveauDepart, unsigned int uiNouvelleArrivee)
{
	/* Recuperation des position de depart des */
	int iPosDepart = GRAPresence_Sommet(uiAncienDepart);
	int iPosArrive = GRAPresence_Sommet(uiAncienArrivee);
	if (iPosArrive > -1 && iPosDepart > -1)
	{
		iPosDepart = GRAPresence_Sommet(uiAncienDepart);
		iPosArrive = GRAPresence_Sommet(uiAncienArrivee);
		if (iPosArrive > -1 && iPosDepart > -1)
		{
			/* Destruction */
			GRASupprimer_Arc(uiAncienDepart, uiAncienArrivee);
			/* Création */
			GRAAjouter_Arc(uiNouveauDepart, uiNouvelleArrivee);
		}
		else
		{
			throw(*new CException(CIBLE_INEXISTANTE));
		}
	}
	else
	{
		throw(*new CException(ARC_INEXISTANT));
	}
}

void CGraphe::GRASupprimer_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
	int iPosDepart = GRAPresence_Sommet(uiDepart);
	int iPosArrive = GRAPresence_Sommet(uiArrivee);

	if (iPosArrive > -1 && iPosDepart > -1)
	{
		/* Ajout des arcs*/
		ppSOMGRAListeSommets[iPosDepart]->SOMRetirer_Arc_Sortant(uiArrivee);
		ppSOMGRAListeSommets[iPosArrive]->SOMRetirer_Arc_Arrivant(uiDepart);
	}
}

/* \brief return 1 si l'arc existe, 0 sinon */
int CGraphe::GRAPresence_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
	int iExisteArc = 0; // variable de retour 

	int iPosSomDepart = GRAPresence_Sommet(uiDepart); // check du sommet de depart 
	if (iPosSomDepart > -1)
	{
		if (ppSOMGRAListeSommets[iPosSomDepart]->SOMArrivant_Existe_T_Il(uiArrivee) != -1)
		{
			iExisteArc = 1;
		}
	}


	return iExisteArc;
}

CGraphe& CGraphe::GRAInverser_Graph()
{
	/* Etape 1 : allocation du nouveaux graphe */
	CGraphe* GRABuff = new CGraphe(*this);

	/* Etape 2 : Modification de tous ses Arcs */
	for (unsigned int uiPosition = 0; uiPosition < uiGRANombreDeSommets; uiPosition++)
	{
		GRABuff->ppSOMGRAListeSommets[uiPosition]->SOMInverser_Arc();
	}

	return *GRABuff;
}