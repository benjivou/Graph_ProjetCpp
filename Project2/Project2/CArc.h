#ifndef CARC_H
#define CARC_H
class CArc
{
private :

	//Attributs

	unsigned int uiARCDestination;

public:

	//Constructeurs et destructeurs

	CArc();
	CArc(unsigned int uiDestination );
	CArc(unsigned int uiSource, unsigned int uiDestination);
	~CArc();

	//Méthodes

	unsigned int ARCLire_Destination() { return uiARCDestination; } //inline
	void ARCModifier_Destination(unsigned int uiDestination) { uiARCDestination = uiDestination; } //inline
	void ARCSupprimer_Arc(unsigned int uiSource, unsigned int uiDestination);
};

#endif //CARC_H