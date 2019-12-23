Record DB Program
Nam Vuong
vuong034@umn.edu

Included files:
Studentdb.h - header file
readme.txt - readme document
record_DB.c - source code
record_DB_script - script file

Program description:
Program starts by initializing the database with 5 students from the header file. A hdptr is allocated using the 5 student records. Each student is then copied to the address of the hdptr via a mover and the mover increments by the size of a student struct after each copy. The menu function then prompts for user input. Variables naccess and maxrecords are global and keep track of accesses to the database and the maximum number of records while the program is active. Their respective options 3 and 6 do not call functions, instead print the current values of the variables while the program is active. When the user is finished and chooses to quit, the hdptr is freed from memory;

Usage statement:
Compile code using gcc and run through command line
When prompted for user input, select 1-7 for the desired option or 7 to quit program.

Data Structure:
Student struct- 
typedef struct student{
    char firstname[25];
    char lastname[25];
    int id;
}

naccess-
static int naccess = 0;

maxrecords-
static int maxrecords = 0;

Function descriptions:
Main-
Calls menu function. Returns when menu function is done.
Menu Function-
Prints prompts and takes user input within a while loop. Takes user input and converts it to an integer. Then selects the correct function matching the user input using a switch case. If the user inputs 7, the function returns to main and exits the program.

printAllRecords-
The mover and hdptr student struct pointers are passed in and mover is reset as the head.
Then the function checks if maxrecords has a positive value, zero, or neither. The function loops through using the mover pointing at the hdptr and prints each record until the maxrecords is reached. 

printnRecords-
The user is prompted to enter a number of records to print. The function checks input if it is within the valid range, then loops through and prints until the number specified is reached. Function returns if input is invalid.

addrecord-
User is prompted to enter the first anme, last name, and id to add to the database. If all input values are recieved, the information is put into a student struct. Memory is allocated temporarily for the hdptr and all the records are copied over to temp. Then the hdptr is freed and reallocated using the incremented maxrecords. Records from temp are then copied back to hdptr along with the new record. The function confirms addition by printing the record at the mover. Temp is then freed and the new hdptr is returned. 

deleteRecord-
The function first checks the max record if it is non zero. Then a temporary memory is allocated to hold all records located at the hdptr. The records are copied then hdptr memory is freed. A new hdptr is created using a decremented maxrecords. Then the temp records are copied back to hdptr excluding the last recorded added. Temp memory is freed and the new hdptr is returned.

Testing criteria:
Menu function-
    check valid input(print size of database)
Random key 
return key
printnRecords-
    Print 3 records
    Print 0 records
addrecord-
    Add record: thomas engol 9999
    Check input validation
deleteRecord-
    Delete one record
    Delete all records
printAllRecords- 
    Valid database read check
Print size of database-
    Valid database read check
Print number of accesses to database-
Quit program-

