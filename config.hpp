#ifndef CONFIG_HPP
#define CONFIG_HPP


// The pins
#define RADIATOR_PIN
#define FAN_PIN
#define ILLUMINATION_PIN
#define PUMP_PIN

#define TEMP_PIN
#define PH_PIN
#define EC_PIN


// Default times
#define SAMPLING_PERIOD_TEMP_SLOW    500
#define SAMPLING_PERIOD_PH_SLOW      500
#define SAMPLING_PERIOD_EC_SLOW      500

#define SAMPLING_PERIOD_TEMP_fast    50
#define SAMPLING_PERIOD_PH_fast      50
#define SAMPLING_PERIOD_EC_fast      50

#define PUMP_PERIOD                  15*60*1000
#define PUMP_DUTY_CYCLE              1*60*1000

#define MESSAGE_PERIOD_SLOW          500
#define MESSAGE_PERIOD_FAST          50

#endif /* CONFIG_HPP */
