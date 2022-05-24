#ifndef __SCHEUDLE_H__
#define __SCHEUDLE_H__

#include "pr2ex5.h"

typedef struct schedule_s *Schedule;

#define SCHEDULE_RESULT_TABLE(X)     \
	X(SCHEDULE_NULL_ARG)             \
	X(SCHEDULE_INVALID_LINE_TYPE)    \
	X(SCHEDULE_INVALID_TRAIN_TYPE)   \
	X(SCHEDULE_INVALID_LINE_NUMBER)  \
	X(SCHEDULE_INVALID_PRICE)        \
	X(SCHEDULE_INVALID_TIME)         \
	X(SCHEDULE_LINE_ALREADY_EXISTS)  \
	X(SCHEDULE_LINE_DOESNT_EXIST)    \
	X(SCHEDULE_STATION_DOESNT_EXIST) \
	X(SCHEDULE_NO_LINES)             \
	X(SCHEDULE_OUT_OF_MEMORY)        \
	X(SCHEDULE_SUCCESS)

#define SCHEDULE_RESULT_AS_ENUM(result) result,

typedef enum
{
	SCHEDULE_RESULT_TABLE(SCHEDULE_RESULT_AS_ENUM)
}ScheduleResult;

/*
 * scheduleCreate
 *
 *  Description:
 *      Creates a new empty Schedule.
 *  Parameters:
 *      None
 *  Result:
 *      NULL - In case of memory allocation failure.
 *      A new Schedule - In case of success.
 */
Schedule scheduleCreate();

/*
 * scheduleDestroy
 *
 *  Description:
 *      Destroys an existing Schedule.
 *  Parameters:
 *      The Schedule to destroy.
 */
void scheduleDestroy(Schedule schedule);

/*
 * scheduleAddLine
 *
 *  Description:
 *      Adds new but/train line to Schedule.
 *  Parameters:
 *      schedule - An existing Schedule.
 *      type - The type of the line.
 *      number - The number of the line,
 *					must be in the inclusive range [1 ... 9999].
 *      description - For bus line: the name of the line.
 *						Otherwise: the type ("Suburban" or "Intercity" or "Direct").
 *      price - The price of the line. Must be bigger than 0.
 *  Result:
 *      SCHEDULE_NULL_ARG - If one or more parameters are NULL.
 *      SCHEDULE_INVALID_LINE_TYPE - If type is invalid.
 *      SCHEDULE_INVALID_LINE_NUMBER - If number is invalid.
 *      SCHEDULE_INVALID_TRAIN_TYPE - If (type == SCHEDULE_LINE_TRAIN) and name is invalid.
 *      SCHEDULE_INVALID_PRICE - If price is invalid.
 *      SCHEDULE_LINE_ALREADY_EXIST - If a line with this number already exists.
 *      SCHEDULE_SUCCESS - In case of success.
 */
ScheduleResult scheduleAddLine(Schedule schedule, ScheduleLineType type, int number,
				const char *description, double price);

/*
 * scheduleRemoveLine
 *
 *  Description:
 *      Removes an existing line from Schedule.
 *  Parameters:
 *      schedule - An existing Schedule.
 *      number - The number of the line,
 *					must be in the inclusive range [1 ... 9999].
 *  Result:
 *      SCHEDULE_NULL_ARG - If one or more parameters are NULL.
 *      SCHEDULE_INVALID_LINE_NUMBER - If number is invalid.
 *      SCHEDULE_LINE_DOESNT_EXIST - If a line with thie number already exists.
 *      SCHEDULE_SUCCESS - In case of success.
 */
ScheduleResult scheduleRemoveLine(Schedule schedule, int number);

/*
 * scheduleAddStationToLine
 *
 *  Description:
 *      Adds station at the end of a given line.
 *      The function fails if the station doesn't exists in the pool.
 *  Parameters:
 *      schedule - An existing Schedule.
 *      number - The number of the line,
 *					must be in the inclusive range [1 ... 9999].
 *      station - The name of the station.
 *      time - The time, in minutes, from the beginning of the journey
 *				to this station. The time must be bigger or equal to zero
 *  Result:
 *      SCHEDULE_NULL_ARG - If one or more parameters are NULL.
 *      SCHEDULE_INVALID_LINE_NUMBER - If number is invalid.
 * 		SCHEDULE_INVALID_TIME - If time is invalid.
 *      SCHEDULE_LINE_DOESNT_EXIST - If a line with thie number already exists.
 *      SCHEDULE_SUCCESS - In case of success.
 */
