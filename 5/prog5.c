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

//Prog#: 5
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

//Global Definitions

typedef struct nodeStruct{
	int number;
	char answer;
	char myAnswer;
	char question[200];
	struct nodeStruct* next;
} Node;

typedef struct{
	struct nodeStruct* top;
	int size;
} Stack;

//General Function Defs
void getId(char* id);
int getTestSelection();
void parseFile(FILE* inFile, Stack* stack);
void giveTest(Stack* stack, FILE* stuOut, FILE* testOut, char* stuId, int testNum); 
void initializeTestFile(char* name, int testNum);
void initializeStuFile(char* name, char* stuId);

//ADT Function Defs
Node* top(Stack* stack); //Returns pointer to the first node of the stack
Node* pop(Stack* stack); //Returns a pointer to the first node of the stack and removes it from the stack (does not deallocate)
void push(Node* node, Stack* stack); //Push a new node onto the stack. Memory must already be allocated for the node
Node* getNode(Stack* stack, int index); //Return a pointer to a node 'index' nodes deep
Stack* makeStack(); //Make an empty stack. Initializes everything to appropriate values.
void destroyStack(Stack* stack);

int main (void)
{
	//Local Declarations
	char tmp[100];
	char stuId[9];
	char inFileName[100];
	char testOutFileName[100];
	char stuOutFileName[100];
	int testSelection;
	FILE* inputFile;
	FILE* testOutputFile;
	FILE* stuOutputFile;

	//Initialize random numbers. Do this here so we know it won't happen more than once
	srand(time(NULL));

	do{
		Stack* myStack = makeStack();
		//Get student ID
		getId(stuId);
		//Get test selection
		testSelection = getTestSelection();

		//Open input file
		sprintf(inFileName,"Test%iquestions.txt",testSelection);
		inputFile = fopen(inFileName,"r");
		if (inputFile == NULL){ //Catch possible error condition
			printf("Failed to open %s for reading. This may indicate a permissions issue, or a non existent file. Terminating. \n",inFileName);
			exit(0);
		} //end if

		//Open test output file
		sprintf(testOutFileName,"Test%iscores.txt",testSelection);
		initializeTestFile(testOutFileName,testSelection);
		testOutputFile = fopen(testOutFileName,"a");
		if (testOutputFile == NULL){
			printf("Failed to open %s for appending. This should not happen and may indicate a permissions issue. Terminating. \n", testOutFileName);
			exit(0);
		} //end if


		//Open student output file
		sprintf(stuOutFileName,"%sresponses.txt",stuId);
		initializeStuFile(stuOutFileName,stuId);
		stuOutputFile = fopen(stuOutFileName, "a");
		if (stuOutputFile == NULL){
			printf("Failed to open %s for appending. This should not happen and may indicate a permissions issue. Terminating. \n", stuOutFileName);
			exit(0);
		} //end if

		//Parse input file
		//printf("Starting file parse...\n"); //Debug
		parseFile(inputFile,myStack);
		//printf("File parse successful! Questions are loaded. Giving test...\n"); //Debug

		//Give test
		giveTest(myStack, stuOutputFile, testOutputFile, stuId, testSelection);
		
		//Clean up
		destroyStack(myStack);
		
		//Continue?
		printf("New test? (Y/N): ");
		scanf("%s",tmp);
	}while(toupper(tmp[0])=='Y');
	return 0;
}

void initializeTestFile(char* name, int testNum)
{
	FILE* testFile = fopen(name, "r");
	if (testFile == NULL){
		testFile = fopen(name,"w");
		fprintf(testFile,"Test%i 0 0\n",testNum);
	}
	fclose(testFile);
	return;
}

void initializeStuFile(char* name, char* stuId)
{
	FILE* stuFile = fopen(name, "r");
	if (stuFile == NULL){
		stuFile = fopen(name,"w");
		fprintf(stuFile,"%s 0\n",stuId);
	}
	fclose(stuFile);
	return;
}

void giveTest(Stack* stack, FILE* stuOut, FILE* testOut, char* stuId, int testNum)
{
	//Local defintions
	char tmp[100];//Buffer to get the answer and grab any extra garbage so stuff doesn't get stuck in the input buffer
	int correct = 0;//Number of points so far
	time_t rawtime;//unix time
	struct tm* currentTime;//formatted time
	char buffer[80];//buffer for storing time
	
	//Time Stuff
	time(&rawtime);
	currentTime = localtime(&rawtime);
	strftime(buffer,80,"%Y-%m-%d", currentTime);//Now our time is in buffer
	
	//printf("Entering question asking sequence...\n"); //Debug
	for (int i = 0; i<5; i++) { //Loop through the questions
		printf("Getting random question.\n");
		Node* current = getNode(stack, rand()%(stack->size)); //Get a random node
		//printf("We have the node.\n"); //Debug
		printf("%s\n", current->question);
		printf("Answer: ");
		scanf("%s",tmp);//our answer is in tmp[0]
		tmp[0]=toupper(tmp[0]);//Force our answer to uppercase
		if (tmp[0] == current->answer)
			correct++; //Give points if right answer
		//Print to the file (Test# qnum, answer, date)
		fprintf(stuOut,"Test%i %i %c %s\n", testNum, current->number, tmp[0], buffer);
	}//end while

	//Print to the test file (per test lists of students)
	fprintf(testOut,"%s %i %s\n", stuId, correct, buffer);
	return;
}
void parseFile(FILE* inFile, Stack* stack)
{
	int qCount;
	char testTitle[100];

	fscanf(inFile,"%s %i",testTitle, &qCount);
	for (int i = 0; i<qCount; i++){
		Node* current = malloc(sizeof(Node));
		//printf("Reading file line...\n"); //Debug
		fscanf(inFile,"%i %c %[^\n]", &(current->number), &(current->answer), current->question);
		//printf("Line read: %i %c %s Pushing...\n",current->number, current->answer, current->question); //Debug
		push(current, stack);
	}
	return;
}

void getId(char* id)
{
	printf("Enter ID: ");
	scanf("%s",id);
	return;
}

int getTestSelection(){
	int selection;
	//Prompt the user until they give us a valid selection
	do{
		printf("Ten tests are available. Select a test: ");
		scanf("%i",&selection);
		if (!(0 < selection <= 10))
			printf("Invalid Selection. Try again.\n");
	} while (!(0 < selection <= 10)); 
	//Return the known valid selection
	return selection;
}

Node* top(Stack* stack)
{
	if (stack == NULL)
		return NULL;
	return stack->top;
}

Node* pop(Stack* stack)
{
	//Error Case
	if (stack == NULL)
		return NULL;
	//Empty Stack Case
	if (stack->top == NULL)
		return NULL;
	//Non empty Stack case
	Node* oldTop = stack->top;
	stack->top = stack->top->next;
	stack->size--;
	return oldTop;
}

void push(Node* node, Stack* stack)
{
	node->next = stack->top;
	stack->top = node;
	stack->size++;
	return;
}

Node* getNode(Stack* stack, int index)
{
	//An index greater than the number of items in the stack is an error
	if (index > stack->size)
		return NULL;
	//Loop through and get the node we need
	Node* current = stack->top;
	for (int i = 1; i<index; i++)
		current = current->next;
	return current;
}

Stack* makeStack()
{
	Stack* current = malloc(sizeof(Stack));
	current->size = 0;
	current->top = NULL;
	return current;
}

void destroyStack(Stack* stack)
{
	Node* current = NULL;

	do{
		current = pop(stack);
		if (current != NULL)
			free(current);
	}while (current !=NULL);
	free(stack);
	return;
}
