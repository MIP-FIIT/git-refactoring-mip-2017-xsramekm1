// Martin Šrámek
// FIIT STU, Bratislava

// Princ hlada princeznu

#include <stdio.h>
#include <stdlib.h>

char mapa[100][100]; // 2D pole pre bludisko
int pocet_riadkov, dlzka_riadku;

// Funkcia nacitava bludisko zo suboru
void nacitaj_bludisko(FILE *f)
{
	char znak;
	int pozicia_v_riadku = 0;
	pocet_riadkov = dlzka_riadku = 0;
	while ((znak = fgetc(f)) > 0) // Cita subor po jednom chare, pokial sa nedostane nakoniec
	{
		if (znak == '\n')
		{
			pocet_riadkov++; // Pocita pocet riadkov
			pozicia_v_riadku = 0;
		}
		if (znak <= 32) // \n ma hodnotu 10, od 32 zaci­naju regulerne znaky v ASCII tabulke
			continue;
		mapa[pocet_riadkov][pozicia_v_riadku++] = znak;
		if (dlzka_riadku < pozicia_v_riadku)  // Ak presiahneme limit
			dlzka_riadku = pozicia_v_riadku;
	}
}

// Vypise bludisko z 2D pola
void vypis_bludisko()
{
	int stlpec, riadok;
	for (stlpec = 0; stlpec < riadok; stlpec++)
	{
		for (riadok = 0; riadok < dlzka_riadku; riadok++)
			printf("%c", mapa[stlpec][riadok]); // znak na ktorom sa nachadzame
		printf("\n");
	}
}

/* Vypocita poziciu v bludisku z riadku a stlpca, vynasobenim dlzky riadku
 s cislom riadku a pripocita poziciu v riadku*/
int pos2int(int riadok, int stlpec)
{
	return riadok * dlzka_riadku + stlpec;
}

/* Vypocita cislo riadku a poziciu v riadku z ciselneho
 vyjadrenia pozicie v bludisku a dosadi ich na adresy intov*/
void int2pos(int pozicia, int *riadok, int *stlpec)
{
	*riadok = pozicia / dlzka_riadku;
	*stlpec = pozicia % dlzka_riadku;
}

// Funkcia hlada cestu bludiskom, ak ju najde tak ju vyznaci
int vyznac_cestu()
{
  // 4 smery (hore, dole, doprava, doalava)
	int d, dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
	int riadok, stlpec, pred[100][100]; // Uchovava int pozicie jednotlivych ciest
	for (riadok = 0; riadok < pocet_riadkov; riadok++)
		for (stlpec = 0; stlpec < dlzka_riadku; stlpec++)
			pred[riadok][stlpec] = -1; // Dosadenie -1 na uzemie rovnake ako su rozmery bludiska

	// alokacia 1D pola o vlekosti poctu poli bludiska (riadky * stlpce)
	int *cesta, hlava, chvost = 0;
	cesta = (int*)malloc(pocet_riadkov * dlzka_riadku * sizeof(int));
	hlava = chvost = 0;

	/* Hlada P (zaciatocny bod) a ak najde tak zaznaci koordinacie do p_riadok a p_stlpec,
	a nastavi ako aktualny bod z ktoreho sa budeme pohybovat na hranicne hodnoty
  (posledny riadok posledny stlpec)*/
	int p_riadok, p_stlpec;
	for (riadok = 0; riadok < pocet_riadkov; riadok++)
		for (stlpec = 0; j < dlzka_riadku; stlpec++)
      // Ak by sme chceli zmenit princa na iny znak zmenit tu...
			if (mapa[riadok][stlpec] == 'P')
			{
				p_riadok = riadok;
				p_stlpec = stlpec;
        // Dosadime do pola chvost na nulte miesto int poziciu princa
				cesta[chvost++] = pos2int(p_riadok, p_stlpec);
				riadok = pocet_riadkov;
				stlpec = dlzka_riadku;
				break;
			}

  // Pokial sa hlava a chvost nerovnaju, cyklus sa vykonava
  // Sprava sa ako rekurzia
	while (hlava < chvost)
	{
    // Dosadime na adresy riadku a stlpca hodnoty vypocitane z Int pozicie (suradnice kam sme sa pohli)
	  int2pos(cesta[hlava++], &riadok, &stlpec);

		for (d = 0; d < 4; d++)
		{
      // Zmeni riadok a stlpec podla podla toho do akeho smeru ideme
			int novy_riadok = i + dir[d][0];
			int novy_stlpec = j + dir[d][1];

      // Ak sa pozicia princa nerovna pozici do ktorej sa chceme pohnut (ak ano tak sa pokracuje v cykle)
			if (novy_riadok != p_riadok || novy_stlpec != p_stlpec)
        /* Ohranicenie aby sme nevysli z mapy
        (riadok aj stlpec musia byt vacsie ako 0 ale mensie ako ich hrancne hodnoty)*/
				if (novy_riadok > 0 && novy_riadok < n && novy_stlpec > 0 && novy_stlpec < dlzka_riadku)
				{
          // Ak sa na poli nachadza P  (znamena to ze sme nasli princeznu)
					if (mapa[novy_riadok][novy_stlpec] == 'P')
					{
            // Cyklus sa vykonava pokial nenarazime na princa
						while (riadok != p_riadok || stlpec != p_stlpec)
						{
							mapa[i][j] = 'x'; // Dosadzujeme x na pozicie (vyznacujeme cestu)
							int2pos(pred[i][j], &i, &j);
						}
						return 1;
					}
          // Ak sa na poli nachadza "." (cesta) a neboli sme zatial na tomto poli (rovna sa -1)
					if (mapa[novy_riadok][novy_stlpec] == '.' && pred[novy_riadok][novy_stlpec] < 0)
					{
            // Ak sa cestou da ist, zapiseme do pola pred na tieto suradnice poziciu vyjadrenu intom
						pred[novy_riadok][novy_stlpec] = pos2int(i, j);
            // Priradi v poli cesta na miesto chvost poziciu reprezentovanu intom
						cesta[chvost++] = pos2int(novy_riadok, novy_stlpec);
					}
			  }
		}
	}


	return 0; // Bludisko nema riesenie (Ked uz nie je policko na ktorom sme neboli)
}

// Vykreslime povodne bludisko a bludisko s vyznacenou cestou
int main(void)
{
	nacitaj_bludisko(fopen("bludisko.txt", "rt"));
  // Pred zmenou
	vypis_bludisko();
  // Ak vrati funkcia 1 neexistuje ziadna cesta
	if (!vyznac_cestu())
	{
		printf("Cesta neexistuje\n");
		getchar();
		return 0;
	}
	printf("\n \n \n");
  // Po zmene
	vypis_bludisko();
	getchar();
	getchar();
	getchar();
	return 0;
}
