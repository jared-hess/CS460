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

//Prog#:7
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
//Program must be compiled with the "-std=c99" option. For example:
//gcc -Wall -std=c99 prog7.c
//Also, currently the program is only set for 10k numbers instead of the 100k requested so it runs in a reasonable time on my computer.
//If you want to change this value, you can change the global "size" variable.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>

int size = 10000;
//Required Function Prototypes
char UserMenu( char *opt ); /* display menu and receive option */ 
void PopulateArrayDes( int *A ); /* populate array A in descending order */ 
void CopyArrays( int *A1, int *A2 ); /* copy array A1 into array A2 */ 
void DisplayArray10Items( int *A ); /* display the first 10 items in array A */ 
void BubbleSortAsc( int *B ); /* sort array B in ascending order using bubble sort algorithm */ 
void InsertionSortAsc( int *I ); /* sort array I in ascending order using insertion sort algorithm */ 
int CalculateTimeBS( int *A ); /* return the time needed to bubble sort an unsorted array A */ 
int CalculateTimeIS( int *A ); /* return the time needed to insertion sort an unsorted array A */ 
void ExitProg( void ); /* normal exit */ 

int main()
{
	//Do something
	int desArray[size];//Our Descending numbers to sort
	int myArray[size];//Array for working with stuff
	char choice = '0';

	while (choice != '1'){
		UserMenu(&choice);
		switch(choice){
			case '2': PopulateArrayDes(myArray);break;
			case '3': CopyArrays(desArray,myArray);break;
			case '4': DisplayArray10Items(myArray);break;
			case '5': BubbleSortAsc(myArray);break;
			case '6': InsertionSortAsc(myArray);break;
			case '7': CalculateTimeBS(myArray);break;
			case '8': CalculateTimeIS(myArray);break;
		}//switch
	}//while
	ExitProg();
	return 0;
}

char UserMenu( char *opt ) /* display menu and receive option */ 
{
	char buffer[100];
	printf("1) Exit\n");
	printf("2) Populate array\n");
	printf("3) Copy array\n");
	printf("4) Display array (first 10 items)\n");
	printf("5) Bubble Sort Ascending\n");
	printf("6) Insertion Sort Ascending\n");
	printf("7) Calculate Time for Bubble Sort\n");
	printf("8) Calculate Time for Insertion Sort\n");
	
	printf("Enter Selection: ");
	scanf("%s",buffer);

	*opt = buffer[0];
	return buffer[0];
}

void PopulateArrayDes( int *A ) /* populate array A in descending order */ 
{
	for(int i = 0; i<size; i++){
		A[i] = size - i;
	}
	return;
}

void CopyArrays( int *A1, int *A2 ) /* copy array A1 into array A2 */ 
{
	memcpy( A1, A2, size*sizeof(int));
	return;
}

void DisplayArray10Items( int *A ) /* display the first 10 items in array A */ 
{
	for(int i = 0; i < 10; i++){
		printf("%i\n",A[i]);
	}
	return;
}

void BubbleSortAsc( int *B ) /* sort array B in ascending order using bubble sort algorithm */ 
{
	int sorted;
	int tmp;
	printf("Please wait, this could take a while...\n");
	do{
		sorted = 1;
		for (int i = 0; i < size - 1; i++){
			if (B[i] > B[i+1]){
				//printf("Swapping %i and %i\n",B[i],B[i+1]);
				tmp = B[i];
				B[i]=B[i+1];
				B[i+1]=tmp;
				sorted = 0;
				//printf("%i\n",B[i]);
			}//if
		}//for
		//printf(".");
	}while(!sorted);
	//printf("\n");
	return;
}
void InsertionSortAsc( int *I ) /* sort array I in ascending order using insertion sort algorithm */ 
{
	int key,i,j;
	for(i = 1; i < size; i++){
		key = I[i];
		for(j = i-1; (j >= 0) && (I[j] > key); j--){
			I[j+1]=I[j];
		}
		I[j+1]=key;
	}
	return;
}
				
int CalculateTimeBS( int *A ) /* return the time needed to bubble sort an unsorted array A */ 
{
	//Local Declarations
	struct timeval tim;     //Time struct that allows us to use usec

	PopulateArrayDes(A);//Make sure it's unsorted
	
	//Get time before sort
	gettimeofday(&tim,NULL);
	double t1 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds

	BubbleSortAsc(A);//Sort
	
	//Time after sort
	gettimeofday(&tim,NULL);
	double t2 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds
	
	printf("Before: %.6lf seconds since epoch\n",t1);
	printf("After: %.6lf seconds since epoch\n",t2);
	printf("Running time: %.6lf seconds\n",t2-t1);

	return 1;
}
	
int CalculateTimeIS( int *A ) /* return the time needed to insertion sort an unsorted array A */ 
{	//Local Declarations
	struct timeval tim;     //Time struct that allows us to use usec

	PopulateArrayDes(A);//Make sure it's unsorted
	
	//Get time before sort
	gettimeofday(&tim,NULL);
	double t1 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds

	InsertionSortAsc(A);//Sort
	
	//Time after sort
	gettimeofday(&tim,NULL);
	double t2 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds
	
	printf("Before: %.6lf seconds since epoch\n",t1);
	printf("After: %.6lf seconds since epoch\n",t2);
	printf("Running time: %.6lf seconds\n",t2-t1);

	return 1;

}

void ExitProg( void ) /* normal exit */ 
{
	//Do nothing
	return;
}
