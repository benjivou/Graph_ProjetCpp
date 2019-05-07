#ifndef CSOMMET_H
#define CSOMMET_H
#include "CArc.h"
#define UITAILLEDEFAULT 3

class CSommet
{
private :

	//Attributs

	unsigned int uiSOMNumero;
	CArc **ppARCPartant;
	CArc **ppARCArrivant;
	unsigned int uiSOMTailleArrivant;
	unsigned int uiSOMTaillePartant;

public:

	//Constructeurs et destructeurs

	CSommet();
	CSommet(unsigned int uiNumero);
	~CSommet();

	//Méthodes

	unsigned int SOMLire_Numero() { return uiSOMNumero ; } //inline
	void SOMModifier_Numero(unsigned int uiNumero) { uiSOMNumero = uiNumero; } //inline

	CArc ** SOMLire_ArcPartant() { return ppARCPartant; } //inline
	CArc ** SOMLire_ArcArrivant() { return ppARCArrivant; } //inline
	
};

#endif //CSOMMET_H