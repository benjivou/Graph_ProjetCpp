#include "CFichier.h"


/**
 *\brief Constructeur par défaut il sert simplement à éviter les problèmes de créations par défaut
 */
CFichier::CFichier()
{
	ppdStockage = nullptr;
	*pcType = '\0';
}


/**
 *\brief desalloue le CMatrice avant de finir 
 */
CFichier::~CFichier()
{
	// s'il y a une CMatrice allouée dynamiquement
	if (*pcType != '\0')
	{
		delete ppdStockage;
	}
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
	unsigned int uiPosLigne;
	int iPos;						// position dns la ligne
	
	unsigned int uiLigne = 0;		// donne la ligne du fichier en cours d'étude
	char pcLine[MAX_LONGUEUR_LINE];	// ligne d'argument pour créer la matrice

	/* Variable nécessaire à la création de matrice*/
	char pcArgType[MAX_TAILLE_ARG];
	unsigned int uiColonne;
	unsigned int uiLigneM;

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
		while (uiLigne < 7 && fgets(pcLine, MAX_LONGUEUR_LINE, pfFile) != NULL)
		{
			/* test qui determine qui permet de passer à la ligne suivante si on a un ']' *////////////////////////
			///////////////////////
			///////////////
			//////////
			if (FICDemarre_Avec(ppcTestBalise[uiLigne], pcLine, MAX_LONGUEUR_LINE) == ']')
			{
				uiLigne == (4 || 6) ? continue : throw ( new CException(CROCHET_MAL_PLACE));
			}
			/* test de la balise */

			// balise invalide
			if (FICDemarre_Avec(ppcTestBalise[uiLigne], pcLine, MAX_LONGUEUR_LINE) == 0  )
			{
				fclose(pfFile);
				CException EXCBalise_Invalid(BALISE_INVALID);
				throw EXCBalise_Invalid;
			}
			/* Les balises sont bonnes */
			else
			{
				iPos = FICLongueur_De_Chaine(ppcTestBalise[uiLigne]);	// positionne le pointeur pour récupéré la valeur
				iPos--;		// repositionnement du ^pointeur sur le début de la value
				switch (uiLigne)
				{
				case 0 :
					FICEst_Un_Entier(pcLine + iPos);	// teste de la value
					uiLigneM = atoi((pcLine + iPos));
					if (uiLigneM == 0)
					{
						throw(new CException(TAILLE_MATRICE_INVALID));
					}
					// Generation des Lignes
					ppdStockage = malloc(sizeof(double *) * uiLigneM);
					if( ppdStockage == nullptr )
						throw(new CException(MATRICE_INITIALISATION_RATE));
					break;
				case 1 :
					FICEst_Un_Entier(pcLine + iPos);	// teste de la value

					uiColonne = atoi((pcLine + iPos));
					if (uiColonne == 0)
					{
						throw(new CException(TAILLE_MATRICE_INVALID));
					}
					// Generation des Colonnes
					for (unsigned int uiPos = 0; uiPos < uiColonne; uiColonne++)
					{
						ppdStockage[uiPos] = (double *)calloc(sizeof(double *) * uiColonne);
						if (ppdStockage[uiPos] == nullptr)
							throw(new CException(MATRICE_INITIALISATION_RATE));
					}
					break;

				case 3 :	// Balise Numero qui peut se répété
					FICEst_Un_Reel(pcLine + iPos);
					unsigned int uiPositionMatrice = uiLigne - 3; // Donne la Ligne cible de la matrice 
					if(uiPositionMatrice >= )
				default:
					break;
				}
				/* balise NBSommet, NBArcs*/
				if (uiLigne < 2)
				{
					FICEst_Un_Entier(pcLine + iPos);	// teste de la value
					
					uiLigne == 0 ?
						uiLigneM = atoi((pcLine + iPos)) :
						uiColonne = atoi((pcLine + iPos));

				}
				/* balise restantes*/
				else
				{
					if()
					
					/* balise NBLigne, NBColonne*/
					if (uiLigne == 1)					// Balise NBLigne
					{
						
						FICEst_Un_Entier(pcLine + iPos);
						
						
						
						
					}
					else
					{
						if (uiLigne == 2)					// Balise NBColonne
						{
							FICEst_Un_Entier(pcLine + iPos);
							
							uiColonne = atoi((pcLine + iPos));
						}
						if (uiLigneM <= 0 || uiColonne <= 0)
						{
							fclose(pfFile);
							throw(new CException(TAILLE_MATRICE_INVALID));
						}
					}
					
				}
				uiLigne++;
			}
		}

		// Création de l'objet CMatrice
		if (FICDemarre_Avec("double", pcArgType, MAX_TAILLE_ARG) == 1)
		{
			
			FICCopie_String((char*)"double",pcType);				// Sauvegarde du type 

			uiPosLigne = 0;

			ppdStockage = new double(uiLigneM, uiColonne);
			/* Step3 : Remplissage */
			// recupération de la ligne
			try {
				while (uiPosLigne < uiLigneM && fgets(pcLine, MAX_LONGUEUR_LINE, pfFile) != NULL)
				{
					// Remplissage Ligne à Ligne
					FICStocke_Ligne_Dans_Matrice(pcLine, ppdStockage, uiPosLigne);
					uiPosLigne++;
				}
			}
			catch(CException EXCErreur)
			{
				fclose(pfFile);
				std::cerr << " Fichier \n Ligne "<< NB_BALISE + uiPosLigne << " : ";
				throw(EXCErreur);
			}
		}
		// Si erreur : mauvais type
		else
		{
			fclose(pfFile);
			CException EXCTypeDifferentDeDouble(MAUVAIS_TYPE_MATRICE);
			throw EXCTypeDifferentDeDouble;
		}
	}

	fclose(pfFile);
	
}

