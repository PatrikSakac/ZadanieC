#ifndef ZOZNAMSUVENIROV_H_
#define ZOZNAMSUVENIROV_H_
#include "DatumCas.h"

typedef struct {
	DatumCas datumVyroby;
	char* nazov;
	char* kategoria;
	char* autor;
	double cena;
	DatumCas datumPredaja;
} Suvenir;

typedef struct {
	Suvenir* suveniry;
	int pocet;
	int kapacita;
} ZoznamSuvenirov;

ZoznamSuvenirov* novyZoznam();

void freeZoznam(ZoznamSuvenirov* zoznam);

void freeSuvenir(Suvenir suvenir);

Suvenir* suvenir(DatumCas datumVyroby, char* nazov, char* kategoria, char* autor,
		double cena, DatumCas datumPredaja);

void nacitajAPridajSuvenir(ZoznamSuvenirov* zoznam);

void pridaj(ZoznamSuvenirov* zoznam,Suvenir* suvenir);

char** toStringZoznamSuvenirov(ZoznamSuvenirov* zoznam);

char* toStringSuvenir(Suvenir suvenir);

Suvenir* fromStringSuvenir(char* string);

void uloz(ZoznamSuvenirov* zoznam,char* nazovSuboru);

ZoznamSuvenirov* zoSuboru(char* nazovSuboru);

char** zoznamUmelcov(ZoznamSuvenirov* zoznam,int* pocet);

Suvenir najlacnejsiVPredaji(ZoznamSuvenirov* zoznam);

ZoznamSuvenirov* zoznamPodlaKategorie(ZoznamSuvenirov* zoznam,char* kategoria);

int inventura(ZoznamSuvenirov* zoznam,char** nazvy,int* pocty);

double predaj(ZoznamSuvenirov* zoznam,char* nazov,DatumCas datumPredaja);

int vyplata(ZoznamSuvenirov* zoznam,char** umelci,double* vyplaty,int rok,int mesiac);

int viacdodavatelskeVyrobky(ZoznamSuvenirov* zoznam,char** nazvy);

int coVyrabat(ZoznamSuvenirov* zoznam,char** nazvy,char* umelec);

Suvenir najrychlejsieVyrobenyVyrobok(ZoznamSuvenirov* zoznam,char* umelec);

int compareTo(Suvenir suvenir1,Suvenir suvenir2);

void zoradPodlaDatumuPredaja(ZoznamSuvenirov* zoznam);

#endif
