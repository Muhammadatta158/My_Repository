#include "Pressure_Sensor.h"
#include "driver.h"

int Pressure_Value;

void Sensor_init()
{
	GPIO_INITIALIZATION ();
}


void Sensor_Reading()
{
	//Set the state name of the sensor state
	Sensor_State = Reading;

	//Get the pressure value
	Pressure_Value = getPressureVal();

}

//Send Pressure Value
int Send_Pressure_Value()
{
	return Pressure_Value;
}
