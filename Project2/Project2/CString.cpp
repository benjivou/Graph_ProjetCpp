#include "CString.h"

/*
 * \brief commportement identique à strLength() en C
 */
unsigned int CString::STRLongueur_De_Chaine(const char * pcChaine)
{
	unsigned int uiTaille = 0;

	while (pcChaine[uiTaille] != '\0')
	{
		uiTaille++;
	}
	return uiTaille;
}

void CString::STREst_Un_Entier(const char * pcValeur)
{
	unsigned int uiPos = 0;


	while ((pcValeur[uiPos] >= '0' && pcValeur[uiPos] <= '9') || (uiPos == 0 && (pcValeur[uiPos] == '+' || pcValeur[uiPos] == '-')))
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
char * CString::STRTrouve_Premiere_Occurrence(char * pcLigne, char cSeparateur)
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
int CString::STRDemarre_Avec(const char * cPrefix, const char * cMot, int iLongueurPrefix)
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
		if (cPrefix[iPosition] == '\0')
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
int CString::STRCopie_String(char * pcSrc, char * pcDest)
{
	int iPos1 = 0;
	int res;
	// Stockage des éléments

	while (*(pcSrc + iPos1) != '\0' && iPos1 < MAX_TAILLE_ARG)	// MAX_TAILLE_ARG donne la taille max du buffer pcDest
	{
		pcDest[iPos1] = pcSrc[iPos1];
		iPos1++;
	}

	pcSrc[iPos1] == '\0' ? res = 0 : res = 1;	// donne 1 s'il n'y a pas de problème
	pcDest[iPos1] = '\0';						// fermeture de la chaine destinataire
	return res;
}