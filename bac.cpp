#include <fstream>
#include <algorithm>
#define MAX_ORASE 2
#define MAX_CURSE 1440
using namespace std;
ifstream fin("bac.in");
ofstream fout("bac.out");
struct Cursa
{
	int destinatie, plecare, sosire;
	bool finalizata;
};
struct Port
{
	int nrCurse;
	Cursa cursa[MAX_CURSE];
};
Port port[MAX_ORASE];
int durataTotala;
void citestePlecariDinPortul(int);
void efectueazaCurseleDinPortul(int, int, int&);
int main()
{
	int durataTraversare, durataImbarcareDebarcare;
	fin >> durataTraversare >> durataImbarcareDebarcare;
	durataTotala = durataTraversare + durataImbarcareDebarcare;
	citestePlecariDinPortul(0);
	citestePlecariDinPortul(1);
	int nrPort = port[0].cursa[0].plecare < port[1].cursa[0].plecare ? 0 : 1; 
	int nrBacuri = 1;
	efectueazaCurseleDinPortul(
		nrPort,
		port[nrPort].cursa[0].plecare,
		nrBacuri);
	fout << nrBacuri;
	fin.close();
	fout.close();
	return 0;
}
bool maiPotFaceCurseDinPortul(int nrPort, int ora)
{
	if (port[nrPort].cursa[0].finalizata == 0
	    && port[nrPort].cursa[0].plecare >= ora)
		return 1;
	return 0;
}
bool comparCurse(Cursa a, Cursa b)
{
	if (!a.finalizata && !b.finalizata)
	{
		if (a.plecare < b.plecare)
			return 1;
		return 0;
	}
	if (!a.finalizata)
		return 1;
	return 0;
}
void efectueazaCurseleDinPortul(int nrPort, int oraCurenta, int& nrBacuri)
{
	sort(port[nrPort].cursa,
	     port[nrPort].cursa + port[nrPort].nrCurse,
	     comparCurse);
	if (maiPotFaceCurseDinPortul(nrPort, oraCurenta))
	{
		port[nrPort].cursa[0].finalizata = 1;
		efectueazaCurseleDinPortul(
			!nrPort,
		        port[nrPort].cursa[0].sosire,
			nrBacuri);
		if (maiPotFaceCurseDinPortul(
			!nrPort,
			port[!nrPort].cursa[0].plecare))
		{
			nrBacuri++;
			efectueazaCurseleDinPortul(
				!nrPort,
				port[!nrPort].cursa[0].plecare,
				nrBacuri);
		}
	}
}
int minute(char* ora)
{
	// converteste ora din format "HH:MM" in minute
	int hh, mm;
	hh = (ora[0]-'0')*10 + (ora[1]-'0');	
	mm = (ora[3]-'0')*10 + (ora[4]-'0');
	return hh*60 + mm;
}
void citestePlecariDinPortul(int nrPort)
{
	int i;
	char oraPlecare[6];
	fin >> port[nrPort].nrCurse;
	for (i = 0; i < port[nrPort].nrCurse; i++)
	{
		fin >> oraPlecare;
		port[nrPort].cursa[i].destinatie = !nrPort;
		port[nrPort].cursa[i].plecare = minute(oraPlecare);
		port[nrPort].cursa[i].sosire = port[nrPort].cursa[i].plecare + durataTotala;
		port[nrPort].cursa[i].finalizata = 0;
	}
}
