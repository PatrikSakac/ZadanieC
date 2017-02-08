#ifndef VYPISNAKONZOLU_H_
#define VYPISNAKONZOLU_H_

#include "ZoznamSuvenirov.h"

void vypisVsetkych(ZoznamSuvenirov* zoznam,char* nadpis);

void nacitajAPridajSuvenir(ZoznamSuvenirov* zoznam);

void vypisUmelcov(ZoznamSuvenirov* zoznam);

void vypisNajlacnejsiVPredaji(ZoznamSuvenirov* zoznam);

void vypisPodlaKategorie(ZoznamSuvenirov* zoznam);

void vypisPredaj(ZoznamSuvenirov* zoznam);

void vypisInventura(ZoznamSuvenirov* zoznam);

void vypisVyplat(ZoznamSuvenirov* zoznam);

void vypisViacdodavatelskychSuvenirov(ZoznamSuvenirov* zoznam);

void vypisCoVyrabat(ZoznamSuvenirov* zoznam);

void vypisNajrychlejsieVyrobeny(ZoznamSuvenirov* zoznam);

void vypisZoradPodlaDatumuPredaja(ZoznamSuvenirov* zoznam);

#endif
