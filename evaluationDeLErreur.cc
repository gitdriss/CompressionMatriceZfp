#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "param.h"
#include <fstream>
#include <iostream>

//gcc -c lecturematriceraw.c
//gcc -o lecture lecturematriceraw.o -lm



int main()
{
//ouverture fichier
	using namespace std;
	ifstream f(M1, ios::in | ios::binary);
	ifstream f2(M2, ios::in | ios::binary);
	ofstream f3(M3, ios::out | ios::binary);
	
//creation matrice
	int nx = NX;
	int ny = NY;
	int nz = NZ;
	double erreur = 0;
	double erreurMax = -1;
	double erreurMoyenne = 0;
	double a1;
	double a2;
	double a3;
	int i, j, k;
	for (k = 0; k < nz; k++){
		for (j = 0; j < ny; j++){
			for (i = 0; i < nx; i++) {
				f.read((char *) &(a1), sizeof(double));
				f2.read((char *) &(a2), sizeof(double));
				erreur = (a1*a1)-(a2*a2);
				if (erreur<0)
					erreur *= -1;
				if(erreurMax<erreur)
					erreurMax = sqrt(erreur);
				erreurMoyenne += erreur;
				/*printf("%f\t",sqrt(erreur));*/
				a3 = sqrt(erreur);
				f3.write((char *) &(a3), sizeof(double));
			}
			/*printf("\n");*/
		}
	}
	/*printf("\n");*/
	printf("Erreur Max %lf \tErreur Moyenne %lf\n",erreurMax,erreurMoyenne/(nx*ny*nz));
	printf("\n");
	f.close();
	f2.close();
	f3.close();
	return 0;
}
