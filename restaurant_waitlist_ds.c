/************************************************************
 * Name: Jason Yeoh
 * Description: Restaurant Waiting List System - DS
 ************************************************************/

#include "restaurant_waitlist.h" 

/* LL IMPLMENTATION FUNCTION #1: addToList() 
 *  - Add a group at the back of the waiting list.
 *  - [DEBUG MODE] Print group's name as it traverses the list.
 */
void addToList(LIST **waitList, char *groupName, int groupSize, restaurantStatus status, int debugMode) {
    LIST *tempList = (LIST *)malloc(sizeof(LIST));  // Allocate temporary list pointer
    
    /* Insert the first element of the waitlist. */
    if(*waitList == NULL) {
        tempList->groupName = groupName;
        tempList->groupSize = groupSize;
        tempList->restaurantStatus = status;
        tempList->next = NULL;                  // Point its next field pointer to NULL
        *waitList = tempList;                   // Point the newly-created node at the front of the list
    }
    
    /* Insert element at the back of an existing waitlist */
    else {
        LIST *pBack = *waitList;
        
        tempList->groupName = groupName;
        tempList->groupSize = groupSize;
        tempList->restaurantStatus = status;
        tempList->next = NULL;                  // Point its next field pointer to NULL
        
        /* Loop until it reaches the back of the list */
        while(pBack->next != NULL) {
            /* DEBUG MODE ON */
            if(debugMode == TRUE) {
                printf("\t[DEBUGGING] ");
                printf("Traversed %s with size %d in the waiting list before reaching %s. \n",
                       pBack->groupName, pBack->groupSize, groupName);
            }
            
            pBack = pBack->next;    // Proceed to the next pointer
        }
        
        pBack->next = tempList;     // Point the newly-created node at the back of the list
    }
}


/* LL IMPLMENTATION FUNCTION #2: doesNameExist()
 *  - Check whether a group name already exists in the waiting list.
 *  - Return TRUE if the name exists, otherwise return FALSE.
 *  - [DEBUG MODE] Print group's name as it traverses the list.
 */
int doesNameExist(LIST **waitList, char *groupName, int debugMode) {
    LIST *tempList = *waitList;
    
    if(tempList == NULL)
        return FALSE;
    
    /* Loop until the list reaches NULL */
    while(tempList != NULL) {
        /* DEBUG MODE ON */
        if(debugMode == TRUE) {
            printf("\t[DEBUGGING] ");
            printf("Compared \"%s\" with \"%s\". \n", tempList->groupName, groupName);
        }
        
        /* Perform string comparison between user-selected name and the group name in the list */
        if(strcmp(tempList->groupName, groupName) == 0)
            return TRUE;    // If strcmp returned 0, then both strings are equal.
        tempList = tempList->next;  // Proceed to the next pointer
    }
    
    return FALSE;   // Traversed the entire list and found no similar strings.
}


/* LL IMPLMENTATION FUNCTION #3: updateStatus()
 *  - If a call-ahead group arrives at the restaurant, then update the in-restaurant status.
 *  - [DEBUG MODE] Print group's name as it traverses the list.
 */
int updateStatus(LIST **waitList, char *groupName, int debugMode) {
    LIST *tempList = *waitList;
    
    /* Loop until both strings are equal */
    while(strcmp(tempList->groupName, groupName) != 0) {
        tempList = tempList->next;  // Proceed to the next pointer
        
        /* DEBUG MODE ON */
        if(debugMode == TRUE) {
            printf("\t[DEBUGGING] ");
            printf("Compared \"%s\" with \"%s\". \n", tempList->groupName, groupName);
        }
    }
    
    /* If the group's in-restaurant status is still call-ahead, then update its status
       to in-restaurant. */
    if(tempList->restaurantStatus != IN_RESTAURANT) {
        tempList->restaurantStatus = IN_RESTAURANT;
        return TRUE;
    }
    
    return FALSE;   // Traversed the entire list and found no similar strings.
}


/* LL IMPLMENTATION FUNCTION #4: retrieveAndRemove()
 *  - Remove the group from the waiting list, if the available table size
 *    fits the group's size.
 *  - Return the name of the group that was removed from the list.
 *  - [DEBUG MODE] Print group's name and size as it traverses the list.
 */
