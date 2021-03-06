
/**
 *\brief Constructeur par d�faut il sert simplement � �viter les probl�mes de cr�ations par d�faut
 */
CFichier::CFichier()
{
	throw(CException(BALISE_INVALID));
}


/**
 *\brief d�salloue le CMatrice avant de finir 
 */
CFichier::~CFichier()
{
	if (ppSTOFICStockage != nullptr)
	{
		// d�sallouer tous les sommets 
		for (unsigned int  uiPosition = 0; uiPosition < uiFICNBSommet; uiPosition++)
		{
			delete(ppSTOFICStockage[uiPosition]);
		}
	}
	uiFICNBArc = 0;
	uiFICNBSommet = 0;
	
}


/**
 *\brief On lui passe en param�tre un chemin d'acc�s � un fichier, g�n�re une matrice avec les informations du fichier
 *\param[in] cAdresse c'est le chemin d'acc�s au fichier cible
 *\return un objet CFichier, initialis� avec CFichier() si probl�me ou vide
 * sinon c'est un Cfichier avec les bonnes valeurs
 */
CFichier::CFichier(const char * cAdresse)
{
	
	printf("%s \n", cAdresse);
	


	CString STRAction;

	unsigned int uiLigne = 0;		// donne la ligne du fichier en cours d'�tude
	char pcLine[MAX_LONGUEUR_LINE];	// ligne d'argument pour cr�er la matrice
	int* piListeSommet = nullptr;	// stocke les sommets d�ja vus

	/* Variable n�cessaire � la cr�ation de la liste*/


	unsigned int uiNBArc;			// stocke le nombre d'arc � g�n�rer
	unsigned int uiNBSommet;		// stocke le nombre de sommet � g�n�rer
	unsigned int uiBufferPosition;  // stocke la position de la position � remplir suivant les cas
	int * piBuffer;					// stocke le r�sultat du buffer des arg de la ligne
	int iBufSommet;					// stocke la valeur du sommet temporairement 
	unsigned int uiPositionDepart;	// stocke la position de d�part dans l'arc
	int iSommet;					// stocke la nom du sommet de d�part d'un arc
	int iBuffer;					// stocke la position du sommet dans la liste pc
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
		// R�cup�ration des colonnes / lignes  / types
		while (uiLigne < NB_BALISE && fgets(pcLine, MAX_LONGUEUR_LINE, pfFile) != NULL)
		{
			/* test qui d�termine, qui permet de passer � la ligne suivante si on a un ']' */
			if (STRAction.STRDemarre_Avec("]", pcLine, MAX_LONGUEUR_LINE) == 1)
			{
				uiLigne++;
				
				// 4 : c'est la fin des sommets, 6 :Fin des Arcs
				if (uiLigne == 4 || uiLigne == 6) continue;
				else throw (CException(CROCHET_MAL_PLACE));
			}
			/* test de la balise */

			// balise invalide
			if (STRAction.STRDemarre_Avec(ppcTestBaliseParametrique[uiLigne], pcLine, MAX_LONGUEUR_LINE) == 0  )
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
					piBuffer = (FICRecup_Ligne_Argument(pcLine, ppcTestBaliseParametrique + uiLigne , 1));	// r�cup�ration

					if (piBuffer[0] < 0) throw(CException(NOT_A_VALID_DIMENSION)); // intialisation avec des valeurs n�gatives
					
					uiNBSommet = (unsigned int) piBuffer[0]; // stockage
					free(piBuffer);	//vidange
					
					if (uiNBSommet == 0)
					{
						throw(CException(GRAPH_VIDE));
					}
					// G�n�ration des Lignes
					ppSTOFICStockage = (CStockageElement **) malloc(sizeof(void *) * uiNBSommet);

					if (ppSTOFICStockage == nullptr) throw(CException(MATRICE_INITIALISATION_RATE));
					
					piListeSommet = (int *) malloc(sizeof(int) * uiNBSommet);
					if (piListeSommet == nullptr) throw(CException(MATRICE_INITIALISATION_RATE));

					uiLigne++; // D�placement du pointeur
					break;
				case 1: // Balise Colonne
					
					piBuffer =FICRecup_Ligne_Argument(pcLine, ppcTestBaliseParametrique + uiLigne, 1);	// r�cup�ration

					if (piBuffer[0] < 0) throw(CException(NOT_A_VALID_DIMENSION));

					uiNBArc = (unsigned int) piBuffer[0]; // stockage
					free(piBuffer);	//vidange

					uiLigne++;
					break;

				case 2: // Balise SOMMET[
					uiLigne++;
					break;

				case 3:	// Balise Numero qui peut se r�p�t�
					
					/* Etape 1 :R�cup�ration de la Ligne cible dans la matrice de stockage */
					uiBufferPosition = uiFICNBSommet; // Donne la Ligne cible de la matrice ppdStockage

					// Erreur : Ligne non d�clar�e
					if (uiBufferPosition >= uiNBSommet) throw(  CException(DECLARATION_LIGNE_COLONNE_INVALID));
					

					/* Etape 2 : R�cup�ration de la valeur et stockage sur la premi�re ligne*/
					piBuffer = FICRecup_Ligne_Argument(pcLine, ppcTestBaliseSommet, 1);	// r�cup�ration
					iBufSommet = piBuffer[0]; // stockage
					free(piBuffer);	//vidange
					// erreur Sommet n�gatif
					if (iBufSommet < 0)
					{
						throw(CException(SOMMET_NEGATIF));
					}
					/* Etape 3 : Test de l'existence de ce sommet*/
					FICSommet_Existe_T_Il(iBufSommet, piListeSommet, uiBufferPosition) == -1?
						piListeSommet[uiBufferPosition] = iBufSommet : // stockage du nouveau sommet
						throw(CException(DECLARATION_DOUBLE_SOMMET));

					/* Etape 3 : Stockage */
					ppSTOFICStockage[uiBufferPosition] = new CStockageElement(iBufSommet);
					
					uiFICNBSommet++;

					break;

				case 4: // Balise ARC[
					uiLigne++;
					
					break;

				case 5: // Ligne d'Arc � stocker
					

					

					// Erreur : Ligne non d�clar�e
					if (uiBufferPosition >= uiNBArc) throw(CException(DECLARATION_LIGNE_COLONNE_INVALID));
					
					/* Etape 2 : R�cup�ration de la valeur et stockage sur la premi�re ligne*/
					piBuffer = FICRecup_Ligne_Argument(pcLine, ppcTestBaliseArc, 2);	// r�cup�ration
					iBuffer = FICSommet_Existe_T_Il(piBuffer[0], piListeSommet, uiFICNBSommet);
					iSommet = piBuffer[1];

					free(piBuffer);		// vidange 

					/* Etape 3 : Test de l'existence des sommets*/
					iBuffer > -1 && FICSommet_Existe_T_Il(iSommet, piListeSommet,uiFICNBSommet) > -1 ?
						uiPositionDepart = (unsigned int) iBuffer:
						throw(CException(DECLARATION_SOMMET_NEXISTE_PAS));

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

/**
 *\brief rempli la matrice du cfichier avec une ligne d'�l�ment
 *\param[in] pcligne ligne de d�part
 *\param[in] ppcBaliseATrouver tableaux des matrices � trouver sur la ligne
 *\param[in] uiNBdeBalise Nombre de balises � trouver
 *\param[out] piResultat est le tableau des valeurs recherch�es
 *\warning pcligne est d�placer sur la derni�re valeur, ne pas utiliser avec des listes allou�es dynamiquement, car pc ligne est modifi�
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
		throw(CException(ERREUR_REALLOC));
	}
	CString STRAction;// modifieur
	/*
	 *Etape 1 : R�cup�ration
	 */
	char * pcCurseur;	// il sert � fermer la chaine pour r�aliser le atoi
	unsigned int  uiNumBalise = 0;

	try
	{
		while (uiNumBalise < uiNBdeBalise)
		{
			/* Phase 1 : fermeture de chaine */
			pcCurseur = STRAction.STRTrouve_Premiere_Occurrence(pcLigne, ','); // positionnement 
			if (pcCurseur != nullptr) *pcCurseur = '\0';			 // fermeture si besoin
			
			/* phase 2 : positionner le pointeur sur l'�l�ment � convertir */
			pcLigne = STRAction.STRTrouve_Premiere_Occurrence(pcLigne, '=') + 1;
			
			/* phase 3 : recup et stockage */
			
			STRAction.STREst_Un_Entier(pcLigne);
			
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
 *\brief son objectif est de trouver si iElement est dans les uiNBElement de piListe
 * -1 n'est pas la sinon return la position
 */

 /**
  *\brief L'objectif de cette m�thode est de trouver si iElement est dans les uiNBElement de piListe
  *\param[in] iElement L'�l�ment � trouver
  *\param[in] piListe pointeur sur la liste de sommet
  *\param[in] uiNBElement est le nombre d'�l�ment dans la liste
  *\return iRes la position de l'�l�ment ou -1 si l'�l�ment n'est pas dans la liste
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

