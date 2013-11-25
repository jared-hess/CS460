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

//Prog#: 9
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
//
//Pseudocode:
//quicksort(array)
//	if 0 or 1, already sorted
//		return
//	if 2 
//		swap if necessary
//		return
//	else (3 or more)
//		choose pivot
//		partitions into 2 arrays, A and B
//		for every element in array
//			if element larger than pivot 
//				go in B
//			else 
//				go in A
//		quicksort A
//		quicksort B
//		array = concatenation of A and B
//		return	


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>
#include <limits.h>

int size = 100000;

//Required Functions
char UserMenu( char *opt ); /* display menu and receive option */ 
void PopulateArrayRand( int *A ); /* populate array A with 10000 random unique numbers */ 
void CopyArrays ( int *A1, int *A2 ); /* copy array A1 into array A2 */ 
void DisplayArray10Items ( int *A ); /* display first 10 items in array A */ 
void QuicksortAsc( int *B,int len ); /* sort array B in ascending order using Quicksort algorithm */ 
double CalculateTimeQS( int *A ); /* return the time needed to Quicksort an unsorted array A */ 
void ExitProg( void ); /* normal exit */ 

int main()
{
	srand (time(NULL));
	//Do some stuff
	int randArray[size];
	int myArray[size];
	char choice = '0';

	while(choice != '1'){
		UserMenu(&choice);
		switch(choice){
			case '2': PopulateArrayRand(myArray);break;
			case '3': CopyArrays(randArray,myArray);break;
			case '4': DisplayArray10Items(myArray);break;
			case '5': QuicksortAsc(myArray,size);break;
			case '6': CalculateTimeQS(myArray);break;
		}//Switch
	}//While

	return 0;
}

char UserMenu(char* opt)
{
	char buffer[100];
	printf("1) Exit\n");
	printf("2) Populate array\n");
	printf("3) Copy array\n");
 	printf("4) Display array (first 10 items)\n");
	printf("5) Quicksort Ascending\n");
	printf("6) Calculate Time for Quicksort\n");

	printf("Enter Selection: ");
	scanf("%s",buffer);

	*opt = buffer[0];
	return buffer[0];
}

void PopulateArrayRand(int* A)
{
	int i;
	for(i = 0; i<size; i++){
		A[i] = rand() % 60000;
	}
	return;
}

void CopyArrays(int *A1, int *A2)
{
	memcpy(A1, A2, size*sizeof(int));
	return;
}

void DisplayArray10Items ( int *A ) /* display first 10 items in array A */
{
	int i;
	for(i = 0; i < 10; i++){
		printf("%i\n",A[i]);
	}
	return;
}

void QuicksortAsc( int *B, int len ) /* sort array B in ascending order using Quicksort algorithm */
{
	int i;
	//Base Case
	if ((len == 1)||(len == 0)){
		//printf("1 or 0\n");
		return;//an array of size one is sorted
	} else if (len == 2){
		//printf("case 2\n");
		if (B[0] > B[1]){//Take care of case of 2 elements
			int tmp = B[0];
			B[0] = B[1];
			B[1] = tmp;
		}
		return;//array is now sorted
	}else{ //Array is size 3 or more
		//printf("3 or more\n");
		//Pick a pivot (let's just pick the middle one)
		int pivot = len/2;
		int pivotElement = B[pivot];
		int larger[len];
		int smaller[len];
		int lCount = 0,sCount = 0;
		for(i = 0; i<len; i++){
			if(i == pivot){
				//Do nothing
			}else if(B[i] < B[pivot]){
				//printf("Move smaller %i\n",B[i]);
				smaller[sCount++] = B[i];
			}else{
				//printf("Move larger %i\n",B[i]);
				larger[lCount++] = B[i];
			}
		}

		//printf("Recursing smaller...\n");
		QuicksortAsc(smaller,sCount);
		//printf("Recursing larger...\n");
		QuicksortAsc(larger,lCount);
		//printf("Copying...\n");
		for(i = 0;i < sCount; i++){
			B[i] = smaller[i];
			//printf("%i",smaller[i]);
		}
		B[sCount] = pivotElement;
		for(i = 0;i < lCount; i++){
			B[i + sCount + 1] = larger[i];
			//printf("%i",larger[i]);
		}
		//printf("Returning...\n");
		return;
	}
}

double CalculateTimeQS( int *A ) /* return the time needed to Quicksort an unsorted array A */
{
	//Local Declarations
	struct timeval tim;

	PopulateArrayRand(A);

	//Get time before sort
	gettimeofday(&tim,NULL);
	double t1 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds

	QuicksortAsc(A,size);//Sort

	gettimeofday(&tim,NULL);
	double t2 = tim.tv_sec+(tim.tv_usec/1000000.0); //Convert to fractional seconds
	printf("Sorted %i randomly generated numbers.\n",size);
	printf("Before: %.6lf seconds since epoch\n",t1);
	printf("After: %.6lf seconds since epoch\n",t2);
	printf("Running time: %.6lf seconds\n",t2-t1);

	return 1.0;
}

void ExitProg( void )
{
	//Do nothing
	return;
}
