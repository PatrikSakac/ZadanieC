#include <stdio.h>
#include <stdlib.h>
#include "VypisNaKonzolu.h"

void vypisVsetkych(ZoznamSuvenirov* zoznam, char* nadpis) {
	printf("%s\n", nadpis);
	char** zoznamString = toStringZoznamSuvenirov(zoznam);
	int i;
	for (i = 0; i < zoznam->pocet; ++i) {
		printf("\t%s\n", zoznamString[i]);
	}
}
void vypisUmelcov(ZoznamSuvenirov* zoznam) {
	printf("Zoznam umelcov:\n");
	int i = 0;
	int pocet;
	char** umelci = zoznamUmelcov(zoznam, &pocet);
	for (i = 0; i < pocet; ++i) {
		printf("\t%s", umelci[i]);
	}
	printf("\n");
}
void vypisInventura(ZoznamSuvenirov* zoznam) {
	char** nazvy = malloc((zoznam->pocet + 1) * sizeof(char*));
	int* pocty = malloc((zoznam->pocet + 1) * sizeof(int));
	int i, pocet = inventura(zoznam, nazvy, pocty);
	printf("\nInventura vsetkych suvenirov: \n");
	for (i = 0; i < pocet; i++) {
		printf("\t%s\t%d\n", nazvy[i], pocty[i]);
	}
}
void vypisVyplat(ZoznamSuvenirov* zoznam, int rok, int mesiac) {
	char** umelci = malloc((zoznam->pocet + 1) * sizeof(char*));
	double* velkostVyplat = malloc((zoznam->pocet + 1) * sizeof(int));

	int i, pocet = vyplata(zoznam, umelci, velkostVyplat, rok, mesiac);
	printf("\nVyplaty v roku %d a v %d. mesiaci maju tyto umelci:\n", rok,
			mesiac);
	for (i = 0; i < pocet; i++) {
		printf("\t%s %g\n", umelci[i], velkostVyplat[i]);
	}
}
void vypisViacdodavatelskychSuvenirov(ZoznamSuvenirov* zoznam) {
	char** nazvy = malloc((zoznam->pocet + 1) * sizeof(char*));
	int i, pocet = viacdodavatelskeVyrobky(zoznam, nazvy);
	printf("\nSuveniry, ktore vyrabaju viaceri umelci:\n");
	for (i = 0; i < pocet; i++) {
		printf("\t%s\n", nazvy[i]);
	}
}
void vypisCoVyrabat(ZoznamSuvenirov* zoznam,char* umelec){
	char** nazvy = malloc((zoznam->pocet + 1) * sizeof(char*));
	int i, pocet = coVyrabat(zoznam, nazvy,umelec);
		printf("\nSuveniry, ktore su predane a bolo by dobre znova predavat:\n");
		for (i = 0; i < pocet; i++) {
			printf("\t%s\n", nazvy[i]);
		}
}
void vypisNajrychlejsieVyrobeny(ZoznamSuvenirov* zoznam,char* umelec){
	Suvenir suvenir = najrychlejsieVyrobenyVyrobok(zoznam,umelec);
	printf("\nUmelec: %s najrychlejsie vyrobil:\n\t%s",umelec,toStringSuvenir(suvenir));
}

void vypisZoradPodlaDatumuPredaja(ZoznamSuvenirov* zoznam){
	zoradPodlaDatumuPredaja(zoznam);
	vypisVsetkych(zoznam,"\n\nVypis vsetkych suvenirov zotriedenych podla datumu predaja:");
}
