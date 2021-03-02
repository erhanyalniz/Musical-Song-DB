//Erhan Yalnýz  -  150117905
//The purpose of this program is to create a musical song database and to make the music in this database available to the user with the necessary information, rankings and features.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char filePath[50];

//Song struct with required nodes and variables
struct node{
	char songName[25];
	int duration;
	struct node *chrono_next;
	struct node *alpha_next;
	struct node *duration_next;
	struct node *random_next;
};
//Creating four head pointers that show the starting node based on the target order.
struct node *chrono_head = NULL;
struct node *alpha_head = NULL;
struct node *duration_head = NULL;
struct node *random_head = NULL;
//To insert a new node to list.
void insertNode(char songName[] , int duration) {
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	strcpy(newNode->songName, songName);
	newNode->duration = duration;
	newNode->chrono_next = NULL;
	newNode->alpha_next = NULL;
	newNode->duration_next = NULL;
	newNode->random_next = NULL;
	
	if (chrono_head == NULL) {
		chrono_head = newNode;
		alpha_head = newNode;
		duration_head = newNode;
		return;
	}
	
	//Chronologic list
	struct node *iterator = chrono_head;
	while (iterator->chrono_next != NULL)
		iterator = iterator->chrono_next;	
	iterator->chrono_next = newNode;
	
	
	//Alphabetic list
	iterator = alpha_head;
	if (strcmp(alpha_head->songName, newNode->songName) > 0) {
		newNode->alpha_next = alpha_head;
		alpha_head = newNode;
	} else {
		while (iterator->alpha_next != NULL && strcmp(iterator->alpha_next->songName, newNode->songName) < 0) {
			iterator = iterator->alpha_next;
		}
		
		newNode->alpha_next = iterator->alpha_next;
		iterator->alpha_next = newNode;
	}
	
	//Duration list
	iterator = duration_head;
	if (duration_head->duration > newNode->duration) {
		newNode->duration_next = duration_head;
		duration_head = newNode;
	} else {
		while (iterator->duration_next != NULL && iterator->duration_next->duration < newNode->duration) {
			iterator = iterator->duration_next;
		}
		
		newNode->duration_next = iterator->duration_next;
		iterator->duration_next = newNode;
	}
}


//This function deletes node with the given songName
void deleteNode(char songName[]){
	int i = 0;
	struct node* iterator = chrono_head;
	//Iterate over one linked list until songNames match and if matches delete that node
	while(iterator!=NULL){
		if(strcmp(songName,iterator->songName)==0){
			struct node* oldNode = iterator;
			iterator = oldNode->chrono_next;
			free(oldNode);
			if(i==0){
				chrono_head = iterator;
			}
			break;
		}
		iterator = iterator->chrono_next;
		i++;
	}
}

//This function will print songs in chronological order
void printChrono() {
	int id = 1;
	printf("The list in chronological order:\n");
	struct node *iterator = chrono_head;
	//Iterate over whole linked list and print if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			printf("%d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->chrono_next;
	}
}

//This function will print songs in alphabetical order
void printAlpha() {
	int id = 1;
	printf("\n\nThe list in alphabetical order:\n");
	struct node *iterator = alpha_head;
	//Iterate over whole linked list and print if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			printf("%d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->alpha_next;
	}
}

//This function will print songs in duration-time order
void printDuration() {
	int id = 1;
	printf("\n\nThe list in duration-time order:\n");
	struct node *iterator = duration_head;
	//Iterate over whole linked list and print if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			printf("%d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->duration_next;
	}
}

//This function will generate a linked list with random songs
void createRandom() {
	int max = 1,i = 0,j;
	struct node *iterator = chrono_head;
	struct node *randomIterator = random_head; 
	struct node *startOfRandom = random_head;
	//Get song number by iterating over whole linked list
	while(iterator->chrono_next!=NULL){
		iterator = iterator->chrono_next;
		max++;
	}
	//Iterate till all linked list is filled with the same number of songs
	while(i<max-1){
		int choosen = rand()%(max)+1;
		int flag=1;
		iterator = chrono_head;
		//Find the choosen random song
		for(j=1;j<choosen;j++){
			iterator = iterator->chrono_next;
		}
		randomIterator = random_head;
		//Find out if randomized list already containing current choosen random song and if contained then set flag to 0
		while(randomIterator!=NULL){
			if(strcmp(randomIterator->songName,iterator->songName)==0){
				flag = 0;
				break;
			}
			randomIterator = randomIterator->random_next;
		}
		//If current choosen random song isn't contained within randomized list then increment count and insert element to randomized list
		if(flag){
			i++;
			startOfRandom = (struct node*)malloc(sizeof(struct node));
			strcpy(startOfRandom->songName,iterator->songName);
			startOfRandom->duration = iterator->duration;
			startOfRandom = startOfRandom->random_next;
		}
	}
}

//This function will generate and print randomized list
void printRandom() {
	//Generate randomized list
	createRandom();
	int id = 1;
	printf("\n\nThe list in random order:\n");
	struct node *iterator = random_head;
	//Iterate over whole linked list and print if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			printf("%d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->random_next;
	}
}

//This function will create file with the name filePath and write chronological list to it
void writeChrono() {
	//Overwrite file
	FILE *file = fopen(filePath, "w");
	int id = 1;
	fprintf(file, "The list in chronological order:\n");
	struct node *iterator = chrono_head;
	//Iterate over whole linked list and write to file if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			fprintf(file, "        %d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->chrono_next;
	}
	fclose(file);
}

