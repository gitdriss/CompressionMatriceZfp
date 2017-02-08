include Config

TARGETS = evaluationDeLErreur genereraw compress decompress

all: $(TARGETS)

evaluationDeLErreur: evaluationDeLErreur.cc
	$(CXX) -Wall evaluationDeLErreur.cc -o evaluationDeLErreur -lm

genereraw: genereraw.cc
	$(CXX) -Wall genereraw.cc -o genereraw -lm
	
compress: compress.cc lib/libzfp.a
	$(CXX) $(CFLAGS) compress.cc -L lib -lzfp -lm -o compress

decompress: decompress.cc lib/libzfp.a
	$(CXX) $(CFLAGS) decompress.cc -L lib -lzfp -lm -o decompress

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

	
	
