#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "param.h"

//gcc -c lecturematriceraw.c
//gcc -o lecture lecturematriceraw.o -lm



int main()
{
//ouverture fichier
	FILE* f = fopen(M1,"rb");
	FILE* f2 = fopen(M2,"rb");
	FILE* f3 = fopen(M3,"wb+");
//creation matrice
	int nx = NX;
	int ny = NY;
	int nz = NZ;
	double erreur = 0;
	double erreurMax = -1;
	double erreurMoyenne = 0;
	double a1;
	double a2;
	int i, j, k;
	for (k = 0; k < nz; k++){
		for (j = 0; j < ny; j++){
			for (i = 0; i < nx; i++) {
				fscanf(f,"%lf",&a1);
				fscanf(f2,"%lf",&a2);
				erreur = (a1*a1)-(a2*a2);
				if (erreur<0)
					erreur *= -1;
				if(erreurMax<erreur)
					erreurMax = sqrt(erreur);
				erreurMoyenne += erreur;
				/*printf("%f\t",sqrt(erreur));*/
				fprintf(f3,"%f\t",sqrt(erreur));
			}
			/*printf("\n");*/
		}
	}
	/*printf("\n");*/
	printf("Erreur Max %lf \tErreur Moyenne %lf\n",erreurMax,erreurMoyenne/(nx*ny*nz));
	printf("\n");
	fclose(f);
	fclose(f2);
	fclose(f3);
	return 0;
}
