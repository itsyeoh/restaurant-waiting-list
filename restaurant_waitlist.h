/************************************************************
 * Name: Jason Yeoh
 * Description: Restaurant Waiting List System (HEADER FILE)
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 30
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;
typedef enum {IN_RESTAURANT, CALL_AHEAD} restaurantStatus;

/* Struct declaration */
typedef struct list {
    char *groupName;
    int groupSize;
    restaurantStatus restaurantStatus;  // enum holding the restaurantStatus
    struct list *next;
} LIST;

/* Function prototypes at jyeoh2Project4A.c */
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printCommands();
int main (int argc, char **argv);

/* Function prototypes at jyeoh2Project4B.c*/
void doAdd(LIST **waitList, int debugMode);
void doCallAhead(LIST **waitList, int debugMode);
void doWaiting(LIST **waitList, int debugMode);
void doRetrieve(LIST **waitList, int debugMode);
void doList(LIST **waitList, int debugMode);
void doDisplay(LIST *waitList, int debugMode);

/* Function prototypes at jyeoh2Project4C.c*/
void addToList(LIST **waitList, char *groupName,
               int groupSize, restaurantStatus status, int debugMode);
int doesNameExist(LIST **waitList, char *groupName, int debugMode);
int updateStatus(LIST **waitList, char *groupName, int debugMode);
char* retrieveAndRemove(LIST **waitList, int groupSize, int debugMode);
int countGroupsAhead(LIST **waitList, char *groupName, int debugMode);
void displayGroupSizeAhead(LIST **waitList, char *groupName, int debugMode);
void displayListInformation(LIST *waitList, int debugMode);
