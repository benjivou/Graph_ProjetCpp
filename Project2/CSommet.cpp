

/**
 *\brief Constructeur par défaut qui initialise à 0 les attributs et les pointeurs à nul
 *\warning : à ne pas utiliser ou une seule fois car les sommets n'accepte pas les doublons
 */
CSommet::CSommet()
{
	uiSOMNumero = 0;
	uiSOMTailleArrivant = 0;
	uiSOMTaillePartant = 0;

	ppARCSOMArrivant = nullptr;
	ppARCSOMPartant = nullptr;

}

/**
 *\brief Constructeur de confort d'un sommet qui initialise le numéro du sommet avec une valeur voulue
 */
CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	uiSOMTailleArrivant = 0;
	uiSOMTaillePartant = 0;

	ppARCSOMArrivant = nullptr;
	ppARCSOMPartant = nullptr;


}

/**
 *\brief Constructeur de recopie d'un sommet
 */
CSommet::CSommet(CSommet & SOMParam)
{
	uiSOMNumero = SOMParam.uiSOMNumero;			// Copie du numero
	

	if (SOMParam.ppARCSOMArrivant != nullptr)	// Il y a des sommets arrivants
	{
		// Allocation memoire des sommets arrivants
		ppARCSOMArrivant = (CArc **) malloc(sizeof(void *) * SOMParam.uiSOMTailleArrivant);

		for (unsigned int uiBoucle = 0; uiBoucle < SOMParam.uiSOMTailleArrivant; uiBoucle++)
		{
			// on stock le nouveau pointeur 
			ppARCSOMArrivant[uiBoucle] = new CArc(SOMParam.ppARCSOMArrivant[uiBoucle]->ARCLire_Destination());
		}
	}
	else {ppARCSOMArrivant = nullptr; };

	if (SOMParam.ppARCSOMPartant != nullptr)
	{
		ppARCSOMPartant = (CArc **) malloc(sizeof(CArc *) * SOMParam.uiSOMTaillePartant);
		
		for (unsigned int uiBoucle = 0; uiBoucle < uiSOMTailleArrivant; uiBoucle++)
		{
			//Stockage / generation
			ppARCSOMPartant[uiBoucle] = new CArc(SOMParam.ppARCSOMArrivant[uiBoucle]->ARCLire_Destination());
		}
	}
	else { SOMParam.ppARCSOMPartant = nullptr; }

	uiSOMTailleArrivant = SOMParam.uiSOMTailleArrivant;
	uiSOMTaillePartant = SOMParam.uiSOMTaillePartant;
	
}

/**
 *\brief Destructeur d'un sommet qui désalloue les pointeurs sur les arcs arrivants et sortants
 */
