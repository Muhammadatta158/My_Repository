#include "driver.h"
#include "Pressure_Sensor.h"
#include "My_Algorithm.h"

int Threshold = 20;

int High_Pressure_Detected()
{
	int Pressure_Value = Send_Pressure_Value();
	if(Pressure_Value > Threshold){
		Pressure_Status = High_Pressure;
		return 1;

	}else{return 0;}
}
