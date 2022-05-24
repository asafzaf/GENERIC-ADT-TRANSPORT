#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include <stdio.h>

/*******************************************************************************************
 * File: linked_list.h
 * Author: David Avdat
 * Last update: 24.04.2022
 *
 * Contents:
 *		This file contains the interface of the LinkedList ADT module.
 *
 * Type list:
 *		ListResult        - possible return values of the list interface functions.
 *		ListElement       - the element of the list (the data being
 *				            held by a list-node).
 *      KeyForListElement - the type of key for find and filter functions
 *		LinkedList        - a simple list ADT. Keeps a list of generic elements.
 *
 *
 * Function list:
 *		linkedListGetNumElements        - get number of elements in a list
 *		linkedListCreate				- initialize an empty list.
 *      linkedListFilterElements        - creates a new list with
 *						                  part of the elements of the given list
 *					      				  (according to arguments)
 *		linkedListDestroy				- destroys the list.
 *		linkedListInsertFirst			- inserts an element as the first element of the list.
 *		linkedListInsertLast			- inserts an element as the last element of the list.
 *		linkedListInsertAfterCurrent	- inserts an element after the current node.
 *		linkedListInsertBeforeCurrent	- inserts an element before the current node.
 *		linkedListGetCurrent			- gets pointer to a copy of the data stored in the
 *											current list node.
 *		linkedListRemoveCurrent	    	- removes the current list node.
 *		linkedListGoToHead				- make head the current node.
 *		linkedListGoToNext				- passes current node pointer to the next node.
 *		linkedListPrint	  			    - prints the list, using the print function, received in
 *										  the linkedListCreate
 *		linkedListSortElements			- sorts the list according to a given relation
 *
 * Description:
 *	LinkedList is a simple linked-list implementation. The nodes of the LinkedList module
 *	hold a copy of the objects supplied by one of the insertion-functions. Since this module
 *	was defined generically, the create-function requires three function's pointers:
 *  copyElemFunc, freeElemFunc and printElemFunc.
 *  In case the list should hold the supplied objects themselves (instead of
 *	their "clones"), the user can supply copy-function that returns the same pointer recieved
 *	as a parameter.
 *	LinkedList has a CURRENT-NODE. Essentially it is a pointer to a list node.
 *	In order to traverse the list's elements, one can use the linkedListGoToHead and
 *	linkedListGoToNext functions.
 *	Once the current-node "stands" in the desired position, the user can use one of the
 *	functions: linkedListGetCurrent, linkedListRemoveCurrent, LinkedList_insertAfterCurrent,
 *	and linkedListInsertBeforeCurrent.
 *******************************************************************************************/

/* ListResult  - possible return values of the list interface functions */
typedef enum
{
  LIST_SUCCESS,
  LIST_FAIL,
  LIST_BAD_ARGUMENTS,
  LIST_OUT_OF_MEMORY
} ListResult;

/* ListElement - the element of the list (the data being held by a list-node) */
typedef void *ListElement;

/* KeyForListElement - the key for filter and find functions */
typedef void *KeyForListElement;

/* LinkedList  - a simple list ADT. Keeps a list of generic elements */
typedef struct LinkedList_s *LinkedList;

/*******************************************************************************************
 * Name: linkedListGetNumElements
 * Arguments: list whose number of elements we want to get
 * Return value: number of elements in given list
 *******************************************************************************************/
int linkedListGetNumElements(LinkedList list);

/*******************************************************************************************
 * Name: linkedListCreate
 * Arguments: a pointer to a list to be created
 * Since this module was defined generically, the create-function requires three
 * function's pointers: copyElemFunc,freeElemFunc and printElemFunc.
 * In case the list should hold the supplied objects themselves (instead of their "clones"),
 * the user can supply copy-function that returns the same pointer recieved as a parameter.
 *
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - one of the arguments is NULL
 *		  LIST_OUT_OF_MEMORY - failed to allocated needed memory
 * Description:
 *      Creates a new list. The list is empty.
 *******************************************************************************************/
