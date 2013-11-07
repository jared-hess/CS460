/*
   The proceeding code was authored by:

         d88b d8888b. db   db d88888b .d8888. .d8888.
        `8P' 88  `8D 88   88 88'     88'  YP 88'  YP
        88  88   88 88ooo88 88ooooo `8bo.   `8bo.
        88  88   88 88~~~88 88~~~~~   `Y8b.   `Y8b.
   db. 88  88  .8D 88   88 88.     db   8D db   8D
   Y8888P  Y8888D' YP   YP Y88888P `8888Y' `8888Y'

   Created for the fulfillment of the requirements for CS460 and should hereafter be considered to be released under the terms of the GNU GPL version 3.
   */

//Prog#: 4
//Name: Hess,Jared
//WSUID: N575U698
//Email: jdhess@wichita.edu

//Notes for the grader:
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Global Definitions

typedef int ElementType;
struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node{
	ElementType Element;
	Position Prev;
	Position Next;
};

//Fuction Defs
char UserMenu(char* opt);
void ExitProg(void);

void BuildList(List L, FILE* fpi);
void MakeEmptyList(List L);
void DisplayList(List L);
void InsertItem(ElementType X, List L, Position P);
void DeleteItem(ElementType X, List L);
void SaveList(List L, FILE* fpo);
void DestroyList(List L);

int IsEmpty(List L);
int IsFirst(Position P, List L);
int IsLast(Position P, List L);
Position FindItemPos(ElementType X, List L);
void DeleteList(List L);

int main (void)
{
	List myList = malloc(sizeof(struct Node));
	MakeEmptyList(myList);

	char choice;
	char inFileName[] = "prog04in.dat";
	char outFileName[] = "prog04out.dat";
	FILE* inFile;
	FILE* outFile;

	int itemChoice;

	while (UserMenu(&choice) != 1){

		char garbage[100];
		//UserMenu (&choice);
		switch(choice){
			case '1': ExitProg();
				  break;
			case '2': MakeEmptyList(myList);
				  break;
			case '3': inFile = fopen("prog04in.dat","r");
				  printf(" check infFile = %p \n", inFile);
				  if (inFile == NULL){
					  printf("Could Not Open File\n");
					  exit(0);
				  }
				  BuildList(myList,inFile);
				  fclose(inFile);
				  break;
			case '4': DisplayList(myList);
				  break;
			case '5': printf("\nItem to find: ");
				  scanf("%i", &itemChoice);
				  if (FindItemPos(itemChoice, myList) != NULL)
					  printf("exists\n");
				  else
					  printf("does not exist\n");
				  break;
			case '6': printf("\nItem to insert: ");
				  scanf("%i", &itemChoice);
				  InsertItem(itemChoice, myList, myList);
				  break;
			case '7': printf("\nItem to delete: ");
				  scanf("%i", &itemChoice);
				  DeleteItem(itemChoice, myList);
				  break;
			case '8': if(NULL == (outFile = fopen(outFileName,"w"))){
					  printf("Failed to open file for writing!\n");
					  exit(0);
				  }
				  SaveList(myList, outFile);
				  fclose(outFile);
				  break;
			case '9': DestroyList(myList);
				  break;
			default: ExitProg();
				 break;
		}//End Switch
	}//End while
	return 0;
}

char UserMenu(char* opt)
{
	char buffer[100];

	printf("\nOptions:\n\n");
	printf("1) Exit\n");
	printf("2) Make an empty list\n");
	printf("3) Build list using file 'prog04in.dat'\n");
	printf("4) Display the list\n");
	printf("5) Find an item\n");
	printf("6) Insert an item\n");
	printf("7) Delete an item\n");
	printf("8) Save the list in file 'prog04out.dat'\n");
	printf("9) Destroy the list\n");

	printf("\nYour selection: ");

	scanf("%s",buffer);
	*opt = buffer[0];

	return *opt;
}
void ExitProg(void)
{
	exit(0);
	return;
}

void BuildList(List L, FILE* fpi)
{
	int item;
	struct Node* previous = NULL;
	struct Node* current = L;

	while (fscanf(fpi,"%i",&item) != EOF){ //While a new item exists
		current->Next = malloc(sizeof(struct Node));//Allocate a new node
		previous = current; //Shift to this node
		current = current->Next; //Save current position to set Prev in new node
		current->Prev = previous; 
		current->Next = NULL; //No next yet
		current->Element = item; //Set the item
	}//End while
	return;
}

void MakeEmptyList(List L) //An empty list is just the head. Which we already have. So this function just makes sure that the pointers are correctly set for an empty list.
{
	L->Prev = NULL;
	L->Next = NULL;
	return;
}

void DisplayList(List L)
{
	if (L->Next != NULL){
		printf("%i\n",L->Next->Element);
		DisplayList(L->Next);
	}
	return;
}

void InsertItem(ElementType X, List L, Position P)
{
	//Insert this element aftter pos P
	//Create a new node
	struct Node* newNode = malloc(sizeof(struct Node));
	newNode->Element = X;

	if (P->Next != NULL)
		P->Next->Prev = newNode;	
	newNode->Prev = P;
	newNode->Next = P->Next;
	P->Next = newNode;
	
	return;
}

void DeleteItem(ElementType X, List L)
{
	if (L->Element == X){ //If current element is X, delete the node
		L->Prev->Next = L->Next;
		if (L->Next != NULL) //If we aren't deleting the last elment in the list, set the next items back pointer
			L->Next->Prev = L->Prev;
		free(L);
	}else if (L->Next != NULL) { //If Next node is not NULL, check it
		DeleteItem(X,L->Next); //recurse
	}//end if
	return; //If we reach NULL, we reach the end of the list without finding it. Nothing is done.
}

void SaveList(List L, FILE* fpo)
{
	if (L->Next != NULL){
		fprintf(fpo,"%i\n",L->Next->Element);
		SaveList(L->Next, fpo);
	}
	return;
}


void DestroyList(List L)
{
	if (L->Next != NULL)
		DestroyList(L->Next);
		L->Next = NULL;
	free(L);
	return;
}

int IsEmpty(List L)
{
	if (L->Next == NULL)
		return 1;
	else
		return 0;
}

int IsFirst(Position P, List L)
{
	if (L->Prev == NULL)
		return 1;
	else
		return 0;
}

int IsLast(Position P, List L)
{
	if (L->Next == NULL)
		return 1;
	else
		return 0;
}

Position FindItemPos(ElementType X, List L)
{
	if (L == NULL)
		return NULL;
	else if (L->Element == X)
		return L;
	else
		return FindItemPos(X, L->Next);
}

void DeleteList(List L)
{
	DestroyList(L->Next);
	L->Next = NULL;
	L->Prev = NULL;
	return;
}

