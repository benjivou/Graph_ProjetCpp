#include "CSommet.h"


CSommet::CSommet()
{
	uiSOMNumero = 0;
	uiSOMTailleArrivant = 0;
	uiSOMTaillePartant = 0;

	ppARCSOMArrivant = (CArc **)(malloc(sizeof(CArc *)));
	ppARCSOMPartant = (CArc **)(malloc(sizeof(CArc *)));

	ppARCSOMArrivant[0] = (CArc*)malloc(sizeof(CArc)*(UITAILLEDEFAULT + 1));
	ppARCSOMPartant[0] = (CArc*)malloc(sizeof(CArc)*(UITAILLEDEFAULT + 1));
	
}

CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	uiSOMTailleArrivant = UITAILLEDEFAULT;
	uiSOMTaillePartant = UITAILLEDEFAULT;

	ppARCSOMArrivant = (CArc **)(malloc(sizeof(CArc *)));
	ppARCSOMPartant = (CArc **)(malloc(sizeof(CArc *)));

	ppARCSOMArrivant[0] =(CArc*) malloc(sizeof(CArc)* (uiSOMTailleArrivant+1));
	ppARCSOMPartant[0] = (CArc*)malloc(sizeof(CArc)*(uiSOMTaillePartant+1));

}

CSommet::CSommet(CSommet & SOMParam)
{
	uiSOMNumero = SOMParam.uiSOMNumero;
	uiSOMTailleArrivant = SOMParam.uiSOMTailleArrivant;
	uiSOMTaillePartant = SOMParam.uiSOMTaillePartant;

	if (SOMParam.ppARCSOMArrivant != nullptr)
	{
		ppARCSOMArrivant = (CArc **)(malloc(sizeof(CArc *)));
		ppARCSOMArrivant[0] = (CArc*)malloc(sizeof(CArc)*(uiSOMTailleArrivant+1));

		for (unsigned int uiBoucle = 0; uiBoucle < uiSOMTailleArrivant; uiBoucle++)
		{
			ppARCSOMArrivant[0][uiBoucle] = SOMParam.ppARCSOMArrivant[0][uiBoucle];
		}
	}
	else { SOMParam.ppARCSOMArrivant = nullptr; }

	if (SOMParam.ppARCSOMPartant != nullptr)
	{
		ppARCSOMPartant = (CArc **)(malloc(sizeof(CArc *)));
		ppARCSOMPartant[0] = (CArc*)malloc(sizeof(CArc)*(uiSOMTaillePartant+1));

		for (unsigned int uiBoucle1 = 0; uiBoucle1 < uiSOMTailleArrivant; uiBoucle1++)
		{
			ppARCSOMPartant[0][uiBoucle1] = SOMParam.ppARCSOMPartant[0][uiBoucle1];
		}
	}
	else { SOMParam.ppARCSOMPartant = nullptr; }
	cout << "numero"<< uiSOMNumero << endl;
	
}


CSommet::~CSommet()
{
	free (ppARCSOMArrivant[0]);
	free (ppARCSOMArrivant);

	free(ppARCSOMPartant[0]);
	free(ppARCSOMPartant);
}

CSommet & CSommet::operator=(CSommet & SOMParam)
{
	uiSOMNumero = SOMParam.uiSOMNumero;
	uiSOMTailleArrivant = SOMParam.uiSOMTailleArrivant;
	uiSOMTaillePartant = SOMParam.uiSOMTaillePartant;

	

	if (SOMParam.ppARCSOMArrivant != nullptr)
	{
		ppARCSOMArrivant = (CArc **)(malloc(sizeof(CArc *)));
		ppARCSOMArrivant[0] = (CArc*)malloc(sizeof(CArc)*(uiSOMTailleArrivant+1));

		for (unsigned int uiBoucle = 0; uiBoucle < uiSOMTailleArrivant; uiBoucle++)
		{
			ppARCSOMArrivant[0][uiBoucle] = SOMParam.ppARCSOMArrivant[0][uiBoucle];
		}
	}
	else { SOMParam.ppARCSOMArrivant = nullptr; }

	if (SOMParam.ppARCSOMPartant != nullptr)
	{
		ppARCSOMPartant = (CArc **)(malloc(sizeof(CArc *)));
		ppARCSOMPartant[0] = (CArc*)malloc(sizeof(CArc)*(uiSOMTaillePartant+1));

		for (unsigned int uiBoucle1 = 0; uiBoucle1 < uiSOMTailleArrivant; uiBoucle1++)
		{
			ppARCSOMPartant[0][uiBoucle1] = SOMParam.ppARCSOMPartant[0][uiBoucle1];
		}
	}
	else { SOMParam.ppARCSOMPartant = nullptr; }

	cout << "numero" << uiSOMNumero << endl;

	return *this;
}
