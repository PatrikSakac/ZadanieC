CC = gcc -std=c99 -Wall

%.o: %.c %.h
	$(CC) -o $@ -c $<

all: Main.c DatumCas.o UserInterface.o VypisNaKonzolu.o ZoznamSuvenirov.o
	$(CC) Main.c DatumCas.o UserInterface.o VypisNaKonzolu.o ZoznamSuvenirov.o -o ZoznamSuvenirov
	
clean:
	rm -f *.o ZoznamSuvenirov