//Prog#: 10
//Names: Jared Hess, Brian Coffman, Travis Whitty
//

//Just general useful stuff
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>
#include <limits.h>

//My files
//#include "avl.h"

//Structure Definitions
typedef struct Movie
{
	char title[100];
	char genre[100];
	int number;
} movie;
//typedef struct Movie movie;

typedef struct List
{
	movie* data;
	struct List *next;
} node;
//typedef struct List node;

//Function Prototypes
char MainMenu(void);
void BuildDatabase(char* filename, node* root);
movie* AddItemMenu(void);
void AddItem(node* root, movie* item);

char* NameMenu(void);
movie* FindByName(node* root, char* name);

int NumMenu(void);
movie* FindByNum(node* root, int number);

//Global Defs


int main()
{
	//Local vars
	char* mainMenuEntries;
	char choice = '0';
	char dbFileName[] = "movieDB.jedi";
	movie* current;

	//Others
	node root;
	root.next=NULL;

	while(choice != '1'){
		choice = MainMenu();
		switch(choice){
			case '2': //Build database
								BuildDatabase(dbFileName, &root);
								break;
			case '3': //Add Item
								AddItem(&root, AddItemMenu());
								break;
			case '4': //Find by name
								current = FindByName(&root, NameMenu());
								break;
			case '5': //Find by number
								current = FindByNum(&root, NumMenu());
								break;
			case '6': //Write to file
								break;
		}//Switch
	}//While


	return 0;

}

char MainMenu(void)
{
	char buffer[100];
	printf("1) Exit\n");
	printf("2) Build Database from File\n");
	printf("3) Add Item \n");
	printf("4) Find Item by Name \n");
	printf("5) Find Item by Number \n");
	printf("6) Write Database to File\n");

	printf("Enter selection: ");
	scanf("%s",buffer);

	return buffer[0];
}

void BuildDatabase(char* filename, node* root)
{
	char buffer[200];
	int number;
	char genre[100];
	char title[100];
	FILE* pfile = fopen(filename,"r");
	//while(fgets(buffer,200,pfile) != EOF){
	while(fscanf(pfile,"%i,%s,%s",&number,genre,title) != EOF){
		movie* myMovie = malloc(sizeof(movie));
		myMovie->number = number;
		memcpy(myMovie->title,title,sizeof(title));
		memcpy(myMovie->genre,genre,sizeof(genre));
		AddItem(root, myMovie);
	}
	return;
}

movie* AddItemMenu(void)
{
	movie* myMovie = malloc(sizeof(movie));
	printf("Title: ");
	scanf("%s",myMovie->title);
	printf("Genre: ");
	scanf("%s",myMovie->genre);
	printf("Number: ");
	scanf("%i", myMovie->number);

	return myMovie;
}

void AddItem(node* root, movie* item)
{
	node* myNode = malloc(sizeof(node));
	node* tmp = root->next;
	root->next = myNode;
	myNode->next = tmp;
	myNode->data = item;
	return;
}

char* NameMenu(void)
{
	char* myString = malloc(20*sizeof(char));
	printf("Enter Name of Movie: ");
	scanf("%s", myString);
	return myString;
}

movie* FindByName(node* root, char* name)
{
	node* current = root->next;
	int found = 0;
	while ((current != NULL) && !found){
		if (!strcmp(name, current->data->title)){
			found = 1;
		}else{
			current = current->next;
		}
	}//while
	if (!found){
		printf("Match not found!\n");
		return NULL;
	}
	return current->data;
}

int NumMenu(void)
{
	int myInt;
	printf("Enter the movie number (UPC Code): ");
	scanf("%i",&myInt);
	return myInt;
}

movie* FindByNum(node* root, int number)
{
	node* current = root->next;
	int found = 0;
	while ((current != NULL) && !found){
		if (number == current->data->number){
			found = 1;
		} else {
			current = current->next;
		}
	}//while
	if (!found){
		printf("Match not found!\n");
		return NULL;
	}
	return current->data;
}


