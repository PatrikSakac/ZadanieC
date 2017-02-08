#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ZoznamSuvenirov.h"
#include "DatumCas.h"

#define dlzkaRiadku 42

ZoznamSuvenirov* novyZoznam() {
	ZoznamSuvenirov* zoznam = malloc(sizeof(ZoznamSuvenirov));
	zoznam->kapacita = 0;
	zoznam->pocet = 0;
	zoznam->suveniry = NULL;

	return zoznam;
}

void freeZoznam(ZoznamSuvenirov* zoznam) {
	int i;
	for (i = 0; i < zoznam->pocet; i++) {
		freeSuvenir(zoznam->suveniry[i]);
	}
	free(zoznam->suveniry);
}

void freeSuvenir(Suvenir suvenir) {
	free(suvenir.autor);
	free(suvenir.kategoria);
	free(suvenir.nazov);
}

Suvenir* suvenir(DatumCas datumVyroby, char* nazov, char* kategoria,
		char* autor, double cena, DatumCas datumPredaja) {
	Suvenir* suvenir = malloc(sizeof(Suvenir));

	char* nazovCopy = malloc((strlen(nazov) + 1) * sizeof(char));
	char* kategoriaCopy = malloc((strlen(kategoria) + 1) * sizeof(char));
	char* autorCopy = malloc((strlen(autor) + 1) * sizeof(char));

	strcpy(nazovCopy, nazov);
	strcpy(kategoriaCopy, kategoria);
	strcpy(autorCopy, autor);

	*suvenir = (Suvenir ) { .datumVyroby = datumVyroby, .nazov = nazovCopy,
					.kategoria = kategoriaCopy, .autor = autorCopy,
					.cena = cena, .datumPredaja = datumPredaja };
	return suvenir;
}

void pridaj(ZoznamSuvenirov* zoznam, Suvenir* suvenir) {
	if (suvenir == NULL || suvenir->nazov == NULL)
		return;

	if (zoznam->pocet >= zoznam->kapacita) {
		zoznam->kapacita += 10;
		zoznam->suveniry = realloc(zoznam->suveniry,
				sizeof(Suvenir) * (zoznam->kapacita + 1));
	}
	zoznam->suveniry[zoznam->pocet] = *suvenir;
	zoznam->pocet++;
}

char** toStringZoznamSuvenirov(ZoznamSuvenirov* zoznam) {
	char** string = malloc(sizeof(char*) * zoznam->pocet);

	int i = 0;
	for (i = 0; i < zoznam->pocet; i++) {
		Suvenir suvenir = zoznam->suveniry[i];
		string[i] = toStringSuvenir(suvenir);
	}
	return string;
}

char* toStringSuvenir(Suvenir suvenir) {
	char* string = malloc(sizeof(char) * 300);
	sprintf(string, "%s\t%s\t%s\t%s\t%g\t%s",
			toStringDatumCas(suvenir.datumVyroby), suvenir.nazov,
			suvenir.kategoria, suvenir.autor, suvenir.cena,
			toStringDatumCas(suvenir.datumPredaja));
	return string;
}

Suvenir* fromStringSuvenir(char* s) {
	char* string = malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(string, s);

	int i;
	Suvenir* suv = NULL;
	char** tokens = malloc(6 * sizeof(char*));
	const char* delim = "\t";

	if (string != NULL) {
		tokens[0] = strtok(string, delim);
		for (i = 1; i < 6; i++) {
			tokens[i] = strtok(NULL, delim);
			if (tokens[i] == NULL)
				return suv;
		}
		DatumCas datumVyroby = *fromStringDatumCas(tokens[0]);
		DatumCas datumPredaja = *fromStringDatumCas(tokens[5]);
		double cena = atof(tokens[4]);
		suv = suvenir(datumVyroby, tokens[1], tokens[2], tokens[3], cena,
				datumPredaja);

	}
	free(tokens);
	free(string);
	return suv;
}

void uloz(ZoznamSuvenirov* zoznam, char* nazovSuboru) {
	FILE* file = fopen(nazovSuboru, "w");
	if (file != NULL) {
		char* suvenirString = NULL;
		int i;
		for (i = 0; i < zoznam->pocet; i++) {
			suvenirString = toStringSuvenir(zoznam->suveniry[i]);
			strcat(suvenirString, "\n");
			fputs(suvenirString, file);
		}
		if (suvenirString != NULL)
			free(suvenirString);
	}

	fclose(file);
}

ZoznamSuvenirov* zoSuboru(char* nazovSuboru) {
	FILE* file = fopen(nazovSuboru, "r");
	ZoznamSuvenirov* zoznam = novyZoznam();
	if (file != NULL) {
		char* buffer;
		const char* delim = "\n";
		int velkostSuboru;

		//nastavi posledny znak 0
		fseek(file, 0, SEEK_END);
		velkostSuboru = ftell(file);

		//vrati sa na zaciatok
		rewind(file);
		buffer = (char*) malloc(sizeof(char) * (velkostSuboru + 1));
		fread(buffer, sizeof(char), velkostSuboru, file);
		buffer[velkostSuboru] = '\0';

		char** tokens = malloc(sizeof(char*));
		int i = 0;
		tokens[0] = strtok(buffer, delim);

		while (tokens[i] != NULL) {
			i++;
			tokens = realloc(tokens, (i + 1) * sizeof(char*));
			tokens[i] = strtok(NULL, delim);
		}

		int j;
		for (j = 0; j < i; j++) {
			Suvenir* suv = malloc(sizeof(Suvenir));
			suv = fromStringSuvenir(tokens[j]);
			pridaj(zoznam, suv);
		}

		free(tokens);
		free(buffer);
	}
	fclose(file);
	return zoznam;
}

