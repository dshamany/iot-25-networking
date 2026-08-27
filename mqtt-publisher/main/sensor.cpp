#include "sensor.h"
#include "timestamp.h"
#include <string>

void Sensor::read(float value) {
  this->timestamp = time(nullptr);
  this->value = value;
}

std::string Sensor::get_value() {
  return std::to_string(this->value);
}

std::string Sensor::get_unit() {
  switch(this->type) {
    case SensorType::Humidity:
      return "%";
    case SensorType::Temperature_C:
      return "°C";
    case SensorType::Temperature_F:
      return "°F";
    default:
      return "UNKNOWN_UNIT";
  }
}

std::string Sensor::get_type() {
  switch(this->type) {
    case SensorType::Humidity:
      return "humidity";
    case SensorType::Temperature_C:
    case SensorType::Temperature_F:
      return "temperature";
    default:
      return "UNKNOWN_SENSOR";
  }
}

std::string Sensor::to_csv_row() {
  return time_to_iso8601(this->timestamp) + "," + this->get_type() + "," + this->get_value() + "," + this->get_unit();
}

Sensor Sensor::temperature_sensor(TemperatureUnit unit) {
  Sensor sensor{};
  switch(unit) {
    case TemperatureUnit::Celsius:
      sensor.type = Temperature_C;
      break;
    case TemperatureUnit::Farenheight:
      sensor.type = Temperature_F;
      break;
  }

  return sensor;
}

Sensor Sensor::humidity_sensor() {
  Sensor sensor{};
  sensor.type = SensorType::Humidity;
  return sensor;
}