CSommet::~CSommet()
{
	if (ppARCSOMPartant != nullptr)
	{
		for (unsigned int  uiPos = 0; uiPos < uiSOMTaillePartant; uiPos++)
		{
			delete(ppARCSOMPartant[uiPos]);
		}
		free(ppARCSOMPartant);
	}
	if (ppARCSOMArrivant!= nullptr)
	{
		for (unsigned int uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
		{
			delete(ppARCSOMArrivant[uiPos]);
		}
		free(ppARCSOMArrivant);
	}
}
/**
 *\brief L'objectif de cette méthode est d'ajouter un arc dans la liste des arcs arrivants du sommet
 *\param[in] pARC pointeur sur l'arc à ajouter
 */
void CSommet::SOMAjouter_Arc_Arrivant(CArc * pARC)
{
	ppARCSOMArrivant == nullptr ?
		ppARCSOMArrivant = (CArc **) malloc(sizeof(void*)) :											// premier element
		ppARCSOMArrivant = (CArc **) realloc(ppARCSOMArrivant, sizeof(void*) * (uiSOMTailleArrivant+1));// autres elements
	if (ppARCSOMArrivant == nullptr) throw(*new CException(REALLOC_PROBLEME));

	ppARCSOMArrivant[uiSOMTailleArrivant] = pARC; // Stockage 
	uiSOMTailleArrivant++;
}

/**
 *\brief L'objectif de cette méthode est d'ajouter un arc dans la liste des arcs sortants du sommet
 *\param[in] pARC pointeur sur l'arc à ajouter
 */
void CSommet::SOMAjouter_Arc_Sortant(CArc * pARC)
{
	ppARCSOMPartant == nullptr ?
		ppARCSOMPartant = (CArc **)malloc(sizeof(void*)) :											// premier element
		ppARCSOMPartant = (CArc **)realloc(ppARCSOMPartant, sizeof(void*) * (uiSOMTaillePartant + 1));// autres elements

	if (ppARCSOMPartant == nullptr) throw(*new CException(REALLOC_PROBLEME));

	ppARCSOMPartant[uiSOMTaillePartant] = pARC; // Stockage 
	uiSOMTaillePartant++;
}

/**
 *\brief L'objectif de cette méthode est de retirer un arc dans la liste arrivant d'un sommet
 *\param[in] uiCible Le numéro du sommet qui retire son arc
 */
void CSommet::SOMRetirer_Arc_Arrivant(unsigned int uiCible)
{
	int iPosition = SOMArrivant_Existe_T_Il(uiCible); // recupération la position de l'élément
	unsigned int uiPosElementAEnlever;
	unsigned int uiTailleNouvelleChaine;
	unsigned int uiOffset = 0; // il donne le nombre d'occurence trouvé jusque là
	unsigned int uiPos;

	if (iPosition > -1) // on doit retirer des éléments
	{
		uiTailleNouvelleChaine = uiSOMTailleArrivant - 1;
		uiPosElementAEnlever = (unsigned int)iPosition;
		if (uiTailleNouvelleChaine) // il reste des éléments à dans la chaine apres deletion
		{

			/* Etape 1 : allocation de la nouvelle chaine */
			CArc ** ppARCNouvelle_Chaine = (CArc **)malloc(sizeof(void*) * uiTailleNouvelleChaine);

			/* Etape 2 : Remplissage de la nouvelle chaine */

			for (uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
			{
				if (uiPos == uiPosElementAEnlever)
				{
					uiOffset = 1;						// on trouve un element à retirer 
				}

				else
					ppARCNouvelle_Chaine[uiPos - uiOffset] = ppARCSOMArrivant[uiPos]; // on stocke 
			}
			delete ppARCSOMArrivant[uiPosElementAEnlever];
			free(ppARCSOMArrivant); // vidange 
			ppARCSOMArrivant = ppARCNouvelle_Chaine;

		}
		else
		{
			delete ppARCSOMArrivant[0]; // destruction de l'élément 
			free(ppARCSOMArrivant);	// desallocation de la liste d'élément
			ppARCSOMArrivant = nullptr;
		}
		uiSOMTailleArrivant = uiTailleNouvelleChaine;
	}
}

/**
 *\brief L'objectif de cette méthode est de retirer un arc dans la liste sortant d'un sommet
 *\param[in] uiCible Le numéro du sommet qui retire son arc
 */
void CSommet::SOMRetirer_Arc_Sortant(unsigned int uiCible)
{
	int iPosition = SOMPartant_Existe_T_Il(uiCible); // recupération la position de l'élément
	unsigned int uiPosElementAEnlever;
	unsigned int uiTailleNouvelleChaine;
	unsigned int uiOffset = 0; // il donne le nombre d'occurence trouvé jusque là
	unsigned int uiPos;

	if (iPosition > -1) // on doit retirer des éléments
	{
		uiTailleNouvelleChaine = uiSOMTaillePartant - 1;
		uiPosElementAEnlever = (unsigned int)iPosition;
		if (uiTailleNouvelleChaine) // il reste des éléments à dans la chaine apres deletion
		{

			/* Etape 1 : allocation de la nouvelle chaine */
			CArc ** ppARCNouvelle_Chaine = (CArc **)malloc(sizeof(void*) * uiTailleNouvelleChaine);

			/* Etape 2 : Remplissage de la nouvelle chaine */
			
			for (uiPos = 0; uiPos < uiSOMTaillePartant; uiPos++)
			{
				if (uiPos == uiPosElementAEnlever)
				{
					uiOffset = 1;						// on trouve un element à retirer 
					delete ppARCSOMPartant[uiPos];
				}
					
				else
					ppARCNouvelle_Chaine[uiPos - uiOffset] = ppARCSOMPartant[uiPos]; // on stocke 
			}
			free(ppARCSOMPartant); // vidange 
			ppARCSOMPartant = ppARCNouvelle_Chaine;

		}
		else
		{
			delete ppARCSOMPartant[0]; // destruction de l'élément 
			free(ppARCSOMPartant);	// desallocation de la liste d'élément
			ppARCSOMPartant = nullptr; 
		}
		uiSOMTaillePartant = uiTailleNouvelleChaine;
	}
}

/**
 *\brief L'objectif de cette méthode est de trouver si uiCible est dans la liste des arcs arrivant d'un sommet
 *\param[in] uiCible Le numéro de sommet de l'arc arrivant à trouver
 *\return iPosition la position de la cible ou -1 si la cible n'est pas dans la liste
 */
int CSommet::SOMArrivant_Existe_T_Il(unsigned int uiCible)
{
	int iPosition = -1;
	for ( unsigned int uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
	{
		if (uiCible == ppARCSOMArrivant[uiPos]->ARCLire_Destination())
		{
			iPosition = (int) uiPos;
		}
	}
	return iPosition;
}

/**
 *\brief L'objectif de cette méthode est de trouver si uiCible est dans la liste des arcs partant d'un sommet
 *\param[in] uiCible Le numéro de sommet de l'arc partant à trouver
 *\return iPosition la position de la cible ou -1 si la cible n'est pas dans la liste
 */
int CSommet::SOMPartant_Existe_T_Il(unsigned int uiCible)
{
	int iPosition = -1;
	for (unsigned int uiPos = 0; uiPos < uiSOMTaillePartant; uiPos++)
	{
		if (uiCible == ppARCSOMPartant[uiPos]->ARCLire_Destination())
		{
			iPosition = (int) uiPos;
		}
	}
	return iPosition;
}


 /**
 *\brief Cette méthode inverse les arcs sortants et entrant,
 * bien faire attention à l'intégrité du Graphe après les modifications
 */
void CSommet::SOMInverser_Arc()
{
	CArc ** ppARCBuffer;
	unsigned int uiBuffer;

	/* On deplace d'abord les espace mémoires */
	
	ppARCBuffer = ppARCSOMArrivant;
	ppARCSOMArrivant = ppARCSOMPartant;
	ppARCSOMPartant = ppARCBuffer;
	/*  Ensuite les tailles */
	uiBuffer = uiSOMTailleArrivant;
	uiSOMTailleArrivant = uiSOMTaillePartant;
	uiSOMTaillePartant = uiBuffer;
}

/**
*\brief Cette méthode affiche le numéro d'un sommet, ses arcs partants et arrivants
*/
void CSommet::SOMAfficher_Sommet()
{
	unsigned int uiPos;
	printf("Sommet : %d \n", uiSOMNumero);

	if (uiSOMTaillePartant>0)
	{
		printf("Ses Arcs partants sont :\n");

		for (uiPos= 0; uiPos < uiSOMTaillePartant; uiPos++)
		{
			printf("-> %d\n", ppARCSOMPartant[uiPos]->ARCLire_Destination());
		}
	}

	if (uiSOMTailleArrivant > 0)
	{
		printf("Ses Arcs arrivants sont :\n");

		for (uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
		{
			printf("-> %d\n", ppARCSOMArrivant[uiPos]->ARCLire_Destination());
		}
	}
	
}

/**
*\brief Surcharge de l'opérateur d'affectation
*\param[in] SOMParam Le sommet à recopier
*/
CSommet & CSommet::operator=(CSommet & SOMParam)
{
	uiSOMNumero = SOMParam.uiSOMNumero;			// Copie du numero


	if (SOMParam.ppARCSOMArrivant != nullptr)	// Il y a des sommets arrivants
	{
		// Allocation memoire des sommets arrivants
		ppARCSOMArrivant = (CArc **)malloc(sizeof(CArc *) * SOMParam.uiSOMTailleArrivant);

		for (unsigned int uiBoucle = 0; uiBoucle < SOMParam.uiSOMTailleArrivant; uiBoucle++)
		{
			// on stock le nouveau pointeur 
			ppARCSOMArrivant[uiBoucle] = new CArc(SOMParam.ppARCSOMArrivant[uiBoucle]->ARCLire_Destination());
		}
	}
	else { ppARCSOMArrivant = nullptr; }

	if (SOMParam.ppARCSOMPartant != nullptr)
	{
		ppARCSOMPartant = (CArc **)(malloc(sizeof(CArc *)* SOMParam.uiSOMTaillePartant));

		for (unsigned int uiBoucle = 0; uiBoucle < uiSOMTailleArrivant; uiBoucle++)
		{
			//Stockage / generation
			ppARCSOMPartant[uiBoucle] = new CArc(SOMParam.ppARCSOMPartant[uiBoucle]->ARCLire_Destination());
		}
	}
	else { SOMParam.ppARCSOMPartant = nullptr; }

	uiSOMTailleArrivant = SOMParam.uiSOMTailleArrivant;
	uiSOMTaillePartant = SOMParam.uiSOMTaillePartant;

	return *this;
}
