#ifndef __SCHEDULE_LINE_LIST_H__
#define __SCHEDULE_LINE_LIST_H__

#include "schedule_line.h"

/*******************************************************************************************
 * file: schedule_line_list.h
 * author: david avdat
 * email: david.avdat@gmail.com
 * last update: 24.04.2022
 *
 * contents:
 *		this file contains the interface of the schedule line list adt module.
 *
 * description:
 *	schedule_line_list is a simple linked-list implementation for scheduler line.
 *  the nodes of the schedule_line_list module hold a copy of the objects supplied by
 *  one of the insertion-functions.
 *	schedule_line_list has a current-node. essentially it is a pointer to a list node.
 *	in order to traverse the list's elements, one can use the gotohead and gotonext functions.
 *	once the current-node "stands" in the desired position, the user can use one of the
 *	functions: getcurrent, removecurrent, insertaftercurrent, and insertbeforecurrent.
 *******************************************************************************************/

/* LineListResult  - possible return values of the list interface functions */
typedef enum
{
    LINE_LIST_SUCCESS,
    LINE_LIST_FAIL,
    LINE_LIST_BAD_ARGUMENTS,
    LINE_LIST_OUT_OF_MEMORY
} LineListResult;

/* ScheduleLineList  - a simple list adt. keeps a list of generic elements */
typedef struct schedule_line_list_s *ScheduleLineList;

/*******************************************************************************************
 * name: lineListGetnumelements
 * arguments: list whose number of elements we want to get
 * return value: number of elements in given list
 *******************************************************************************************/
int lineListGetNumElements(ScheduleLineList list);

/*******************************************************************************************
 * name: lineListCreate
 * arguments: a pointer to a list to be created
 *
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - one of the arguments is null
 *		LINE_LIST_OUT_OF_MEMORY - failed to allocated needed memory
 * description:
 *      creates a new list. the list is empty.
 *******************************************************************************************/

LineListResult lineListCreate(ScheduleLineList *list /* out */);

/*******************************************************************************************
 * name: lineListDestroy
 * arguments:
 *      list - the list to be destroyed.
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent
 * description:
 *      destroys the list and releases the memory resources used by the list.
 *******************************************************************************************/
LineListResult lineListDestroy(ScheduleLineList list);

/*******************************************************************************************
 * name: lineListInsertFirst
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      LINE_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  as the first element to the list.
 * remarks:
 *      after inserting a new element the current node will be the head.
 *******************************************************************************************/
LineListResult lineListInsertFirst(ScheduleLineList list, ScheduleLine elm);

/*******************************************************************************************
 * name: LineListInsertLast
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      LINE_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  as the last element to the list.
 * remarks:
 *      after inserting a new element the current node will be the new inserted node.
 *      if the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
LineListResult lineListInsertLast(ScheduleLineList list, ScheduleLine elm);

/*******************************************************************************************
 * name: LineListInsertBeforeCurrent
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent
 *      LINE_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  before the current node.
 * remarks:
 *      after inserting a new element the current node will be the new inserted node.
 *      if the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
LineListResult lineListInsertBeforeCurrent(ScheduleLineList list, ScheduleLine elm);

/*******************************************************************************************
 * name: LineListInsertAfterCurrent
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent
 *      LINE_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  after the current node.
 * remarks:
 *      after inserting a new element the current node will be the new inserted node.
 *      if the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
LineListResult LineListInsertAfterCurrent(ScheduleLineList list, ScheduleLine elm);

/*******************************************************************************************
 * name: lineListGetCurrent
 * arguments:
 *      list  - the list from which the element is returned.
 *      p_elm - a pointer to an element that will be set to the data element.
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      LINE_LIST_FAIL          - failed to get because the list is empty .
 * remarks:
 *		Note that *p_elm will point to an internal data element of the list !
 *******************************************************************************************/
LineListResult lineListGetCurrent(ScheduleLineList list, ScheduleLine *p_elm /*out*/);

/*******************************************************************************************
 * name: lineListRemoveCurrent
 * arguments:
 *      list - the list from which the element is removed.
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      LINE_LIST_FAIL          - failed to remove the element of the list because the list
 *                               is empty.
 * description:
 *      removes the current node of the list.
 * remarks:
 *      after the removing of an element the current node will be the head of the list.
 *******************************************************************************************/
LineListResult lineListRemoveCurrent(ScheduleLineList list);

/*******************************************************************************************
 * name: lineListGotoHead
 *  arguments:
 *      list - the list where we want to pass current node pointer to the head.
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent.
 *
 * description:
 *      passes current node pointer to the head of the list.
 *******************************************************************************************/
LineListResult lineListGotoHead(ScheduleLineList list);

/*******************************************************************************************
 * name: lineListGotoNext
 *  arguments:
 *      list - the list where we want to pass current node pointer to the next node.
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      LINE_LIST_FAIL          -  the list is empty  - or -
 *                            the current node is the last node of the list.
 *
 * description:
 *      passes the current node pointer to the next node.
 *******************************************************************************************/
LineListResult lineListGotoNext(ScheduleLineList list);

/*******************************************************************************************
 * name: lineListFind
 *  arguments:
 *      list - the list where we want to find a specific node
 *	    tofind - The line number to be found
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      LINE_LIST_FAIL          - could not find the element we are looking for
 *
 * description:
 *      finds the first element, matching tofind
 *      and moves the current node pointer to it
 *******************************************************************************************/

LineListResult lineListFind(ScheduleLineList list, int tofind);

/*******************************************************************************************
 * name: lineListFilterelements
 * arguments: the original list
 *			  the list to hold the filtered elements
 *            the line type to filter by
 *
 * return value:
 *      LINE_LIST_SUCCESS
 *      LINE_LIST_BAD_ARGUMENTS - one of the arguments is null
 *		LINE_LIST_OUT_OF_MEMORY
 *
 * description:
 *      creates a list of elements from given list, for which the line type is specified
 *      current node of the new list is the head
 *	order of elements in new list is similiar to order of elements in given list
 *  it is the responsibility of the user to destroy the created list.
 *
 *******************************************************************************************/

LineListResult lineListFilterElements(ScheduleLineList list, ScheduleLineList *result_list /* out */,
                                      ScheduleLineType type);

/*******************************************************************************************
 * name: lineListSortBy
 * arguments: the list to be sorted
 *            the sorting method
 *
 * return value:
 *      LINE_LIST_SUCCESS.
 *      LINE_LIST_BAD_ARGUMENTS - a null pointer sent or wrong method
 * description:
 *      sorts the list according to method
 *******************************************************************************************/
typedef enum
{
    LINE_LIST_SORT_BY_LINE_NUMBER,
    LINE_LIST_SORT_BY_PRICE
} LineListSortMethod;

LineListResult lineListSortBy(ScheduleLineList list, LineListSortMethod method);

#endif /* __SCHEDULE_LINE_LIST_H__ */