typedef ListElement (*copyListElemFunc)(ListElement); /*should return NULL if fails*/
typedef void (*freeListElemFunc)(ListElement);
typedef void (*printListElemFunc)(FILE *, ListElement);

ListResult linkedListCreate(LinkedList *list /* out */, copyListElemFunc cpyFunc,
                            freeListElemFunc freeFunc, printListElemFunc printFunc);

/*******************************************************************************************
 * Name: linkedListDestroy
 * Arguments:
 *      list - the list to be destroyed.
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent
 * Description:
 *      Destroys the list and releases the memory resources used by the list.
 *		Use the freeElemFunc to free the memory allocated for the elements clones.
 *******************************************************************************************/
ListResult linkedListDestroy(LinkedList list);

/*******************************************************************************************
 * Name: linkedListInsertFirst
 * Arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent.
 *      LIST_OUT_OF_MEMORY - failed to allocate memory (or when the copyElemFunc returns NULL).
 * Description:
 *      Inserts a copy of the element (using the copyElemFunc) as the first element to the list.
 * Remarks:
 *      After inserting a new element the current node will be the head.
 *******************************************************************************************/
ListResult linkedListInsertFirst(LinkedList list, ListElement elm);

/*******************************************************************************************
 * Name: linkedListInsertLast
 * Arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent.
 *      LIST_OUT_OF_MEMORY - failed to allocate memory (or when the copyElemFunc returns NULL).
 * Description:
 *      Inserts a copy of the element (using the copyElemFunc) as the last element to the list.
 * Remarks:
 *      After inserting a new element the current node will be the new inserted node.
 *      If the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
ListResult linkedListInsertLast(LinkedList list, ListElement elm);

/*******************************************************************************************
 * Name: linkedListInsertBeforeCurrent
 * Arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent
 *      LIST_OUT_OF_MEMORY - failed to allocate memory (or when the copyElemFunc returns NULL).
 * Description:
 *      Inserts a copy of the element (using the copyElemFunc) before the current node.
 * Remarks:
 *      After inserting a new element the current node will be the new inserted node.
 *      If the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
ListResult linkedListInsertBeforeCurrent(LinkedList list, ListElement elm);

/*******************************************************************************************
 * Name: LinkedList_insertAfterCurrent
 * Arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent
 *      LIST_OUT_OF_MEMORY - failed to allocate memory (or when the copyElemFunc returns NULL).
 * Description:
 *      Inserts a copy of the element (using the copyElemFunc) after the current node.
 * Remarks:
 *      After inserting a new element the current node will be the new inserted node.
 *      If the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
ListResult linkedListInsertAfterCurrent(LinkedList list, ListElement elm);

/*******************************************************************************************
 * Name: linkedListGetCurrent
 * Arguments:
 *      list  - the list from which the element is returned.
 *      p_elm - a pointer to an element that will be set to the data element.
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent.
 *      LIST_FAIL          - failed to get because the list is empty (or when the copyElemFunc
 *							 returns NULL).
 * Remarks:
 *		This function will NOT use the copyElemFunc to create a copy of the element.
 *		Thus, note that *p_elm will point to an internal data element of the list !
 *******************************************************************************************/
ListResult linkedListGetCurrent(LinkedList list, ListElement *p_elm /*out*/);

/*******************************************************************************************
 * Name: linkedListRemoveCurrent
 * Arguments:
 *      list - the list from which the element is removed.
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent.
 *      LIST_FAIL          - failed to remove the element of the list because the list
 *                               is empty.
 * Description:
 *      Removes the current node of the list.
 * Remarks:
 *      After the removing of an element the current node will be the head of the list.
 *      The freeElemFunc will be activated in order to free the removed element.
 *******************************************************************************************/
ListResult linkedListRemoveCurrent(LinkedList list);

