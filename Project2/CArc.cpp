#include "CArc.h"


/**
 *\brief Constructeur par défaut d'un arc, on assigne 0 à la destination
 *\warning : ne peut être utilisé qu'une fois car on ne veut pas de doublon
 */
CArc::CArc()
{
	uiARCDestination = 0;
}

/**
 *\brief Constructeur de confort d'un arc, on assigne une destination à la destination de l'objet
 */
CArc::CArc(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}

/**
 *\brief Destructeur par défaut d'un arc
 */
CArc::~CArc()
{
	//Ne fais rien
}


