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

	unsigned int EXCLire_Erreur() { return uiEXCErreur; }
	void EXCModifier_Erreur(unsigned int uiErreur) { uiEXCErreur = uiErreur; }
	void EXCAfficher_Erreur();
};

#endif //CEXCEPTION_H
