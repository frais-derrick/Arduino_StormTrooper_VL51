#include "Adafruit_VL53L1X.h"

#define IRQ_PIN 2
#define XSHUT_PIN 3

#define DETECTION_DISTANCE  2000      /// 2m

//Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X();

/// Simultate Storm Trooper Shooting
void shootIntruder()
{
  int i;

  for(i=0; i<2; i++)
  {
        digitalWrite(10, HIGH);
        delay(250);
        digitalWrite(10, LOW);
        delay(250);
  }

  delay(500);

  for(i=0; i<3; i++)
  {
        digitalWrite(10, HIGH);
        delay(150);
        digitalWrite(10, LOW);
        delay(100);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);

  Wire.setSDA(8);
  Wire.setSCL(9);


  Serial.println(F("Adafruit VL53L1X sensor demo"));

  Wire.begin();
  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(vl53.sensorID(), HEX);

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(vl53.getTimingBudget());

  /*
  vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
  vl.VL53L1X_SetInterruptPolarity(0);
  */
}

void loop() {
  int16_t distance;

  if (vl53.dataReady()) {
    // new measurement for the taking!
    distance = vl53.distance();
    if (distance == -1) {
      // something went wrong!
      Serial.print(F("Couldn't get distance: "));
      Serial.println(vl53.vl_status);
      return;
    }
    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.println(" mm");

    if(distance < DETECTION_DISTANCE)
    {
      shootIntruder();
    }

    // data is read out, time for another reading!
    vl53.clearInterrupt();
  }
}
