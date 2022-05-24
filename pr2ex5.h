#ifndef __PR2_EX5__
#define __PR2_EX5__

#include <stdio.h> // For FILE*, you should avoid including unnecessary header files

#define LINE_TYPE(X)       \
	X(SCHEDULE_LINE_BUS)   \
	X(SCHEDULE_LINE_TRAIN) \
	X(SCHEDULE_LINE_METRO)

#define LINE_TYPE_AS_ENUM(type) type,

typedef enum
{
	LINE_TYPE(LINE_TYPE_AS_ENUM)
		SCHEDULE_LINE_ALL,
} ScheduleLineType;

/*
 * schedulePrintLine: Prints a schedule line
 *
 * outputChannel - file descriptor to print to.
 * type - type of the line.
 * number - Line number
 * description - For bus: The company running the line
 *               Otherwise: one of the following: "Suburban", "Intercity", "Direct"
 * firstStation - First station of the line, NULL if it does not exist.
 * lastStation - Last station of the line, NULL if it does not exist.
 * price - Fair price for the line
 *
 * return value - number of characters printed, or a negative number in
 * 	case of failure.
 */
int schedulePrintLine(FILE *outputChannel,
					  ScheduleLineType type,
					  int number,
					  const char *description,
					  const char *firstStation,
					  const char *lastStation,
					  double price);

/*
 * schedulePrintStation: Prints the name of a given station and its arrival time.
 *
 * outputChannel - file descriptor to print to.
 * station - Station's name.
 * time - Arrival time in minutes.
 *
 * return value - number of characters printed, or a negative number in
 * 	case of failure.
 */
int schedulePrintStation(FILE *outputChannel, const char *station, int time);

#endif /* __PR2_EX5__ */
