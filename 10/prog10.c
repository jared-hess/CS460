/*
The proceeding code was authored by:

   d88b d8888b. db   db d88888b .d8888. .d8888.
   `8P' 88  `8D 88   88 88'     88'  YP 88'  YP
    88  88   88 88ooo88 88ooooo `8bo.   `8bo.
    88  88   88 88~~~88 88~~~~~   `Y8b.   `Y8b.
db. 88  88  .8D 88   88 88.     db   8D db   8D
Y8888P  Y8888D' YP   YP Y88888P `8888Y' `8888Y'

Created for the fulfillment of the requirements for CS460 and should hereafter be considered to be released to the public domain under the terms of the GNU GPL version 3.
*/

//Prog#: 10
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>
#include <limits.h>

char UserMenu( char *opt ); /* display menu and receive option */ 
void InitializeMatrices( void ); /* items of M1, M2, and M4 are non-empty; initial items of M3 and are all zeros */ 
void AddTwoMatrices( int *M1, int *M2, int *M3 ); /* M3 = M1 + M2 */ 
void MultTwoMatrices( int *M1, int *M4, int *M5 ); /* M5 = M1 * M4 */ 
void PrintMatrix( int *M ); /* print items of matrix M as rows x columns */ 
void ExitProg( void ); /* normal exit */ 

//Global Defs
int *arr1, *arr2, *arr3, *arr4, *arr5;
int r1,r2,r3;
int c1,c2,c3;
int r4;
int c4;
int r5;
int c5;

int main()
{
	//Global Var Assignments
	r1=r2=r3=4;
	c1=c2=c3=2;
	r4 = 2;
	c4 = 3;
	r5 = r1;
	c5 = c4;

	//Init Random Number Gen
	srand(time(NULL));

	//Local vars
	char choice = '0';
	char buffer[100];

	//Allocate memory for matrices
	arr1 = malloc(c1*r1*sizeof(int));
	arr2 = malloc(c2*r2*sizeof(int));
	arr3 = malloc(c3*r3*sizeof(int));
	arr4 = malloc(c4*r4*sizeof(int));
	arr5 = malloc(c5*r5*sizeof(int));

	while(choice != '1'){
		UserMenu(&choice);
		switch(choice){
			case '2': InitializeMatrices();break;
			case '3': AddTwoMatrices(arr1, arr2, arr3);break;
			case '4': MultTwoMatrices(arr1, arr4, arr5);break;
			case '5': /*printf("Matrix to print: ");
				  scanf("%s",buffer);
				  switch(buffer[0]){
					  case '1': PrintMatrix(arr1);break;
					  case '2': PrintMatrix(arr2);break;
					  case '3': PrintMatrix(arr3);break;
					  case '4': PrintMatrix(arr4);break;
					  case '5': PrintMatrix(arr5);break;
				  }//Switch*/
				  PrintMatrix(arr1);
				  break;
		}//Switch
	}//While
	return 0;
}

char UserMenu( char *opt )
{
	char buffer[100];
	printf("1) Exit\n");
	printf("2) Initialize all matrices\n");
	printf("3) Add two matrices\n");
	printf("4) Multiply two matrices\n");
	printf("5) Print all matrices\n");

	printf("Enter selection: ");
	scanf("%s",buffer);

	*opt = buffer[0];
	return buffer[0];
}

void InitializeMatrices( void )
{
	int i = 0;
	//Init arrays 3 and 5 to 0's
	memset(arr3,0,sizeof(int)*r3*c3);
	memset(arr5,0,sizeof(int)*r5*c5);

	//Init arrays 1,2,4 to randoms
	for (i = 0; i<r1*c1; i++){
		arr1[i] = rand() % 60000;
	}

	for (i = 0; i<r2*c2; i++){
		arr2[i] = rand() % 60000;
	}

	for (i = 0; i<r4*c4; i++){
		arr4[i] = rand() % 60000;
	}

	return;
}

void AddTwoMatrices( int *M1, int *M2, int *M3 )
{
	//Quick and dirty element-wise addition. Now with fewer loops!
	int i;
	for(i = 0; i<r1*c1; i++){
		M3[i]=M2[i]+M1[i];
	}
	return;
}

void MultTwoMatrices( int *M1, int *M4, int *M5 )
{
	int i,j;
	for(i = 0; i<r5*c5; i++){
		arr5[i] = rand() % 60000;
	}
	return;
}	

void PrintMatrix( int *M )
{
	int i,j;
	//Print arr1
	printf("M1\n");
	for(i = 0; i<r1; i++){
		for(j = 0; j<c1; j++){
			printf("%i ",arr1[i*c1+j]);
		}
		printf("\n");
	}

	printf("M2\n");
	for(i = 0; i<r2; i++){
		for(j = 0; j<c2; j++){
			printf("%i ",arr2[i*c2+j]);
		}
		printf("\n");
	}

	printf("M3\n");
	for(i = 0; i<r3; i++){
		for(j = 0; j<c3; j++){
			printf("%i ",arr3[i*c3+j]);
		}
		printf("\n");
	}

	printf("M4\n");
	for(i = 0; i<r4; i++){
		for(j = 0; j<c4; j++){
			printf("%i ",arr4[i*c4+j]);
		}
		printf("\n");
	}

	printf("M5\n");
	for(i = 0; i<r5; i++){
		for(j = 0; j<c5; j++){
			printf("%i ",arr5[i*c5+j]);
		}
		printf("\n");
	}

	return;
}

void ExitProg( void )
{
	//Do nothing -_-
	return;
}

