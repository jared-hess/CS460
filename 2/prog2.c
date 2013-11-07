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

//Prog#: 	2
//Name: 	Hess,Jared
//WSUID: 	N575U698
//Email: 	jdhess@wichita.edu

//Notes for the grader:
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyHeader.h"
//#include "LateByDays.c"

//Global Defs
#define COUNT460 3 //number of students
struct hwpoints{
	char course[7];		//Always CS460
	char wsuid[9];		//user input a123b456
	char subdate[9];	//user input YYYYMMDD
	double points1;		//user input 99.00
	double points2;		//should be calculated
};
typedef struct hwpoints cs460hwp;
static char course[7] = "cs460";

//Prototypes
double CalculatePoints(char* duedt, char* subdt, double pts1);
void PrintGrades(cs460hwp* hw);
int LateByDays(char* duedt, char* subdt);

int main (void)
{
	//Local Variables
	cs460hwp hw02[COUNT460];
	char dueDate[9];

	//Get Due DAte
	printf("Please enter hw02 due date (YYYYMMDD)>");
	scanf("%s",dueDate);

	//Loop uisng COUNT460
	for (int i = 0; i < COUNT460; i++){
		strcpy(hw02[i].course,course);
		printf("Please Enter WSU ID>");
		scanf("%s",hw02[i].wsuid);
		printf("Please Enter hw02 submission date (YYYYMMDD)>");
		scanf("%s",hw02[i].subdate);
		printf("Please enter grade points>");
		scanf("%lf",&hw02[i].points1);
		//Calculate points2
		hw02[i].points2 = CalculatePoints(dueDate,hw02[i].subdate, hw02[i].points1);
	}

	PrintGrades(hw02);

	return 0;
}

void PrintGrades(cs460hwp* hw){
	for (int i = 0; i < COUNT460; i++){
		printf("\n[%s] ",hw[i].course);
		printf("%s:\n",hw[i].wsuid);
		printf("subdate: %s ,",hw[i].subdate);
		printf("points1: %f ,",hw[i].points1);
		printf("points2: %f\n",hw[i].points2);
	}

	return;
}

double CalculatePoints (char* duedt, char* subdt, double pts1)
{
	//Figure out how many days we are late by
	int lateDays = LateByDays(duedt,subdt);
	//printf("Late: %i",lateDays); //Testing stuff

	//If latedays is Negative, something went wrong.
	if (lateDays < 0){
		printf("\nYou done goofed! Bad input!\n");
		exit (0);
	}

	//If Less than 5 days late, 10 points penalty per day	
	if (lateDays <= 5){
		return (pts1 - 10.0*lateDays);
	} 
	//Else, no points!
	else {
		return 0.0;
	}
}


