#ifndef SENSORS_HPP
#define SENSORS_HPP

#include "config.hpp"
#include "actuators.hpp"

#include <OneWire.h>
#include <DallasTemperature.h>

//{{{ class Sensor

class Sensor
{
	protected:
		uint8_t sensing_pin;
		uint32_t sampling_period;
		uint32_t sampling_time = 0;
		virtual uint32_t measure(void) const = 0;	// Return the current sensor read out
		//{
		//	//return analogRead(sensing_pin);
		//	return 0x44;
		//}
		virtual void process(uint32_t measure) = 0;	// Do filtering on the sensor value and store it
		uint32_t value = 0;

	public:
		virtual Sensor(uint8_t sensing_pin, uint32_t sampling_period) : sensing_pin(sensing_pin), sampling_period(sampling_period) {}
		uint32_t get_value(void)
		{
			return value;
		}
		void set_period(uint32_t period)
		{
			sampling_period = period;
		}
		uint32_t get_period(void)
		{
			return sampling_period;
		}

		virtual void operator()(const uint32_t current_time)
		{
			if( sampling_time+sampling_period <= current_time )
			{
				process(measure());
			}
		}
};
//}}}

//{{{ class Temp_sensor

class Temp_sensor: public Sensor
{
	uint32_t nominal_temperature;
	uint32_t temperature_plus_margin;
	uint32_t temperature_minus_margin;

	OneWire one_wire_interface;	//(ONE_WIRE_BUS);
	DallasTemperature sensor_backend;	//(&oneWire);

	// Some stuff like an array for low-pass filtering, etc.

	uint32_t measure(void) const override	// The temperature sensor is measured differently
	{
		int t2;
// Send the command to get temperatures
  sensor_backend.requestTemperatures();  
  Serial.print("Temperature is: ");
 
 // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  float t1=sensor_backend.getTempCByIndex(0)*10;
  t2= (int) t1;
 
 return t2;
	}

	void process(uint32_t measure)
	{
		// TODO filter
		uint32_t temp = measure;

		if( temp > nominal_temperature+temperature_plus_margin )
		{
			fan.start();
		}
		else if( temp < nominal_temperature )
		{
			fan.stop();
		}

		if( temp > nominal_temperature )
		{
			heater.stop();
		}
		else if( temp < nominal_temperature-temperature_minus_margin )
		{
			heater.start();
		}

		value = temp;
	}

	public:
		Actuator heater;
		Actuator fan;

		Temp_sensor(uint8_t sensing_pin,
		            uint8_t heater_pin,
		            uint8_t fan_pin,
		            uint32_t sampling_period,
		            uint32_t nominal_temperature,
		            uint32_t temperature_plus_margin = 0,
		            uint32_t temperature_minus_margin = 0) : Sensor(sensing_pin, sampling_period),
			nominal_temperature(nominal_temperature),
			temperature_plus_margin(temperature_plus_margin ? temperature_plus_margin : 100),
			temperature_minus_margin(temperature_minus_margin ? temperature_minus_margin : (temperature_plus_margin ? temperature_plus_margin : 100)),
			one_wire_interface(sensing_pin),
			sensor_backend(&one_wire_interface),
			heater(heater_pin),
			fan(fan_pin)
		{}

		void set_nominal_temperature(uint32_t temperature)
		{
			nominal_temperature = temperature;
		}
		void set_plus_margin(uint32_t margin)
		{
			temperature_plus_margin = margin;
		}
		void set_minus_margin(uint32_t margin)
		{
			temperature_minus_margin = margin;
		}

		uint32_t get_nominal_temperature(void)
		{
			return nominal_temperature;
		}
		uint32_t get_plus_margin(void)
		{
			return temperature_plus_margin;
		}
		uint32_t get_minus_margin(void)
		{
			return temperature_minus_margin;
		}
};
//}}}

//{{{ class EC_sensor

class EC_sensor: public Sensor
{
	using Sensor::Sensor;
	// If we titrate the water, we'll add electrolytes.
	// Let's track their amount as a current offset
	// Static because offset will be the same for all sensors
	static int32_t current_offset;

	uint32_t measure(void) const	// Return the current sensor read out
	{
		//return analogRead(sensing_pin);
		return 0x44;
	}
	// Some stuff like an array for low-pass filtering, etc.

	void process(uint32_t measure)
	{
		// TODO filter
		value = measure;
	}
	public:
		static void add_offset(int32_t offset)
		{
			current_offset += offset;
		}
		static void set_offset(int32_t offset)
		{
			current_offset = offset;
		}
		static int32_t get_offset(void)
		{
			return current_offset;
		}
};

int32_t EC_sensor::current_offset = 0;
//}}}

//{{{ class PH_sensor

class PH_sensor: public Sensor
{
	using Sensor::Sensor;
	// Some stuff like an array for low-pass filtering, etc.

  
	uint32_t measure(void) const// Return the current sensor read out
	{

 unsigned long int avgValue;  //Store the average value of the sensor feedback
 float b;
 int buf[10],temp;
  
   for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(sensing_pin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
	 phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  digitalWrite(13, HIGH);       
  delay(800);
  digitalWrite(13, LOW); 
	}

	void process(uint32_t measure)
	{
		// TODO filter
		// if there is a change, inform the EC sensor of the offset
		// EC_sensor::add_offset(xxx);
		value = measure;
	}
};
//}}}



#endif /* SENSORS_HPP */
