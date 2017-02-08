#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "param.h"
#include <fstream>

int main()
{
//ouverture fichier
	//FILE* f = fopen(M1,"wb+");
	using namespace std;
	ofstream f(M1, ios::out | ios::binary);
//creation matrice
	int nx = NX;
	int ny = NY;
	int nz = NZ;
	int taille = nx * ny * nz;
	double array[taille];
	int i, j, k;
	for (k = 0; k < nz; k++){
		for (j = 0; j < ny; j++){
			for (i = 0; i < nx; i++) {
				double x = 2.0 * i / nx;
				double y = 2.0 * j / ny;
				double z = 2.0 * k / nz;
				array[i + nx * (j + ny * k)] = exp(-(x * x + y * y + z * z));
				printf("%f\t",array[i + nx * (j + ny * k)]);
				//fprintf(f,"%f\t",array[i + nx * (j + ny * k)]);
				f.write((char *) &(array[i + nx * (j + ny * k)]), sizeof(double));
			}
			//printf("\n");
		}
	}
	//fclose(f);
	f.close();
	return 0;
}
