#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// Create sensor object
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup() {
  Serial.begin(115200);
  Serial.println("TSL2561 Light Sensor Test");

  // Initialize sensor
  if (!tsl.begin()) {
    Serial.println("No TSL2561 detected ... Check your wiring or I2C address.");
    while (1);
  }

  // Display sensor details
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");
  Serial.println("------------------------------------");

  // Set gain and integration time
tsl.setGain(TSL2561_GAIN_1X);  // Use 1X gain (normal)
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); // Shorter time for fast updates

  // Optional: Auto gain control
  // tsl.enableAutoRange(true);

  Serial.println("Sensor initialized.\n");
}

void loop() {
  sensors_event_t event;
  tsl.getEvent(&event);

  if (event.light) {
    Serial.print("Light: ");
    Serial.print(event.light);
    Serial.println(" lux");
  } else {
    Serial.println("Sensor overload or too dark to detect light");
  }

  delay(1000); // 1 second delay
}
