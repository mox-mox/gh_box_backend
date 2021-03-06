#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "sensors.hpp"
#include "actuators.hpp"



extern Periodic_actuator        pump;
extern Periodic_actuator        lamp;

extern PH_sensor                ph;
extern EC_sensor                ec;
extern Temp_sensor              temp;

#include "message.hpp"

//extern Message                  communicate;

// The pins
#define HEATER_PIN                   9
#define FAN_PIN                      8
#define PUMP_PIN                     7
#define LAMP_PIN                     10

#define TEMP_PIN                     2
#define PH_PIN                       A0
#define EC_PIN                       A1
#define EC_TEMP_PIN                  4


// Default times, all in milliseconds
#define SAMPLING_PERIOD_TEMP         500
#define SAMPLING_PERIOD_PH           500
#define SAMPLING_PERIOD_EC           500

#define PUMP_PERIOD                  1000
#define PUMP_DUTY_CYCLE              800
//#define PUMP_PERIOD                  15*60*1000
//#define PUMP_DUTY_CYCLE              1*60*1000

//#define LAMP_PERIOD                  24*60*60*1000
//#define LAMP_DUTY_CYCLE              12*60*60*1000
#define LAMP_PERIOD                  200000ul
#define LAMP_DUTY_CYCLE              100000ul

#define MESSAGE_PERIOD_SLOW          500
#define MESSAGE_PERIOD_FAST          50

#define NOMINAL_TEMP                 28*10
#define TEMP_MARGIN                  1*10



// constants won't change. Used here to set a pin number :
#define ledPin 13      // the number of the LED pin
extern int ledState;






#endif /* CONFIG_HPP */
