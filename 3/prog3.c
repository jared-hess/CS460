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

//Prog#: 	3
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
	struct hwpoints* nextPtr;//pointer to next
};
typedef struct hwpoints cs460hwp;
static char course[7] = "cs460";
char dueDate[9];
int numStudents = 0;

//Prototypes
double CalculatePoints(char* duedt, char* subdt, double pts1);
void PrintGrades(cs460hwp* hw);
int LateByDays(char* duedt, char* subdt);
//New Prototypes
int UserMenu(int *opt);
void BuildList(cs460hwp* hw);
void DisplayGrade(cs460hwp hw, char* id);
void StoreGrades(cs460hwp hw);
void ExitProg(cs460hwp* hw);
void EmptyList(cs460hwp* hw);

int main (void)
{
	int option = 0;
	char wsuIDchoice[9];
	cs460hwp hwList;
	char garbage[100];

	hwList.nextPtr = NULL;
	printf("Instructions: You must first create a list or none of the other functions will work.\n");
	while (1){

	while (UserMenu(&option) != 1)
		printf("Invalid Option. Try again. \n");

	switch (option){
		case 1: ExitProg(&hwList); //exit
			break;
		case 6: printf("\nWSUID: "); //Display Grade (currently unused)
			scanf("%s",wsuIDchoice);
			DisplayGrade(hwList,wsuIDchoice);
			break;
		case 2: PrintGrades(&hwList); //Print Grades
			break;
		case 3: BuildList(&hwList); //Build List
			break;
		case 4: StoreGrades(hwList); //Store grades to file
			break;
		case 5: EmptyList(&hwList); //Empty the list
			break;
		default: option = 0;
			 scanf("%s",garbage); //This handles stuff getting stuck in the buffer. Probably a better way to handle this
			 break;
	}
	}


	return 0;
}

void PrintGrades(cs460hwp* hw){
	cs460hwp* current = hw;
	while (current->nextPtr != NULL){
		current = current->nextPtr;
		printf("\n[%s] ",(*current).course);
		printf("%s:\n",(*current).wsuid);
		printf("subdate: %s ,",(*current).subdate);
		printf("points1: %f ,",(*current).points1);
		printf("points2: %f\n",(*current).points2);
	}

	return;
}

double CalculatePoints (char* duedt, char* subdt, double pts1)
{
	//Figure out how many days we are late by
	printf("%s %s\n",duedt,subdt); 
	int lateDays = LateByDays(duedt,subdt);
	printf("Late: %i\n",lateDays); //Testing stuff

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

int UserMenu(int *opt) //returns 1 on success
{
	int choice = 0;

	printf("\n");
	printf("1) Exit\n");
	printf("2) Print List\n");
	printf("3) Create List\n");
	printf("4) Store Grades\n");
	printf("5) Empty List\n");
	printf("6) Print Grades for ID\n");

	scanf("%i",&choice);
	if (0 < choice < 6){
		*opt = choice;
		return 1;
	}
	//else
	return 0;
}

void BuildList(cs460hwp* hw) //Creates a list using the node passed as the head.
{
	FILE *filePtr;
	cs460hwp* current = hw;

	filePtr = fopen("HW3input.dat","r"); //DAT FILE
	
	if (filePtr == NULL){ //Catch Error Case
		printf("Can't open file!\n");
		return;
	}

	fscanf(filePtr, "%d", &numStudents); //Get number of students
	printf("%d\n",numStudents);
	fscanf(filePtr, "%s", dueDate);
	printf("%s\n",dueDate);

	for (int i = 0; i < numStudents; i++){
		(*current).nextPtr = malloc(sizeof(cs460hwp));
		current = current->nextPtr;
		(*current).nextPtr = NULL;
		fscanf(filePtr,"%s %s %s %lf", (*current).course, (*current).wsuid, (*current).subdate, &(*current).points1);
		printf("%s %s %s %lf %lf\n",(*current).course, (*current).wsuid, (*current).subdate, (*current).points1, (*current).points2);
		(*current).points2 = CalculatePoints(dueDate,(*current).subdate, (*current).points1);
	}
	return;
}

void DisplayGrade(cs460hwp hw, char* id)
{
	cs460hwp* current = &hw;
	printf("%i",numStudents);
	for (int i = 0; i < numStudents; i++){
		current = current->nextPtr;
		printf("id: %s %s\n",(*current).wsuid, id);
		if (!(strcmp((*current).wsuid,id))){
			printf("%s %s %s %lf %lf\n",(*current).course, (*current).wsuid, (*current).subdate, (*current).points1, (*current).points2);
		}
	}
	return;
}

void StoreGrades(cs460hwp hw)
{
	FILE* filePtr;
	cs460hwp* current = &hw;

	filePtr = fopen("HW3output.dat","w"); //DAT FILE
	fprintf(filePtr, "%d\n", numStudents); //Get number of students
	fprintf(filePtr, "%s\n", dueDate);

	for (int i = 0; i < numStudents; i++){
		current = current->nextPtr;
		fprintf(filePtr, "%s %s %s %lf %lf\n",(*current).course, (*current).wsuid, (*current).subdate, ((*current).points1), ((*current).points2));
	}	
	return;
}

void ExitProg(cs460hwp* hw)
{
	EmptyList(hw);
	exit(0);
	return;
}


void EmptyList(cs460hwp* hw)
{
	if ((*hw).nextPtr != NULL){
		EmptyList((*hw).nextPtr);
		free((*hw).nextPtr);
	}
	return;
}
