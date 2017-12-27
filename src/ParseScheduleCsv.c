#include "ParseScheduleFunctions.h"
#include "ParseScheduleCsv.h"

int* getOutputsStatusForTime(int currentDay, int currentHour, int currentMinute, struct ScheduledIrrigation* scheduleArray, int scheduleCount)
{
    int* outputs = malloc(8 * sizeof(int));
    for(int i=0; i<8; i++){
    	outputs[i] = 0;
    }
    int currentMinuteOfDay = currentHour * 60 + currentMinute;

    for( int i=0; i < scheduleCount; i++){
		int scheduledDay = scheduleArray[i].day;
		int scheduledStartHour = scheduleArray[i].startTime[0];
		int scheduledStartMinute = scheduleArray[i].startTime[1];
		int scheduledEndHour = scheduleArray[i].endTime[0];
		int scheduledEndMinute = scheduleArray[i].endTime[1];

		int scheduledStartMinuteOfDay = scheduledStartHour * 60 + scheduledStartMinute;
		int scheduledEndMinuteOfDay = scheduledEndHour * 60 + scheduledEndMinute;

		printf("Processing Schedule\n");
		if( currentDay == scheduledDay && currentMinuteOfDay >= scheduledStartMinuteOfDay && currentMinuteOfDay <= scheduledEndMinuteOfDay){
			//to do: add to the array of enabled outputs
			for (int j=0; j<scheduleArray[i].outputCount; j++){
				int output = scheduleArray[i].outputs[j];
				if(j < 8){
					outputs[j] = scheduleArray[i].outputs[j];
				}
			}
		}

	}
    return outputs;
}


//Unit Tests
//this is an example of usage. In the real implementation we will use the for loop and check each line to see
//if it contains the day and hours and minute.
//if currentDay == scheduleDay
//and curentMinute >= startTime and curentMinute <= endTime
//then start the outputs specified
//if not schedule matches, turn off all
void printSchedules(struct ScheduledIrrigation* scheduleArray, int scheduleCount){

	for( int i=0; i < scheduleCount; i++){
		//scheduleArray[i]->startTime, scheduleArray[i]->endTime
		printf("Day: %i, From: %i:%i, To: %i:%i, Outs: %s",
				scheduleArray[i].day,
				scheduleArray[i].startTime[0],
				scheduleArray[i].startTime[1],
				scheduleArray[i].endTime[0],
				scheduleArray[i].endTime[1],
				"");
		for(int j=0; j<scheduleArray[i].outputCount; j++){
			int out = scheduleArray[i].outputs[j];
			printf("%i,", out);
		}
		printf("\n");
	}
	free(scheduleArray);
	printf("Done\n");

}


