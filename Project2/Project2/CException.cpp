#include "CException.h"
#include <iostream>
using namespace std;

CException::CException()
{
}
CException::~CException()
{
}

void CException::EXCAfficher_Erreur()
{
	switch (EXCLire_Erreur())
	{
	case 11:
		cerr << "Erreur : Chemin invalid " << endl;
		break;
	case 12:
		cerr << "Erreur: mauvaise balises" << endl;
		break;
	case 13:
		cerr << "Erreur: mauvaise balises ( Type trop long )" << endl;
		break;
	case 14:
		cerr << "Erreur: Type different de double" << endl;
		break;
	case 15:
		cerr << "Erreur: Taille invalide de matrice, Corrigez le fichier" << endl;
		break;
	case 16:
		cerr << "Erreur: La Valeur n'est pas un entier naturel" << endl;
		break;
	case 17:
		cerr << "Erreur: La valeur de  NbSommet ou NBArc negatif" << endl;
		break;
	case 18:
		cerr << "Erreur: Matrice Mal déclarée" << endl;
		break;
	case 19:
		cerr << "Erreur: probleme allocation memoire" << endl;
		break;
	case 20:
		cerr << "Erreur: Syntaxe erreur : Crochet mal place" << endl;
		break;
	case 21:
		cerr << "Erreur: Declaration probleme : Sommet / Arc non declare" << endl;
		break;
	case 22:
		cerr << "Erreur: Declaration probleme : Sommet declare en double" << endl;
		break;
	case 23:
		cerr << "Erreur: Declaration probleme : Arc : le sommet n'existe pas " << endl;
		break;
	case 30:
		cerr << "Erreur: Ce sommet existe deja " << endl;
		break;
	case 31:
		cerr << "Erreur: probleme re/allocation memoire" << endl;
		break;
	case 32:
		cerr << "Erreur: probleme allocation memoire : Stockage vide" << endl;
		break;
	}
}