#include "CArc.h"


/**
 *\brief Constructeur par d�faut d'un arc, on assigne 0 � la destination
 *\warning : ne peut �tre utilis� qu'une fois car on ne veut pas de doublon
 */
CArc::CArc()
{
	uiARCDestination = 0;
}

/**
 *\brief Constructeur de confort d'un arc, on assigne une destination � la destination de l'objet
 */
CArc::CArc(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}

/**
 *\brief Destructeur par d�faut d'un arc
 */
CArc::~CArc()
{
	//Ne fais rien
}


