#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream> // TEMP

struct preorg{// s pour la structure, t pour la taille du coté de l'axe X
	unsigned int s[36];// La taille du tableau est le nombre de cellules vivantes en ordre croissant, le contenu est l'emplacement des cellules
	unsigned int t;
	unsigned int x;
	char d[23];
};

short unsigned int voisinscellule_ile (unsigned int, unsigned int, unsigned int, unsigned int, bool**);
short unsigned int voisinscellule_tore (unsigned int, unsigned int, unsigned int, unsigned int, bool**);
bool etatcellule (bool,unsigned int, unsigned int, unsigned int, unsigned int, bool**, bool);
void cellulesMortes(bool**, unsigned int, unsigned int);
bool** initialisationGrille(unsigned int, unsigned int);
void effaceGrille(bool**, unsigned int, unsigned int);
bool** generationPlusUn(bool**, unsigned int, unsigned int, bool);
void chargedonnees(preorg, unsigned short int, bool**, unsigned int, unsigned int);
preorg DONNEES(unsigned int);
void apercuCellule(bool**, unsigned int, unsigned int);
void apercuBords(unsigned int);
void apercuGrille(unsigned int, unsigned int, bool**);
void manuelCellule(unsigned int, unsigned int, bool**);
void preCellules(unsigned int, unsigned int, bool**);
bool** manuelGrille(bool*, unsigned int*, unsigned int*);

short unsigned int voisinscellule_ile (unsigned int x, unsigned int y, unsigned int X, unsigned int Y, bool** grille){// Détermine le nombre de cellules vivantes en son voisinage en île
	bool gauche = true, bas = true, droite = true, haut = true; short unsigned int a = 0;//Ces booléens servent à empêcher les erreurs de limites de grille
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
			a += grille[y+1][x-1];
	}
	if (bas == true)
		a += grille[y-1][x];
	if (haut == true)
		a += grille[y+1][x];
	if (droite == true){
		if (bas == true)
			a += grille[y-1][x+1];
		a += grille[y][x+1];
		if (haut == true)
			a += grille[y+1][x+1];
	}
	return a;
}

short unsigned int voisinscellule_tore (unsigned int x, unsigned int y, unsigned int X, unsigned int Y, bool** grille){// Détermine le nombre de cellules vivantes en son voisinage en tore
	short unsigned int a = 0;
	for (short int i = -1; i <= 1; i++)
		for (short int ii = -1; ii <= 1; ii++)
			if (i != 0 || ii != 0)
				a += grille[(y + Y + ii)% Y][(x + X + i)% X];// Ajout de X et Y pour éviter (0 - 1)
	return a;
}

bool etatcellule (bool etat,unsigned int x, unsigned int y, unsigned int X, unsigned int Y, bool** grille, bool mode_tore){// Détermine l'état de la cellule à la génération n+1
	int a;
	if (mode_tore)
		a = voisinscellule_tore(x,y,X,Y,grille);
	else
		a = voisinscellule_ile(x,y,X,Y,grille);
	if (a > 3 || a < 2)
		etat = false;
	else if (a == 3)
		etat = true;
	return etat;
}

void cellulesMortes(bool** grille, unsigned int X, unsigned int Y){
	for (unsigned int i = 0; i < Y; i++)
		for (unsigned int ii = 0; ii < X; ii++)
			grille[i][ii] = false;
}

bool** initialisationGrille(unsigned int X, unsigned int Y){// Crée une grille de taille X*Y
	bool** grille = new bool*[Y];
	for(unsigned int i = 0; i < Y; i++)
		grille[i] = new bool[X];
	for(unsigned int i = 0; i < Y; i++)
		for(unsigned int ii = 0; ii < X; ii++)
			grille[i][ii] = false;
	return grille;
}

void effaceGrille(bool** grille, unsigned int X, unsigned int Y){// Enlève la grille
	for(unsigned int i = 0; i < Y; i++)
		delete[] grille[i];
	delete[] grille;
}

bool** generationPlusUn(bool** grille1, unsigned int X, unsigned int Y, bool mode_tore){// Donne la grille à la génération n+1
	bool** grille2 = initialisationGrille(X, Y);
	for(unsigned int i = 0; i < Y; i++)
		for(unsigned int ii = 0; ii < X; ii++)
			grille2[i][ii] = etatcellule (grille1[i][ii], ii, i, X, Y, grille1, mode_tore);
	effaceGrille(grille1, X, Y);
	return grille2;
}

