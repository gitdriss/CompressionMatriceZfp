#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "param.h"

int main()
{
//ouverture fichier
	FILE* f = fopen(M1,"wb+");
//creation matrice
	int nx = NX;
	int ny = NY;
	int nz = NZ;
	int taille = nx * ny * nz * sizeof(double);
	double* array = malloc(taille);
	int i, j, k;
	for (k = 0; k < nz; k++){
		for (j = 0; j < ny; j++){
			for (i = 0; i < nx; i++) {
				double x = 2.0 * i / nx;
				double y = 2.0 * j / ny;
				double z = 2.0 * k / nz;
				array[i + nx * (j + ny * k)] = exp(-(x * x + y * y + z * z));
				/*printf("%f\t",array[i + nx * (j + ny * k)]);*/
				fprintf(f,"%f\t",array[i + nx * (j + ny * k)]);
			}
			/*printf("\n");*/
		}
	}
	fclose(f);
	return 0;
}
