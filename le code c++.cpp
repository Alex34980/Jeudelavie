#include <iostream> // TEMP

short unsigned int voisinscellule (unsigned int x, unsigned int y, unsigned int X, unsigned int Y, bool** grille){// Détermine le nombre de cellules vivantes en son voisinage
	bool gauche = true, bas = true, droite = true, haut = true; short unsigned int a = 0;//Ces booléens servent à empécher les erreurs de limites de grille
	if (x == 0)
		gauche = false;
	if (y == 0)
		bas = false;
	if (x == X-1)
		droite = false;
	if (y == Y-1)
		haut = false;
	if (gauche == true){
		if (bas == true)
			a += grille[x-1][y-1];
		a += grille[x-1][y];
		if (haut == true)
			a += grille[x-1][y+1];}
	if (bas == true)
		a += grille[x][y-1]
	if (haut == true)
		a += grille[x][y+1]
	if (droite == true){
		if (bas == true)
			a += grille[x+1][y-1];
		a += grille[x-1][y];
		if (haut == true)
			a += grille[x+1][y+1];}
	return a;
}

bool etatcellule (bool etat,unsigned int x, unsigned int y, unsigned int X, unsigned int Y, int** grille){// Détermine l'état de la cellule à la génération n+1
	int a = voisinscellule(x,y,X,Y,grille);
	if (a < 4 || a > 3)
		etatcellule = false;
	else if (a == 4)
		etatcellule = true;
	return a;
}

bool** initialisationGrille(unsigned int X, unsigned int Y){// Crée une grille de taille X*Y
	bool** grille = new bool*[X];
	for(unsigned int i; i < X; i++)
		grille[i] = new bool[Y];
	for(unsigned int i; i < X; i++)
		for(unsigned int ii; ii < X; ii++)
			grille[i][ii] = false;
	return grille;
}

void effaceGrille(bool** grille, unsigned int X, unsigned int Y){// Enlève la grille
	for(unsigned int i; i < X; i++)
		delete[] grille[i];
	delete[] grille;
}

void generationPlusUn(bool** grille, unsigned int X, unsigned int Y){// Donne la grille à la génération n+1
	for(unsigned int i; i < X; i++)
		for(unsigned int ii; ii < X; ii++)
			grille[i][ii] = etatcellule (grille[i][ii], i, ii, X, Y, grille)
}

