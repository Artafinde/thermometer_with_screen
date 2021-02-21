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
int loop_period = 2000;  //seconds
int b_led_pin=3;
int g_led_pin=6;
int r_led_pin=5;
int temp_low = 34;
int temp_high = 40;
int b_duty_cycle = 20;
int g_duty_cycle = 100;
int r_duty_cycle = 20;

void setup(void) 
{ 
 // start serial port 
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
  analogWrite(b_led_pin, b_duty_cycle);
  digitalWrite(g_led_pin, LOW);
  digitalWrite(r_led_pin, LOW);
 }
 else if (sensors.getTempCByIndex(0)<temp_high)
 {
  digitalWrite(b_led_pin, LOW);
  analogWrite(g_led_pin, g_duty_cycle);
  digitalWrite(r_led_pin, LOW);
 }
 else
 {
  digitalWrite(b_led_pin, LOW);
  digitalWrite(g_led_pin, LOW);
  analogWrite(r_led_pin, r_duty_cycle);
 }

 //Blink builtin LED
 digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
 delay(0.1*loop_period);                       // wait for a second
 digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
 delay(0.9*loop_period);  
} 