char** zoznamUmelcov(ZoznamSuvenirov* zoznam, int* pocet) {
	char** umelci = malloc(sizeof(char*) * zoznam->pocet);
	int i, j, pridaj, pocetUmelcov = 0;
	for (i = 0; i < zoznam->pocet; i++) {
		pridaj = 1;
		for (j = 0; j < pocetUmelcov; j++) {
			if (strcmp(zoznam->suveniry[i].autor, umelci[j]) == 0) {
				pridaj = 0;
				break;
			}
		}
		if (pridaj) {
			char* pridavany = malloc(
					(strlen(zoznam->suveniry[i].autor) + 1) * sizeof(char));
			strcpy(pridavany, zoznam->suveniry[i].autor);
			umelci[pocetUmelcov] = pridavany;
			pocetUmelcov++;
		}
	}
	*pocet = pocetUmelcov;
	return umelci;
}

Suvenir najlacnejsiVPredaji(ZoznamSuvenirov* zoznam) {
	Suvenir* suv = suvenir(nezadane(), "neexistuje", "nepredany", "suvenir", 0,
			nezadane());
	int i;
	double najnizsiaCena = INT_MAX;
	for (i = 0; i < zoznam->pocet; i++) {
		if (isNezadane(zoznam->suveniry[i].datumPredaja)
				&& zoznam->suveniry[i].cena < najnizsiaCena) {
			suv = &zoznam->suveniry[i];
			najnizsiaCena = suv->cena;
		}
	}
	return *suv;
}

ZoznamSuvenirov* zoznamPodlaKategorie(ZoznamSuvenirov* zoznam,char* kategoria) {
	ZoznamSuvenirov* novy_zoznam = novyZoznam();
	int i;
	for (i = 0; i < zoznam->pocet; i++) {
		if (strcmp(zoznam->suveniry[i].kategoria, kategoria) == 0) {
			pridaj(novy_zoznam, &zoznam->suveniry[i]);
		}
	}

	return novy_zoznam;
}

int inventura(ZoznamSuvenirov* zoznam, char** nazvy, int* pocty) {
	int i, j, pridaj, pocetNazvov = 0;
	for (i = 0; i < zoznam->pocet; i++) {
		pridaj = 1;
		for (j = 0; j < pocetNazvov; j++) {
			if (strcmp(zoznam->suveniry[i].nazov, nazvy[j]) == 0) {
				pridaj = 0;
				pocty[j]++;
				break;
			}
		}
		if (pridaj) {
			nazvy[pocetNazvov] = zoznam->suveniry[i].nazov;
			pocty[pocetNazvov] = 1;
			pocetNazvov++;
		}
	}
	return pocetNazvov;
}

double predaj(ZoznamSuvenirov* zoznam,char* nazov,DatumCas datumPredaja) {
	double najnizsiaCena = INT_MAX;
	int i;
	Suvenir* suv = NULL;
	for (i = 0; i < zoznam->pocet; i++) {
		if (strcmp(zoznam->suveniry[i].nazov, nazov) == 0
				&& isNezadane(zoznam->suveniry[i].datumPredaja)
				&& zoznam->suveniry[i].cena < najnizsiaCena) {
			suv = &zoznam->suveniry[i];
			najnizsiaCena = suv->cena;
		}
	}

	if (suv != NULL) {
		suv->datumPredaja = datumPredaja;
		return najnizsiaCena;
	} else {
		return -1;
	}

}

int vyplata(ZoznamSuvenirov* zoznam, char** umelci, double* vyplaty, int rok,
		int mesiac) {
	int i, j, pridaj, pocetUmelcov = 0;
	for (i = 0; i < zoznam->pocet; i++) {
		if (zoznam->suveniry[i].datumPredaja.rok == rok
				&& zoznam->suveniry[i].datumPredaja.mesiac == mesiac) {
			pridaj = 1;
			for (j = 0; j < pocetUmelcov; j++) {
				if (strcmp(zoznam->suveniry[i].autor, umelci[j]) == 0) {
					pridaj = 0;
					vyplaty[j] += zoznam->suveniry[i].cena * 0.7;
					break;
				}
			}
			if (pridaj) {
				umelci[pocetUmelcov] = zoznam->suveniry[i].autor;
				vyplaty[pocetUmelcov] = zoznam->suveniry[i].cena;
				pocetUmelcov++;
			}
		}
	}

	return pocetUmelcov;
}

