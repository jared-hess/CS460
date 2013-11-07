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

//Prog#:
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
//

#include <stdio.h>
#include <stdlib.h>

//Global Defs
typedef struct
{
	int recid;
	char course[7];
	char wsuid[9];
	char test[9];
	char subdate[9];
	double score1;
	double score2;	//Why is this here if we don't use it?
} anyscore;
	
//I'm not completely sure what was meant by using typedef to create "instances" of anyscore. The way I have done it here works well and is a correct way of creating structure declarations.
anyscore cs300score; 
anyscore cs460score; //creates 2 variables of anyscore type

//Function Prototypes
void PrintScore ();

int main (void)
{
	//CS300
	printf("\nPlease enter the value of the recid for cs300score>");
	scanf("%i",&cs300score.recid);
	printf("\nYou entered: %i",cs300score.recid);

	printf("\nPlease enter the value of the course for cs300score>");
	scanf("%s",cs300score.course);
	printf("\nYou entered: %s",cs300score.course);

	printf("\nPlease enter the value of the wsuid for cs300score");
        scanf("%s",cs300score.wsuid);
	printf("\nYou entered: %s",cs300score.wsuid);

	printf("\nPlease enter the value of the test for cs300score");
        scanf("%s",cs300score.test);
	printf("\nYou entered: %s",cs300score.test);

	printf("\nPlease enter the value of the subdate for cs300score");
        scanf("%s",cs300score.subdate);
	printf("\nYou entered: %s",cs300score.subdate);

	printf("\nPlease enter the value of the score1 for cs300score");
        scanf("%lf",&cs300score.score1);
	printf("\nYou entered: %f",cs300score.score1);


	//sc460score
	printf("\nPlease enter the value of the recid for cs460score>");
	scanf("%i",&cs460score.recid);
	printf("\nYou entered: %i",cs460score.recid);

	printf("\nPlease enter the value of the course for cs460score>");
	scanf("%s",cs460score.course);
	printf("\nYou entered: %s",cs460score.course);

	printf("\nPlease enter the value of the wsuid for cs460score");
        scanf("%s",cs460score.wsuid);
	printf("\nYou entered: %s",cs460score.wsuid);

	printf("\nPlease enter the value of the test for cs460score");
        scanf("%s",cs460score.test);
	printf("\nYou entered: %s",cs460score.test);

	printf("\nPlease enter the value of the subdate for cs460score");
        scanf("%s",cs460score.subdate);
	printf("\nYou entered: %s",cs460score.subdate);

	printf("\nPlease enter the value of the score1 for cs460score");
        scanf("%lf",&cs460score.score1);
	printf("\nYou entered: %f",cs460score.score1);

	printf("\nALL VALUES FOR CS300SCORE ARE RECEIVED\n");

	PrintScore();
return 0;
}

void PrintScore()
{
	//CS300
	printf("\nSTRUCT CS300SCORE VALUES:");

	printf("\nrecid: %i",cs300score.recid);
	printf("\ncourse: %s",cs300score.course);
	printf("\nwsuid: %s",cs300score.wsuid);
	printf("\ntest: %s",cs300score.test);
	printf("\nsubdate: %s",cs300score.subdate);
	printf("\nscore1: %f",cs300score.score1);
	printf("\nscore2: %f\n",cs300score.score2);

	//CS460
	printf("\nSTRUCT CS460SCORE VALUES:");

	printf("\nrecid: %i",cs460score.recid);
	printf("\ncourse: %s",cs460score.course);
	printf("\nwsuid: %s",cs460score.wsuid);
	printf("\ntest: %s",cs460score.test);
	printf("\nsubdate: %s",cs460score.subdate);
	printf("\nscore1: %f",cs460score.score1);
	printf("\nscore2: %f\n",cs460score.score2);
	
	return;
}
