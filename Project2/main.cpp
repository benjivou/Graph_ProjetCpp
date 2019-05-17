// main.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
// Ex�cuter le programme : Ctrl+F5 ou menu D�boguer > Ex�cuter sans d�bogage
// D�boguer le programme : F5 ou menu D�boguer > D�marrer le d�bogage

#include <iostream>
#include <stdio.h>
#include "CGraphe.h"

using namespace std;

int main(int argc,char* arg[])
{
	CGraphe *pGRAbuffer;
	unsigned uiPos,uiNbArg;
	if (argc < 1)
	{
		cerr << "Pas suffisament d'arguments";
	}
	else {
		uiNbArg = (unsigned int)argc;
		for (uiPos= 1; uiPos < uiNbArg; uiPos++)
		{
			try
			{
				pGRAbuffer = new CGraphe(arg[uiPos]);
				try
				{
					pGRAbuffer->GRAAfficher_Graphe();
					cout << endl << " Inverser graph " << endl;
					pGRAbuffer->GRAInverser_Graph().GRAAfficher_Graphe();

					cout << endl << " On retire le sommet 1" << endl;
					pGRAbuffer->GRASupprimer_Sommet(1);
					pGRAbuffer->GRAAfficher_Graphe();

					cout << endl << "On ajoute un sommet 4" << endl;
					pGRAbuffer->GRAAjouter_Sommet(4);
					pGRAbuffer->GRAAfficher_Graphe();


					cout << endl << "On ajoute un arc 2->4 " << endl;
					pGRAbuffer->GRAAjouter_Arc(2, 4);
					pGRAbuffer->GRAAfficher_Graphe();

					cout << endl << "On modifie 2 par 5 " << endl;
					pGRAbuffer->GRAModifier_Sommet(2, 5);
					pGRAbuffer->GRAAfficher_Graphe();

					cout << endl << "On modifie l'arc 3 vers 4 " << endl;
					pGRAbuffer->GRAModifier_Arc(3, 4, 4, 5);
					pGRAbuffer->GRAAfficher_Graphe();
					delete(pGRAbuffer);
				}
				catch (CException e)
				{
					delete(pGRAbuffer);
					throw e;
				}

			}
			catch (CException EXCe)
			{
				EXCe.EXCAfficher_Erreur();
			}


		}
	}
	
	
	
	return 0;
}
