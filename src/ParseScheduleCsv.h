#ifdef __cplusplus
extern "C" {
#endif

int* getOutputsStatusForTime(int currentDay, int currentHour, int currentMinute, struct ScheduledIrrigation* scheduleArray, int scheduleCount);
void printSchedules(struct ScheduledIrrigation* scheduleArray, int scheduleCount);
#ifdef __cplusplus
}
#endif
