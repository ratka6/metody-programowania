#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void plecak(int indeks, int profit, int waga, int *best, int *temp, int pojemnosc, int ilosc, int *p, int *q, int &maxprofit);
bool obiecujace(int indeks, int profit, int waga, int pojemnosc, int ilosc, int *p, int *q, int maxprofit);

int main()
{
	ifstream r;
	ofstream w;
	r.open("dane.txt");
	w.open("wynik.txt");
	int n, pojemnosc, max, i;
	int *p = NULL;
	int *q = NULL;
	int *best = NULL;
	int *temp = NULL;
	r >> n >> pojemnosc;
	p = new int[n + 1];
	q = new int[n + 1];
	best = new int[n + 1];
	temp = new int[n + 1];
	p[0] = 0;
	q[0] = 0;
	max = 0;
	for (i = 1; i < n + 1; i++)
	{
		r >> p[i];
		r >> q[i];
	}
	plecak(0, 0, 0, best, temp, pojemnosc, n, p, q, max);
	w << "wartosc plecaka -> " << max << endl;
	w << "przedmioty w plecaku -> ";
	for (i = 1; i < n + 1; i++)
	{
		if (best[i] == 1) w << i << " ";
	}
	delete[] p;
	delete[] q;			
	r.close();
	w.close();
	return 0;
}

void plecak(int indeks, int profit, int waga, int *best, int *temp, int pojemnosc, int ilosc, int *p, int *q, int &maxprofit)
{
	int i;
	if (profit > maxprofit && waga <= pojemnosc)
	{
		maxprofit = profit;
		for (i = 1; i < pojemnosc + 1; i++)
		{
			best[i] = temp[i];
		}
	}
	if (obiecujace(indeks, profit, waga, pojemnosc, ilosc, p, q, maxprofit))
	{
		temp[indeks + 1] = 1;
		plecak(indeks + 1, profit + p[indeks + 1], waga + q[indeks + 1], best, temp, pojemnosc, ilosc, p, q, maxprofit);
		temp[indeks + 1] = 0;
		plecak(indeks + 1, profit, waga, best, temp, pojemnosc, ilosc, p, q, maxprofit);
	}
}

bool obiecujace(int indeks, int profit, int waga, int pojemnosc, int ilosc, int *p, int *q, int maxprofit)
{
	int j, total;
	float b;
	if (waga >= pojemnosc) return false;
	else{
		j = indeks + 1;
		total = waga;
		b = (float)profit;
		while (total + q[j] <= pojemnosc && j < ilosc)
		{
			total += q[j];
			b += p[j];
			j++;
		}
		if (j <= ilosc) 
			b += (pojemnosc - total) * (float)p[j] / q[j];
		return b > maxprofit;
	}
}
