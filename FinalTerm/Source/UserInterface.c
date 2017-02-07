#include <stdio.h>
#include <stdlib.h>
#include "ZoznamSuvenirov.h"
#include "VypisNaKonzolu.h"

#define nazovSuboru "suveniry.txt"

static const char* moznosti[] = { "Ukoncit program", "Zobraz moznosti",
		"Vypis vsetkych suvenirov", "Pridaj suvenir", "Vypis Umelcov" };

static const int pocetMoznosti = sizeof moznosti / sizeof moznosti[0];

void zobrazMoznosti() {
	int i;
	for (i = 0; i < pocetMoznosti; i++)
		printf(" %d. %s\n", i, moznosti[i]);

	printf("\n");

}

void vyberMoznosti() {
	while (1) {
		printf("Zadajte cislo moznosti:\n");

		int cislo;
		scanf("%d",&cislo);

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
		}
		//uloz(zoznam,nazovSuboru);
		freeZoznam(zoznam);
	}

}