char *retrieveAndRemove(LIST **waitList, int tableSize, int debugMode) {
    LIST *tempList = *waitList; // list that handles the waiting list
    LIST *pRemove;              // list that handles the group to be removed
    
    if(tempList == NULL)
        return '\0';
    
    char* removedGroupName = (char*)malloc(sizeof(char) * CHAR_SIZE);

    /* GROUP TO BE REMOVED IS AT THE FRONT OF THE LIST */
    if(tempList->groupSize <= tableSize) {
        /* DEBUG MODE ON */
        if(debugMode == TRUE) {
            printf("\t[DEBUGGING] ");
            printf("Compared table size of %d with \"%s\"'s size of %d. \n",
                   tableSize, tempList->groupName, tempList->groupSize);
        }
        
        pRemove = *waitList;
        // String copy the name of the group to be removed to the pRemove list.
        strcpy(removedGroupName, pRemove->groupName);
        
        *waitList = (*waitList)->next;  // Advance the list's current pointer to its next pointer.
        free(pRemove);                  // Delete group's node.
        
        return removedGroupName;    // Return the freed node
    }
    
    /* GROUP TO BE REMOVED IS AT THE MIDDLE OR END OF THE LIST */
    while(tempList->next != NULL) {
        /* DEBUG MODE ON */
        if(debugMode == TRUE) {
            printf("\t[DEBUGGING] ");
            printf("Compared table size of %d with \"%s\"'s size of %d. \n",
                   tableSize, tempList->next->groupName, tempList->next->groupSize);
        }
        
        /* Checks if the available table size fits the list->next group's size */
        if(tempList->next->groupSize <= tableSize) {
            pRemove = tempList->next;
            // String copy the name of the group to be removed to the pRemove list.
            strcpy(removedGroupName, pRemove->groupName);
            
            // Advance the list's current pointer to its next pointer.
            //  (A) Group is at the middle of the list
            if(tempList->next->next != NULL)
                tempList->next = tempList->next->next;
            //  (B) Group is at the end of the list
            else
                tempList->next = NULL;
            
            free(pRemove);      // Delete group's node.

            return removedGroupName;    // Return the freed node.
        }
        
        tempList = tempList->next;  // Proceed to the next pointer
    }
    
    return '\0';
}


/* LL IMPLMENTATION FUNCTION #5: countGroupsAhead()
 *  - Return the total number of groups ahead of a user-selected group name.
 *  - [DEBUG MODE] Print group's name and size as it traverses the list.
 */
int countGroupsAhead(LIST **waitList, char *groupName, int debugMode) {
    LIST *tempList = *waitList;
    int groupCount = 0;

    /* Loop until both strings are equal (or reaches the specified group name) */
    while(strcmp(tempList->groupName, groupName) != 0) {
        /* DEBUG MODE ON */
        if(debugMode == TRUE) {
            printf("\t[DEBUGGING] ");
            printf("There are %d number of groups waiting ahead of %s. \n", groupCount, groupName);
            printf("\tTraversed %s with size %d in the waiting list before reaching %s\n",
                    tempList->groupName, tempList->groupSize, groupName);
        }
        
        groupCount++;                   // Increment the number of groups ahead
        tempList = tempList->next;      // Proceed to the next pointer
    }
    
    return groupCount;  // Return the total count
}


/* LL IMPLMENTATION FUNCTION #6: displayGroupSizeAhead()
 *  - Traverse the list until it reaches the specific group name.
 *  - Print the node's group size.
 *  - [DEBUG MODE] Print group's name and size as it traverses the list.
 */
void displayGroupSizeAhead(LIST **waitList, char *groupName, int debugMode) {
    LIST *tempList = *waitList;
    int order = 1;
    
    printf("The following groups are the following: \n");

    /* Loop until both strings are equal (or reaches the specified group name) */
    while(strcmp(tempList->groupName, groupName) != 0) {
        /* DEBUG MODE ON */
        if(debugMode == TRUE) {
            printf("\t[DEBUGGING] ");
            printf("Traversed %s with size %d in the waiting list before reaching %s\n",
                   tempList->groupName, tempList->groupSize, groupName);
        }
        
        printf("%d. %s with group size of %d\n", order, tempList->groupName, tempList->groupSize);
        tempList = tempList->next;  // Proceed to the next pointer.
        order++;
    }

    /* The temporary list reached the user-selected group. */
    // Print the node's group size.
    printf(">> Group size of \"%s\": %d\n", tempList->groupName, tempList->groupSize);
}


/* LL IMPLMENTATION FUNCTION #7: displayListInformation()
 *  - Display the entire list and all its information.
 */
void displayListInformation(LIST *waitList, int debugMode) {
    LIST *tempList = waitList;
    char* getStatus[] = {"IN-RESTAURANT", "CALL-AHEAD"};    // used for the enumeration
    int order = 1;
    
    printf("============================================================\n");
    printf(" #\t GROUP NAME\t\t\t SIZE\t STATUS                         \n");
    printf("============================================================\n");
    
    if(tempList == NULL) {
        printf("NO ENTRIES YET. \n");
        return;
    }
    
    while(tempList != NULL) {
        printf("%2d\t %-30s %3d\t %s\n", order, tempList->groupName,
               tempList->groupSize, getStatus[tempList->restaurantStatus]);
        tempList = tempList->next;  // Proceed to the next pointer
        order++;
    }
}
