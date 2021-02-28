#include <EEPROM.h>
#include "C:/Users/Brian/Documents/Programming/Arduino/ProMiniTest/OutputModule/offgrid_arduino/shared_constants.h"
#include "C:/Users/Brian/Documents/Programming/Arduino/ProMiniTest/OutputModule/offgrid_arduino/internal_constants.h"

// BANK 0 - Defaults for 200Ah Battleborn lithium, 500A/50mv shunt
#define AMPS0_ADC_SCALE     0.0000078125
#define AMPS0_AMPS        500.0
#define AMPS0_VOLTS         0.05
#define AMPS0_CORRECTION    1.0
#define VOLTS0_SCALE        0.00125
#define VOLTS0_CORRECTION   1.0

// BANK 1 - Defaults for 200Ah FLA, 200A/75mv shunt
#define AMPS1_ADC_SCALE     0.0000078125
#define AMPS1_AMPS        200.0
#define AMPS1_VOLTS         0.075
#define AMPS1_CORRECTION    1.0
#define VOLTS1_SCALE        0.00125
#define VOLTS1_CORRECTION   1.0

void setup() {
  struct BMConst battery_monitor_const[2];

  Serial.begin(115200);

  battery_monitor_const[0].amps_multiplier = AMPS0_ADC_SCALE * AMPS0_AMPS / AMPS0_VOLTS * AMPS0_CORRECTION;
  battery_monitor_const[0].volts_multiplier = VOLTS0_SCALE * VOLTS0_CORRECTION;
  battery_monitor_const[0].amphours_capacity = 198;
  battery_monitor_const[0].volts_charged = 14.4;
  battery_monitor_const[0].minutes_charged_detection_time = 3;
  battery_monitor_const[0].current_threshold = 0.001;
  battery_monitor_const[0].tail_current_factor = 0.04;
  battery_monitor_const[0].peukert_factor = 1.05;
  battery_monitor_const[0].charge_efficiency_factor = 0.99;
  
  battery_monitor_const[1].amps_multiplier = AMPS1_ADC_SCALE * AMPS1_AMPS / AMPS1_VOLTS * AMPS1_CORRECTION;
  battery_monitor_const[1].volts_multiplier = VOLTS1_SCALE * VOLTS1_CORRECTION;
  battery_monitor_const[1].amphours_capacity = 198;
  battery_monitor_const[1].volts_charged = 13.8;
  battery_monitor_const[1].minutes_charged_detection_time = 3;
  battery_monitor_const[1].current_threshold = 0.001;
  battery_monitor_const[1].tail_current_factor = 0.04;
  battery_monitor_const[1].peukert_factor = 1.25;
  battery_monitor_const[1].charge_efficiency_factor = 0.95;  

  EEPROM.put(0, battery_monitor_const);
  
  // Ensure the rest is set to factory condition, 0xFF
  for ( unsigned int i = sizeof(battery_monitor_const); i < EEPROM.length(); i++ ) {
    EEPROM.update(i, 0xFF);
  }

  // Read out the contents of EEPROM to verify

  EEPROM.get(0, battery_monitor_const);

  for (unsigned int i = 0; i < ( sizeof(battery_monitor_const)/sizeof(battery_monitor_const[0]) ); i++) {
    Serial.print("Bank ");Serial.print(i); Serial.println(":");
    Serial.print("amps_multiplier: "); Serial.println(battery_monitor_const[i].amps_multiplier, 12);
    Serial.print("volts_multiplier: "); Serial.println(battery_monitor_const[i].volts_multiplier, 6);
    Serial.print("amphours_capacity: "); Serial.println(battery_monitor_const[i].amphours_capacity);
    Serial.print("volts_charged: "); Serial.println(battery_monitor_const[i].volts_charged, 3);
    Serial.print("minutes_charged_detection_time: "); Serial.println(battery_monitor_const[i].minutes_charged_detection_time);
    Serial.print("current_threshold: "); Serial.println(battery_monitor_const[i].current_threshold, 3);
    Serial.print("tail_current_factor: "); Serial.println(battery_monitor_const[i].tail_current_factor, 3);
    Serial.print("peukert_factor: "); Serial.println(battery_monitor_const[i].peukert_factor, 3);
    Serial.print("charge_efficiency_factor: "); Serial.println(battery_monitor_const[i].charge_efficiency_factor, 2);
    Serial.println();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
