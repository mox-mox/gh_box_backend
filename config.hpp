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
#define HEATER_PIN                   9 // TODO: Insert correct value
#define FAN_PIN                      8 // TODO: Insert correct value
#define PUMP_PIN                     7 // TODO: Insert correct value
#define LAMP_PIN                     10 // TODO: Insert correct value

#define TEMP_PIN                     2  
#define PH_PIN                       0 // TODO: Insert correct value
#define EC_PIN                       0 // TODO: Insert correct value
#define EC_TEMP_PIN                  0


// Default times, all in milliseconds
#define SAMPLING_PERIOD_TEMP         500
#define SAMPLING_PERIOD_PH           500
#define SAMPLING_PERIOD_EC           500

#define PUMP_PERIOD                  15*60*1000
#define PUMP_DUTY_CYCLE              1*60*1000

#define LAMP_PERIOD                  24*60*60*1000
#define LAMP_DUTY_CYCLE              12*60*60*1000

#define MESSAGE_PERIOD_SLOW          500
#define MESSAGE_PERIOD_FAST          50

#define NOMINAL_TEMP                 28*10
#define TEMP_MARGIN                  1*10



// constants won't change. Used here to set a pin number :
#define ledPin 13      // the number of the LED pin
extern int ledState;



#endif /* CONFIG_HPP */
