#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "feuille3.h"


void print_M(int n, int m, float M[n][n+m]) {

	for (int i = 0; i < n; ++i)
	{
		printf("|");
		for (int j = 0; j < n+m; ++j)
		{
			if(j==0)		printf("%.2f", M[i][j]);
			else if(j==n)	printf("|\t\t%.2f", M[i][j]);
			else 			printf("\t%.2f",M[i][j]);
		}
		printf("|\n");
	}
	printf("\n");
}

void print_X(int n, int m, float X[n][m]) {

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if(j==0)		printf("%.2f", X[i][j]);
			else 			printf("\t%.2f",X[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void resolution_tri(int n, float M[n][n+1], float X[n]) {
	float sum = 0;
	for (int i = n-1; i >= 0; --i)
	{
		sum = 0;
		for (int j = i+1; j < n; ++j)
		{
			sum += M[i][j] * X[j];
		}
		X[i] = (1.0/M[i][i]) * (M[i][n] - sum);
	}
}

void invert(int n, int m, float M[n][n+m], int k, int p) {
	for (int i = 0; i < n+m; ++i)
	{
		swap(&M[k][i], &M[p][i]);
	}
}

void swap (float * a, float * b) {
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

int ligne_pivot(int n, float M[n][n+1], int k) {
	int rgMax = k;
	float max = M[k][k];

	for (int i = k+1; i < n; ++i)
	{
		if(max < M[i][k]) {
			max = M[i][k];
			rgMax = i;

		}
	}
	return rgMax;
}


float triangulation(int n, int m, float M[n][n+m]) {
	float eps = 10e-9;
	int inv=1, k=0, p, signeDet = 1;

	while(k<n && inv) {
		p = ligne_pivot(n, M, k);
		float a = M[p][k];
		if(fabs(a) > eps) {
			if (k != p) {
			 	invert(n, m, M, k, p);
				signeDet *= -1;
			} 
			for (int i = k+1; i < n; ++i)
			{
				float d = M[i][k];
				for (int j = 0; j < n+m; ++j)
				{
					M[i][j] = M[i][j] - (d/a) * M[k][j];
				}
			}
		} else {
			inv = 0;
		}
		k++;
	}

	return (det(n, M) * (float)signeDet);
}

float det(int n, float M[n][n+1]) {
	float det = 1;

	for (int i = 0; i < n; ++i)
	{
		det *= M[i][i];
	}
	return det;
}

void tabX(int n, int m, float M[n][n+m], float X[n][m]) {
	float det = triangulation(n, m, M);
	float Xtemp[n];

	if(!det) {
		for (int k = 0; k < m; ++k)
		{
			float AB[n][n+1];
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n+1; ++j)
				{
					if(j==n) {
						AB[i][j] = M[i][j+k];
					} else {
						AB[i][j] = M[i][j];
					}
				}
			}
			print_M(n,m,AB);
			resolution_tri(n, AB, Xtemp);
			for (int i = 0; i < n; ++i)
			{
				printf("%.2f\n", Xtemp[i]);
				X[i][m] = Xtemp[i];
			}
		}
			
	} else {
		printf("ABORT THE MISSION !!! Det = 0\n");
	}
}

