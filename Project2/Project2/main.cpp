// main.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
// Ex�cuter le programme : Ctrl+F5 ou menu D�boguer > Ex�cuter sans d�bogage
// D�boguer le programme : F5 ou menu D�boguer > D�marrer le d�bogage

#include "CSommet.h"

#include <iostream>
#include <stdio.h>

using namespace std;


int main()
{
	cout << "Hello World !" << endl;

	CArc *c1 = new CArc(1);
	CArc *c2 = new CArc(2);

	CSommet *sommet1 = new CSommet(1);
	CSommet *sommet2 = new CSommet(2);
	CSommet *sommet3 = new CSommet(3);
	CSommet *sommet4 = new CSommet(*sommet3);
	sommet1 = sommet3;



	/*try {
		

	}
	catch (CException EXCException) {
		EXCException.EXCAfficherErreur();
	}*/
	getchar();
	return 0;
}