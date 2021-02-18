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

int loop_period = 2000;  //seconds
int led_pin=13;

void setup(void) 
{ 
 // start serial port 
 //Serial.begin(9600); 
 
 // Start up the sensor library 
 sensors.begin(); 
 
 //Initialise the lcd
 lcd.init(); //initialize the lcd
 //lcd.backlight();  //turn on lcd backlight
 lcd.clear();
 lcd.setCursor(0, 0);  //column_index, row_index
 lcd.print("Temp (degC)");

 //Setup LED pin
 pinMode(led_pin, OUTPUT);
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

 //Blink LED
 digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
 delay(0.1*loop_period);                       // wait for a second
 digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
 delay(0.9*loop_period);  
} 
