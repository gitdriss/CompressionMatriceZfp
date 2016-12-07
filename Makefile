include Config

TARGETS = evaluationDeLErreur genereraw compress decompress

all: $(TARGETS)

evaluationDeLErreur: evaluationDeLErreur.c
	$(CC) -Wall evaluationDeLErreur.c -o evaluationDeLErreur -lm

genereraw: genereraw.c
	$(CC) -Wall genereraw.c -o genereraw -lm
	
compress: compress.c lib/libzfp.a
	$(CC) $(CFLAGS) compress.c -L lib -lzfp -lm -o compress

decompress: decompress.c lib/libzfp.a
	$(CC) $(CFLAGS) decompress.c -L lib -lzfp -lm -o decompress

clean:
	rm -f $(TARGETS) fields.o
	rm -f compressed.zfp
	rm -f *.raw
	
run:
	./genereraw
	./compress > compressed.zfp
	./decompress < compressed.zfp
	./evaluationDeLErreur
	
reset: clean all

	
	
