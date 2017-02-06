#ifndef VYPISNAKONZOLU_H_
#define VYPISNAKONZOLU_H_

#include "ZoznamSuvenirov.h"

void vypisVsetkych(ZoznamSuvenirov* zoznam,char* nadpis);

void vypisUmelcov(ZoznamSuvenirov* zoznam);

void vypisInventura(ZoznamSuvenirov* zoznam);

void vypisVyplat(ZoznamSuvenirov* zoznam,int rok,int mesiac);

void vypisViacdodavatelskychSuvenirov(ZoznamSuvenirov* zoznam);

void vypisCoVyrabat(ZoznamSuvenirov* zoznam,char* umelec);

void vypisNajrychlejsieVyrobeny(ZoznamSuvenirov* zoznam,char* umelec);

void vypisZoradPodlaDatumuPredaja(ZoznamSuvenirov* zoznam);

#endif
