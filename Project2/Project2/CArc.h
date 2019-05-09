#ifndef CARC_H
#define CARC_H

#include <stdlib.h>
#include <iostream>

using namespace std;
class CArc
{
private :

	/*Attributs*/

	unsigned int uiARCDestination;

public:

	/*Constructeurs et destructeurs*/

	CArc();
	CArc(unsigned int uiDestination );
	~CArc();

	/*Méthodes*/

	unsigned int ARCLire_Destination() { return uiARCDestination; } //inline
	void ARCModifier_Destination(unsigned int uiDestination) { uiARCDestination = uiDestination; } //inline
	
};

#endif //CARC_H