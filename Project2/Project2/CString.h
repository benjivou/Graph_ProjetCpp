#include "CException.h"
#ifndef CSTRING_H
#define CSTRING_H


#define NOT_A_NUMBER 16
#define MAX_TAILLE_ARG 20		// nombre de caractère dans 1 argument du fichier

class CString
{
public:
	static unsigned int STRLongueur_De_Chaine(const char *);
	static void STREst_Un_Entier(const char* pcValeur);
	static char* STRTrouve_Premiere_Occurrence(char * pcLigne, char cSeparateur);
	static int STRDemarre_Avec(const char* cPrefix, const char* cMot, int iLongueurPrefix);
	static int STRCopie_String(char *pcSrc, char* pcDest);
};
#endif // !CSTRING_H
