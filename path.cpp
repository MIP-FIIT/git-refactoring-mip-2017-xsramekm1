// Martin Šrámek
// FIIT STU, Bratislava

// Princ hlada princeznu

#include <stdio.h>
#include <stdlib.h>

char map[100][100];
int n, m;

void scan(FILE *f){
	char c;
	int j = 0;
	n = m = 0;
	while ((c = fgetc(f)) > 0)
	{
		if (c == '\n')
		{
			n++;
			j = 0;
		}

		if (c <= 32)
			continue;

		map[n][j++] = c;
		if (m < j)
			m = j;
}}


void write()
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%c", map[i][j]);
		printf("\n");
}}


int inti(int i, int j)
{ return i * m + j; }

void posi(int pos, int *i, int *j)
{
	*i = pos / m;
	*j = pos%m;
}

int path()
{
	int d, dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
	int i, j, pred[100][100];
	for (i = 0; i < n; i++)
	for (j = 0; j < m; j++)
	pred[i][j] = -1;

	int *q, h, t = 0;
	q = (int*)malloc(n*m * sizeof(int));
	h = t = 0;


	int pi, pj;
	for (i = 0; i < n; i++)
	for (j = 0; j < m; j++)
		if (map[i][j] == 'P')
		{
				pi = i;	pj = j;
				q[t++] = inti(pi, pj);
			  i = n;
				j = m;
				break;
		}


	while (h < t)
    {
      posi(q[h++], &i, &j);

      for (d = 0; d < 4; d++)
      {
        int ni = i + dir[d][0];
            int nj = j + dir[d][1];
              if (ni != pi || nj != pj)
          if (ni > 0 && ni < n && nj > 0 && nj < m)
            {
              if (map[ni][nj] == 'P')
              {
                while (i != pi || j != pj)
                { map[i][j] = 'x';
                  posi(pred[i][j], &i, &j); }


              return 1;
              }
              if (map[ni][nj] == '.' && pred[ni][nj] < 0)
                {
                  pred[ni][nj] = inti(i, j);

                q[t++] = inti(ni, nj);
              }
            }
        }

    }


	return 0;
}

int main(void)
{
	scan(fopen("bludisko.txt", "rt"));
	write();
	if (!path())
	{
		printf("Cesta neexistuje\n");
		getchar();
		return 0;
	}
	printf("\n");
	printf("\n");
	printf("\n");

	write();
	getchar();
	getchar();
	getchar();
	return 0;
}
