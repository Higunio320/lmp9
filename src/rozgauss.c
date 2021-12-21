#include "gauss.h"
#include <math.h>
#include <stdlib.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
	int i, n, a, x;
	double p;
	int maxzamwier (int i, Matrix *mat, Matrix *b) {
		int x, a, ind;
		double *s;
		double tmp;
		s = (double *) malloc(sizeof(double) * (mat->r - i));	//wektor przechowujacy najwiekszy element z kazdego wiersza
		for (x = 0; x < (mat->r - i); x++) {
			s[x] = fabs(mat->data[i+x][0]);
			for(a = 1; a < mat->c; a++) {
				if (fabs(mat->data[i+x][a]) > s[x] ) 
					s[x] = fabs(mat->data[i+x][a]); //zapisanie maksymalnych wartosci w wektorze
			}
			if(s[x] == 0)		//jezeli ktorys wiersz sklada sie z samych 0, to ten uklad nie ma rozwiazan
				return 1;
		}
		tmp = fabs(mat->data[i][i]/s[0]);
		ind = i;
		for (x = 1; x < (mat->r - i); x++) {
			if(fabs(mat->data[x+i][i]/s[x]) > tmp) {
				tmp = fabs(mat->data[x+i][i]/s[x]);	//szukanie indeksu wiersza, z ktorym nalezy zamienic "i" wiersz
				ind = x+i;
			}
		}
		if(mat->data[ind][i] == 0) //jezeli na diagonali mialby sie znalezc element 0, to uklad nie ma rozwiazan
			return 1;
		if(ind == i) {		//jezeli najlepszym kandydatem na zamiane jest wiersz, ktory juz znajduje sie na tym miejscu,
			free(s);	//to mozna po prostu przerwac dzialanie funkcji i nic nie zamieniac 
			return 0;
		}
		for (x = 0; x < mat->c; x++) {		//zamiana wierszy
			tmp = mat->data[i][x];
			mat->data[i][x] = mat->data[ind][x];
			mat->data[ind][x] = tmp;
		}
		tmp = b->data[i][0];
		b->data[i][0] = b->data[ind][0];
		b->data[ind][0] = tmp;
		free(s);
		return 0;
	}



	for(i = 0; i < (mat->c - 1); i++) { 
		if (maxzamwier(i, mat, b) == 1)
		       return 1;	
		for(n = (i + 1); n < mat->r; n++) {
			p = mat->data[n][i]/mat->data[i][i];	//p - wspolczynnik przez ktory nalezy pomnozyc "i" wiersz aby go odjac od "n" wiersza
			for(a = 0; a < mat->c; a++) 
				mat->data[n][a] -= (p*mat->data[i][a]);		//odejmowanie kazdego kolejnego wspolczynnika (odejmowanie od siebie wierszy)
			b->data[n][0] -= (p*b->data[i][0]);		//nalezy rowniez odpowiednio odjac wiersze w macierzy wyrazow wolnych "b"
		
		}
	}
	if (mat->data[mat->r-1][mat->c-1] == 0)		//jezeli po stworzeniu macierzy trojkatnej element w ostatnim wierszu i ostatniej kolumnie jest rowny 0, to macierz jest osobliwa
		return 1;
	return 0;
}
