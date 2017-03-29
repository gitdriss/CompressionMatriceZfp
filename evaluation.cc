#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>

//gcc -c lecturematriceraw.c
//gcc -o lecture lecturematriceraw.o -lm



int main(int argc, char **argv){
//ouverture fichier
	using namespace std;
	ifstream f(argv[1], ios::in | ios::binary);
	ifstream f2(argv[2], ios::in | ios::binary);
	ofstream f3(argv[3], ios::out | ios::binary);
	printf("%s %s %s\n",argv[1],argv[2],argv[3]);
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
