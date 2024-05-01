#include "driver.h"
#include "LED_Monitor.h"
#include "Pressure_Sensor.h"
#include "My_Algorithm.h"
#include "LED_Actuator.h"

int main(void)
{
	Sensor_init();
	LED_init();
	 while(1)
	 {
		 Sensor_Reading();
		 High_Pressure_Detected();
		 Start_Monitor();
	 }
}