/*
 *\brief Affiche un fichier
 */
void CFichier::FICAffiche_Contenu_Fich()
{
	printf(" \nSon type est : %s \n", pcType);
	
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
	
	while ( pcValeur[uiPos] >= '0' && pcValeur[uiPos] <= '9' )
	{
		
		uiPos++;
	}

	if (pcValeur[uiPos] != '\n' )
	{
		
		throw(new CException(NOT_A_NUMBER));
	}
}

/*
 *\brief si la chaine n'st pas un nombre throw erreur
 *\param[in] pcValeur a analyser
 */
void CFichier::FICEst_Un_Reel(const char * pcValeur)
{
	unsigned int uiPos =0;
	unsigned int uiNbDeVirgules = 0;
	unsigned int uiNbDeSignes = 0;
	while (pcValeur[uiPos] == '.' || (pcValeur[uiPos] <= '9' && pcValeur[uiPos] >= '0') || pcValeur[uiPos] == '+' || pcValeur[uiPos] == '-')
	{
		if (pcValeur[uiPos] == '+' || pcValeur[uiPos] == '-')
		{
			uiNbDeSignes++;
		}
		if (pcValeur[uiPos] == '.')
		{
			uiNbDeVirgules++;
		}
		uiPos++;
	}
	if (pcValeur[uiPos] != '\0' ||uiNbDeSignes > 1 || uiNbDeVirgules > 1)
	{
		throw(new CException(NOT_A_REEL));
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
 *\brief rempli la matrice du CFichier avec une ligne d'élément
 *\param[in] pcLigne Ligne de départ
 *\param[in] pmStockage	Matrice à remplir 
 *\param[in] uiCurrentLigne	Donne la ligne à remplir
 *\param[out] 1 si c'est bon 0 sinon
 *\warning pcLigne est deplacer sur la dernière valeur, ne pas utiliser avec des listes alloué dynamiquement, car pc Ligne est modifié
 */

int CFichier::FICStocke_Ligne_Dans_Matrice(char* pcLigne, double** ppdStockage, unsigned int uiCurrentLigne)
{
	unsigned int uiCurrentColonne = 0;
	char *pcCurrent;					// pointeur sur la derniere occurence du ' '
	pcCurrent = FICTrouve_Premiere_Occurrence(pcLigne, ' ');

	/* L'idée c'est de retrouver le prochaine espace, le remplacer par un caractère de fin de chaine. 
		Ensuite on déplace la position de pcLigne*/
	while (pcCurrent != nullptr && uiCurrentColonne != (pmStockage->MTPLire_NbColonne() - 1))
	{
		*pcCurrent = '\0';
		FICEst_Un_Reel((const char *) pcLigne);
		ppdStockage->MTPModifier_Element(uiCurrentLigne, uiCurrentColonne, atof(pcLigne));	// remplissage de la matrice
		pcLigne = pcCurrent + 1;															// déplacement le pointeur
		pcCurrent = FICTrouve_Premiere_Occurrence(pcLigne, ' ');							// Recherche de la prochaine valeur
		uiCurrentColonne++;
	}

	if (uiCurrentColonne < (pmStockage->MTPLire_NbColonne() - 1))
	{
		throw(CException(MATRICE_MAL_DECLARE));
	}
	// la dernière occurrence est volontairement différente, car il n'y a pas à repositionner pcCurrent après
	ppdStockage->MTPModifier_Element(uiCurrentLigne, uiCurrentColonne, atof(pcLigne));	// dernier élément

	return 0;
}

