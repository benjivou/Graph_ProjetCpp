
#ifndef CSTRING_H
#define CSTRING_H

#include "CException.h"
#define NOT_A_NUMBER 14
#define MAX_TAILLE_ARG 20		// nombre de caractère dans 1 argument du fichier

class CString
{
public:
	CString();
	~CString();
	unsigned int STRLongueur_De_Chaine(const char *);
	void STREst_Un_Entier(const char* pcValeur);
	char* STRTrouve_Premiere_Occurrence(char * pcLigne, char cSeparateur);
	int STRDemarre_Avec(const char* cPrefix, const char* cMot, int iLongueurPrefix);
	int STRCopie_String(char *pcSrc, char* pcDest);
};
#endif // !CSTRING_H
