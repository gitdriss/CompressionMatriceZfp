#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zfp.h"
#include <fstream>

/* compress or decompress array */
static int
compress(double* array, int nx, int ny, int nz, double tolerance, int decompress)
{
  int status = 0;    /* return value: 0 = success */
  zfp_type type;     /* array scalar type */
  zfp_field* field;  /* array meta data */
  zfp_stream* zfp;   /* compressed stream */
  void* buffer;      /* storage for compressed stream */
  size_t bufsize;    /* byte size of compressed buffer */
  bitstream* stream; /* bit stream to write to or read from */
  size_t zfpsize;    /* byte size of compressed stream */
  /* allocate meta data for the 3D array a[nz][ny][nx] */
  type = zfp_type_double;
  field = zfp_field_3d(array, type, nx, ny, nz);
  
  /* allocate meta data for a compressed stream */
  zfp = zfp_stream_open(NULL);

  /* set compression mode and parameters via one of three functions */
/*  zfp_stream_set_rate(zfp, rate, type, 3, 0); */
/*  zfp_stream_set_precision(zfp, precision, type); */
  zfp_stream_set_accuracy(zfp, tolerance, type);

  /* allocate buffer for compressed data */
  bufsize = zfp_stream_maximum_size(zfp, field);
  buffer = malloc(bufsize);

  /* associate bit stream with allocated buffer */
  stream = stream_open(buffer, bufsize);
  zfp_stream_set_bit_stream(zfp, stream);
  zfp_stream_rewind(zfp);

  /* compress or decompress entire array */
  if (decompress) {
    /* read compressed stream and decompress array */
    zfpsize = fread(buffer, 1, bufsize, stdin);
    if (!zfp_decompress(zfp, field)) {
      fprintf(stderr, "decompression failed\n");
      status = 1;
    }
  }
  else {
    /* compress array and output compressed stream */
    zfpsize = zfp_compress(zfp, field);
    if (!zfpsize) {
      fprintf(stderr, "compression failed\n");
      status = 1;
    }
    else
      fwrite(buffer, 1, zfpsize, stdout);
  }

  /* clean up */
  zfp_field_free(field);
  zfp_stream_close(zfp);
  stream_close(stream);
  free(buffer); 
  /*free(array);*/	
  return status;
}


int main(int argc, char **argv){
	using namespace std;
	int taille;
	FILE * fichier = fopen("tmp.txt", "r");
	fscanf(fichier,"%d",&taille);
	fclose(fichier);
	double * t = (double *) malloc(sizeof(double)*taille);

	compress(t, taille, 1, 1, atoi(argv[1]), 1);
	ofstream f(argv[2], ios::out | ios::binary);
	//ofstream f("matrix2.raw", ios::out | ios::binary);
	for(int i = 0; i<taille;i++)
		f.write((char *) &(t[i]), sizeof(double));
	f.close();	
	return 0;
}

