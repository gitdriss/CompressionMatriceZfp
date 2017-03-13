#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>

//gcc -c lecturematriceraw.c
//gcc -o lecture lecturematriceraw.o -lm



int main()
{
//ouverture fichier
	using namespace std;
	ifstream f("matrix.raw", ios::in | ios::binary);
	ifstream f2("matrix2.raw", ios::in | ios::binary);
	ofstream f3("matrix3.raw", ios::out | ios::binary);
	
//creation matrice

	int taille;
	FILE * fichier = fopen("tmp.txt", "r");
	fscanf(fichier,"%d",&taille);
	fclose(fichier);
	
	double erreur = 0;
	double erreurMax = -1;
	double erreurMoyenne = 0;
	double a1;
	double a2;


	for(int i = 0; i<taille;i++){
		f.read((char *) &(a1), sizeof(double));
		f2.read((char *) &(a2), sizeof(double));
		erreur = (a1-a2);
		if (erreur<0)
			erreur *= -1;
		if(erreurMax<erreur)
			erreurMax = erreur;
			
		erreurMoyenne += erreur;

		f3.write((char *) &(erreur), sizeof(double));
	
	}

	printf("Erreur Max %lf \tErreur Moyenne %lf\n",erreurMax,erreurMoyenne/(taille));
	printf("\n");
	f.close();
	f2.close();
	f3.close();
	return 0;
}
