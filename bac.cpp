#include <fstream>
#define COD_ORAS_A 0
#define COD_ORAS_B 1
#define NR_ORASE 2
using namespace std;
ifstream fin("bac.in");
ofstream fout("bac.out");
struct Plecare { int timpPlecare, timpSosire; Plecare *prec, *urm; };
struct ListaPlecari { Plecare *prima, *ultima; };
int durataDeCalatorie;
ListaPlecari L[NR_ORASE];
void calculeazaDurataDeCalatorie(int, int);
void citestePlecariDinOrasul(bool);
void calculeazaNumarulMinimDeBacuriNecesare(int &);
int main()
{
	int durataDeTraversare, durataDeImbarcareSiDebarcare, nrBacuri;
	fin >> durataDeTraversare >> durataDeImbarcareSiDebarcare;
	calculeazaDurataDeCalatorie(durataDeTraversare, durataDeImbarcareSiDebarcare);
	citestePlecariDinOrasul(COD_ORAS_A);
	citestePlecariDinOrasul(COD_ORAS_B);
	fin.close();
	calculeazaNumarulMinimDeBacuriNecesare(nrBacuri);
	fout << nrBacuri;
	fout.close();
	return 0;
}
int orasulDePlecare()
{
	if (L[COD_ORAS_A].prima && L[COD_ORAS_B].prima)
		return L[COD_ORAS_A].prima->timpPlecare < L[COD_ORAS_B].prima->timpPlecare
		       ? COD_ORAS_A
		       : COD_ORAS_B;
	if (L[COD_ORAS_A].prima)
		return COD_ORAS_A;
	if (L[COD_ORAS_B].prima)
		return COD_ORAS_B;
	return -1;
}
void scoatePlecareaDePeLista(Plecare * p, ListaPlecari & L)
{
	if (L.prima == p && p == L.ultima)
		L.prima = L.ultima = 0;
	else if (L.prima == p)
	{
		L.prima = L.prima->urm;
		L.prima->prec = 0;
	}
	else if (L.ultima == p)
	{
		L.ultima = L.ultima->prec;
		L.ultima->urm = 0;
	}
	else
	{
		p->prec->urm = p->urm;
		p->urm->prec = p->prec;
	}
	delete p;
}
bool efectueazaPrimaPlecareDinOrasDupaOra(int & timpCurent, bool oras)
{
	for (Plecare *p = L[oras].prima; p; p = p->urm)
		if (p->timpPlecare >= timpCurent)
		{
			timpCurent = p->timpSosire;
			scoatePlecareaDePeLista(p, L[oras]);
			return 1;
		}
	return 0;
}
void efectueazaPlecarileDinOrasul(bool oras)
{
	int timpCurent = L[oras].prima->timpPlecare;
	while (efectueazaPrimaPlecareDinOrasDupaOra(timpCurent, oras))
		oras = !oras;
}
void calculeazaNumarulMinimDeBacuriNecesare(int & nrBacuri)
{
	nrBacuri = 0;
	int orasPlecare = orasulDePlecare();
	while (orasPlecare >= 0)
	{
		nrBacuri++;
		efectueazaPlecarileDinOrasul(orasPlecare);
		orasPlecare = orasulDePlecare();
	}
}
void insereazaInListaDePlecari(bool oras, int timp)
{
	Plecare *p = new Plecare;
	p->timpPlecare = timp;
	p->timpSosire = timp + durataDeCalatorie;
	p->prec = p->urm = 0;
	if (!L[oras].ultima)
		L[oras].prima = L[oras].ultima = p;
	else
	{
		p->prec = L[oras].ultima;
		L[oras].ultima->urm = p;
		L[oras].ultima = p;
	}
}
void initializeazaListaDePlecariDinOrasul(bool oras)
{
	L[oras].prima = L[oras].ultima = 0;
}
int minute(char* ora)
{
	// converteste ora din format "HH:MM" in minute
	int hh, mm;
	hh = (ora[0]-'0')*10 + (ora[1]-'0');
	mm = (ora[3]-'0')*10 + (ora[4]-'0');
	return hh*60 + mm;
}
void citestePlecariDinOrasul(bool oras)
{
	int nrPlecari, i;
	char oraPlecare[6];
	initializeazaListaDePlecariDinOrasul(oras);
	fin >> nrPlecari;
	for (i = 0; i < nrPlecari; i++)
	{
		fin >> oraPlecare;
		insereazaInListaDePlecari(oras, minute(oraPlecare));
	}
}
void calculeazaDurataDeCalatorie(int durataDeTraversare, int durataDeImbarcareSiDebarcare)
{
	durataDeCalatorie = durataDeTraversare + durataDeImbarcareSiDebarcare;
}
/*void afiseazaListaDePlecariDinOrasul(bool oras)
{
	for (Plecare *p = L[oras].prima; p; p = p->urm)
		fout << p->timpPlecare << ' ';
	fout << '\n';
}*/
