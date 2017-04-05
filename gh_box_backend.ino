#include "config.hpp"
//#include "sensors.hpp"


Periodic_actuator        pump(PUMP_PIN, PUMP_PERIOD, PUMP_DUTY_CYCLE);
Periodic_actuator        lamp(LAMP_PIN, LAMP_PERIOD, LAMP_DUTY_CYCLE);

PH_sensor                ph(PH_PIN, SAMPLING_PERIOD_PH);
EC_sensor                ec(EC_PIN, EC_TEMP_PIN, SAMPLING_PERIOD_EC);
Temp_sensor              temp(TEMP_PIN, HEATER_PIN, FAN_PIN, SAMPLING_PERIOD_TEMP, NOMINAL_TEMP, TEMP_MARGIN);

Message_interface        communicate;


int ledState = 0;

void setup(void)
{
	Serial.begin(9600);

	// set the digital pin as output:
	pinMode(ledPin, OUTPUT);
	pinMode(FAN_PIN,OUTPUT);//FAN
	pinMode(HEATER_PIN,OUTPUT);//HEATHER
	pinMode(PUMP_PIN,OUTPUT);//PUMP
	pinMode(LAMP_PIN ,OUTPUT);//LED

	ledState = 0;
	digitalWrite(ledPin, ledState);
	return;
}


void loop(void)
{
	// Create a timebase
	uint32_t current_time = millis();

	// Read the sensors
	temp(current_time); // Temperature sensor will also controll the radiator and fan
	ph(current_time);
	ec(current_time);

	// See if we need to turn on the water pump or the lamp
	pump(current_time);
	lamp(current_time);
}


void serialEvent()
{
	communicate();
}
