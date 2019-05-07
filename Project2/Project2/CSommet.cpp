#include "CSommet.h"
#include "CArc.h"

#include<stdlib.h>

CSommet::CSommet()
{
	
}

CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	uiSOMTailleArrivant = 3;
	uiSOMTaillePartant = 3;

	ppARCArrivant = (CArc **)(malloc(sizeof(void *)*UITAILLEDEFAULT));
	ppARCPartant = (CArc **)(malloc(sizeof(void *)*UITAILLEDEFAULT));
	




}

CSommet::CSommet(CSommet & SOMParam)
{
}


CSommet::~CSommet()
{
}

CSommet & CSommet::operator=(CSommet & SOMParam)
{
	// TODO: insérer une instruction return ici
}
