#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "UserInterface.h"

#include "DatumCas.h"
#include "ZoznamSuvenirov.h"
#include "VypisNaKonzolu.h"

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	zobrazMoznosti();

	vyberMoznosti();

	/*Suvenir* prvy = suvenir(*fromStringDatumCas("2008-12-5-4-29"), "Kamen modry",
			"stare", "Jozo", 2.69, *fromStringDatumCas("2012-7-19-10-44"));
	Suvenir* druhy = suvenir(*fromStringDatumCas("2010-11-30-12-25"),
			"Kamen cerveny", "nove", "Jozo", 2.49, nezadane());
	Suvenir* treti = suvenir(*fromStringDatumCas("2012-1-20-8-0"),
			"Malovanky farebne", "nove", "Dano", 0.99,
			*fromStringDatumCas("2013-2-18-10-0"));
	Suvenir* stvrti = suvenir(*fromStringDatumCas("2012-1-20-10-0"),
			"Malovanky ciernobiele", "stare", "Dano", 0.79, nezadane());

	ZoznamSuvenirov* zoznam;
	zoznam = novyZoznam();

	pridaj(zoznam, prvy);
	pridaj(zoznam, druhy);
	pridaj(zoznam, treti);
	pridaj(zoznam, stvrti);

	uloz(zoznam, "suveniry.txt");
	zoznam = zoSuboru("suveniry.txt");

	vypisVsetkych(zoznam,"Vypis vsetkych suvenirov:");

	vypisUmelcov(zoznam);

	Suvenir najlacnejsiSuvenir = najlacnejsiVPredaji(zoznam);
	printf("\n\nNajlacnejsi v predaji je:\n\t %s",
			toStringSuvenir(najlacnejsiSuvenir));

	char* kategoria = "stare";
	ZoznamSuvenirov* zoznamKategoria = zoznamPodlaKategorie(zoznam, kategoria);
	vypisVsetkych(zoznamKategoria,"\n\nZoznam podla kategorie:");

	vypisInventura(zoznam);

	char* predavanyNazov = "Kamen cerveny";

	double cena = predaj(zoznam, predavanyNazov, *fromStringDatumCas("2015-9-9-9-9"));
	printf("\nPredava sa suvenir s nazvom: %s a cenou: %g", predavanyNazov,cena);
	vypisVsetkych(zoznam,"\nKontrolny vypis vsetkych:");

	vypisVyplat(zoznam,2015,9);
	vypisViacdodavatelskychSuvenirov(zoznam);
	vypisCoVyrabat(zoznam,"Dano");

	vypisNajrychlejsieVyrobeny(zoznam,"Jozo");

	vypisZoradPodlaDatumuPredaja(zoznam);*/

	return EXIT_SUCCESS;
}



