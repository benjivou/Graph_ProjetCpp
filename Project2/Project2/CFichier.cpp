#include "CFichier.h"


/**
 *\brief Constructeur par défaut il sert simplement à éviter les problèmes de créations par défaut
 */
CFichier::CFichier()
{
	throw(*new CException(BALISE_INVALID));
}


/**
 *\brief desalloue le CMatrice avant de finir 
 */
CFichier::~CFichier()
{
	if (ppSTOFICStockage != nullptr)
	{
		// desallouer tous les sommets 
		for (unsigned int  uiPosition = 0; uiPosition < uiFICNBSommet; uiPosition++)
		{
			delete(ppSTOFICStockage[uiPosition]);
		}
	}
	uiFICNBArc = 0;
	uiFICNBSommet = 0;
	
}


/**
 *\brief On lui passe en paramètre un chemin d'accés à un fichier, génére une matrice avec les informations du fichier
 *\param[in] cAdresse c'est le chemin d'accés au fichier cible
 *\return un objet CFichier, initialiser avec CFichier() si probléme ou vide
 * sinon c'est un Cfichier avec les bonnes valeurs
 */
CFichier::CFichier(const char * cAdresse)
{
	
	printf("%s \n", cAdresse);
	


	

	unsigned int uiLigne = 0;		// donne la ligne du fichier en cours d'étude
	char pcLine[MAX_LONGUEUR_LINE];	// ligne d'argument pour créer la matrice
	int* piListeSommet = nullptr;	// stock les sommets déja vus

	/* Variable nécessaire à la création de la liste*/


	unsigned int uiNBArc;			// stocke le nombre d'arc à générer
	unsigned int uiNBSommet;		// stocke le nombre de sommet à générer
	unsigned int uiBufferPosition;  // stocke la position de la position à remplir suivant les cas
	int * piBuffer;					// stocke le resultat de le buffer des arg de la ligne
	int iBufSommet;					// stocke la valeur du sommet temporairement 
	unsigned int uiPositionDepart;	// stocke la position de depart dans l'arc
	int iSommet;					// stocke la nom du sommet de depart d'un arc
	int iBuffer;					// stocke la postion du sommet dans la liste pc
	/* Step1 : Ouverture du flux */
	FILE *pfFile;
	fopen_s(&pfFile, cAdresse, "r");



	// Si erreur : Ouverture
	if (pfFile == NULL)
	{
		CException EXCChemin_Invalid(CHEMIN_INVALID);
		throw EXCChemin_Invalid;
	}
	else
	{
		/* Step2 : Initialisation */
		// Récupération des colonnes / lignes  / types
		while (uiLigne < NB_BALISE && fgets(pcLine, MAX_LONGUEUR_LINE, pfFile) != NULL)
		{
			/* test qui determine qui permet de passer à la ligne suivante si on a un ']' *////////////////////////
			if (FICDemarre_Avec("]", pcLine, MAX_LONGUEUR_LINE) == 1)
			{
				uiLigne++;
				
				// 4 : c'est la fin des sommets, 6 :Fin des Arcs
				if (uiLigne == 4 || uiLigne == 6) continue;
				else throw (*new CException(CROCHET_MAL_PLACE));
			}
			/* test de la balise */

			// balise invalide
			if (FICDemarre_Avec(ppcTestBaliseParametrique[uiLigne], pcLine, MAX_LONGUEUR_LINE) == 0  )
			{
				fclose(pfFile);
				CException EXCBalise_Invalid(BALISE_INVALID);
				throw EXCBalise_Invalid;
			}
			/* Les balises sont bonnes */
			else
			{
				
				switch (uiLigne)
				{
				case 0: // balise Sommet
					piBuffer = (FICRecup_Ligne_Argument(pcLine, ppcTestBaliseParametrique + uiLigne , 1));	// recupération

					if (piBuffer[0] < 0) throw(*new CException(NOT_A_VALID_DIMENSION)); // intialisation avec des valeurs negatives
					
					uiNBSommet = (unsigned int) piBuffer[0]; // stockage
					free(piBuffer);	//vidange
					
					if (uiNBSommet == 0)
					{
						throw(*new CException(GRAPH_VIDE));
					}
					// Generation des Lignes
					ppSTOFICStockage = (CStockageElement **) malloc(sizeof(void *) * uiNBSommet);

					if (ppSTOFICStockage == nullptr) throw(*new CException(MATRICE_INITIALISATION_RATE));
					
					piListeSommet = (int *) malloc(sizeof(int) * uiNBSommet);
					if (piListeSommet == nullptr) throw(*new CException(MATRICE_INITIALISATION_RATE));

					uiLigne++; // Deplacement du pointeur
					break;
				case 1: // Balise Colonne
					
					piBuffer =FICRecup_Ligne_Argument(pcLine, ppcTestBaliseParametrique + uiLigne, 1);	// recupération

					if (piBuffer[0] < 0) throw(*new CException(NOT_A_VALID_DIMENSION));

					uiNBArc = (unsigned int) piBuffer[0]; // stockage
					free(piBuffer);	//vidange

					uiLigne++;
					break;

				case 2: // Balise SOMMET[
					uiLigne++;
					break;

				case 3:	// Balise Numero qui peut se répété
					
					/* Etape 1 :Recupération de la Ligne cible dans la matrice de stockage */
					uiBufferPosition = uiFICNBSommet; // Donne la Ligne cible de la matrice ppdStockage

					// Erreur : Ligne non déclarée
					if (uiBufferPosition >= uiNBSommet) throw(  *new CException(DECLARATION_LIGNE_COLONNE_INVALID));
					

					/* Etape 2 : Recuperation de la valeur et stockage sur la première ligne*/
					piBuffer = FICRecup_Ligne_Argument(pcLine, ppcTestBaliseSommet, 1);	// recupération
					iBufSommet = piBuffer[0]; // stockage
					free(piBuffer);	//vidange
					
					/* Etape 3 : Teste de l'existance de ce sommet*/
					FICSommet_Existe_T_Il(iBufSommet, piListeSommet, uiBufferPosition) == -1?
						piListeSommet[uiBufferPosition] = iBufSommet : // stockage du nouveau sommet
						throw(*new CException(DECLARATION_DOUBLE_SOMMET));

					/* Etape 3 : Stockage */
					ppSTOFICStockage[uiBufferPosition] = new CStockageElement(iBufSommet);
					
					uiFICNBSommet++;

					break;

				case 4: // Balise ARC[
					uiLigne++;
					
					break;

				case 5: // Ligne d'ARc à stocker
					

					

					// Erreur : Ligne non déclarée
					if (uiBufferPosition >= uiNBArc) throw(*new CException(DECLARATION_LIGNE_COLONNE_INVALID));
					
					/* Etape 2 : Recuperation de la valeur et stockage sur la première ligne*/
					piBuffer = FICRecup_Ligne_Argument(pcLine, ppcTestBaliseArc, 2);	// recupération
					iBuffer = FICSommet_Existe_T_Il(piBuffer[0], piListeSommet, uiFICNBSommet);
					iSommet = piBuffer[1];

					free(piBuffer);		// vidange 

					/* Etape 3 : Teste de l'existance des sommets*/
					iBuffer > -1 && FICSommet_Existe_T_Il(iSommet, piListeSommet,uiFICNBSommet) > -1 ?
						uiPositionDepart = (unsigned int) iBuffer:
						throw(*new CException(DECLARATION_SOMMET_NEXISTE_PAS));

					/* Etape 4 : Stockage */
					ppSTOFICStockage[uiPositionDepart]->STOAjouter_Arc(iSommet);
					uiFICNBArc++;
					break;
				default:
					break;
				}

			}
				
		}
		
	}

	fclose(pfFile);
	
}

