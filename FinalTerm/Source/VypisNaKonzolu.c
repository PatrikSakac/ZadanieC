#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VypisNaKonzolu.h"

#define dlzkaRiadku 42

void vypisVsetkych(ZoznamSuvenirov* zoznam, char* nadpis) {
	printf("%s\n", nadpis);
	char** zoznamString = toStringZoznamSuvenirov(zoznam);
	int i;
	for (i = 0; i < zoznam->pocet; ++i) {
		printf("\t%s\n", zoznamString[i]);
	}
	for (i = 0; i < zoznam->pocet; ++i) {
		free(zoznamString[i]);
	}
	free(zoznamString);
}

void nacitajAPridajSuvenir(ZoznamSuvenirov* zoznam) {
	Suvenir* suv;
	const char* delim = "\n";

	getchar();

	printf("datum vyroby (rok-mesiac-den-hodina-minuta): ");
	char* datumVyroby = malloc(sizeof(char) * dlzkaRiadku);
	fgets(datumVyroby, dlzkaRiadku, stdin);
	datumVyroby = strtok(datumVyroby, delim);

	printf("nazov: ");
	char* nazov = malloc(sizeof(char) * dlzkaRiadku);
	fgets(nazov, dlzkaRiadku, stdin);
	nazov = strtok(nazov, delim);

	printf("autor: ");
	char* autor = malloc(sizeof(char) * dlzkaRiadku);
	fgets(autor, dlzkaRiadku, stdin);
	autor = strtok(autor, delim);

	printf("kategoria: ");
	char* kategoria = malloc(sizeof(char) * dlzkaRiadku);
	fgets(kategoria, dlzkaRiadku, stdin);
	kategoria = strtok(kategoria, delim);

	printf("cena: ");
	double cena;
	scanf("%lf", &cena);

	getchar();

	printf("datum predaja (rok-mesiac-den-hodina-minuta): ");
	char* datumPredaja = malloc(sizeof(char) * dlzkaRiadku);
	fgets(datumPredaja, dlzkaRiadku, stdin);
	datumPredaja = strtok(datumPredaja, delim);

	suv = suvenir(*fromStringDatumCas(datumVyroby), nazov, kategoria, autor,
			cena, *fromStringDatumCas(datumPredaja));
	free(datumVyroby);
	free(nazov);
	free(kategoria);
	free(autor);
	free(datumPredaja);

	pridaj(zoznam, suv);

}

void vypisUmelcov(ZoznamSuvenirov* zoznam) {
	printf("Zoznam umelcov:\n");
	int i = 0;
	int pocet = 0;
	char** umelci = zoznamUmelcov(zoznam, &pocet);
	for (i = 0; i < pocet; i++) {
		printf("\t%s", umelci[i]);
	}
	for (i = 0; i < pocet; i++) {
		free(umelci[i]);
	}
	free(umelci);
	printf("\n");
}

void vypisNajlacnejsiVPredaji(ZoznamSuvenirov* zoznam) {
	Suvenir najlacnejsiSuvenir = najlacnejsiVPredaji(zoznam);
	char* stringNajlacnejsi = toStringSuvenir(najlacnejsiSuvenir);
	printf("Najlacnejsi v predaji je:\n\t %s\n", stringNajlacnejsi);
	free(stringNajlacnejsi);
}

void vypisPodlaKategorie(ZoznamSuvenirov* zoznam) {
	char* kategoria = malloc(sizeof(char) * dlzkaRiadku);
	printf("kategoria: ");

	getchar();
	fgets(kategoria, dlzkaRiadku, stdin);
	kategoria = strtok(kategoria, "\n");

	ZoznamSuvenirov* zoznamKategoria = zoznamPodlaKategorie(zoznam, kategoria);
	vypisVsetkych(zoznamKategoria, "Zoznam podla kategorie:");
	free(kategoria);
}

