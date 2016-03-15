// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP9808
// This code is designed to work with the MCP9808_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=MCP9808_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// MCP9808 I2C address is 0x18(24)
#define Addr 0x18

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // Continuous conversion mode, Power-up default
  Wire.write(0x00);
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select resolution rgister
  Wire.write(0x08);
  // Resolution = +0.0625 / C
  Wire.write(0x03);
  // Stop I2C Transmission
  Wire.endTransmission();
}

void loop()
{
  unsigned int data[2];
  
  // Starts I2C communication
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x05);
  // Stop I2C transmission
  Wire.endTransmission();
  
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);
  
  // Read 2 bytes of data
  // temp MSB, temp LSB
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  
  // Convert the data to 13-bits
  int temp = ((data[0] & 0x1F) * 256 + data[1]);
  if(temp > 4095)
  {
    temp -= 8192;
  }
  float cTemp = temp * 0.0625;
  float fTemp = cTemp * 1.8 + 32;
  
  // Output data to screen
  Serial.print("Temperature in Celsius : ");
  Serial.println(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit : ");
  Serial.println(fTemp);
  Serial.println(" F");
  delay(500);
}
