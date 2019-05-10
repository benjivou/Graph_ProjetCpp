#ifndef CEXCEPTION_H
#define CEXCEPTION_H

class CException
{

private:
	/*Attributs*/
	unsigned int uiEXCErreur;

public:
	CException();
	CException(unsigned int uiErreur) { uiEXCErreur = uiErreur; }
	~CException();

	unsigned int EXCLireErreur() { return uiEXCErreur; }
	void EXCModifierErreur(unsigned int uiErreur) { uiEXCErreur = uiErreur; }
	void EXCAfficherErreur();
};

#endif //CEXCEPTION_H
