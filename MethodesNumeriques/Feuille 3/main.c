#include <stdio.h>
#include <stdlib.h>
#include "feuille3.h"

#define N2 3
#define MM2 5


int main()
{
	/*int n1 = 3; int m1 = 1;
	float M1[3][n1 + m1] = {	{1,2,3,6},
						{4,5,6,15},
						{7,8,9,24}
					};*/

	int n2 = 3; int m2 = 2;
	float M2[N2][MM2] = {	{3,-1,1,4,8},
						{-2,2,3,1,2},
						{1,3,-2,7,14}
					};

	/*int n3 = 3; int m3 = 3;
	float M3[3][n3] = {	{3,-1,1},
						{-2,2,-3},
						{1,3,-2}
					};

	int n4 = 4; int m4 = 4;
	float M4[4][n4] = {	{10,7,8,7},
						{7,5,6,5},
						{8,6,10,9},
						{7,5,9,10}
					};
	int n5 = 2; int m5 = 2;
	float M5[2][n3] = {	{1,0.5},
						{0.5,0.33}
					};*/



	float X2[3][2];

	//triangulation(n2, m2, M2);

	print_M(n2,m2,M2);

	tabX(n2, m2, M2, X2);

	print_X(n2, m2, X2);



	// float X[3];
	// float det;


	// print_M(3, M);
	// resolution_tri(3, M2, X);
	// print_X(3, X);

	// print_M(3,M3);
	// det = triangulation(3, M3);
	// print_M(3,M3);
	// resolution_tri(3, M3, X);
	// print_X(3, X);
	// printf("Det = %.2f\n", det);

	return 0;
}



