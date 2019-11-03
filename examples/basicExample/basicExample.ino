#include <mq135.h>

//simple for arduino
Mq135 sensor(A0); //A0 is analog input pin, feel free to set it to any other
//advanced mode :D ->>> Mq135 sensor(pin, num_of_averaging_samples, ADC_bit_resolution, ADC_voltage_reference);
//examples:
//Mq135 sensor(A0,30,10,3.3); // for ESP8266 microcontrollers
//Mq135 sensor(PA_0,30,12,3.3); // for STM32 f1 microcontrollers eg. bluepill board

void setup() {
   // analogReadResolution(12); only for bluepill board/others with 12bits ADC
    Serial.begin(9600);

    // set LOAD RESISTANCE in kilo-ohms, must be mathing with SMD resistor on sensor PCB board 
    // mostly it is resistor with number 102, whith corresponding 1 kOhm resistance
    // if you dont set it, 1kOhm value will be loaded by default
    sensor.setRL(1); 

    Serial.println("Heating sensor and Calibrating\n Wait 20 sec...\n");
    delay(20000);
    Serial.print("Calibrated R0 value = ");
    Serial.print(sensor.calibrate(8));  // !!!!!!  replace '8' with actual ppm concentration of Benzene in air !!!!!!
    Serial.print("kOhms\n\n");
    delay(3000);
    //after calibrating sensor, you can read calibrated R0 value, and you can use this:
    // sensor.setR0(123) // replace 123 with calibrated R0 value printed from calibration, to permanently calibrate it
}

void loop() {
  //MQ-135 is sensitive for temperature and humidity of air
  // values needed for calibrated ppm
  float temperature = 13.2; // in celcius degres
  float humidity = 33; // in %

  Serial.print("Benzene (C6H6) ppm: ");
  Serial.println(sensor.getPPM());
  
  Serial.print("temp and humidity corrected ppm value: ");
  Serial.println(sensor.getCorrectedPPM(20,33)); // correction first parameter temp, second humidity
  Serial.println();
  
  delay(2000);

}
