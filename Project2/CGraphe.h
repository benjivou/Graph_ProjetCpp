#ifndef CGRAPHE_H
#define CGRAPHE_H
#include "CSommet.h"
#include "CFichier.h"

#define ARC_INEXISTANT 33
#define CIBLE_INEXISTANTE 33
#define SOMMET_NEGATIF 34
#define INVALID_NEW_OR_ANCIEN_NUM 35

class CGraphe
{
private :
	/*Attributs*/

	CSommet **ppSOMGRAListeSommets;
	unsigned int uiGRANombreDeSommets;
	unsigned int uiGRANombreDArc;

public:

	/*Constructeurs et destructeurs*/

	CGraphe();
	CGraphe(CGraphe &GRPParam);
	CGraphe(const char *);
	~CGraphe();

	/*Méthodes*/

	void GRAAfficher_Graphe();

	void GRAAjouter_Sommet(unsigned int uiValeur);
	void GRAModifier_Sommet(unsigned int uiAncienneValeur, unsigned int uiNouvelleValeur);
	void GRASupprimer_Sommet(unsigned int uiAncienneValeur);
	int GRAPresence_Sommet(unsigned int uiValeur); // valeur  -1 n'existe pas sinon existe

	void GRAAjouter_Arc(unsigned int uiDepart, unsigned int uiArrivee);
	void GRAModifier_Arc(unsigned int uiAncienDepart, unsigned int uiAncienArrivee, unsigned int uiNouveauDepart, unsigned int uiNouvelleArrivee);
	void GRASupprimer_Arc(unsigned int uiDepart, unsigned int uiArrivee);
	int GRAPresence_Arc(unsigned int uiDepart, unsigned int uiArrivee);

	unsigned int GRALire_NbSommet() {return uiGRANombreDeSommets;} //inline
	unsigned int GRALire_NbArc() { return uiGRANombreDArc;} //inline
	
	CGraphe & GRAInverser_Graph();
};
#include "CGraphe.cpp"
#endif //CGRAPHE_H