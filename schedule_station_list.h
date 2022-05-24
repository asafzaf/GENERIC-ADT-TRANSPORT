#ifndef __SCHEDULE_STATION_LIST_H__
#define __SCHEDULE_STATION_LIST_H__

#include "schedule_station.h"

/*******************************************************************************************
 * file: schedule_station_list.h
 * author: david avdat
 * email: david.avdat@gmail.com
 * last update: 24.04.2022
 *
 * contents:
 *		this file contains the interface of the schedule station list adt module.
 *
 * description:
 *	schedule_station_list is a simple linked-list implementation for scheduler station.
 *  the nodes of the schedule_station_list module hold a copy of the objects supplied by
 *  one of the insertion-functions.
 *	schedule_station_list has a current-node. essentially it is a pointer to a list node.
 *	in order to traverse the list's elements, one can use the gotohead and gotonext functions.
 *	once the current-node "stands" in the desired position, the user can use one of the
 *	functions: getcurrent, removecurrent, insertaftercurrent, and insertbeforecurrent.
 *******************************************************************************************/

/* StationListResult  - possible return values of the list interface functions */
typedef enum
{
    STATION_LIST_SUCCESS,
    STATION_LIST_FAIL,
    STATION_LIST_BAD_ARGUMENTS,
    STATION_LIST_OUT_OF_MEMORY
} StationListResult;

/* ScheduleStationList  - a simple list adt. keeps a list of generic elements */
typedef struct schedule_station_list_s *ScheduleStationList;

/*******************************************************************************************
 * name: stationListGetnumelements
 * arguments: list whose number of elements we want to get
 * return value: number of elements in given list
 *******************************************************************************************/
int stationListGetNumElements(ScheduleStationList list);

/*******************************************************************************************
 * name: stationListCreate
 * arguments: a pointer to a list to be created
 *
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - one of the arguments is null
 *		STATION_LIST_OUT_OF_MEMORY - failed to allocated needed memory
 * description:
 *      creates a new list. the list is empty.
 *******************************************************************************************/
StationListResult stationListCreate(ScheduleStationList *list /* out */);

/*******************************************************************************************
 * name: stationListDestroy
 * arguments:
 *      list - the list to be destroyed.
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent
 * description:
 *      destroys the list and releases the memory resources used by the list.
 *******************************************************************************************/
StationListResult stationListDestroy(ScheduleStationList list);

/*******************************************************************************************
 * name: stationListInsertFirst
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENT S - a null pointer sent.
 *      STATION_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  as the first element to the list.
 * remarks:
 *      after inserting a new element the current node will be the head.
 *******************************************************************************************/
StationListResult stationListInsertFirst(ScheduleStationList list, ScheduleStation elm);

/*******************************************************************************************
 * name: stationListInsertLast
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      STATION_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  as the last element to the list.
 * remarks:
 *      after inserting a new element the current node will be the new inserted node.
 *      if the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
StationListResult stationListInsertLast(ScheduleStationList list, ScheduleStation elm);

/*******************************************************************************************
 * name: stationListInsertBeforeCurrent
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent
 *      STATION_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  before the current node.
 * remarks:
 *      after inserting a new element the current node will be the new inserted node.
 *      if the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
StationListResult stationListInsertBeforeCurrent(ScheduleStationList list, ScheduleStation elm);

/*******************************************************************************************
 * name: stationListInsertAfterCurrent
 * arguments:
 *      list - the list to which the element is inserted.
 *      elm  - the element to be inserted
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent
 *      STATION_LIST_OUT_OF_MEMORY - failed to allocate memory .
 * description:
 *      inserts a copy of the element  after the current node.
 * remarks:
 *      after inserting a new element the current node will be the new inserted node.
 *      if the list was empty, the element is inserted as the first node.
 *******************************************************************************************/
StationListResult stationListInsertAfterCurrent(ScheduleStationList list, ScheduleStation elm);

/*******************************************************************************************
 * name: stationListGetCurrent
 * arguments:
 *      list  - the list from which the element is returned.
 *      p_elm - a pointer to an element that will be set to the data element.
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      STATION_LIST_FAIL          - failed to get because the list is empty .
 * remarks:
 *		Note that *p_elm will point to an internal data element of the list !
 *******************************************************************************************/
StationListResult stationListGetCurrent(ScheduleStationList list, ScheduleStation *p_elm /*out*/);

/*******************************************************************************************
 * name: stationListRemoveCurrent
 * arguments:
 *      list - the list from which the element is removed.
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      STATION_LIST_FAIL          - failed to remove the element of the list because the list
 *                               is empty.
 * description:
 *      removes the current node of the list.
 * remarks:
 *      after the removing of an element the current node will be the head of the list.
 *******************************************************************************************/
StationListResult stationListRemoveCurrent(ScheduleStationList list);

/*******************************************************************************************
 * name: stationListGotoHead
 *  arguments:
 *      list - the list where we want to pass current node pointer to the head.
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent.
 *
 * description:
 *      passes current node pointer to the head of the list.
 *******************************************************************************************/
StationListResult stationListGotoHead(ScheduleStationList list);

/*******************************************************************************************
 * name: stationListGotoNext
 *  arguments:
 *      list - the list where we want to pass current node pointer to the next node.
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      STATION_LIST_FAIL          -  the list is empty  - or -
 *                            the current node is the last node of the list.
 *
 * description:
 *      passes the current node pointer to the next node.
 *******************************************************************************************/
StationListResult stationListGotoNext(ScheduleStationList list);

/*******************************************************************************************
 * name: stationListFind
 *  arguments:
 *      list - the list where we want to find a specific node
 *	    tofind - The station name to find
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent.
 *      STATION_LIST_FAIL          - could not find the element we are looking for
 *
 * description:
 *      finds the first element, matching tofind
 *      and moves the current node pointer to it
 *******************************************************************************************/

StationListResult stationListFind(ScheduleStationList list, const char *tofind);

/*******************************************************************************************
 * name: stationListSortBy
 * arguments: the list to be sorted
 *            the sorting method
 *
 * return value:
 *      STATION_LIST_SUCCESS.
 *      STATION_LIST_BAD_ARGUMENTS - a null pointer sent or wrong method
 * description:
 *      sorts the list according to method
 *******************************************************************************************/
typedef enum
{
    STATION_LIST_SORT_BY_NAME,
    STATION_LIST_SORT_BY_TIME
} StationListSortMethod;

StationListResult stationListSortBy(ScheduleStationList list, StationListSortMethod method);

#endif /* __SCHEDULE_STATION_LIST_H__ */
