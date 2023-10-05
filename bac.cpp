#include <fstream>

#define CMAX 1440
#define PMAX 2

using namespace std;

ifstream fin("bac.in");
ofstream fout("bac.out");

int minute(char ora[]);

int main()
{
	int K, L, A, B, i, c[PMAX][CMAX], st[PMAX], dr[PMAX], b[2*CMAX], nrc, nrb, p;
	char ora[6];

	fin >> K >> L;

	fin >> A;

	for (i = 0; i < A; i++)
	{
		fin >> ora;

		c[0][i] = minute(ora);
	}

	fin >> B;

	for (i = 0; i < B; i++)
	{
		fin >> ora;
		
		c[1][i] = minute(ora);
	}

	fin.close();

	st[0] = st[1] = 0;
	dr[0] = A-1;
	dr[1] = B-1;

	nrc = nrb = 0;

	while (nrc < A+B)
	{
		if (st[0] <= dr[0] && st[1] <= dr[1])
		{
			p = c[0][st[0]] < c[1][st[1]] ? 0 : 1;
		}
		else if (st[0] <= dr[0])
		{
			p = 0;
		}
		else if (st[1] <= dr[1])
		{
			p = 1;
		}

		nrc++;
		b[nrb++] = c[p][st[p]] + K + L;
		st[p]++;
		p = !p;

		while (nrc < A+B
			&& st[p] <= dr[p]
			&& b[nrb-1] <= c[p][st[p]])
		{
			nrc++;
			b[nrb-1] = c[p][st[p]] + K + L;
			st[p]++;
			p = !p;
		}

		while (nrc < A+B 
			&& st[!p] <= dr[!p]
			&& b[nrb-1] + K <= c[!p][st[!p]])
		{
			nrc++;
			b[nrb-1] = c[!p][st[!p]] + K + L;
			st[!p]++;
		}
	}

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
// scor 20