/*******************************************************************************************
 * Name: linkedListGoToHead
 *  Arguments:
 *      list - the list where we want to pass current node pointer to the head.
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent.
 *
 * Description:
 *      passes current node pointer to the head of the list.
 *******************************************************************************************/
ListResult linkedListGoToHead(LinkedList list);

/*******************************************************************************************
 * Name: linkedListGoToNext
 *  Arguments:
 *      list - the list where we want to pass current node pointer to the next node.
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent.
 *      LIST_FAIL          -  the list is empty  - or -
 *                            the current node is the last node of the list.
 *
 * Description:
 *      passes the current node pointer to the next node.
 *******************************************************************************************/
ListResult linkedListGoToNext(LinkedList list);

/* return 1 if the element matches the key, 0 if not */
typedef int (*matchListElemFunc)(ListElement, KeyForListElement);

/*******************************************************************************************
 * Name: linkedListFind
 *  Arguments:
 *      list - the list where we want to find a specific node
 *	    toFind - a key by which we want to find the element
 *	    matchFunc - a function that returns 1 iff the element matches the key
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent.
 *      LIST_FAIL          - could not find the element we are looking for
 *
 * Description:
 *      finds the first element, matching toFind starting at current
 *      and moves the current node pointer to it.
 * Note! If you need to find element in the whole list, use linkedListGoToHead first
 *******************************************************************************************/
ListResult linkedListFind(LinkedList list, KeyForListElement toFind,
                          matchListElemFunc matchFunc);

/*******************************************************************************************
 * Name: linkedListFilterElements
 * Arguments: the original list
 *			  the list to hold the filtered elements
 *			  filterElemFunc - a generic filter function
 *            FilterElement - is passed as second parameter to filterElemFunc
 *                            this is additional parameter to make filter
 *                            function generic
 *
 * Return value:
 *      LIST_SUCCESS
 *      LIST_BAD_ARGUMENTS - one of the arguments is NULL
 *		LIST_OUT_OF_MEMORY
 *
 * Description:
 *      creates a list of elements from given list, for which
 *      filterFunc returns non zero value.
 *      current node of the new list is the head
 *	Order of elements in new list is similiar to order of elements in given
 *	list
 *  The copy, free and print functions of the new list are the same as in the given list
 *  It is the responsibility of the user to destroy the created list.
 *	YOU CAN USE THIS FUNCTION AS COPY FUNCTION (for example: make filterFunc return 1
 *	allways)
 *
 *******************************************************************************************/

ListResult linkedListFilterElements(LinkedList list, LinkedList *result_list /* out */,
                                    matchListElemFunc filterFunc,
                                    KeyForListElement filterElement);

/*******************************************************************************************
 * Name: linkedListPrint
 *  Arguments:
 *      list - the list to print
 *	    outstream - the output stream to print the list
 *      n - first elements to print
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - NULL pointers sent or n < 0
 *
 *
 * Description:
 *      prints the list using the print function, received in the linkedListCreate
 *      The current node moves to be the last node in the list
 * Remarks:
 *      if n >= number of elements in the list, all the list is printed
 *******************************************************************************************/
ListResult linkedListPrint(LinkedList list, FILE *outstream, int n);

/*******************************************************************************************
 * Name: linkedListSortElements
 * Arguments: Since this module was defined generically, the sort requires one
 * function pointers  cmpElemFunc
 *
 * Return value:
 *      LIST_SUCCESS.
 *      LIST_BAD_ARGUMENTS - a NULL pointer sent
 * Description:
 *      Sorts the list according to given cmp function
 * Usage Example:
 *      See file list_test.c
 *******************************************************************************************/
/* generic function type , return -1 if first element should be placed
   ahead of 2nd , return 1 if vica versa , return 0 if can't decide */

typedef int (*cmpListElemFunc)(ListElement, ListElement);

ListResult linkedListSortElements(LinkedList list, cmpListElemFunc cmpFunc);

#endif