//This function will appent to a file with the name filePath and write alphabetical list to it
void writeAlpha() {
	FILE *file = fopen(filePath, "a");
	int id = 1;
	fprintf(file, "\n\nThe list in alphabetical order:\n");
	struct node *iterator = alpha_head;
	//Iterate over whole linked list and write to file if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			fprintf(file, "        %d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->alpha_next;
	}
	fclose(file);
}

//This function will appent to a file with the name filePath and duration-time list to it
void writeDuration() {
	FILE *file = fopen(filePath, "a");
	int id = 1;
	fprintf(file, "\n\nThe list in duration-time order:\n");
	struct node *iterator = duration_head;
	//Iterate over whole linked list and write to file if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			fprintf(file, "        %d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->duration_next;
	}
	fclose(file);
}

//This function will appent to a file with the name filePath and write generated randomized list to it
void writeRandom() {
	//Generate randomized list
	createRandom();
	FILE *file = fopen(filePath, "a");
	int id = 1;
	fprintf(file, "\n\nThe list in random order:\n");
	struct node *iterator = random_head;
	//Iterate over whole linked list and write to file if name is not null
	while (iterator != NULL ) {
		int minute = iterator->duration / 60;
		int second = iterator->duration % 60;
		if(iterator->songName[0]!='\0'){
			fprintf(file, "        %d.%s %d:%d\n", id++, iterator->songName, minute, second);
		}
		iterator = iterator->random_next;
	}
	fclose(file);
}

//This function will combine all of write functions and user input and save to playlist
void writeFile() {
	printf("Enter a file name:\n");
	scanf(" %[^\n]s",filePath);
	getchar();
	printf("Output is printed to the file %s\n",filePath);
	writeChrono();
	writeAlpha();
	writeDuration();
	writeRandom();
}

//This function will create menu and print options
void menu(){
	printf("\nEnter your choice:\n");
	printf("1 to insert a song into the list.\n");
	printf("2 to delete a song from the list.\n");
	printf("3 to print the songs in the list.\n");
	printf("4 to print the songs to an output file.\n");
	printf("5 to end.\n");
}

int main(void) {
	//Read from songs.txt
	FILE *filePointer = fopen("songs.txt" , "r");
    char buffer[50];
    char *input;
    char inputsArray[2][30];
    int i = 0, minute, second;
    char *duration;
    char durations[2][5];
    int flag = 0;
    int choice;
    //Read line by line to buffer and parse songs
	while (fgets(buffer, 50, filePointer)) {
		i = 0;
		//parse first token (name of song) to input
		input = strtok(buffer, "\t");
		while( input != NULL ) {
			//copy name to inputsArray[0] and duration token to inputsArray[1]
			strcpy(inputsArray[i++], input);
			//get next token
	      	input = strtok(NULL, "\t");
	    }
	    
	    i = 0;
	    flag = 0;
		//start parsing duration token
	    duration = strtok(inputsArray[1], ":");
	    while (duration != NULL) {
			//copy parsed strings to duration
	    	strcpy(durations[i++], duration);
	    	//Check if this one is the first token if so parse it to minute
	    	if (flag == 0) {
	    		minute = atoi(durations[0]);
	    		flag = 1;
	    	}
			//parse next token
	    	duration = strtok(NULL, ":");
		}
		//Parse second from durations
		second = atoi(durations[1]);
		//Calculate total seconds from minute and second
		int total = minute * 60 + second;
		//Create new node and insert
	    insertNode(inputsArray[0], total);
	}
	//Print playlists for first time
	printChrono();
	printAlpha();
	printDuration();
	printRandom();
	do {
		char oldSongName[25];
		//Print options to inform user
		menu();
		
		//get choosen option
		scanf("%d" , &choice);
		
		switch(choice) {
			case 1:
				printf("Enter a song name with duration: \n");
				//Read whole line to buffer
				scanf(" %[^\n]s",buffer);
				i = 0;
				//Parse using tokens just like how it is done before
				//Split tokens by tab
				input = strtok(buffer, "\t");
				while( input != NULL ) {
					//copy name to inputsArray[0] and duration token (M:S format) to inputsArray[1]
					strcpy(inputsArray[i++], input);
					//get next token
	      			input = strtok(NULL, "\t");
	    		}

	    		i = 0;
	    		flag = 0;
				//start parsing duration token
	    		duration = strtok(inputsArray[1], ":");
	    		while (duration != NULL) {

	    			strcpy(durations[i++], duration);
	    			//Check if this one is the first token if so parse it to minute
	    			if (flag == 0) {
	    				minute = atoi(durations[0]);
	    				flag = 1;
	    			}
					//parse next token
	    			duration = strtok(NULL, ":");
				}
				//Parse second from durations
				second = atoi(durations[1]);
				//Calculate total seconds from minute and second
				int total = minute * 60 + second;
	    		//Consume \n character from stdin
				getchar();
				//Create new node and insert
				insertNode(inputsArray[0], total);
				break;
		case 2:
			printf("Enter a song name:\n");
			//Read whole line
			scanf(" %[^\n]s",oldSongName);
			//Consume \n character from stdin
			getchar();
			//Delete node with name oldSongName
			deleteNode(oldSongName);
			//Inform user that node is deleted
			printf("The song \"%s\" is deleted from the list!\n",oldSongName);
			break;
		case 3:
			//Print all playlists
			printChrono();
			printAlpha();
			printDuration();
			printRandom();
			break;
		case 4:
			//Write all playlists
	    	writeFile();
			break;
	    case 5:
			//Exit program
	    	printf("Good Bye...");
	    	exit(0);
	    	break;
		}
	} while (choice < 6);
	//if choice isn't valid exit program
	if(choice >= 6){
		printf("Your choice is unvalid... Try again later...\n");
		exit(0);
	}
}

