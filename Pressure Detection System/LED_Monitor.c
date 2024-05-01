#include "driver.h"
#include "LED_Monitor.h"
#include "Pressure_Sensor.h"
#include "My_Algorithm.h"

int Alarm_Duration = 600000; //60 seconds

void Start_Monitor()
{
	if(High_Pressure_Detected()){
		LED_STATUS = LED_ON;
		Set_Alarm_actuator(LED_STATUS);
		Delay(Alarm_Duration);
		Set_Alarm_actuator(LED_OFF);

	}
}
