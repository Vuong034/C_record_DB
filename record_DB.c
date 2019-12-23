#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studentdb.h"

//global variables
static int naccess = 0;
static int maxrecords = 0;

//function prototypes
int menu();
int printAllRecords(struct student *mover,struct student *hdptr);
int printnRecords(struct student *mover,struct student *hdptr);
struct student * addRecord(struct student *mover,struct student *hdptr);
struct student * deleteRecord(struct student *mover,struct student *hdptr);

int main(void){

	menu();
	return 0;
}

int menu(){

	char sel;
	char buf[32];	
	struct student *hdptr;
	struct student *mover;	
	
//initialize database with 5 records
	maxrecords+=5;
	hdptr = (struct student *)malloc(sizeof(struct student)*maxrecords);

	//copy struct elements to preallocated memory
	mover = hdptr;
	memcpy(mover, &student1, sizeof(*hdptr));
	mover++;
	memcpy(mover, &student2, sizeof(*hdptr));
	mover++;
	memcpy(mover, &student3, sizeof(*hdptr));
	mover++;
	memcpy(mover, &student4, sizeof(*hdptr));
	mover++;
	memcpy(mover, &student5, sizeof(*hdptr));
//
	//loop until user inputs quit option
	while (1){ 

		printf("\nMENU\n");
	        printf("=====\n");
	        printf("Enter selection :\n 1: Print all records \n 2: Print number of records \n 3: Print size of database \n 4: Add record \n 5: Delete record \n 6: Prints number of accesses to database\n 7: Quit\n");
	
		//reads line as string and puts it in buffer
		if(fgets(buf,sizeof(buf),stdin) == NULL){
			perror("Error: Input exceeds buffer");
		}
		//convert buffer to int
		sel = atoi(buf);

		//menu options 
		switch(sel){
			case 1: printAllRecords(mover,hdptr);
				break;
			case 2: printnRecords(mover, hdptr);
				break;			
			case 3: fprintf(stderr,"Current size of Database: %d records",maxrecords);
				break;
			case 4: hdptr = addRecord(mover, hdptr);
				break;
			case 5: hdptr = deleteRecord(mover, hdptr);
				break;
			case 6: fprintf(stderr,"Number of accesses to database: %d\n", naccess);
				break;
			case 7: fprintf(stderr,"quitting\n");
				//free allocated memory and quit
				free(hdptr);
				return 0;
			default: fprintf(stderr,"Please input a valid option\n\n");
				break;
			
		}//switch
		
	    }//while

}

int printAllRecords(struct student *mover,struct student *hdptr){
	
	//set mover as head
	mover = hdptr;
	//check record count then print records
	if(maxrecords !=0){
		fprintf(stderr,"\n All records in database\n");	
		for(int i = 0; i<maxrecords;i++){		
			fprintf(stderr," firstname: %s",mover->firstname);
			fprintf(stderr," last name: %s",mover->lastname);	
			fprintf(stderr," id: %d\n",mover->id);	
			mover++;
		}
		//access count
		naccess++;
	}else if(maxrecords == 0){
		fprintf(stderr,"Nothing in the database\n");
		//access count
		naccess++;
		return 0;		
	}else{
		perror("Error: Can not read database\n");
		return 0;	
	}
	
}
int printnRecords(struct student *mover,struct student *hdptr){

	int n;
	char buf[10];
	
	//get number of records to print
	fprintf(stderr,"Please enter a number of records to print: (current # of records %d)\n", maxrecords);
	if(fgets(buf,sizeof(buf),stdin) == NULL){
		perror("Error: Input exceeds buffer");
	}
	//convert buffer to int
	n = atoi(buf);
	//check valid record range to print
	if(n <= maxrecords && n!= 0){
		fprintf(stderr,"\n Printing %d records:\n",n);	
		//set mover as head
		mover = hdptr;
		for(int i = 0; i<n;i++){		
			fprintf(stderr," firstname: %s",mover->firstname);
			fprintf(stderr," last name: %s",mover->lastname);	
			fprintf(stderr," id: %d\n",mover->id);	
			mover++;
		}
		//access count
		naccess++;
	}else{
		fprintf(stderr, "input not valid\n");
		return 0;
	}
}

struct student* addRecord(struct student *mover,struct student *hdptr){

	//record input var
	char buf[60];
	char tempfirst[25]; 
	char templast[25]; 
	int tempid;	
	//create new struct student, add values, add to pointer
	struct student studenta;
	//temp struct mem pointer
	struct student *temp;

	fprintf(stderr,"Please enter first name, last name, and id seperated by a space\n");
	if(fgets(buf,sizeof(buf),stdin) == NULL){
		perror("Error: Input exceeds buffer");
		return hdptr;
	}
	//get user input for new record
	if(sscanf(buf,"%s %s %d", tempfirst, templast, &tempid) != 3){
		fprintf(stderr,"Input not valid\n");
		return hdptr;	
	}

	//put input into struct 
	memcpy(studenta.firstname, &tempfirst, 25);
	memcpy(studenta.lastname, &templast, 25);
	studenta.id = tempid;
	//create temp storage
	temp = (struct student *)malloc(sizeof(struct student)*maxrecords);
	int tempsize = maxrecords;
	//copy old student list in temp memory
	memcpy(temp, hdptr, sizeof(struct student)*tempsize);
	//free old hdptr
	free(hdptr);
	//increase max size by 1, reallocate new hdptr with size
	maxrecords++;
	//access count
	naccess++;
	hdptr = (struct student *)malloc(sizeof(struct student)*maxrecords);
	//copy all temp values back to hdptr
	memcpy(hdptr, temp, sizeof(struct student)*tempsize);
	//point mover to last free space
	mover = hdptr;
	mover+=tempsize; 
	//add student to mover
	memcpy(mover,&studenta,sizeof(*hdptr));

	fprintf(stderr,"student added to record: firstname: %s",mover->firstname);
	fprintf(stderr," last name: %s",mover->lastname);	
	fprintf(stderr," id: %d\n",mover->id);	

	//free temp
	free(temp);

	return hdptr;

}

struct student* deleteRecord(struct student *mover,struct student *hdptr){//deletes last record
		
	//temp struct mem pointer
	struct student *temp;
	//checks if record number is valid before deleting
	if(maxrecords > 0){
		//create temp storage
		temp = (struct student *)malloc(sizeof(struct student)*maxrecords);
		//copy old student list in temp memory
		memcpy(temp, hdptr, sizeof(struct student)*maxrecords);
		//free old hdptr
		free(hdptr);
		//increase max size by 1, reallocate new hdptr with size
		maxrecords--;
		//access count
		naccess++;
		hdptr = (struct student *)malloc(sizeof(struct student)*maxrecords);
		//copy temp values back to hdptr
		memcpy(hdptr, temp, sizeof(struct student)*maxrecords);

		fprintf(stderr,"record in database deleted\n");	
	
		//free temp
		free(temp);
	}else{
		fprintf(stderr, "No records to delete!");
	}

	return hdptr;

}
