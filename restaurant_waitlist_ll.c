/************************************************************
 * Name: Jason Yeoh
 * Description: Restaurant Waiting List System
 ************************************************************/

#include "restaurant_waitlist.h"

/* LL FUNCTION #1: doAdd() */
void doAdd(LIST **waitList, int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf("Error: Add command requires an integer value of at least 1\n");
        printf("Add command is of form: a <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf("Error: Add command requires a name to be given\n");
        printf("Add command is of form: a <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* doAdd() Linked List Implementation 
     *  – IF name does not exist, add it to waiting list.
     *  – ELSE print a error message.
     */
    if(!doesNameExist(waitList, name, debugMode)) {
        printf("Adding group \"%s\" of size %d\n", name, size);
        addToList(waitList, name, size, IN_RESTAURANT, debugMode);
    }
    else {
        printf("<ERROR MESSAGE>\n");
        printf("The group name \"%s\" input already exists in the list\n", name);
        return;
    }
}


/* LL FUNCTION #2: doCallAhead() */
void doCallAhead(LIST **waitList, int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf("Error: Call-ahead command requires an integer value of at least 1\n");
        printf("Call-ahead command is of form: c <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name) {
        printf("Error: Call-ahead command requires a name to be given\n");
        printf("Call-ahead command is of form: c <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }
    
    /* doCallAhead() Linked List Implementation
     *  – IF name does not exist, add it to waiting list as a CALL-AHEAD.
     *  – ELSE print a error message.
     */
    if(!doesNameExist(waitList, name, debugMode)) {
        printf ("Call-ahead group \"%s\" of size %d\n", name, size);
        addToList(waitList, name, size, CALL_AHEAD, debugMode);
    }
    else {
        printf("<ERROR MESSAGE>\n");
        printf("The group name \"%s\" input already exists in the list\n", name);
        return;
    }
}


/* LL FUNCTION #3: doWaiting() */
void doWaiting(LIST **waitList, int debugMode)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name) {
        printf("Error: Waiting command requires a name to be given\n");
        printf("Waiting command is of form: w <name>\n");
        printf("  where: <name> is the name of the group that is now waiting\n");
        return;
    }

    /* doWaiting() Linked List Implementation
     *  – IF name does not exist or the group is not yet in the restaurant, print an error message.
     *  – ELSE mark the call-ahead group as waiting in the restaurant.
     */
    if(!doesNameExist(waitList, name, debugMode) || !updateStatus(waitList, name, debugMode)) {
        printf("<ERROR MESSAGE>\n");
        printf(" (1) Either the group name \"%s\" input might not exist in the list OR\n", name);
        printf(" (2) The particular group \"%s\" is already at the restaurant. \n", name);
        return;
    }
    else
        printf("Waiting group \"%s\" is now in the restaurant\n", name);
    
}


/* LL FUNCTION #4: doRetrieve() */
void doRetrieve(LIST **waitList, int debugMode)
{
    /* get table size from input */
    int size = getPosInt();
    if (size < 1) {
        printf("Error: Retrieve command requires an integer value of at least 1\n");
        printf("Retrieve command is of form: r <size>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    
    /* doRetrieve() Linked List Implementation
     *  – Retrieve and remove the first group with table size equal or less than to its size.
     */
    printf("Retrieve (and remove) the first group that can fit at a table of size %d\n", size);
    printf("Remove group \"%s\" \n", retrieveAndRemove(waitList, size, debugMode));
}


/* LL FUNCTION #5: doList() */
void doList(LIST **waitList, int debugMode)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name) {
        printf("Error: List command requires a name to be given\n");
        printf("List command is of form: l <name>\n");
        printf("  where: <name> is the name of the group to inquire about\n");
        return;
    }
    
    /* doList() Linked List Implementation
     *  – IF name does not exist, print an error message.
     *  – ELSE list down the group's name and size ahead of the user-selected group and
     *    print the number of groups ahead of it.
     */
    if(!doesNameExist(waitList, name, debugMode)) {
        printf("<ERROR MESSAGE>\n");
        printf("The group name \"%s\" input does not exist in the list\n", name);
    }
    else {
        printf("Group \"%s\" is behind the following %d groups\n", name, countGroupsAhead(waitList, name, debugMode));
        displayGroupSizeAhead(waitList, name, debugMode);  // kailangan pa ng group name ahead ?
    }
}


/* LL FUNCTION #6: doDisplay() */
void doDisplay(LIST *waitList, int debugMode)
{
    clearToEoln();
    
    /* doDisplay() Linked List Implementation
     *  – Display all the information (which are group's name, size, restaurant status and
     *    its order in the waitlist).
     */
    printf ("Display information about all groups\n");
    displayListInformation(waitList, debugMode);
}
