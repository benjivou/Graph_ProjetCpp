
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
	for (unsigned int uiPos =  0; uiPos < uiGRANombreDeSommets ; uiPos++)
	{
		ppSOMGRAListeSommets[uiPos] = new CSommet(ppSTOListeDuGraph[uiPos]->iSTOLire_Sommet());
	}

	/* Etape 4 : Generation des Arcs */
	/* Deplacement dans la liste des sommets du CFichier*/
	for (unsigned int  uiPosSommet = 0; uiPosSommet < uiGRANombreDeSommets;  uiPosSommet++)
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
				ppSOMGRAListeSommets[uiBufferPosition]->SOMAjouter_Arc_Arrivant(new CArc(ppSOMGRAListeSommets[uiPosSommet]->SOMLire_Numero()));
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
		for (unsigned int  uiPosition = 0; uiPosition < GRPParam.GRALire_NbSommet(); uiPosition++)
		{
			ppSOMGRAListeSommets[uiPosition] = new CSommet(* GRPParam.ppSOMGRAListeSommets[uiPosition]); // construction par recopie
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
	cout << "NB ARC: "<<uiGRANombreDArc << endl;
	cout << "NB Sommet: " << uiGRANombreDeSommets << endl;
	for (unsigned int uiPos = 0; uiPos < uiGRANombreDeSommets; uiPos++)
	{
		ppSOMGRAListeSommets[uiPos]->SOMAfficher_Sommet() ;
	}
}

void CGraphe::GRAAjouter_Sommet(unsigned int uiValeur)
{
	int iPos = GRAPresence_Sommet(uiValeur);
	if (iPos == -1 ) // le sommet n'existe pas 
	{
		CSommet * sommet = new CSommet(uiValeur); // création du nouveau sommet
		ppSOMGRAListeSommets = (CSommet**)realloc(ppSOMGRAListeSommets, (uiGRANombreDeSommets+1) * sizeof(CSommet)); // reallocation memoire
		ppSOMGRAListeSommets[uiGRANombreDeSommets] = sommet; // ajout de l'élément
		uiGRANombreDeSommets++;	// Sauvegarde du nombre
	}
	
	
	
	;
}

void CGraphe::GRAModifier_Sommet(unsigned int uiAncienneValeur, unsigned int uiNouvelleValeur)
{
	
	unsigned int uiPos = 0, uiPosArc;
	unsigned int *puiBuffSortant, *puiBuffEntrant;
	unsigned int uiTailleArrivant, uiTaillePartant;
	int iExiste,iPosArc;
	CArc ** ppARCBuff;

	if (GRAPresence_Sommet(uiAncienneValeur) > -1 ) // Si lélément est bien présent
	{
		/* Etape 1 : Recherche du Sommet */
		while (ppSOMGRAListeSommets[uiPos]->SOMLire_Numero() != uiAncienneValeur)uiPos++;  // Positionne le pointeur 

		
		/* Etape 2 : recuperation des arcs */
		uiTailleArrivant = ppSOMGRAListeSommets[uiPos]->SOMLire_TailleArrivant();
		uiTaillePartant = ppSOMGRAListeSommets[uiPos]->SOMLire_TaillePartant();
		/* Arrivant */
		ppARCBuff = ppSOMGRAListeSommets[uiPos]->SOMLire_ArcArrivant(); // Stockage des arcs arrivants

		if ( uiTailleArrivant > 0)
		{
			// A : Creation d'un buffer
			puiBuffEntrant = (unsigned int *)malloc(sizeof(unsigned int) * uiTailleArrivant);
			
			// B : Remplissage
			for ( uiPosArc = 0; uiPosArc < uiTailleArrivant; uiPosArc++)
			{
				puiBuffEntrant[uiPosArc] = ppARCBuff[uiPosArc]->ARCLire_Destination();
			}
			/* Etape 3 : modification de chaque cible des arcs dans les sommets cibles*/
		/* Arrivant */
			for (uiPos = 0; uiPos < uiTailleArrivant; uiPos++)
			{
				iExiste = GRAPresence_Sommet(puiBuffEntrant[uiPos]); // recuperation de la position du sommet

				ppARCBuff = ppSOMGRAListeSommets[iExiste]->SOMLire_ArcPartant();

				iPosArc = ppSOMGRAListeSommets[iExiste]->SOMPartant_Existe_T_Il(uiAncienneValeur); // Recup de la position de l'arc

				ppARCBuff[iPosArc]->ARCModifier_Destination(uiNouvelleValeur); // modification
			}
			free(puiBuffEntrant);
		}

		/* PArtant*/

		ppARCBuff = ppSOMGRAListeSommets[uiPos]->SOMLire_ArcPartant(); // Stockage des arcs arrivants

		if (uiTaillePartant > 0)
		{
			// A : Creation d'un buffer
			puiBuffSortant = (unsigned int *)malloc(sizeof(unsigned int) * uiTaillePartant);

			// B : Remplissage
			for (uiPosArc = 0; uiPosArc < uiTaillePartant; uiPosArc++)
			{
				puiBuffSortant[uiPosArc] = ppARCBuff[uiPosArc]->ARCLire_Destination();
			}

			/* Sortant */
			for (uiPos = 0; uiPos < uiTaillePartant; uiPos++)
			{
				iExiste = GRAPresence_Sommet(puiBuffSortant[uiPos]); // recuperation de la position du sommet

				ppARCBuff = ppSOMGRAListeSommets[iExiste]->SOMLire_ArcArrivant();

				iPosArc = ppSOMGRAListeSommets[iExiste]->SOMArrivant_Existe_T_Il(uiAncienneValeur); // Recup de la position de l'arc

				ppARCBuff[iPosArc]->ARCModifier_Destination(uiNouvelleValeur); // modification
			}
			free(puiBuffSortant);
		}

		


		/* Etape 4 : modification du sommet */
		ppSOMGRAListeSommets[uiPos]->SOMModifier_Numero(uiNouvelleValeur);
		
		
	}
	else
	{
		throw *new CException(INVALID_NEW_OR_ANCIEN_NUM);
	}
	
}

