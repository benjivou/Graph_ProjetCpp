#ifndef CGRAPHE_H
#define CGRAPHE_H
#include "CSommet.h"
class CGraphe
{
private :
	/*Attributs*/

	CSommet ppSOMListeSommets;
	unsigned int uiNombreDeSommets;
	unsigned int uiNombreDArc;

public:

	/*Constructeurs et destructeurs*/

	CGraphe();
	CGraphe(CGraphe &GRPParam);
	~CGraphe();

	/*Méthodes*/

	void GRAAfficher_Graphe();

	void GRAAjouter_Sommet(unsigned int uiValeur);
	void GRAModifier_Sommet(unsigned int uiAncienneValeur, unsigned int uiNouvelleValeur);
	void GRASupprimer_Sommet(unsigned int uiValeur);
	unsigned int GRAPresence_Sommet(unsigned int uiValeur);

	void GRAAjouter_Arc(unsigned int uiDepart, unsigned int uiArrivee);
	void GRAModifier_Arc(unsigned int uiAncienDepart, unsigned int uiAncienArrivee, unsigned int uiNouveauDepart, unsigned int uiNouvelleArrivee);
	void GRASupprimer_Arc(unsigned int uiDepart, unsigned int uiArrivee);
	unsigned int GRAPresence_Arc(unsigned int uiDepart, unsigned int uiArrivee);

	unsigned int GRALire_NbSommet() {return uiNombreDeSommets;} //inline
	unsigned int GRALire_NbArc() { return uiNombreDArc;} //inline
};

#endif //CGRAPHE_H