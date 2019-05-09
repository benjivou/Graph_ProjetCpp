#ifndef CGRAPHE_H
#define CGRAPHE_H
#include "CSommet.h"
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
	~CGraphe();

	/*Méthodes*/

	void GRAAfficher_Graphe();

	void GRAAjouter_Sommet(unsigned int uiValeur);
	void GRAModifier_Sommet(CSommet sommet, unsigned int uiNouvelleValeur);
	void GRASupprimer_Sommet(CSommet sommet);
	unsigned int GRAPresence_Sommet(unsigned int uiValeur);

	void GRAAjouter_Arc(unsigned int uiDepart, unsigned int uiArrivee);
	void GRAModifier_Arc(unsigned int uiAncienDepart, unsigned int uiAncienArrivee, unsigned int uiNouveauDepart, unsigned int uiNouvelleArrivee);
	void GRASupprimer_Arc(unsigned int uiDepart, unsigned int uiArrivee);
	unsigned int GRAPresence_Arc(unsigned int uiDepart, unsigned int uiArrivee);

	unsigned int GRALire_NbSommet() {return uiGRANombreDeSommets;} //inline
	unsigned int GRALire_NbArc() { return uiGRANombreDArc;} //inline
};

#endif //CGRAPHE_H