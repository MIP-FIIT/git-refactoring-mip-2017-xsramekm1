// Martin Šrámek
// FIIT STU, Bratislava

// Princ hlada princeznu

#include <stdio.h>
#include <stdlib.h>

char mapa[100][100];
int pocet_riadkov, dlzka_riadku;

void nacitaj_bludisko(FILE *f)
{
	char znak;
	int pozicia_v_riadku = 0;
	pocet_riadkov = dlzka_riadku = 0;
	while ((znak = fgetc(f)) > 0)
	{
		if (znak == '\n')
		{
			pocet_riadkov++;
			pozicia_v_riadku = 0;
		}
		if (znak <= 32)
			continue;
		mapa[pocet_riadkov][pozicia_v_riadku++] = znak;
		if (dlzka_riadku < pozicia_v_riadku)
			dlzka_riadku = pozicia_v_riadku;
	}
}

void vypis_bludisko()
{
	int stlpec, riadok;
	for (stlpec = 0; stlpec < riadok; stlpec++)
	{
		for (riadok = 0; riadok < dlzka_riadku; riadok++)
			printf("%c", mapa[stlpec][riadok]);
		printf("\n");
	}
}

int pos2int(int riadok, int stlpec)
{
	return riadok * dlzka_riadku + stlpec;
}

void int2pos(int pozicia, int *riadok, int *stlpec)
{
	*riadok = pozicia / dlzka_riadku;
	*stlpec = pozicia % dlzka_riadku;
}

int vyznac_cestu()
{
	int d, dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
	int riadok, stlpec, pred[100][100];
	for (riadok = 0; riadok < pocet_riadkov; riadok++)
		for (stlpec = 0; stlpec < dlzka_riadku; stlpec++)
			pred[riadok][stlpec] = -1;

	int *cesta, hlava, chvost = 0;
	cesta = (int*)malloc(pocet_riadkov * dlzka_riadku * sizeof(int));
	hlava = chvost = 0;

	int p_riadok, p_stlpec;
	for (riadok = 0; riadok < pocet_riadkov; riadok++)
		for (stlpec = 0; j < dlzka_riadku; stlpec++)
			if (mapa[riadok][stlpec] == 'P')
			{
				p_riadok = riadok;
				p_stlpec = stlpec;
				cesta[chvost++] = pos2int(p_riadok, p_stlpec);
				riadok = pocet_riadkov;
				stlpec = dlzka_riadku;
				break;
			}

	while (hlava < chvost)
	{
	  int2pos(cesta[hlava++], &riadok, &stlpec);

		for (d = 0; d < 4; d++)
		{
			int novy_riadok = i + dir[d][0];
			int novy_stlpec = j + dir[d][1];

			if (novy_riadok != p_riadok || novy_stlpec != p_stlpec)
				if (novy_riadok > 0 && novy_riadok < n && novy_stlpec > 0 && novy_stlpec < dlzka_riadku)
				{
					if (mapa[novy_riadok][novy_stlpec] == 'P')
					{
						while (riadok != p_riadok || stlpec != p_stlpec)
						{
							mapa[i][j] = 'x';
							int2pos(pred[i][j], &i, &j);
						}
						return 1;
					}
					if (mapa[novy_riadok][novy_stlpec] == '.' && pred[novy_riadok][novy_stlpec] < 0)
					{
						pred[novy_riadok][novy_stlpec] = pos2int(i, j);
						cesta[chvost++] = pos2int(novy_riadok, novy_stlpec);
					}
			  }
		}
	}


	return 0;
}

int main(void)
{
	nacitaj_bludisko(fopen("bludisko.txt", "rt"));
	vypis_bludisko();
	if (!vyznac_cestu())
	{
		printf("Cesta neexistuje\n");
		getchar();
		return 0;
	}
	printf("\n \n \n");
	vypis_bludisko();
	getchar();
	getchar();
	getchar();
	return 0;
}
