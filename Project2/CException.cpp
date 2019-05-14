#include "CException.h"

/**
 *\brief Constructeur par défaut d'une exception
 */
CException::CException()
{
	//Ne fais rien
}

/**
 *\brief Destructeur par défaut d'un arc, on assigne 0 à la destination
 */
CException::~CException()
{
	//Ne fais rien
}

/**
 *\brief Fonction qui affiche une erreur selon le code erreur adéquat
 */
void CException::EXCAfficher_Erreur()
{
	switch (EXCLire_Erreur())
	{
	
	case 10:
		cerr << "Erreur : Chemin invalide " << endl;
		break;
	case 11:
		cerr << "Erreur: mauvaises balises" << endl;
		break;
	case 12:
		cerr << "Erreur: mauvaises balises ( Type trop long )" << endl;
		break;
	case 13:
		cerr << "Erreur: Graphe vide, Corrigez le fichier" << endl;
		break;
	case 14:
		cerr << "Erreur: La Valeur n'est pas un entier naturel" << endl;
		break;
	case 15:
		cerr << "Erreur: La valeur de  NbSommet ou NBArc negatif" << endl;
		break;
	case 16:
		cerr << "Erreur: Matrice Mal déclarée" << endl;
		break;
	case 17:
		cerr << "Erreur: probleme allocation memeoire" << endl;
		break;
	case 18:
		cerr << "Erreur: Syntax erreur : Crochet mal place" << endl;
		break;
	case 19:
		cerr << "Erreur: Declaration probleme : Sommet / Arc non declare" << endl;
		break;
	case 20:
		cerr << "Erreur: Declaration probleme : Sommet declare en double" << endl;
		break;
	case 21:
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
	case 33: 
		cerr << "Erreur : Arc : Arc indefinie"<< endl;
		break;
	case 34:
		cerr << "Erreur : Somme negatif" << endl;
		break;
	case 35:
		cerr << "Erreur : Modification impossible, le sommet n'existe pas et/ou le nouveau numero existe deja " << endl;
		break;
	default: 
		cerr << "Erreur : numero " << EXCLire_Erreur() <<"introuvable" << endl;
	}
}