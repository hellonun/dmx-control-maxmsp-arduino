#include <ArduinoRS485.h> // the ArduinoDMX library depends on ArduinoRS485
#include <ArduinoDMX.h>

const int universeSize = 512;

String inString = "";    // string to hold input
String inString1;
String inString2;
int value1;
int value2;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!DMX.begin(universeSize)) {
    Serial.println("Failed to initialize DMX!");
    while (1); // wait for ever
  }

}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      //            Serial.print("Value:");
      //            Serial.println(inString.toInt());
      //            Serial.print("String: ");

      inString1 = inString.substring(0, 3);
      value1 = inString1.toInt();
      inString2 = inString.substring(3, 6);
      value2 = inString2.toInt();

      Serial.print(value1);
      Serial.print(" ");
      Serial.print(value2);
      Serial.println();
      // clear the string for new input:
      inString = "";

    }
  }


  DMX.beginTransmission();
  DMX.write(101, value1);
  DMX.endTransmission();

  delay(1);

  DMX.beginTransmission();
  DMX.write(203, value2);
  DMX.endTransmission();

  delay(1);

}
