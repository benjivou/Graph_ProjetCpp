#include "CSommet.h"


CSommet::CSommet()
{
	uiSOMNumero = 0;
	uiSOMTailleArrivant = 0;
	uiSOMTaillePartant = 0;

	ppARCSOMArrivant = nullptr;
	ppARCSOMPartant = nullptr;

}

CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	uiSOMTailleArrivant = 0;
	uiSOMTaillePartant = 0;

	ppARCSOMArrivant = nullptr;
	ppARCSOMPartant = nullptr;


}

CSommet::CSommet(CSommet & SOMParam)
{
	uiSOMNumero = SOMParam.uiSOMNumero;			// Copie du numero


	if (SOMParam.ppARCSOMArrivant != nullptr)	// Il y a des sommets arrivants
	{
		// Allocation memoire des sommets arrivants
		ppARCSOMArrivant = (CArc **)malloc(sizeof(void *) * SOMParam.uiSOMTailleArrivant);

		for (unsigned int uiBoucle = 0; uiBoucle < SOMParam.uiSOMTailleArrivant; uiBoucle++)
		{
			// on stock le nouveau pointeur 
			ppARCSOMArrivant[uiBoucle] = new CArc(SOMParam.ppARCSOMArrivant[uiBoucle]->ARCLire_Destination());
		}
	}
	else { ppARCSOMArrivant = nullptr; };

	if (SOMParam.ppARCSOMPartant != nullptr)
	{
		ppARCSOMPartant = (CArc **)malloc(sizeof(CArc *) * SOMParam.uiSOMTaillePartant);

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


CSommet::~CSommet()
{
	if (ppARCSOMPartant != nullptr)
	{
		for (unsigned int uiPos = 0; uiPos < uiSOMTaillePartant; uiPos++)
		{
			delete(ppARCSOMPartant[uiPos]);
		}
		free(ppARCSOMPartant);
	}
	if (ppARCSOMArrivant != nullptr)
	{
		for (unsigned int uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
		{
			delete(ppARCSOMArrivant[uiPos]);
		}
		free(ppARCSOMArrivant);
	}
}

void CSommet::SOMAjouter_Arc_Arrivant(CArc * pARC)
{
	ppARCSOMArrivant == nullptr ?
		ppARCSOMArrivant = (CArc **)malloc(sizeof(void*)) :											// premier element
		ppARCSOMArrivant = (CArc **)realloc(ppARCSOMArrivant, sizeof(void*) * (uiSOMTailleArrivant + 1));// autres elements
	if (ppARCSOMArrivant == nullptr) throw(*new CException(REALLOC_PROBLEME));

	ppARCSOMArrivant[uiSOMTailleArrivant] = pARC; // Stockage 
	uiSOMTailleArrivant++;
}

void CSommet::SOMAjouter_Arc_Sortant(CArc * pARC)
{
	ppARCSOMPartant == nullptr ?
		ppARCSOMPartant = (CArc **)malloc(sizeof(void*)) :											// premier element
		ppARCSOMPartant = (CArc **)realloc(ppARCSOMPartant, sizeof(void*) * (uiSOMTailleArrivant + 1));// autres elements

	if (ppARCSOMPartant == nullptr) throw(*new CException(REALLOC_PROBLEME));

	ppARCSOMPartant[uiSOMTailleArrivant] = pARC; // Stockage 
	uiSOMTailleArrivant++;
}

void CSommet::SOMRetirer_Arc_Arrivant(unsigned int uiCible)
{
	unsigned int uiNboccurrence = SOMArrivant_Existe_T_Il(uiCible); // recupération du nombre d'occurrence a enlever

	if (uiNboccurrence > 0) // on doit retirer des éléments
	{
		unsigned int uiTailleNouvelleChaine = uiSOMTailleArrivant - uiNboccurrence;

		if (uiTailleNouvelleChaine) // il reste des éléments dans la chaine apres deletion
		{

			/* Etape 1 : allocation de la nouvelle chaine */
			CArc ** ppARCNouvelle_Chaine = (CArc **)malloc(sizeof(void*) * uiTailleNouvelleChaine);

			/* Etape 2 : Remplissage de la nouvelle chaine */
			unsigned int uiOffset = 0; // il donne le nombre d'occurence trouvé jusque là
			for (unsigned int uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
			{
				if (ppARCSOMArrivant[uiPos]->ARCLire_Destination() == uiCible)
					uiOffset++;						// on trouve un element à retirer 
				else
					ppARCNouvelle_Chaine[uiPos - uiOffset] = ppARCSOMArrivant[uiPos]; // on stocke 
			}
		}
		else
		{
			free(ppARCSOMArrivant);
			ppARCSOMArrivant = nullptr;
		}
		uiSOMTailleArrivant = uiNboccurrence;
	}
}

void CSommet::SOMRetirer_Arc_Sortant(unsigned int uiCible)
{
	unsigned int uiNboccurrence = SOMPartant_Existe_T_Il(uiCible); // recupération du nombre d'occurrence a enlever

	if (uiNboccurrence > 0) // on doit retirer des éléments
	{
		unsigned int uiTailleNouvelleChaine = uiSOMTaillePartant - uiNboccurrence;

		if (uiTailleNouvelleChaine) // il reste des éléments à dans la chaine apres deletion
		{

			/* Etape 1 : allocation de la nouvelle chaine */
			CArc ** ppARCNouvelle_Chaine = (CArc **)malloc(sizeof(void*) * uiTailleNouvelleChaine);

			/* Etape 2 : Remplissage de la nouvelle chaine */
			unsigned int uiOffset = 0; // il donne le nombre d'occurence trouvé jusque là
			for (unsigned int uiPos = 0; uiPos < uiSOMTaillePartant; uiPos++)
			{
				if (ppARCSOMPartant[uiPos]->ARCLire_Destination() == uiCible)
					uiOffset++;						// on trouve un element à retirer 
				else
					ppARCNouvelle_Chaine[uiPos - uiOffset] = ppARCSOMPartant[uiPos]; // on stocke 
			}
		}
		else
		{
			free(ppARCSOMPartant);
			ppARCSOMPartant = nullptr;
		}
		uiSOMTaillePartant = uiNboccurrence;
	}
}

void CSommet::SOMModifier_Arc_Arrivant(unsigned int uiCible)
{
}

void CSommet::SOMModifier_Arc_Sortant(unsigned int uiCible)
{
}

unsigned int CSommet::SOMArrivant_Existe_T_Il(unsigned int uiCible)
{
	unsigned int iNbOccurrence = 0;
	for (unsigned int uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
	{
		if (uiCible == ppARCSOMArrivant[uiPos]->ARCLire_Destination())
		{
			iNbOccurrence++;
		}
	}
	return iNbOccurrence;
}

unsigned int CSommet::SOMPartant_Existe_T_Il(unsigned int uiCible)
{
	int iNbOccurrence = 0;
	for (unsigned int uiPos = 0; uiPos < uiSOMTaillePartant; uiPos++)
	{
		if (uiCible == ppARCSOMPartant[uiPos]->ARCLire_Destination())
		{
			iNbOccurrence++;
		}
	}
	return iNbOccurrence;
}

void CSommet::SOMAfficher_Sommet()
{
	cout << "Sommet : " << uiSOMNumero << endl;
	if (uiSOMTailleArrivant)
	{
		cout << "Ses Arcs partants sont :" << endl;
		for (unsigned int uiPos = 0; uiPos < uiSOMTailleArrivant; uiPos++)
		{
			cout << " -> " << ppARCSOMArrivant[uiPos]->ARCLire_Destination() << endl;
		}
	}

}

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
			ppARCSOMPartant[uiBoucle] = new CArc(SOMParam.ppARCSOMArrivant[uiBoucle]->ARCLire_Destination());
		}
	}
	else { SOMParam.ppARCSOMPartant = nullptr; }

	uiSOMTailleArrivant = SOMParam.uiSOMTailleArrivant;
	uiSOMTaillePartant = SOMParam.uiSOMTaillePartant;

	return *this;
}
