#ifndef CSOMMET_H
#define CSOMMET_H
#include "CArc.h"
#include "CException.h"
#include <stdlib.h>


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

	void SOMAjouter_Arc_Arrivant(CArc* pARC); 
	void SOMAjouter_Arc_Sortant(CArc* pARC); 
	void SOMRetirer_Arc_Arrivant(unsigned int uiCible); 
	void SOMRetirer_Arc_Sortant(unsigned int uiCible); 

	int SOMArrivant_Existe_T_Il(unsigned int uiCible); 
	int SOMPartant_Existe_T_Il(unsigned int uiCible); 

	void SOMInverser_Arc();

	void SOMAfficher_Sommet();			
	CSommet & operator=(CSommet &SOMParam); 
};
#include "CSommet.cpp"
#endif //CSOMMET_H