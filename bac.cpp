#include <fstream>

#define CMAX 1440
#define PMAX 2

using namespace std;

ifstream fin("bac.in");
ofstream fout("bac.out");

int c[PMAX][CMAX], nrc[PMAX], b[2*CMAX], nrb;

int minute(char ora[]);

int main()
{
	int K, L, A, B, i, p, ok, st, dr, mij;
	char ora[6];

	fin >> K >> L;

	fin >> A;

	nrc[0] = A;

	for (i = 0; i < A; i++)
	{
		fin >> ora;
		
		c[0][i] = minute(ora);
	}

	fin >> B;

	nrc[1] = B;

	for (i = 0; i < B; i++)
	{
		fin >> ora;
		
		c[1][i] = minute(ora);
	}

	fin.close();

	do
	{
		// aleg portul din care incep prima cursa
		if (nrc[0] && nrc[1])
		{
			p = c[0][0] < c[1][0] ? 0: 1;
		}
		else if (nrc[0])
		{
			p = 0;
		}
		else if (nrc[1])
		{
			p = 1;
		}

		b[nrb] = c[p][0]+K+L, nrc[p]--;

		for (i = 0; i < nrc[p]; i++)
		{
			c[p][i] = c[p][i+1];
		}

		// dupa prima cursa am ajuns in portul opus
		p = !p;
		
		// caut urm. cursa pe care o pot face din portul p
		// cu aceeasi barca
		for (ok = 1; ok && nrc[p];)
		{
			st = -1, dr = nrc[p];

			while (dr-st > 1)
			{
				mij = st + (dr-st)/2;
				
				if (c[p][mij] < b[nrb])
				{
					st = mij;
				}
				else
				{
					dr = mij;
				}
			}

			if (dr == nrc[p] || c[p][dr] < b[nrb])
			{
				ok = 0;
			}
			else
			{
				b[nrb] = c[p][dr]+K+L, nrc[p]--;

				for (i = dr; i < nrc[p]; i++)
				{
					c[p][i] = c[p][i+1];
				}

				// dupa cursa am ajuns in portul opus
				p = !p;
			}
		}

		// nu mai pot face nicio cursa in portul p
		// caut urm. cursa pe care o pot face din portul opus (!p)
		// cu aceeasi barca
		for (ok = 1; ok && nrc[!p];)
		{
			st = -1, dr = nrc[!p];
		
			while (dr-st > 1)
			{
				mij = st + (dr-st)/2;

				if (c[!p][mij] < b[nrb]+K)
				{
					st = mij;
				}
				else
				{
					dr = mij;
				}
			}

			if (dr == nrc[!p] || c[!p][dr] < b[nrb]+K)
			{
				ok = 0;
			}
			else
			{
				b[nrb] = c[!p][dr]+K+L, nrc[!p]--;

				for (i = dr; i < nrc[!p]; i++)
				{
					c[!p][i] = c[!p][i+1];
				}
			}
		}
		
		// nu mai pot face nicio cursa cu aceasta barca
		nrb++;
	}
	while(nrc[0] || nrc[1]);

	fout << nrb;
	
	fout.close();

	return 0;
}

// convertesc ora din format HH:MM in minute
int minute(char ora[6])
{
	int HH, MM;

	HH = (ora[0]-'0')*10 + (ora[1]-'0');

	MM = (ora[3]-'0')*10 + (ora[4]-'0');

	return HH*60 + MM;
}
// scor 40
