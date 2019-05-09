#include "CException.h"
#include <iostream>
using namespace std;

CException::CException()
{
}
CException::~CException()
{
}

void CException::EXCAfficherErreur()
{
	switch (EXCLireErreur())
	{
	case 1:
		cerr << "Erreur : Initialisation taille matrice" << endl;
		break;

	case 2:
		cerr << "Erreur : Addition de deux matrices" << endl;
		break;

	case 3:
		cerr << "Erreur : Soustraction de deux matrices" << endl;
		break;
	case 4:
		cerr << "Erreur : Multiplication de deux matrices" << endl;
		break;

	case 5:
		cerr << "Erreur : Division par un scalaire egale a 0" << endl;
		break;
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
		cerr << "Erreur: Taille invalid de matrice, Corrigez le fichier" << endl;
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
		cerr << "Erreur: probleme allocation memeoire" << endl;
		break;
	case 20:
		cerr << "Erreur: Syntax erreur : Crochet mal place" << endl;
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
		cerr << "Erreur: probleme allocation memeoire : Stockage vide" << endl;
		break;
	}
}