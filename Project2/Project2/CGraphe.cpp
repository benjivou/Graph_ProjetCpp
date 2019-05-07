#include "CGraphe.h"

CGraphe::CGraphe()
{
}

CGraphe::CGraphe(CGraphe & GRPParam)
{
}

CGraphe::~CGraphe()
{
}

void CGraphe::GRAAfficher_Graphe()
{
}

void CGraphe::GRAAjouter_Sommet(unsigned int uiValeur)
{
}

void CGraphe::GRAModifier_Sommet(unsigned int uiAncienneValeur, unsigned int uiNouvelleValeur)
{
}

void CGraphe::GRASupprimer_Sommet(unsigned int uiValeur)
{
}

unsigned int CGraphe::GRAPresence_Sommet(unsigned int uiValeur)
{
	return 0;
}

void CGraphe::GRAAjouter_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
}

void CGraphe::GRAModifier_Arc(unsigned int uiAncienDepart, unsigned int uiAncienArrivee, unsigned int uiNouveauDepart, unsigned int uiNouvelleArrivee)
{
}

void CGraphe::GRASupprimer_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
}

unsigned int CGraphe::GRAPresence_Arc(unsigned int uiDepart, unsigned int uiArrivee)
{
	return 0;
}
