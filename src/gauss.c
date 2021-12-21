#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
	int i, n, a;
	double x;

	int zamwier (int i, int n, Matrix *mat, Matrix *b) {		//funkcja zamieniajaca wiersz "i" z nastepnym wierszem (zarowno w macierzy "mat",
		int x;							//jak i w macierzy "b") w ktorym element w kolumnie "i" nie jest 0 
		n++;							//wyszukiwanie zaczyna od wiersza "n+1" (przy tworzeniu macierzy schodkowej srednio
		double tmp;						//sie powinno zamieniac wiersz z wierszem wczesniejszym)
		for (; n < mat->r; n++) {		
			if (mat->data[n][i] != 0) { 		//znaleziono niezerowy element w tej samej kolumnie
				for(x = 0; x < mat->c; x++) {		//zamiana wierszy "i" z "n"
					tmp = mat->data[i][x];
					mat->data[i][x] = mat->data[n][x];
					mat->data[n][x] = tmp;
				}
				tmp = b->data[n][0];		//przy zamianie wierszy w macierzy wspolczynnikow "mat" trzeba rowniez zamienic
				b->data[n][0] = b->data[i][0];	//te same wiersze w macierzy wyrazow wolnych "b"
				b->data[i][0]=tmp;
				break;
			}
			if (n == (mat->r - 1)) {	//jezeli w kazdym wierszu w "i" kolumnie jest 0, to ten uklad rownan nie ma rozwiazan - macierz osobliwa
				return 1;		//mat->r - 1 to ostatni mozliwy wiersz, jezeli petla sie wczesniej nie zakonczyla, to trzeba zakonczyc dzialanie funkcji
			}
		}
		return 0;
	}
	for(i = 0; i < (mat->c - 1); i++) { //
		if (mat->data[i][i] == 0)	//jezeli wspolczynnik na glownej przekatnej jest rowny 0 nalezy zamienic wiersze
			if(zamwier(i, i, mat, b) == 1)
				return 1;
		for(n = (i + 1); n < mat->r; n++) {
			x = mat->data[n][i]/mat->data[i][i];	//x - wspolczynnik przez ktory nalezy pomnozyc "i" wiersz aby go odjac od "n" wiersza
			for(a = 0; a < mat->c; a++) 
				mat->data[n][a] -= (x*mat->data[i][a]);		//odejmowanie kazdego kolejnego wspolczynnika (odejmowanie od siebie wierszy)
			b->data[n][0] -= x*b->data[i][0];		//nalezy rowniez odpowiednio odjac wiersze w macierzy wyrazow wolnych "b"
		
		}
	}
	if (mat->data[mat->r-1][mat->c-1] == 0)		//jezeli po stworzeniu macierzy trojkatnej element w ostatnim wierszu i ostatniej kolumnie jest rowny 0, to macierz jest osobliwa
		return 1;
	return 0;
}
