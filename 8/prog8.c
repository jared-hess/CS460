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

//Prog#:8
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
//Program must be compiled with the "-std=c99" option. For example:
//gcc -Wall -std=c99 prog8.c
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
void ShellSortAsc( int *B ); /* sort array B in ascending order using bubble sort algorithm */ 
void HeapSortAsc( int *I ); /* sort array I in ascending order using insertion sort algorithm */ 
int CalculateTimeSS( int *A ); /* return the time needed to bubble sort an unsorted array A */ 
int CalculateTimeHS( int *A ); /* return the time needed to insertion sort an unsorted array A */ 
void ExitProg( void ); /* normal exit */ 

//Mine
void siftDown( int *I, int start, int end);

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
			case '5': ShellSortAsc(myArray);break;
			case '6': HeapSortAsc(myArray);break;
			case '7': CalculateTimeSS(myArray);break;
			case '8': CalculateTimeHS(myArray);break;
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
	printf("5) Shell Sort Ascending\n");
	printf("6) Heap Sort Ascending\n");
	printf("7) Calculate Time for Shell Sort\n");
	printf("8) Calculate Time for Heap Sort\n");
	
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

void ShellSortAsc( int *B ) /* sort array B in ascending order using shell sort algorithm */ 
{
	int gapSeq[]={1,4,10,23,57,132,301,701};
	int gapSize=sizeof(gapSeq)/sizeof(gapSeq[0]);
	int currentGap,currentSeq;
	
	for(currentSeq = gapSize-1; currentSeq>=0; currentSeq--){
		int key,i,j;
		currentGap = gapSeq[currentSeq]; 
		for(i = 1; i*currentGap < size; i++){
			key = B[i*currentGap];
			for(j = i-1; (j >= 0) && (B[j*currentGap] > key); j--){
				B[(j+1)*currentGap]=B[j*currentGap];
			}
			B[(j+1)*currentGap]=key;
		}
	}

	return;
}
void HeapSortAsc( int *I ) /* sort array I in ascending order using heap sort algorithm */ 
{
	int i, tmp;
	//Make a heap!
	//Heapify
	for (i = (size-2)/2; i >=0; i--)
		siftDown(I,i,size);
	for (i = size-1; i >= 1; i--){
		tmp = I[0];
		I[0] = I[i];
		I[i] = tmp;
		siftDown(I,0,i-1);
	}
	return;
}

void siftDown( int *I, int start, int end)
{
	int done, maxChild,tmp;
	done = 0;

	while((start*2 <= end) && !done){
		if(start*2 <= end)
			maxChild = start*2;
		else if (I[start*2] > I[start*2+1])
			maxChild = start*2;
		else
			maxChild = start*2+1;

		if (I[start] < I[maxChild]){
			tmp = I[start];
			I[start] = I[maxChild];
			I[maxChild] = tmp;
			start = maxChild;
		}
		else
			done = 1;
	}
	return;
}

				
int CalculateTimeSS( int *A ) /* return the time needed to bubble sort an unsorted array A */ 
{
	//Local Declarations
	struct timeval tim;     //Time struct that allows us to use usec

	PopulateArrayDes(A);//Make sure it's unsorted
	
	//Get time before sort
	gettimeofday(&tim,NULL);
	double t1 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds

	ShellSortAsc(A);//Sort
	
	//Time after sort
	gettimeofday(&tim,NULL);
	double t2 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds
	
	printf("Before: %.6lf seconds since epoch\n",t1);
	printf("After: %.6lf seconds since epoch\n",t2);
	printf("Running time: %.6lf seconds\n",t2-t1);

	return 1;
}
	
int CalculateTimeHS( int *A ) /* return the time needed to insertion sort an unsorted array A */ 
{	//Local Declarations
	struct timeval tim;     //Time struct that allows us to use usec

	PopulateArrayDes(A);//Make sure it's unsorted
	
	//Get time before sort
	gettimeofday(&tim,NULL);
	double t1 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds

	HeapSortAsc(A);//Sort
	
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
