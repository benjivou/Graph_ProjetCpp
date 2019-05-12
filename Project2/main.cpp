// main.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
// Ex�cuter le programme : Ctrl+F5 ou menu D�boguer > Ex�cuter sans d�bogage
// D�boguer le programme : F5 ou menu D�boguer > D�marrer le d�bogage

#include <iostream>
#include <stdio.h>
#include "CGraphe.h"


using namespace std;

const char * pcFicherValide = "Fichier_Valide.txt";
const char * pcFicherInvalide1 = "Fichier_NBSommet_Negatif.txt";
const char * pcFicherInvalide2 = "Fichier_Ligne_Vides.txt";
const char * pcFicherInvalide3 = "Fichier_coordonne_Doublés.txt";
const char * pcFicherInvalide4 = "Fichier_Arc_Manquant.txt";

const char  *ppcFichierTest[] = {pcFicherValide,pcFicherInvalide1 , pcFicherInvalide2 , pcFicherInvalide3 ,pcFicherInvalide4 };
int main()
{
	cout << "Hello World !" << endl;
	// test Cfichier
	for (size_t i = 0; i < 5; i++)
	{
		try
		{
			CGraphe *buffer = new CGraphe(ppcFichierTest[i]);
			buffer->GRAAfficher_Graphe();
			buffer->GRAInverser_Graph().GRAAfficher_Graphe();
			delete(buffer);

		}
		catch (CException EXCe)
		{
			EXCe.EXCAfficherErreur();
		}
		

	}
	
	getchar();
	return 0;
}
