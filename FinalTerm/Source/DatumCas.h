#ifndef DATUMCAS_H_
#define DATUMCAS_H_

typedef struct
{
	int rok;
	int mesiac;
	int den;
	int hodiny;
	int minuty;
} DatumCas;

DatumCas* fromStringDatumCas(char* string);

char* toStringDatumCas(DatumCas datumCas);

DatumCas randomDatumCas();

DatumCas nezadane();

int isNezadane(DatumCas datumCas);

long rozdielCasov(DatumCas dc1,DatumCas dc2);

long datumCasVDnoch(DatumCas datumCas);

#endif
