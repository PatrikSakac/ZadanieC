#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DatumCas.h"


DatumCas* fromStringDatumCas(char* s) {
	char* string = malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(string, s);

	DatumCas* datumCas = malloc(sizeof(DatumCas));

	const char* delim = "-";

	if (string != NULL) {

		char* token = strtok(string, delim);

		if (strcmp(token, "nezadane") == 0) {
			*datumCas = nezadane();
			return datumCas;
		}

		int rok = atoi(token);
		int mesiac = atoi(strtok(NULL, delim));
		int den = atoi(strtok(NULL, delim));
		int hodiny = atoi(strtok(NULL, delim));
		int minuty = atoi(strtok(NULL, delim));

		DatumCas dat = { rok, mesiac, den, hodiny, minuty };
		*datumCas = dat;
	}
	return datumCas;
}

char* toStringDatumCas(DatumCas datumCas) {
	if (isNezadane(datumCas)) {
		return "nezadane";
	}
	char* result = malloc(20 * sizeof(char));
	sprintf(result, "%d-%d-%d-%d-%d", datumCas.rok, datumCas.mesiac,
			datumCas.den, datumCas.hodiny, datumCas.minuty);
	return result;
}

DatumCas randomDatumCas() {
	DatumCas datumCas;
	datumCas.rok = (rand() % 16) + 2000;
	datumCas.mesiac = rand() % 12 + 1;
	datumCas.den = rand() % 30 + 1;
	datumCas.hodiny = rand() % 24;
	datumCas.minuty = rand() % 60;
	return datumCas;
}

DatumCas nezadane() {
	DatumCas* datumCas = malloc(sizeof(DatumCas));
	datumCas->rok = 0;
	datumCas->mesiac = 0;
	datumCas->den = 0;
	datumCas->hodiny = 0;
	datumCas->minuty = 0;
	return *datumCas;
}

int isNezadane(DatumCas datumCas) {
	if (datumCas.rok == 0 && datumCas.mesiac == 0 && datumCas.den == 0
			&& datumCas.hodiny == 0 && datumCas.minuty == 0) {
		return 1;
	} else {
		return 0;
	}
}

long rozdielCasov(DatumCas dc1, DatumCas dc2) {

	DatumCas rozdiel;

	int d1 = dc1.den, d2 = dc2.den;
	int mes1 = dc1.mesiac, mes2 = dc2.mesiac;
	int r1 = dc1.rok, r2 = dc2.rok;


	if (d2 >= d1) {
		rozdiel.den = d2 - d1;
	} else {
		d2 += 30;
		mes2 -= 1;
		rozdiel.den = d2 - d1;
	}

	if (mes2 >= mes1)
		rozdiel.mesiac = mes2 - mes1;
	else {
		mes2 += 12;
		r2 -= 1;
		rozdiel.mesiac = mes2 - mes1;
	}
	rozdiel.rok = r2 - r1;
	return datumCasVDnoch(rozdiel);
}

long datumCasVDnoch(DatumCas datumCas) {
	long dni = 0;
	dni += datumCas.den;
	dni += datumCas.mesiac * 30;
	dni += datumCas.rok * 12 * 30;
	return dni;
}