void chargedonnees(preorg a, unsigned short int c, bool** grille, unsigned int x, unsigned int y){	//X + + - - - - + +
	if (a.t != 0){																					//Y + - - + + - - +
		bool sy = ((c+1)/2) % 2 == 0, sx = (c / 2)% 2 == c / 4;
		unsigned int ty =(a.s[a.t - 1] + a.x - 1)/ a.x;
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
	preorg p1 = {{0, 1, 2}, 3, 1, "Clignoteur"};
	preorg p2 = {{6, 7, 18, 19, 40, 41, 42, 43, 48, 49, 51, 54, 56, 60, 61, 63, 65, 68, 75, 77, 80, 82, 83, 87, 92, 94, 95, 100, 101, 102, 103, 124, 125, 136, 137}, 35, 12, "Horloge"};
	preorg p3 = {{0, 1, 2, 3}, 4, 2, "Bloc"};
	preorg p4 = {{0, 1, 5, 9, 11, 14, 15}, 7, 4, "Hameçon (stable)"};
	preorg p5 = {{12, 13, 47, 51, 82, 88, 96, 108, 109, 118, 122, 124, 125, 130, 132, 144, 145, 154, 160, 164, 165, 191, 195, 200, 201, 214, 215, 228, 229, 236, 237, 250, 251, 274, 276, 312}, 36, 36, "Cannon (le + petit)"};
	preorg p6 = {{0, 1, 4, 5, 6}, 5, 3, "Planeur"};
	preorg p7 = {{0, 3, 9, 10, 14, 16, 17, 18, 19}, 9, 5, "LWSS"};
	preorg p0 = {{}, 0, 0, "Aucune prédisposition"};
	switch(a){
		case 1:
		return p1;
		case 2:
		return p2;
		case 3:
		return p3;
		case 4:
		return p4;
		case 5:
		return p5;
		case 6:
		return p6;
		case 7:
		return p7;
		default:
		return p0;
	}
}

// FIN ZONE

// ZONE TEMP

void apercuCellule(bool** grille, unsigned int x, unsigned int y){
	if (grille[y][x])
		std::cout << "O";
	else
		std::cout << " ";
}

void apercuBords(unsigned int t){
	for (unsigned int i = t; i > 0; i--)
		std::cout << "=";
	std::cout << std::endl;
}

void apercuGrille(unsigned int X, unsigned int Y, bool** grille){// Affiche la grille
	if (X == 0 || Y == 0)
		std::cout << "[]" << std::endl;
	else{
		unsigned int bords = (X * 2)+ 1;
		apercuBords(bords);
		for (unsigned int i = Y; i > 0; i--){
			std::cout << "|";
			for (unsigned int ii = 0; ii < X; ii++){
				apercuCellule(grille, ii, i-1);
				if (ii == X-1)
					std::cout << "|" << std::endl;
				else
					std::cout << " ";
			}
		}
		apercuBords(bords);
	}
}

void manuelCellule(unsigned int X, unsigned int Y, bool** grille){// Change une cellule précisement
	unsigned int x, y; char choix;
	apercuGrille(X, Y, grille);
	do{
		std::cout << "Donner deux entiers naturels x et y dont le max de X est " << X-1 << ", pour Y " << Y-1 << std::endl;
		std::cin >> x >> y;
		if (x < X && y < Y)
			grille[y][x] = !(grille[y][x]);
		apercuGrille(X, Y, grille);
		std::cout << "Continuer? (Envoyez 's' pour s'arrêter, sinon, on continue)" << std::endl;
		std::cin >> choix;}
	while(choix != 's');
}

void preCellules(unsigned int X, unsigned int Y, bool** grille){// L'aléatoire de l'orientation de la structure
	unsigned int c; bool b = false; preorg a;// b permet la boucle
	while (!b){
		std::cout << "Choisir une organisation par un entier naturel" << std::endl;
		std::cin >> c;
		a = DONNEES(c);
		std::cout << "Vous avez choisi " << a.d << ". Confirmer? (Répondez par: 0 -> Non, 1 -> Oui)" << std::endl;
		std::cin >> b;
	}
	if (a.t != 0){
		unsigned int ty = (a.s[a.t - 1] + a.x)/ a.x;
		bool xy = (a.x <= X && ty <= Y), yx = (a.x <= Y && ty <= X);// Booléens pour savoir si ça rentre
		if (!xy && !yx)
			std::cout << "Il n'y a pas assez de place dans la grille" << std::endl;
		else if (!xy)
			chargedonnees(a, (rand() % 4 + 1)* 2, grille, X / 2 - a.x / 2, Y / 2 - ty / 2);
		else if (!yx)
			chargedonnees(a, ((rand() % 4 + 1)* 2) - 1, grille, X / 2 - a.x / 2, Y / 2 - ty / 2);
		else
			chargedonnees(a, rand() % 8, grille, X / 2 - a.x / 2, Y / 2 - ty / 2);
		}
}

bool** manuelGrille(bool* mode_tore, unsigned int* X, unsigned int* Y){// Permet de créer une grille de n'importe quelle taille
	bool** grille;
	std::cout << "Donner deux entiers naturels X et Y pour la taille de la grille" << std::endl;
	std::cin >> *X >> *Y;
	grille = initialisationGrille(*X, *Y);
	std::cout << "Répondez par: 0 -> Mode île, 1 -> Mode tore" << std::endl;
	std::cin >> *mode_tore;
	return grille;
}
	
	
int main(){
	char choix; bool mode_tore = false; unsigned int X, Y;
	std::cout << "[]-[]-[]JEU DE LA VIE[]-[]-[]" << std::endl;
	do{
		bool** grille = manuelGrille(&mode_tore, &X, &Y);
		if (X > 0 && Y > 0){
			do{
				std::cout << "Validez: 'P' -> Prédispositions, si non -> Disposition manuelle. ('p' -> Prédispositions puis disposition manuelle)" << std::endl;
				std::cin >> choix;
				if (choix == 'p' || choix == 'P')
					preCellules(X, Y, grille);
				if (choix != 'P')
					manuelCellule(X, Y, grille);
				do{
					apercuGrille(X, Y, grille);
					std::cout << "Validez 'c' pour changer les cellules, 'f' pour effacer les cellules, 'g' pour la grille, et 'Q' pour quitter le programme; Le reste donne la grille à la génération suivante" << std::endl;
					std::cin >> choix;
					if (choix != 'c' && choix != 'f' && choix != 'g' && choix != 'Q')
						grille = generationPlusUn(grille, X, Y, mode_tore);
				}
				while (choix != 'c' && choix != 'f' && choix != 'g' && choix != 'Q');
				if (choix == 'f')
					cellulesMortes(grille, X, Y);
				}
			while (choix != 'g' && choix != 'Q');
		}
		effaceGrille(grille, X, Y);
	}
	while (choix != 'Q');
	std::cout << "Au revoir :)" << std::endl;
	return 0;
}
				
		
