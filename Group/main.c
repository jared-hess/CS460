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
void AsciiSplash(void);
void BuildDatabase(char* filename, node* root);
void WriteDatabase(char* filename, node* root);
movie* AddItemMenu(void);
void AddItem(node* root, movie* item);

char* NameMenu(void);
node* FindByName(node* root, char* name);

int NumMenu(void);
node* FindByNum(node* root, int number);

int DelMenu(void);

void PrintMovie(movie* item);
void DumpDatabase(node* root);
void DelItem(node* item);

int main()
{
	//Local vars
	char* mainMenuEntries;
	char choice = '0';
	char dbFileName[] = "movieDB.jedi";
	node* current;

	//Others
	node root;
	root.next=NULL;

	//Splash
	AsciiSplash();

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
								PrintMovie(current->data);
								break;
			case '5': //Find by number
								current = FindByNum(&root, NumMenu());
								PrintMovie(current->data);
								break;
			case '6': //Write to file
								WriteDatabase(dbFileName, &root);
								break;
			case '7': //Delete item
								switch (DelMenu()){
									case '1': DelItem(FindByName(&root, NameMenu()));
													  break;
									case '2': DelItem(FindByNum(&root, NumMenu()));
														break;
								}
								break;
			case '9': //Dump Database
								DumpDatabase(&root);
								break;
		}//Switch
	}//While
	return 0;
}

int DelMenu(void)
{
	char buffer[100];
	printf("1) Delete by name\n");
	printf("2) Delete by number\n");
	printf("\n");
	printf("Enter selection: ");
	scanf("%s",buffer);

	return buffer[0];
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
	printf("7) Delete movie \n");
	printf("\n");
	printf("Enter selection: ");
	scanf("%s",buffer);

	return buffer[0];
}

void AsciiSplash(void)
{
	printf("*********************************************\n");
	printf("*          Movie Store Database             *\n");
	printf("* DB File: movieDB.jedi                     *\n");
	printf("* Authors: Jared Hess                       *\n");
	printf("*          Travis Whitty                    *\n");
	printf("*          Brian Coffman                    *\n");
	printf("*********************************************\n");
	printf("\n");
}

void DelItem(node* item)
{
	return;
}

void WriteDatabase(char* filename, node* root)
{
	node* current = root->next;
	FILE* pfile = fopen(filename,"w");
	while (current != NULL){
		fprintf(pfile,"%i,%s,%s\n",current->data->number,current->data->genre,current->data->title);
		current = current->next;
		printf("In loop!\n");
	}
	fclose(pfile);
	return;
}
void BuildDatabase(char* filename, node* root)
{
	char buffer[200];
	int number;
	char* strNum;
	char* genre;
	char* title;
	FILE* pfile = fopen(filename,"r");
	while(fgets(buffer,200,pfile) != NULL){
	//while(fscanf(pfile,"%i,%99[0-9a-zA-Z ]s,%99[0-9a-zA-Z ]s",&number,genre,title) != EOF){
		strNum = strtok(buffer,",");
		genre = strtok(NULL,",");
		title = strtok(strtok(NULL,","),"\n");
		number = atoi(strNum);
		printf("%i,%s,%s\n",number,genre,title);
		movie* myMovie = malloc(sizeof(movie));
		myMovie->number = number;
		strcpy(myMovie->title,title);
		strcpy(myMovie->genre,genre);
		//memcpy(myMovie->title,title,sizeof(title));
		//memcpy(myMovie->genre,genre,sizeof(genre));
		AddItem(root, myMovie);
	}
	fclose(pfile);
	return;
}

movie* AddItemMenu(void)
{
	printf("\nEnter movie information...\n");
	movie* myMovie = malloc(sizeof(movie));
	scanf("%*c");
	printf("Title: ");
	//scanf("%s",myMovie->title);
	scanf("%99[0-9a-zA-Z ]s", myMovie->title);
	//fgets(myMovie->title,100*sizeof(char),stdin);
	scanf("%*c");
	printf("Genre: ");
	//scanf("%s",myMovie->genre);
	scanf("%99[0-9a-zA-Z ]s", myMovie->genre);
	//fgets(myMovie->genre,100*sizeof(char),stdin);
	scanf("%*c");
	printf("Number: ");
	scanf("%i", &(myMovie->number));

	return myMovie;
}

void PrintMovie(movie* item)
{
	printf("\nTitle: %s\n",item->title);
	printf("Genre: %s\n",item->genre);
	printf("Number: %i\n",item->number);
	printf("\n");
	return;
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
	char* myString = malloc(100*sizeof(char));
	scanf("%*c");
	printf("Enter Name of Movie: ");
	//fgets(myString,100*sizeof(char),stdin);
	scanf("%99[0-9a-zA-Z ]s",myString);
	return myString;
}

node* FindByName(node* root, char* name)
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
	return current;
}

int NumMenu(void)
{
	int myInt;
	printf("Enter the movie number (UPC Code): ");
	scanf("%i",&myInt);
	return myInt;
}

node* FindByNum(node* root, int number)
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
	return current;
}

void DumpDatabase(node* root)
{
	node* current = root->next;
	while (current != NULL){
		PrintMovie(current->data);
		printf("\n");
		current = current->next;
	}
	return;
}
