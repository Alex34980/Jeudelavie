//INSERER ICI L'ALEATOIRE

#include <iostream> // TEMP

struct preorg{// s pour la structure, t pour la taille du coté de l'axe X
	unsigned int s[];// La taille du tableau est le nombre de cellules vivantes en ordre croissant, le contenu est l'emplacement des cellules
	unsigned int t
	unsigned int x;
	char d;
};

short unsigned int voisinscellule_ile (unsigned int x, unsigned int y, unsigned int X, unsigned int Y, bool** grille){// Détermine le nombre de cellules vivantes en son voisinage en île
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
			a += grille[y-1][x-1];
		a += grille[y][x-1];
		if (haut == true)
			a += grille[y+1][x-1];}
	if (bas == true)
		a += grille[y-1][x]
	if (haut == true)
		a += grille[y+1][x]
	if (droite == true){
		if (bas == true)
			a += grille[y-1][x+1];
		a += grille[y][x-1];
		if (haut == true)
			a += grille[y+1][x+1];}
	return a;
}

short unsigned int voisinscellule_tore (unsigned int x, unsigned int y, unsigned int X, unsigned int Y, bool** grille){// Détermine le nombre de cellules vivantes en son voisinage en tore
	short unsigned int a = 0;
	for (short int i = -1; i <= 1; i++)
		for (short int ii = -1; i <= 1; ii++)
			if (i != 0 || ii != 0)
				a += grille[(y + ii)% Y][(x + i)% X];
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
	bool** grille = new bool*[Y];
	for(unsigned int i; i < Y; i++)
		grille[i] = new bool[X];
	for(unsigned int i; i < Y; i++)
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

void chargedonnees(preorg a, unsigned short int c, bool** grille, unsigned int x, unsigned int y){	//X + + - - - - + +
	if (a.t != 0){																					//Y + - - + + - - +
		bool sy = ((c+1)/2) % 2 == 0, sx = (c / 2)% 2 == c / 4;
		unsigned int ty =(a.s[t-1] + a.x-1)/ a.x;
		if (c % 2 == 0)
			for (unsigned int i = 0; i < a.t; i++)
				grille[y + ty * !sy +(a.s[i]/a.x)*((sy * 2)- 1)][x + a.x * !sx +(a.s[i]% a.x)*((sx * 2)- 1)] = true;
		else
			for (unsigned int i = 0; i < a.t; i++)
				grille[x + a.x * !sx +(a.s[i]% a.x)*((sx * 2)- 1)][y + ty * !sy +(a.s[i]/a.x)*((sy * 2)- 1)] = true;
	}
}

// ZONE DES DONNEES

preorg DONNEES(unsigned int a){
	switch(a){
		case 1:
		return preorg{[7, 8, 19, 20], 4, 1, "Clignoteur" ()}
		case 2:
		return preorg{[6, 7, 18, 19, 40, 41, 42, 43, 48, 49, 51, 54, 56, 60, 61, 63, 65, 68, 75, 77, 80, 82, 83, 87, 92, 94, 95, 100, 101, 102, 103, 124, 125, 136, 137], 35, 12, "Horloge"}
		case 3:
		return preorg{[0, 1, 2, 3], 4, 2, "Bloc"}
		case 4:
		return preorg{[0, 1, 2, 6, 10, 12, 15, 16], 8, 4, "Hameçon (stable)"}
		case 5:
		return preorg{[12, 13, 47, 51, 82, 88, 96, 108, 109, 118, 122, 124, 125, 130, 132, 144, 145, 154, 160, 164, 165, 191, 195, 200, 201, 214, 215, 228, 229, 236, 237, 250, 251, 274, 276, 312], 34, 36, "Cannon (le + petit)"}
		case 6:
		return preorg{[0, 1, 4, 5, 7], 5, 3, "Planeur"}
		case 7:
		return preorg{[0, 3, 9, 10, 14, 16, 17, 18, 19], 9, 5, "LWSS"}
		case default:
		return preorg{[], 0, 0, "Aucune prédisposition"}
	}
}

// FIN ZONE

// ZONE TEMP

void apercuGrille(unsigned int X, unsigned int Y, bool** grille){
	if (X == 0 || Y == 0)
		std::cout << "[]" << std::endl;
	else{
		for (unsigned int i = Y; i > 0; i--){
			std::cout << "[";
			for (unsigned int ii = 0; ii < X-1; ii++)
				std::cout << grille[i][ii] << "|";
			std::cout << grille[i][ii] << "]" << std::endl;}}
}

void manuelCellule(unsigned int X, unsigned int Y, bool** grille){// Change une cellule précisement
	unsigned int x, y;
	std::cout << "Donner deux entier naturels x et y dont le max de x est " << X-1 << ", pour Y " << Y-1 << std::endl;
	std::cin >> x >> y;
	if (x < X && y < Y)
		grille[y][x] = !grille[y][x];
}

void preCellules(unsigned int X, unsigned int Y, bool** grille){
	unsigned int c, x, y, bool b = false;// b permet la boucle
	while (!b){
		std::cout << "Choisir une organisation par un entier naturel" << std::endl;
		std::cin >> c;
		preorg a = DONNEES(c);
		std::cout << "Vous avez choisi " << a.d << ". Confirmer? (Répondez par un entier naturel: 0 -> Non, le reste -> Oui)" << std::endl;
		std::cin >> b;}
		if (p.t != 0){
			unsigned int ty = (a.s[a.t - 1] + a.x)/ a.x;
			bool xy = (a.x <= X && ty <= Y), yx = (a.x > Y || ty > X);// Booléens pour savoir si ça rentre
			if (!xy && !yx)
				std::cout << "Il n'y a pas assez de place dans la grille" << std::endl;
			else if (!xy)
				chargedonnees(a,"RANDOM 1 4" * 2,grille,X / 2 - a.x / 2, Y / 2 - ty / 2);
			else id (!yx)
				chargedonnees(a,("RANDOM 1 4" * 2) - 1,grille,X / 2 - a.x / 2, Y / 2 - ty / 2);
			else
				chargedonnees(a,"RANDOM 0 7",grille,X / 2 - a.x / 2, Y / 2 - ty / 2);}
}