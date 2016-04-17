#include <health.h>

static void health_handler(HealthEventType event, void *context) {

	#if defined(PBL_HEALTH)
				HealthMetric metric = HealthMetricStepCount;
				time_t start = time_start_of_today();
				time_t end = time(NULL);


				// Check the metric has data available for today
				HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, start, end);

				if(mask & HealthServiceAccessibilityMaskAvailable) {
					// Data is available!
					char stepsCount[] = "Steps: ";
					char itoaReturn[15];
					memset(&itoaReturn[0], 0, sizeof(itoaReturn));
					itoa((int)health_service_sum_today(metric), itoaReturn);
					strcat(stepsCount, itoaReturn);
					 APP_LOG(APP_LOG_LEVEL_INFO,  stepsCount);
					APP_LOG(APP_LOG_LEVEL_INFO,  "steps: %d",(int)health_service_sum_today(metric));
					//memcpy(&weekday_text,stepsCount, sizeof(weekday_text));
				}
	#endif

}
