// main.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
// Ex�cuter le programme : Ctrl+F5 ou menu D�boguer > Ex�cuter sans d�bogage
// D�boguer le programme : F5 ou menu D�boguer > D�marrer le d�bogage

#include "CGraphe.h"

#include <iostream>
#include <stdio.h>

using namespace std;

const char * pcFicherValide = "Fichier_Valide.txt";
const char * pcFicherInvalide1 = "Fichier_NBSommet_Negatif.txt";
const char * pcFicherInvalide2 = "Fichier_Ligne_Vides.txt";
const char * pcFicherInvalide3 = "Fichier_coordonne_Doublés.txt";
const char * pcFicherInvalide4 = "Fichier_Arc_Manquant.txt";

const char  *ppcFichierTest[] = {pcFicherValide,pcFicherInvalide1 , pcFicherInvalide2 , pcFicherInvalide3 ,pcFicherInvalide4 };
int main(int argc, char *argv[])
{
	unsigned int uiNbGrapheValide = 0;
	
	if (argc > 1)
	{
		/* Etape 1 : récupération des paramètres */
		CGraphe **ppGRAEntree = (CGraphe**)malloc(sizeof(void *) * argc - 1);	// Stockage des pointeurs de Graphe en entrée
		CFichier **ppFICBuffer_CFichier = (CFichier **)malloc(sizeof(void *) * argc - 1);	// Stockage des CFichiers généré.

		try 
		{
			cout << "Hello World !" << endl;
			// test Cfichier
			for (unsigned int uiPosition_Entre = 1; uiPosition_Entre < argc; uiPosition_Entre++)
			{
				ppFICBuffer_CFichier[uiNbGrapheValide] = new CFichier(argv[uiPosition_Entre]);
				/*try
				{
					CFichier *buffer = new CFichier(ppcFichierTest[i]);
					buffer->FICAffiche_Contenu_Fich();
					delete(buffer);

				}
				catch (CException EXCErreur)
				{
					EXCErreur.EXCAfficher_Erreur();
				}*/
			}
		}
		catch (CException EXCErreur)
		{
			EXCErreur.EXCAfficher_Erreur();
			free(ppGRAEntree);
			for (unsigned int uiCurrentFicfichier = 0; uiCurrentFicfichier < uiNbGrapheValide; uiCurrentFicfichier++)
			{
				delete ppFICBuffer_CFichier[uiCurrentFicfichier];
			}
			free(ppFICBuffer_CFichier);

		}
	}
	else
	{
		cout << "Donner un fichier la prochaine fois" << endl;
	}

	getchar();
	return 0;
}