void vypisPredaj(ZoznamSuvenirov* zoznam) {
	char* nazov = malloc(dlzkaRiadku * sizeof(char));
	getchar();

	printf("nazov: ");
	fgets(nazov, dlzkaRiadku, stdin);
	nazov = strtok(nazov, "\n");

	char* datumPredaja = malloc(sizeof(char) * dlzkaRiadku);
	printf("datum predaja: ");
	fgets(datumPredaja, dlzkaRiadku, stdin);
	datumPredaja = strtok(datumPredaja, "\n");
	DatumCas datum = *fromStringDatumCas(datumPredaja);

	double cena = predaj(zoznam, nazov, datum);
	if (cena == -1) {
		printf("Suvenir s nazvom %s nie je v zozname\n", nazov);
	} else {
		printf("Predal sa suvenir s nazvom: %s a cenou: %g\n", nazov, cena);
	}
	free(nazov);
	free(datumPredaja);
}

void vypisInventura(ZoznamSuvenirov* zoznam) {
	char** nazvy = malloc((zoznam->pocet + 1) * sizeof(char*));
	int* pocty = malloc((zoznam->pocet + 1) * sizeof(int));
	int i, pocet = inventura(zoznam, nazvy, pocty);
	printf("\nInventura vsetkych suvenirov: \n");
	for (i = 0; i < pocet; i++) {
		printf("\t%s\t%d\n", nazvy[i], pocty[i]);
	}
	free(nazvy);
	free(pocty);
}

void vypisVyplat(ZoznamSuvenirov* zoznam) {
	char** umelci = malloc((zoznam->pocet + 1) * sizeof(char*));
	double* velkostVyplat = malloc((zoznam->pocet + 1) * sizeof(int));
	int rok, mesiac;
	printf("rok: ");
	scanf("%d", &rok);

	printf("mesiac:");
	scanf("%d", &mesiac);

	int i, pocet = vyplata(zoznam, umelci, velkostVyplat, rok, mesiac);
	printf("\nVyplaty v roku %d a v %d. mesiaci maju tyto umelci:\n", rok,
			mesiac);
	for (i = 0; i < pocet; i++) {
		printf("\t%s %g\n", umelci[i], velkostVyplat[i]);
	}
	free(umelci);
	free(velkostVyplat);
}

void vypisViacdodavatelskychSuvenirov(ZoznamSuvenirov* zoznam) {
	char** nazvy = malloc((zoznam->pocet + 1) * sizeof(char*));
	int i, pocet = viacdodavatelskeVyrobky(zoznam, nazvy);
	printf("\nSuveniry, ktore vyrabaju viaceri umelci:\n");
	for (i = 0; i < pocet; i++) {
		printf("\t%s\n", nazvy[i]);
	}
	free(nazvy);
}

void vypisCoVyrabat(ZoznamSuvenirov* zoznam) {
	char** nazvy = malloc((zoznam->pocet + 1) * sizeof(char*));
	char* umelec = malloc(sizeof(char) * dlzkaRiadku);
	getchar();

	printf("umelec: ");
	fgets(umelec, dlzkaRiadku, stdin);
	umelec = strtok(umelec, "\n");

	int i, pocet = coVyrabat(zoznam, nazvy, umelec);
	printf("Suveniry, ktore su predane a bolo by dobre znova predavat:\n");
	for (i = 0; i < pocet; i++) {
		printf("\t%s\n", nazvy[i]);
	}
	free(umelec);
	free(nazvy);
}

void vypisNajrychlejsieVyrobeny(ZoznamSuvenirov* zoznam) {
	char* umelec = malloc(sizeof(char) * dlzkaRiadku);
	getchar();

	printf("umelec: ");
	fgets(umelec, dlzkaRiadku, stdin);
	umelec = strtok(umelec, "\n");

	Suvenir suvenir = najrychlejsieVyrobenyVyrobok(zoznam, umelec);
	char* stringSuvenir = toStringSuvenir(suvenir);
	printf("Umelec: %s najrychlejsie vyrobil:\n\t%s\n", umelec, stringSuvenir);
	free(umelec);
	free(stringSuvenir);
}

void vypisKedyNaDovolenku(ZoznamSuvenirov* zoznam){
	getchar();
	int rok;
	printf("rok: ");
	scanf("%d",&rok);
	double trzba = kedyNaDovolenku(zoznam,rok);
	printf("\tv tomto intervale bola trzba %g\n",trzba);

}

void vypisZoradPodlaDatumuPredaja(ZoznamSuvenirov* zoznam) {
	zoradPodlaDatumuPredaja(zoznam);
	vypisVsetkych(zoznam,
			"Vypis vsetkych suvenirov zotriedenych podla datumu predaja:");
}