ScheduleResult scheduleAddStationToLine(Schedule schedule, int number,
						 const char *station, int time);

/*
 * scheduleRemoveStationFromLine
 *
 *  Description:
 *      Removes a station from a given line.
 *  Parameters:
 *      schedule - An existing Schedule.
 *      number - The number of the line,
 *					must be in the inclusive range [1 ... 9999].
 *      index - The index of the station to be removed.
 *				Can be any number in the inclusive range [-1 ... N-1],
 *				where N is the number of stations in the line.
 *				0 means the 1st station, 1 means the 2nd station, etc.
 *				-1 means the last station.
 *  Result:
 *      SCHEDULE_NULL_ARG - If one or more parameters are NULL.
 *      SCHEDULE_INVALID_LINE_NUMBER - If number is invalid.
 *      SCHEDULE_LINE_DOESNT_EXIST - If the line doesn't exist.
 *      SCHEDULE_STATION_DOESNT_EXIST - If no station at the requested index.
 *      SCHEDULE_SUCCESS - In case of success.
 */
ScheduleResult scheduleRemoveStationFromLine(Schedule schedule, int number, int index);

/*
 * scheduleReportStationsForLine
 *
 *  Description:
 *      Prints the stations of a given line.
 *		First the line details are printed.
 *		For bus line - <line type> <line number> <company name>
 *						<first station> <last station> <price>
 *		For train/metro line - <line type> <line number> <train type>
 *								<first station> <last station> <price>
 *		Then the list of the stations will be printed.
 *  Parameters:
 *      schedule - An existing Schedule.
 *		number - The number of the line, integer in the inclusive range [1 ... 9999].
 *  Result:
 *      SCHEDULE_NULL_ARG - If one or more parameters are NULL.
 *      SCHEDULE_INVALID_LINE_NUMBER - If number is invalid.
 *      SCHEDULE_LINE_DOESNT_EXIST - If the line doesn't exist.
 *      SCHEDULE_SUCCESS - In case of success.
 */
ScheduleResult scheduleReportStationsForLine(Schedule schedule, int number);

/*
 * scheduleReportLines
 *
 *  Description:
 *      Prints the lines in Schedule. If type != SCHEDULE_LINE_ALL, then only lines
 *		of the specific type will be printed.
 *		For bus line the following details will be printed:
 *			line type, line number, company name, first station, last station and price.
 *		For train line the following details will be printed:
 *			line type, line number, train type, first station, last station and price.
 *		For lines with no stations at all "N/A" will be printed as first and last stations.
 *  Parameters:
 *      schedule - An existing Schedule.
 *      type - The type of the lines.
 *  Result:
 *      SCHEDULE_NULL_ARG - If one or more parameters are NULL.
 *      SCHEDULE_INVALID_LINE_TYPE - If there're no registered stations in Schedule.
 *      SCHEDULE_NO_LINES - If there're no such lines in Schedule.
 *      SCHEDULE_SUCCESS - In case of success.
 */
ScheduleResult scheduleReportLines(Schedule schedule, ScheduleLineType type);

/*
 * scheduleReportLinesBetweenStations
 *
 *  Description:
 *      Prints all the lines in Schedule, that pass in station "to" AFTER they
 *		passed in station "from". Note that the order of the journey matters.
 *		The lines will be sorted in ascending price order. Lines with equal
 *		price order does not matter.
 *		For bus line the following details will be printed:
 *			line type, line number, company name, first station, last station and price.
 *		For train line the following details will be printed:
 *			line type, line number, train type, first station, last station and price.
 *  Parameters:
 *      schedule - An existing Schedule.
 *      from - The origin station.
 *      to - The destination station.
 *  Result:
 *      SCHEDULE_NULL_ARG - If one or more parameters are NULL.
 *      SCHEDULE_STATION_DOESNT_EXIST - If any of the station doesn't exist.
 *      SCHEDULE_NO_LINES - If there're no appropriate lines in Schedule.
 *      SCHEDULE_SUCCESS - In case of success.
 */
ScheduleResult scheduleReportLinesBetweenStations(Schedule schedule, const char *from,
								   const char *to);

 void test(Schedule schedule);
#endif /* __SCHEDULE_H__ */