/*
 *\brief Affiche un fichier
 */
void CFichier::FICAffiche_Contenu_Fich()
{
	cout << "Il y a : "<<uiFICNBArc << " Arcs"<<endl;
	cout << "Il y a : " << uiFICNBSommet << " Sommets" << endl;

	for (unsigned int  uiPosition = 0; uiPosition < uiFICNBSommet; uiPosition++)
	{
		ppSTOFICStockage[uiPosition]->STOAfficher_Stockage();
	}
}

/*
 * \brief commportement identique à strLength() en C
 */
unsigned int CFichier::FICLongueur_De_Chaine(const char * pcChaine)
{
	unsigned int uiTaille = 0;
	
	while (pcChaine[uiTaille] != '\0')
	{
		uiTaille++;
	}
	return uiTaille;
}

void CFichier::FICEst_Un_Entier(const char * pcValeur)
{
	unsigned int uiPos = 0;
	
	
	while ( (pcValeur[uiPos] >= '0' && pcValeur[uiPos] <= '9') || (uiPos == 0 && ( pcValeur[uiPos] == '+' || pcValeur[uiPos]== '-')))
	{
		
		uiPos++;
	}

	if (pcValeur[uiPos] != '\n' &&  pcValeur[uiPos] != '\0')
	{
		CException *pEXCErreur = new CException(NOT_A_NUMBER);
		throw(*pEXCErreur);
	}
}


	
	

/*
 *\brief trouve la première occurrence de cSeparateur dans la pcLigne
 *\param[in] pcLigne Ligne à parser 
 *\param[in] cSeparateur éleemnt à chercher
 *\param[out] pointeur sur la nouvelle occurrence, sinon nullptr
 */
