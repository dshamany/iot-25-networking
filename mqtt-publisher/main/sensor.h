#pragma once

#include <time.h>
#include <string>

enum SensorType {
  Temperature_F,
  Temperature_C,
  Humidity
};

enum TemperatureUnit {
  Farenheight,
  Celsius
};

struct Sensor {
  time_t timestamp;
  SensorType type; 
  float value;

  // Getters
  std::string get_value();
  std::string get_type();
  std::string get_unit();

  // Setters
  void read(float);
  std::string to_csv_row();

  // Builders
  static Sensor temperature_sensor(TemperatureUnit);
  static Sensor humidity_sensor();

};
