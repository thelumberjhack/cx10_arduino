/************************************************************
* CX-10 drone RC scanner
* Author: Chi Zhang
* Refered to Yannick's CX-10 Scanner and https://github.com/m-melchior/QC-360-A1/blob/master/src/Arduino/myRF24Scanner/myRF24Scanner.ino
* PIN setup
* CE   -> 7
* CSN  -> 8
* SCK  -> 13
* MOSI -> 11
* MISO -> 12
************************************************************/
#include <SPI.h>
#include <printf.h>
#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>


#define PIN_CE  7   // chip enable
#define PIN_CSN 8   // chip select (for SPI)

RF24 radio(PIN_CE, PIN_CSN);
const uint8_t num_channels = 127;
uint8_t flags[num_channels];
const int numReps = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  printf_begin();                  // needed for printDetails() function
  Serial.println(F("nRF24l01+ CX-10 Scanner"));

  // Setup and configure RF Radio
  radio.begin();
  //radio.setChannel(channel);
  //radio.disableCRC();
  radio.setAutoAck(false);
//  radio.setRetries(0,0);
  radio.setDataRate(RF24_1MBPS);
//  radio.setPALevel(RF24_PA_MAX);
//  radio.setAddressWidth(3);         // CX-10 use 5 bytes addresses

  // Standby mode
  radio.startListening();
  radio.stopListening();

  radio.printDetails();

  Serial.println("Done with setup");
}

void loop() {
  // put your main code here, to run repeatedly:
int rep_counter = numReps;
while  (rep_counter--)//numbers of repeats of each full scan
//   for(int i = 0; i < numReps; i++)
  {
    int i = num_channels;
    while (i--)//scan over defined channels 
//    for(int j =0; j < num_channels; j++)
    {
//      Serial.println(i);
//      Serial.println("zzzz");
      radio.setChannel(i);
 
      
      radio.startListening();
      delayMicroseconds(500);
      
 
      
      if ( radio.testRPD() )// Test if signals over -60dB on current signal
      {
        flags[i]++;
      }
      radio.stopListening();
    }
  }
 
//  int i = 0;
//  while ( i < num_channels )
//  {
//    Serial.println(flags[i]);
//    ++i;
//  }

  for (int k = 0; k < num_channels; k++)//output channels and its time of apperance serial port
  {
    if(!(flags[k] == 0))
    {
    Serial.println(String(k) + ": " + String(flags[k]));
    }
//      Serial.println(flags[k]);
    }
  Serial.println("End of 1 Full Scan");
}