char * CFichier::FICTrouve_Premiere_Occurrence(char * pcLigne, char cSeparateur)
{
	int iCurseur = 0;
	while (pcLigne[iCurseur] != '\0')
	{

		if (pcLigne[iCurseur] == cSeparateur)
		{
			return pcLigne + iCurseur;
		}
		iCurseur++;
	}
	return nullptr;
}

/**
 *\brief fonction cacher pour tester les balises
 *\param[in] cPrefx	le préfix recherché
 *\param[in] cMot à comparer
 *\param[in] iLongueurPrefix Taille du prefix
 *\param[out] 1 si c'est bon 0 sinon
 */
int CFichier::FICDemarre_Avec(const char * cPrefix, const char * cMot, int iLongueurPrefix)
{	
	{
		
		int iRes = 0;
		int iPosition = 0;
		/*
		 * Etats de sorties des 3 tests du while
		 * Cas 1: On a comparé toutes les caractères du Prefix 
		 * Cas 2: le mot est trop cours 
		 * Cas 3: les caractères ne correspond pas
		 */
		while (iPosition < iLongueurPrefix && cMot[iPosition] != '\0' && cPrefix[iPosition] == cMot[iPosition])
		{
			
			iPosition++;

		}
		// Les prefix est bien le bon
		if (cPrefix[iPosition] == '\0'	)
		{
			iRes = 1;
		}
		
		return iRes;
	}
}


/**
 *\brief Rempli pcDest avec les elements de pcSrc
 *\param[in] pcSrc
 *\param[in] pcDest
 *\param[out] 1 si c'est bon 0 sinon
 */
int CFichier::FICCopie_String(char * pcSrc, char * pcDest)
{
	int iPos1 = 0;
	int res;
	// Stockage des éléments

	while (*(pcSrc + iPos1) != '\0' && iPos1 < MAX_TAILLE_ARG)	// MAX_TAILLE_ARG donne la taille max du buffer pcDest
	{
		pcDest[iPos1] = pcSrc[iPos1];			
		iPos1++;
	}

	pcSrc[iPos1] == '\0' ? res = 0  : res = 1;	// donne 1 s'il n'y a pas de problème
	pcDest[iPos1] = '\0';						// fermeture de la chaine destinataire
	return res;
}

/**
 *\brief rempli la matrice du cfichier avec une ligne d'élément
 *\param[in] pcligne ligne de départ
 *\param[in] ppcBaliseATrouver tableuax des matrices à trouver sur la ligne
 *\param[in] uiNBdeBalise Nombre de balises à trouver
 *\param[out] piResultat est le tableau des valeurs recherchées
 *\warning pcligne est deplacer sur la dernière valeur, ne pas utiliser avec des listes alloué dynamiquement, car pc ligne est modifié
 */
int * CFichier::FICRecup_Ligne_Argument(char * pcLigne, const char ** ppcBaliseATrouver, unsigned int uiNBdeBalise)
{
	/*
	 *Etape 0 : Initialisation du buffer de sortie
	 */
	int * piResultat = (int*) malloc(sizeof(int) * uiNBdeBalise);
	// Erreur : Allocation
	if (piResultat == nullptr)
	{
		throw(*new CException(ERREUR_REALLOC));
	}
	
	/*
	 *Etape 1 : Recupération
	 */
	char * pcCurseur;	// il sert à fermer la chaine pour réaliser le atoi
	unsigned int  uiNumBalise = 0;

	try
	{
		while (uiNumBalise < uiNBdeBalise)
		{
			/* Phase 1 : fermeture de chaine */
			pcCurseur = FICTrouve_Premiere_Occurrence(pcLigne, ','); // positionnement 
			if (pcCurseur != nullptr) *pcCurseur = '\0';			 // fermeture si besoin
			
			/* phase 2 : positionner le pointeur sur l'élément à convertir */
			pcLigne = FICTrouve_Premiere_Occurrence(pcLigne, '=') + 1;
			
			/* phase 3 : recup et stockage */
			
			FICEst_Un_Entier(pcLigne);
			
			piResultat[uiNumBalise] = atoi(pcLigne);

			/* phase 4 : repositionnement de pcLigne*/
			pcLigne = pcCurseur + 1;

			uiNumBalise++;
		}
	}
	catch (CException EXCErreur)
	{
		free(piResultat);
		throw(EXCErreur);
	}
	

	return piResultat;
}

/*
 *\brief son objectif c'est de trouver si iElement est dans les uiNBElement de piListe
 * -1 n'est pas la  sinon return la position
 */
int CFichier::FICSommet_Existe_T_Il(int iElement, int * piListe, unsigned int uiNBElement ) {
	unsigned int uiPosition = 0;
	int iRes = -1;

	while (uiPosition < uiNBElement && iRes == -1 )
	{
		piListe[uiPosition] == iElement ? iRes = (int) uiPosition : uiPosition++;
	}
	return iRes;
}

