/*
 * ParseScheduleFunctions.h
 *
 *  Created on: Dec 3, 2017
 *      Author: lee
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef PARSESCHEDULEFUNCTIONS_H_
#define PARSESCHEDULEFUNCTIONS_H_



#endif /* PARSESCHEDULEFUNCTIONS_H_ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ScheduledIrrigation{
	int day;
	int startTime [2];
	int endTime [2];
	int outputs [8];
	int outputCount;
};

char** str_split(char* a_str, const char a_delim);
struct ScheduledIrrigation  handleLine(char* line);
struct ScheduledIrrigation* parseCsv(char* csvString, int* scheduleCount);
void parseTime(char* str, int* timeOut);


#ifdef __cplusplus
}
#endif