int viacdodavatelskeVyrobky(ZoznamSuvenirov* zoznam, char** nazvy) {
	int i, j, pocet, pridaj, pocetUmelcov = 0;
	for (i = 0; i < zoznam->pocet; i++) {
		pridaj = 1;
		for (j = 0; j < pocetUmelcov; j++) {
			if (strcmp(zoznam->suveniry[i].nazov, nazvy[j]) == 0) {
				pridaj = 0;
				break;
			}
		}
		if (pridaj) {
			pocet = 1;
			for (j = 0; j < zoznam->pocet; j++) {
				if (j == i) {
					continue;
				} else {
					if (strcmp(zoznam->suveniry[j].nazov,
							zoznam->suveniry[i].nazov) == 0
							&& strcmp(zoznam->suveniry[j].autor,
									zoznam->suveniry[i].autor) != 0) {
						pocet++;
					}
				}
			}
			if (pocet > 1) {
				nazvy[pocetUmelcov] = zoznam->suveniry[i].nazov;
				pocetUmelcov++;
			}
		}
	}

	return pocetUmelcov;
}

int coVyrabat(ZoznamSuvenirov* zoznam, char** nazvy, char* umelec) {
	int i, j, pridaj, pocetSuvenirov = 0;
	for (i = 0; i < zoznam->pocet; i++) {
		if (strcmp(zoznam->suveniry[i].autor, umelec) == 0) {
			if (!isNezadane(zoznam->suveniry[i].datumPredaja)) {
				pridaj = 1;
				for (j = 0; j < zoznam->pocet; j++) {
					if (i == j) {
						continue;
					} else {
						if (strcmp(zoznam->suveniry[j].nazov,
								zoznam->suveniry[i].nazov) == 0
								&& isNezadane(
										zoznam->suveniry[j].datumPredaja)) {
							pridaj = 0;
						}
					}
				}
				for (j = 0; j < pocetSuvenirov; j++) {
					if (strcmp(zoznam->suveniry[i].nazov, nazvy[j]) == 0) {
						pridaj = 0;
					}
				}
				if (pridaj) {
					nazvy[pocetSuvenirov] = zoznam->suveniry[i].nazov;
					pocetSuvenirov++;
				}
			}

		}
	}
	if (pocetSuvenirov < 3) {
		nazvy[pocetSuvenirov] = "nieco nove";
		pocetSuvenirov++;
	}
	return pocetSuvenirov;
}

Suvenir najrychlejsieVyrobenyVyrobok(ZoznamSuvenirov* zoznam, char* umelec) {
	Suvenir suv;
	long tmpRozdiel, najmensiRozdielCasov = LONG_MAX;
	int i, j, pridany = 0;
	for (i = 0; i < zoznam->pocet; i++) {
		if (strcmp(zoznam->suveniry[i].autor, umelec) == 0) {
			for (j = 0; j < zoznam->pocet; j++) {
				if (i == j) {
					continue;
				} else {
					if (strcmp(zoznam->suveniry[j].autor, umelec) == 0) {
						tmpRozdiel = rozdielCasov(
								zoznam->suveniry[i].datumVyroby,
								zoznam->suveniry[j].datumVyroby);
						if (tmpRozdiel > 0
								&& tmpRozdiel < najmensiRozdielCasov) {
							najmensiRozdielCasov = tmpRozdiel;
							suv = zoznam->suveniry[j];
							pridany = 1;
						}
					}
				}
			}
		}
	}
	if (pridany == 0) {
		for (i = 0; i < zoznam->pocet; i++) {
			if (strcmp(zoznam->suveniry[i].autor, umelec) == 0) {
				suv = zoznam->suveniry[i];
				break;
			}
		}
	}
	return suv;
}

int compareTo(Suvenir suvenir1, Suvenir suvenir2) {
	//vrati 1 ak je suvenir1 > suvenir2
	if (isNezadane(suvenir1.datumPredaja))
		if (isNezadane(suvenir2.datumPredaja))
			return 0;
		else
			return 1;
	else if (isNezadane(suvenir2.datumPredaja))
		return -1;

	long rozdiel = rozdielCasov(suvenir1.datumPredaja, suvenir2.datumPredaja);
	if (rozdiel > 0)
		return -1;
	else if (rozdiel < 0)
		return 1;
	else {
		rozdiel = rozdielCasov(suvenir1.datumVyroby, suvenir2.datumVyroby);
		if (rozdiel > 0)
			return -1;
		else if (rozdiel < 0)
			return 1;
		else
			return 0;
	}
}

void zoradPodlaDatumuPredaja(ZoznamSuvenirov* zoznam) {

	if (zoznam->pocet <= 1) {
		return;
	}

	// bubble sort
	int vymena = 1;
	while (vymena) {
		vymena = 0;
		int i;
		for (i = 1; i < zoznam->pocet; i++) {
			if (compareTo(zoznam->suveniry[i - 1], zoznam->suveniry[i]) == 1) {
				Suvenir tmp = zoznam->suveniry[i - 1];
				zoznam->suveniry[i - 1] = zoznam->suveniry[i];
				zoznam->suveniry[i] = tmp;
				vymena = 1;
			}
		}
	}

}
