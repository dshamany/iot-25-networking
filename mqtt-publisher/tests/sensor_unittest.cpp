#include <gtest/gtest.h>
#include <cmath>
#include "sensor.h"

// --- Builders ---

TEST(SensorBuilders, TemperatureSensorCelsiusHasCelsiusType) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Celsius);
  ASSERT_EQ(sensor.type, SensorType::Temperature_C);
}

TEST(SensorBuilders, TemperatureSensorFahrenheitHasFahrenheitType) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Farenheight);
  ASSERT_EQ(sensor.type, SensorType::Temperature_F);
}

TEST(SensorBuilders, HumiditySensorHasHumidityType) {
  Sensor sensor = Sensor::humidity_sensor();
  ASSERT_EQ(sensor.type, SensorType::Humidity);
}

// --- read() ---

TEST(SensorRead, StoresTheGivenValue) {
  Sensor sensor = Sensor::humidity_sensor();
  sensor.read(42.5f);
  ASSERT_FLOAT_EQ(sensor.value, 42.5f);
}

TEST(SensorRead, StampsTheCurrentTime) {
  Sensor sensor = Sensor::humidity_sensor();
  time_t before = time(nullptr);
  sensor.read(1.0f);
  time_t after = time(nullptr);

  ASSERT_GE(sensor.timestamp, before);
  ASSERT_LE(sensor.timestamp, after);
}

TEST(SensorRead, OverwritesPreviousValueAndTimestamp) {
  Sensor sensor = Sensor::humidity_sensor();
  sensor.read(1.0f);
  time_t first_timestamp = sensor.timestamp;

  sensor.read(2.0f);

  ASSERT_FLOAT_EQ(sensor.value, 2.0f);
  ASSERT_GE(sensor.timestamp, first_timestamp);
}

// --- get_type() ---

TEST(SensorGetType, CelsiusReportsTemperature) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Celsius);
  ASSERT_EQ(sensor.get_type(), "temperature");
}

TEST(SensorGetType, FahrenheitReportsTemperature) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Farenheight);
  ASSERT_EQ(sensor.get_type(), "temperature");
}

TEST(SensorGetType, HumidityReportsHumidity) {
  Sensor sensor = Sensor::humidity_sensor();
  ASSERT_EQ(sensor.get_type(), "humidity");
}

TEST(SensorGetType, UnknownTypeReportsUnknown) {
  Sensor sensor = Sensor::humidity_sensor();
  sensor.type = static_cast<SensorType>(999);
  ASSERT_EQ(sensor.get_type(), "UNKNOWN_SENSOR");
}

// --- get_unit() ---

TEST(SensorGetUnit, CelsiusUsesDegreesCelsius) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Celsius);
  ASSERT_EQ(sensor.get_unit(), "°C");
}

TEST(SensorGetUnit, FahrenheitUsesDegreesFahrenheit) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Farenheight);
  ASSERT_EQ(sensor.get_unit(), "°F");
}

TEST(SensorGetUnit, HumidityUsesPercent) {
  Sensor sensor = Sensor::humidity_sensor();
  ASSERT_EQ(sensor.get_unit(), "%");
}

TEST(SensorGetUnit, UnknownTypeReportsUnknown) {
  Sensor sensor = Sensor::humidity_sensor();
  sensor.type = static_cast<SensorType>(999);
  ASSERT_EQ(sensor.get_unit(), "UNKNOWN_UNIT");
}

// --- get_value() ---

TEST(SensorGetValue, FormatsPositiveValue) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Celsius);
  sensor.read(21.5f);
  ASSERT_EQ(sensor.get_value(), std::to_string(21.5f));
}

TEST(SensorGetValue, FormatsNegativeValue) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Farenheight);
  sensor.read(-40.0f);
  ASSERT_EQ(sensor.get_value(), std::to_string(-40.0f));
}

TEST(SensorGetValue, FormatsZero) {
  Sensor sensor = Sensor::humidity_sensor();
  sensor.read(0.0f);
  ASSERT_EQ(sensor.get_value(), std::to_string(0.0f));
}

// --- to_csv_row() ---

TEST(SensorToCsvRow, ContainsIsoTimestampTypeValueAndUnit) {
  Sensor sensor = Sensor::temperature_sensor(TemperatureUnit::Celsius);
  sensor.timestamp = 0;  // 1970-01-01T00:00:00Z
  sensor.value = 21.5f;

  std::string expected = "1970-01-01T00:00:00Z,temperature," +
                          std::to_string(21.5f) + ",°C";

  ASSERT_EQ(sensor.to_csv_row(), expected);
}

TEST(SensorToCsvRow, ReflectsHumiditySensor) {
  Sensor sensor = Sensor::humidity_sensor();
  sensor.timestamp = 0;
  sensor.value = 55.0f;

  std::string expected = "1970-01-01T00:00:00Z,humidity," +
                          std::to_string(55.0f) + ",%";

  ASSERT_EQ(sensor.to_csv_row(), expected);
}
