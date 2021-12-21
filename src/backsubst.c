#include <stdio.h>
#include "backsubst.h"

/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
 
double sumaWspolIWynPoPrawej(int i, Matrix *mat, Matrix *b, Matrix *x)
{
	double suma = 0;
	for(int z = i + 1;z < mat->r;z++)
		suma += mat->data[i][z] * x->data[z][0];

	return suma;
}
 
int backsubst(Matrix *x, Matrix *mat, Matrix *b)
{
	printf("%d, %d\n\n",mat->r, b->r);
	if(mat->r != b->r)
		return 2;
	
	x->data[b->r-1][0] = b->data[b->r - 1][b->c - 1] / mat->data[mat->r-1][mat->c-1];
	
	for(int i = b->r - 1;i >= 0;i--)
	{
		if(mat->data[i][i] != 0)
			x->data[i][0] = (b->data[i][0] - sumaWspolIWynPoPrawej(i, mat, b, x)) / mat->data[i][i];
		else
			return 1;
	}

	return 0;
}


