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
	ifstream f3(argv[3], ios::in | ios::binary);
	ifstream f4(argv[4], ios::in | ios::binary);
	ifstream f5(argv[5], ios::in | ios::binary);
	ifstream f6(argv[6], ios::in | ios::binary);
	ofstream f7(argv[7], ios::out | ios::binary);
	printf("%s %s %s %s %s %s %s\n",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);
//creation matrice

	int taille;
	FILE * fichier = fopen("tmp.txt", "r");


	fscanf(fichier,"%d",&taille);

	fclose(fichier);
	
	double erreur = 0;
	double erreurMax = -1;
	double erreurMoyenne = 0;
	double vx;
	double vx2;
	double vy,vy2,vz,vz2;

	for(int i = 0; i<taille;i++){
		f.read((char *) &(vx), sizeof(double));
		f2.read((char *) &(vx2), sizeof(double));
		f3.read((char *) &(vy), sizeof(double));
		f4.read((char *) &(vy2), sizeof(double));
		f5.read((char *) &(vz), sizeof(double));
		f6.read((char *) &(vz2), sizeof(double));
		erreur = sqrt((vx-vx2)*(vx-vx2)+(vy-vy2)*(vy-vy2)+(vz-vz2)*(vz-vz2));
			
		erreurMoyenne += erreur;

		if(erreur>erreurMax){
			erreurMax=erreur;
		}

		f7.write((char *) &(erreur), sizeof(double));
	
	}

	printf("Erreur Max %lf \tErreur Moyenne %lf\n",erreurMax,erreurMoyenne/(taille));
	printf("\n");
	f.close();
	f2.close();
	f3.close();
	f4.close();
	f5.close();
	f6.close();
	f7.close();
	return 0;
}
