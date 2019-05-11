#ifndef CSOMMET_H
#define CSOMMET_H
#include "CArc.h"
#include<stdlib.h>

#define UITAILLEDEFAULT 0

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
	unsigned int Lire_TailleArrivant() { return uiSOMTailleArrivant; } //inline
	unsigned int Lire_TaillePartant() { return uiSOMTaillePartant; } //inline

	CSommet & operator=(CSommet &SOMParam);
};

#endif //CSOMMET_H