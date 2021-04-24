/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
#include <LiquidCrystal_I2C.h> // Library for LCD

//Declare a LiquidCrystal_I2C object
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

//Other variables
int b_led_pin=3;
int g_led_pin=6;
int r_led_pin=5;
int temp_low = 35;
int temp_high = 39;
int b_duty_cycle = 255;
int g_duty_cycle = 255;
int r_duty_cycle = 255;
int loop_period = 2000;  //milliseconds
float b_flash_period = 400; //milliseconds
float r_flash_period = 400; //milliseconds
int i;  //FOR loop iterator

void setup(void) 
{ 
 //Serial.begin(9600); 
 
 // Start up the sensor library 
 sensors.begin(); 
 
 //Initialise the lcd
 lcd.init(); //initialize the lcd
 lcd.backlight();  //turn on lcd backlight
 lcd.clear();
 lcd.setCursor(0, 0);  //column_index, row_index
 lcd.print("Temp (degC)");

 //Setup LEDs 
 pinMode(LED_BUILTIN, OUTPUT);
 pinMode(g_led_pin, OUTPUT);  //green
 pinMode(b_led_pin, OUTPUT);  //blue
 pinMode(r_led_pin, OUTPUT);  //red

 //Flash all three LEDs
 analogWrite(b_led_pin, b_duty_cycle);
 analogWrite(g_led_pin, g_duty_cycle);
 analogWrite(r_led_pin, r_duty_cycle);
 delay(500);
 digitalWrite(b_led_pin, LOW);
 digitalWrite(g_led_pin, LOW);
 digitalWrite(r_led_pin, LOW);
} 

void loop(void) 
{ 
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 //Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 //Serial.println("DONE"); 
/********************************************************************/
 //Serial.print("Temperature is: "); 
 //Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 

 lcd.setCursor(0,1);
 lcd.print(sensors.getTempCByIndex(0));

 //Set LED colur according to temperature
 if(sensors.getTempCByIndex(0)<temp_low)
 {
  digitalWrite(g_led_pin, LOW);
  digitalWrite(r_led_pin, LOW);
  for(i=0;i<(loop_period/b_flash_period);i++)
  {
    analogWrite(b_led_pin, b_duty_cycle);
    delay(0.5*b_flash_period);
    analogWrite(b_led_pin, 0);
    delay(0.5*b_flash_period);
  }
 }
 else if (sensors.getTempCByIndex(0)<temp_high)
 {
  digitalWrite(b_led_pin, LOW);
  digitalWrite(r_led_pin, LOW);
  analogWrite(g_led_pin, g_duty_cycle);
  delay(loop_period);
 }
 else
 {
  digitalWrite(b_led_pin, LOW);
  digitalWrite(g_led_pin, LOW);
  for(i=0;i<(loop_period/r_flash_period);i++)
  {
    analogWrite(r_led_pin, r_duty_cycle);
    delay(0.5*r_flash_period);
    analogWrite(r_led_pin, 0);
    delay(0.5*r_flash_period);
  }
 }
} 
