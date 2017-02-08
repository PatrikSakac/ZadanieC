#include <stdio.h>
#include <stdlib.h>
#include "VypisNaKonzolu.h"

#define nazovSuboru "suveniry.txt"

static const char* moznosti[] = { "Ukoncit program", "Zobraz moznosti",
		"Vypis vsetkych suvenirov", "Pridaj suvenir", "Vypis Umelcov",
		"Najlacnejsi suvenir v predaji", "Vypis zoznamu podla kategorie",
		"Inventura", "Predat suvenir", "Vypis vyplat",
		"Vypis viacdodavatelskych suvenirov", "Co vyrabat",
		"Najrychlejsie vyrobeny", "Zorad podla datumu predaja" };

static const int pocetMoznosti = sizeof moznosti / sizeof moznosti[0];

void zobrazMoznosti() {
	int i;
	for (i = 0; i < pocetMoznosti; i++)
		printf(" %d. %s\n", i, moznosti[i]);

	printf("\n");

}

void vyberMoznosti() {
	while (1) {
		printf("Zadajte cislo moznosti: ");

		int cislo;
		scanf("%d", &cislo);

		ZoznamSuvenirov* zoznam = zoSuboru(nazovSuboru);

		switch (cislo) {
		case 0:
			return;
		case 1:
			zobrazMoznosti();
			break;
		case 2:
			vypisVsetkych(zoznam, "Vypis vsetkych suvenirov:");
			break;
		case 3:
			nacitajAPridajSuvenir(zoznam);
			break;
		case 4:
			vypisUmelcov(zoznam);
			break;
		case 5:
			vypisNajlacnejsiVPredaji(zoznam);
			break;
		case 6:
			vypisPodlaKategorie(zoznam);
			break;
		case 7:
			vypisInventura(zoznam);
			break;
		case 8:
			vypisPredaj(zoznam);
			break;
		case 9:
			vypisVyplat(zoznam);
			break;
		case 10:
			vypisViacdodavatelskychSuvenirov(zoznam);
			break;
		case 11:
			vypisCoVyrabat(zoznam);
			break;
		case 12:
			vypisNajrychlejsieVyrobeny(zoznam);
			break;
		case 13:
			vypisZoradPodlaDatumuPredaja(zoznam);
			break;
		}
		uloz(zoznam, nazovSuboru);
		freeZoznam(zoznam);
	}

}
