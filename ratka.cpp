#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int wierzcholki(ifstream &odczyt);
void graf(int **tab, int n);
void show(int **tab, int wiersz, ofstream &plik);

int main()
{
	ifstream r;
	ofstream w;
	r.open("dane.txt"); 
	w.open("wynik.txt");
	int **t = NULL; 
	int n, vert, a, b, i;
	vert=wierzcholki(r);
	t = new int *[vert];
	for (i = 0; i < vert; i++) 
		t[i] = new int[vert];
	graf(t, vert);
	r.seekg(ios::beg);
	r >> n;
	for (i = 0; i < n; i++)
	{
		r >> a >> b; // odczytanie naraz 2 elementow
		t[a-1][b-1] = 1; // zapisanie we wspolrzenych np 2x1 
		t[b-1][a-1] = 1; // zapisanie we wspolrzenych np 1x2 <- odwrotnosc poprzedneigo wersu 
	}
	show(t, vert, w);
	for (int i = 0; i < vert; i++) 
		delete[] t[i];
	delete[] t;
	//funkcja_listy(r, max);
	return 0;
}

int wierzcholki(ifstream &odczyt)
	{
		int n, i, a, b, wierzcholek=0;
		odczyt >> n;
		for (i = 0; i < n; i++){
			odczyt >> a >> b; // pobieram na raz 2 elementy i sprawdzam który jest najwiekszy w calym pliku
			if (b > a && b > wierzcholek)
				wierzcholek = b;
			if (a > b && a > wierzcholek)
				wierzcholek = a;
		}
		return wierzcholek;
	}

void graf(int **tab, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			tab[i][j] = 0;
	}
}

void show(int **tab, int w, ofstream &plik) // tab_2_wym - wierzcholek - kolumna - strumien_pliku
{
	int i, j;
	plik << "  \t";
	for (i = 0; i < w; i++) 
		plik << i + 1 << "\t";
	plik << endl << "  \t";
	for (i = 0; i < w; i++) 
		plik << "-\t";
	plik << endl;
	for (i = 0; i < w; i++)
	{
		plik << i + 1 << "|\t";
		for (j = 0; j < w; j++)
			plik << tab[i][j] << "\t";
		plik << endl << endl;
	}
}