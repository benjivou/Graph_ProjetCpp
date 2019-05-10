// main.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
// Ex�cuter le programme : Ctrl+F5 ou menu D�boguer > Ex�cuter sans d�bogage
// D�boguer le programme : F5 ou menu D�boguer > D�marrer le d�bogage

#include "CFichier.h"
#include "CArc.h"
#include "CSommet.h"
#include <iostream>
#include <stdio.h>

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
			CFichier *buffer = new CFichier(ppcFichierTest[i]);
			buffer->FICAffiche_Contenu_Fich();
			delete(buffer);

		}
		catch (CException EXCe)
		{
			EXCe.EXCAfficherErreur();
		}
		

	}
	// Test Arc
	CArc *c1 = new CArc(1);
	CArc *c2 = new CArc(2);

	//Test CSommet
	CSommet *sommet1 = new CSommet(1);
	CSommet *sommet2 = new CSommet(2);
	CSommet *sommet3 = new CSommet(3);
	CSommet *sommet4 = new CSommet(*sommet3);
	*sommet1 = *sommet3;

	getchar();
	return 0;
}