void CGraphe::GRASupprimer_Sommet(unsigned int uiValeur)
{
	unsigned int uiPosNouvelle = 0;	// curseur de la nouvelle boucle 
	unsigned int uiPosAncienne; // curseur dans l'anienne liste de sommet 
	unsigned int uiPosElementAEnlever;// posittion du sommet uiValeur 
	unsigned int uiNBPartant;
	unsigned int uiNBArrivant;
	int iEstPresent;
	CSommet ** ppSOMBuffer;
	CArc ** ppARCBufferCible;

	iEstPresent = GRAPresence_Sommet(uiValeur);

	/* Etape 0 : L'élément existe - t - il?*/
	if ( iEstPresent> -1) // présence de lélément
	{
		uiPosElementAEnlever = (unsigned int )iEstPresent;
		/* Etape 1: Allocation de la nouvelle zone memoire */
		ppSOMBuffer = (CSommet **) malloc(sizeof(void*) * (uiGRANombreDeSommets-1));

		/* Etape 2: Recopie */
		for (uiPosAncienne= 0; uiPosAncienne < uiGRANombreDeSommets; uiPosAncienne++)
		{
			/* Etape 2.1 : Element à supprimer*/
			if (uiPosAncienne == uiPosElementAEnlever)
			{
				uiNBPartant = ppSOMGRAListeSommets[uiPosElementAEnlever]->SOMLire_TaillePartant();
				uiNBArrivant = ppSOMGRAListeSommets[uiPosElementAEnlever]->SOMLire_TailleArrivant();
				/*Etape 2.1.A : Retirer le nb d'arc de ce sommet du graphe */
				uiGRANombreDArc -= uiNBArrivant ; // Arc part
				uiGRANombreDArc -= uiNBPartant; // Arc Arrivant

				/* Etape 2.1.B : Retirer tous les Arcs partant et arrivant dans les autres CSommets */
				
				
				// Partant de uiValeur
				ppARCBufferCible = ppSOMGRAListeSommets[uiPosElementAEnlever]->SOMLire_ArcPartant();

				for (unsigned int  uiPos = 0; uiPos < uiNBPartant; uiPos++)
				{
					
					GRASupprimer_Arc(uiValeur, ppARCBufferCible[uiPos]->ARCLire_Destination());																					
				}
				
				
				// Arrivant a uiValeur
				ppARCBufferCible = ppSOMGRAListeSommets[uiPosElementAEnlever]->SOMLire_ArcArrivant();

				for (unsigned int uiPos = 0; uiPos < uiNBArrivant; uiPos++)
				{
					
					GRASupprimer_Arc(ppARCBufferCible[uiPos]->ARCLire_Destination(), uiValeur);
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
		free(ppSOMGRAListeSommets);
		ppSOMGRAListeSommets = ppSOMBuffer;
	}
	
}

/* \brief Si le sommet existe, on retourne sa position dans le tableau*/
int CGraphe::GRAPresence_Sommet(unsigned int uiValeur)
{
	int iPositionValeur = -1 ;
	unsigned int uiPos = 0;

	// positionnement 
	while (iPositionValeur < 0  && uiGRANombreDeSommets > uiPos)
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
	if (iPosSomDepart> -1 )
	{
		if (ppSOMGRAListeSommets[iPosSomDepart]->SOMArrivant_Existe_T_Il(uiArrivee) != -1 )
		{
			iExisteArc = 1;
		}
	}
	

	return iExisteArc;
}

CGraphe& CGraphe::GRAInverser_Graph()
{
	/* Etape 1 : allocation du nouveaux graphe */
	CGraphe* GRABuff(this);

	/* Etape 2 : Modification de tous ses Arcs */
	for (unsigned int  uiPosition = 0; uiPosition < uiGRANombreDeSommets; uiPosition++)
	{
		GRABuff->ppSOMGRAListeSommets[uiPosition]->SOMInverser_Arc();
	}

	return *GRABuff;
}
