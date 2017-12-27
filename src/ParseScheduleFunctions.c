#include "ParseScheduleFunctions.h"


//when using pointers instead of arrays it is important to allocate memory on the heap with SIZE+1
//the last element is set to 0 to identify the end of the array

char** str_split(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}

struct ScheduledIrrigation handleLine(char* line)
{
	struct ScheduledIrrigation si;
	si.outputCount = 8;
	char** tokens2;
	tokens2 = str_split(line, ',');
	if (tokens2)
    {
		si.day = atoi(tokens2[0]);

		for(int k=0; k<si.outputCount; k++){
			si.outputs[k] = 0;
		}

		//*(si.startTime) = parseTime(tokens2[1]);
		//*(si.endTime) = parseTime(tokens2[2]);
		parseTime(tokens2[1], si.startTime);
		parseTime(tokens2[2], si.endTime);

		char** outputs = str_split(tokens2[3], ';');
		if( outputs ){
			int numberOfOutputs = 0;
			for( ; *(outputs + numberOfOutputs); numberOfOutputs++);
			for( int i=0; i<numberOfOutputs; i++){
				//si.outputs[i] =  atoi(outputs[i]);
				int outputIndex =  atoi(outputs[i]);
				si.outputs[outputIndex] = 1;
			}
		}
		free(outputs);
		free(tokens2);
	}
	return si;
}

struct ScheduledIrrigation* parseCsv(char* csvString, int* scheduleCount)
{
    char** tokens;
    //printf("csvString=[%s]\n\n", csvString);

    tokens = str_split(csvString, '\n');
    int lineCount = 0;
    for( ;*(tokens+lineCount); lineCount++);

    //allocate memory for the array of pointers. SIZE_OF_POINTER_TO_A_STRUCT * NUMBER_OF_POINTERS
    struct ScheduledIrrigation* scheduleArray = malloc(sizeof(struct ScheduledIrrigation) * (lineCount));
    *scheduleCount = lineCount;
    //serves as a null element
    //scheduleArray[lineCount] = 0;

    if (tokens)
    {
        int i;
        for (i = 0; *(tokens + i); i++)
        {
        	char* line = *(tokens + i);
            //printf("Line=[%s]\n", line);
        	//schedule is a local variable and must be copied to be returned
            struct ScheduledIrrigation schedule = handleLine(line);
            //printf("Day: %i\n", schedule.day);

            //each element is a pointer to a struct. We allocate memory to hold the actual STRUCT and assign the address to that new memory location to the pointer
            scheduleArray[i].outputCount = 8;
            scheduleArray[i].day = schedule.day;
            scheduleArray[i].startTime[0] = schedule.startTime[0];
            scheduleArray[i].startTime[1] = schedule.startTime[1];
            scheduleArray[i].endTime[0] = schedule.endTime[0];
            scheduleArray[i].endTime[1] = schedule.endTime[1];
            for( int j=0; j<scheduleArray[i].outputCount; j++){
            	scheduleArray[i].outputs[j] = schedule.outputs[j];
            }
            scheduleArray[i].outputCount = schedule.outputCount;

            free( line );

        }
        printf("\n");
        free(tokens);

        //printf("%s\n", scheduleArray[0]->startTime);
        //printf("%s\n", scheduleArray[1]->startTime);
        //printf("%s\n", scheduleArray[2]->startTime);
    }
    return scheduleArray;
}

void parseTime(char* str, int* timeOut){
	char** segments = str_split(str, ':');
	timeOut[0] = atoi(segments[0]);
	timeOut[1] = atoi(segments[1]);

}

//gets a current time in seconds from 1/1/1970 (epoch)
//returns array of enabled inputs
