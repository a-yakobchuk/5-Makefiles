/******************************************************************************
 An student framework implementation of doubly linked lists that holds 
 elements containing a 256 character string and a sequence number.
 12/24/2017 - R. Repka     Removed AddToFrontOfLinkedList()
 03/12/2018 - R. Repka     Added pseudo code 
 09/17/2019 - R. Repka     fixed minor prototype errors 
 09/26/2019 - R. Repka     Added comments to RemoveFromFrontOfLinkedList()
 10/01/2019 - R. Repka     Changed search function to int
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassErrors.h"
#include "LinkedLists.h"


/******************************************************************************
  Pseudo code: 
  
  add 1st node
    LinkedList front = points to node 1,  LinkedList back = points to node 1
      Node 1 next     = NULL  (at the end)
      Node 1 previous = NULL (at the start)
          
  add 2nd node
    LinkedList front = points to node 1,  LinkedList back = points to node 2
      Node 1 next points to node 2             Node 2 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)    Node 2 previous points to node 1

  add 3rd node
  LinkedList front = points to node 1,  LinkedList back = points to node 3
      Node 1 next points to node 2           Node 2 next points to node 3      Node 3 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)  Node 2 previous points to node 1  Node 3 previous points to node 2
      
   Note: It is possible to implement with only 2 special cases 
      
   Remove from front of 3 node list 
    save the pointer to the data and return it at the end
    LinkedList front = points to node 2,  LinkedList back = points to node 3
      Node 2 next points to node 3           Node 3 next   = NULL  (at the end)
      Node 2 previous = NULL (at the start)  Node 3 previous points to node 2
      free Node but NOT the data
******************************************************************************/
  
/******************************************************************************
 Initialize the linked list data structure.  Points to nothing, no entries.

 Where: LinkedLists *ListPtr - Pointer to the linked list to create
 Returns: nothing
 Errors: none
******************************************************************************/
void InitLinkedList(LinkedLists *ListPtr)
{
  ListPtr->NumElements = 0;
  ListPtr->FrontPtr = NULL;
  ListPtr->BackPtr = NULL;
  
} /* InitLinkedList() */

/******************************************************************************
 Adds a node to the back of the list.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to add to
        char *DataPtr - Pointer to the data to add to the list
 Returns: nothing
 Errors: Prints to stderr and exits
******************************************************************************/
void AddToBackOfLinkedList(LinkedLists *ListPtr, char *DataPtr)
{
  if(ListPtr == NULL) {
  fprintf(stderr, "LIST DOES NOT EXIST");
  exit(9);
  }
  LinkedListNodes *NewNode = (LinkedListNodes *)malloc(sizeof(LinkedListNodes));
	if(NewNode == NULL) {
	fprintf(stderr, "NewNode MALLOC FAILED");
	exit(9);}
  strncpy(NewNode->String, DataPtr, MAX_BUFF_LEN);  
  NewNode->Previous = NULL;
  NewNode->Next = NULL;
  if(ListPtr->NumElements == 0) {
    ListPtr->FrontPtr = NewNode;
    ListPtr->BackPtr = NewNode;
  }
  if(ListPtr->NumElements >=1) {
    NewNode->Previous = ListPtr->BackPtr;
    ListPtr->BackPtr->Next = NewNode;
    ListPtr->BackPtr = NewNode;
  }
  ListPtr->NumElements++; 
} /* AddToBackOfLinkedList */


/******************************************************************************
 Removes a node from the front of the list and returns a pointer to the node
 data removed. On empty lists should return a NULL pointer.  
 Note: This you will need to malloc a string buffer and copy the data from the
       linked list node before destroying the node.  The calling routine was
       written to free the string so there are no memory leaks

 
   Linked lists contain nodes, which contain data strings
 
 Where: LinkedLists *ListPtr    - Pointer to the linked list to remove from
 Returns: Pointer to the data removed or NULL for none
 Errors: none
******************************************************************************/
char *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr)
{ 
  if(ListPtr->NumElements == 0) {
  return(NULL);
  }
  char *StringBuffer = (char *)malloc(sizeof(char)*MAX_BUFF_LEN);
	if(StringBuffer == NULL){
	fprintf(stderr,"StringBuffer MALLOC FAILED");
	exit(9);}
  
  strncpy(StringBuffer, ListPtr->FrontPtr->String, MAX_BUFF_LEN);
  if(ListPtr->NumElements == 1) {
  free(ListPtr->FrontPtr);
  ListPtr->FrontPtr = NULL;
  ListPtr->BackPtr = NULL;
  }
  if(ListPtr->NumElements >=2) {
  ListPtr->FrontPtr = ListPtr->FrontPtr->Next;
  free(ListPtr->FrontPtr->Previous);
  ListPtr->FrontPtr->Previous = NULL;
  }
  ListPtr->NumElements--;
  return(StringBuffer);  
} /* RemoveFromFrontOfLinkedList() */


/******************************************************************************
 De-allocates the linked list and resets the struct fields (in the header) 
 to indicate that the list is empty.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to destroy
 Returns: nothing
 Errors: none
******************************************************************************/
void DestroyLinkedList(LinkedLists *ListPtr)
{
char *charVar = malloc(MAX_BUFF_LEN);
while(ListPtr->NumElements != 0) {
charVar = RemoveFromFrontOfLinkedList(ListPtr);
free(charVar);
charVar = NULL;
}
} /* DestroyLinkedList() */


/******************************************************************************
 Searches the linked list for a provided word. If found, returns the pointer
 to the element struct. If not found, returns a NULL pointer
 
 Where: LinkedLists *ListPtr - Pointer to the linked list to search
        char *String         - Pointer to the string to search
 Returns: 1 if found, 0 otherwise
 Errors: none
 * ***************************************************************************/
int SearchList(LinkedLists *ListPtr, char *String)
{
LinkedListNodes *temp = ListPtr->FrontPtr;
while(temp != NULL) {
int compare = strncmp(temp->String, String, MAX_BUFF_LEN);
   if (compare == 0) {
   return(1);
   }
   if (compare != 0) {
   temp = temp->Next;
   }
}
return 0;
} /* SearchList() */




