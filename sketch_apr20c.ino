
#include <OneWire.h> // Include OneWire communication library
#include <LiquidCrystal.h> // Include Temperature sensor library
#define DS18S20_ID 0x10 // Set fixed values for Temperature sensor
#define DS18B20_ID 0x28 // >>     >>     >>      >>      >>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Create variable for the LCD Screen
OneWire ds(8); // Command to access 1−wire devices , in this case in pin 8
int ledPin = 9; // Connect LED light to pin 8
int gasPin = 0; // Alcohol Sensor connected to analogue pin 0
int flexiForcePin = 1; // Pressure sensor connected in analogue pin 1
int flexiForceReading = analogRead(flexiForcePin); // Value conversion command from analogue to digital
int LDR_Pin = A2; // Photocell Sensor connected to analogue pin 2 
int LDRReading = analogRead(LDR_Pin); // Value conversion command from analogue to digital
int isConnected = 0; //Set variable equal to zero
float temp; // Float command for floating point numbers
int value = 0;

void setup() { // Begin SKETCH command
  // initialize serial communication at 9600 bits per second:
  pinMode(ledPin, HIGH); // Set LED light as output
  Serial.begin(9600); // Set the BAUD rate at 9600
  pinMode(gasPin,INPUT);
  
  lcd.begin(16,2); // Initialize LCD screen command
}
// the loop routine runs over and over again forever:
void loop() { // Endless loop command
  delay(1000); // Delay command
  getTemperature(); // Reads Temprature Sensor’s value
        gasPin = analogRead (0) ; // Set to the variable gasPin the reading from analogue pin 0
        flexiForceReading = analogRead(flexiForcePin); // Set to the FlexiForceReading variable the reading from the pressure sensor
        LDRReading = analogRead(LDR_Pin); // Set to the LDRReading variable the value from the Photocell

  
      // float digital = (flexiForceReading) * (5.0 / 1023.0); // Value conversion from analogue to digital
      // float Lbs = (digital-0.13)/1.01; // Converts above value to Libra

       
       float LDR; //Float command for floating point numbers
       float Vout; //Float command for floating point numbers
       float Lux; //Float command for floating point numbers
       float Kgs; //Float command for floating point numbers
       
       Vout = (LDRReading * 0.0048828125); // Set Vout value
       LDR = (10000.0*(5-Vout))/Vout; // Set LDR value
       Lux = (500/LDR)*100; // Value conversion to LUX
       Kgs = (flexiForceReading * 0.45359237)/1000; // Conversion of Libra to Kilos
       
        Serial.print(temp); //Send to serial port command
        Serial.print("/"); //Send to serial port command
        Serial.print(value); //Send to serial port command
        Serial.print("/"); //Send to serial port command
        Serial.print(Kgs); //Send to serial port command
        Serial.print("/"); //Send to serial port command
        Serial.print(Lux); //Send to serial port command
        Serial.print("\n"); //Send to serial port command
     
  //Serial.println(temp); //Send to serial port command
        //Serial.println(gasPin, DEC); // Data printing command in decimal form
  if(temp > 31) { // Condition if Temperature is above 31
    digitalWrite(ledPin, HIGH);  // Turn on LED light
  } else { //συνθηκη αλλιως
    digitalWrite(ledPin, LOW); // Turn off LED light
  }       
        if(Serial.available() > 0 ) { // Send serial data command only if data is received
          lcd.clear(); // Clear LCD Screen
          lcd.setCursor(0,0); // LCD cursor placement command
          isConnected = Serial.parseInt(); // We set to this variable the command that reads the first integer number from the serial buffer
          
          Serial.flush(); // Pending of sending data termination in progress
          
          lcd.print(isConnected); // Print to screen command
        }    
        if (isConnected == 0) { // If condition
        lcd.clear(); // Clear screen
        lcd.setCursor(0,0); // Set cursor
        lcd.print("Waiting for "); // Print to LCD screen
        lcd.setCursor(0,1); // Set Cursor
        lcd.print("MTLB connection"); // Print to LCD screen
        } else { // If condition
          lcd.clear(); // Clear screen
          lcd.setCursor(0,0); // Set Cursor
        lcd.print("C:"); // Print to LCD Screen
          lcd.print(temp); // Print to LCD Screen
          lcd.setCursor(0,1); // Set Cursor
          lcd.print("Vol:"); // Print to LCD Screen
          lcd.print(value,DEC); // Print to LCD Screen
          lcd.setCursor(8,0); // Set Cursor
          lcd.print("Kg:"); // Print to LCD Screen
          lcd.print(Kgs); // Print to LCD Screen
          lcd.setCursor(8,1); // Set Cursor
          lcd.print("lux:"); // Print to LCD Screen
          lcd.print(Lux); // Print to LCD Screen
        }
   }

        int readAlcohol()
 {
  int value = 0;
  int val1;
  int val2;
  int val3; 
  
  val1 = analogRead(gasPin); 
  delay(10);
  val2 = analogRead(gasPin); 
  delay(10);
  val3 = analogRead(gasPin);
  
  value = (val1+val2+val3)/3;
  return value;
 }

boolean getTemperature(){ //Boolean command holds on of the two values, true or false
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  // Finding device  
        if (!ds.search(addr)) {
    ds.reset_search();
    return false;
  }
  if (OneWire::crc8( addr, 7) != addr[7]) {
    return false;
  }
  if (addr[0] != DS18S20_ID && addr[0] != DS18B20_ID) {
    return false;
  }
  ds.reset();
  ds.select(addr);
  // Start conversion command
  ds.write(0x44, 1);
  delay(850); // Delay command
  present = ds.reset();
  ds.select(addr); // Issue reading command
  ds.write(0xBE);
  // Received 9 bytes
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  // Temperature Reading Calculation
  temp = ( (data[1] << 8) + data[0] )*0.0625;
  return true;
}
