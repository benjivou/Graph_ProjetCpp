#ifndef CSOMMET_H
#define CSOMMET_H
#include "CArc.h"
#include <stdlib.h>
#include "CException.h"

#define REALLOC_PROBLEME 31

class CSommet
{
private :

	//Attributs

	unsigned int uiSOMNumero;
	CArc **ppARCSOMPartant;
	CArc **ppARCSOMArrivant;
	unsigned int uiSOMTailleArrivant;
	unsigned int uiSOMTaillePartant;

public:

	//Constructeurs et destructeurs

	CSommet();
	CSommet(unsigned int uiNumero);
	CSommet(CSommet &SOMParam);
	~CSommet();

	//Méthodes

	unsigned int SOMLire_Numero() { return uiSOMNumero ; } //inline
	void SOMModifier_Numero(unsigned int uiNumero) { uiSOMNumero = uiNumero; } //inline

	CArc ** SOMLire_ArcPartant() { return ppARCSOMPartant; } //inline
	CArc ** SOMLire_ArcArrivant() { return ppARCSOMArrivant; } //inline
	unsigned int SOMLire_TailleArrivant() { return uiSOMTailleArrivant; } //inline
	unsigned int SOMLire_TaillePartant() { return uiSOMTaillePartant; } //inline

	void SOMAjouter_Arc_Entrant(CArc* pARC); // TO-DO
	void SOMAjouter_Arc_Sortant(CArc* pARC); // TO-DO
	void SOMRetirer_Arc_Entrant(unsigned int uiCible); // TO-DO
	void SOMRetirer_Arc_Sortant(unsigned int uiCible); // TO-DO

	int SOMArrivant_Existe_T_Il(unsigned int uiCible); // TO-DO
	int SOMPartant_Existe_T_Il(unsigned int uiCible); // TO-DO

	void SOMAfficher_Sommet();			// TO-DO
	CSommet & operator=(CSommet &SOMParam); // TO-CHECK
};

#endif //CSOMMET_H