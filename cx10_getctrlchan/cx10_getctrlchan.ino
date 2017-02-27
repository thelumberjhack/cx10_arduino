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
const uint8_t num_channels = 90;    // CX-10 do not use channels after 90.
uint8_t flags[num_channels];
const int numReps = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  printf_begin();                  // needed for printDetails() function
  Serial.println(F("nRF24l01+ CX-10 Scanner"));

  // Setup and configure RF Radio
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);

  // Standby mode
  radio.startListening();
  radio.stopListening();

  radio.printDetails();

  Serial.println("Done with setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  int rep_counter = numReps;
  while  (rep_counter--){ //number of repetitions of each full scan
    int i = num_channels;
    while (i--) { //scan over defined channels
      radio.setChannel(i);
      radio.startListening();
      delayMicroseconds(500);

      if (radio.testRPD()) { // Test if signals over -60dB on current signal
        flags[i]++;
      }
      radio.stopListening();
    }
  }
  for (int k = 0; k < num_channels; k++) { //output channels and its time of apperance serial port
    if(!(flags[k] == 0)){
      Serial.println(String(k) + ": " + String(flags[k]));
    }
  }
  Serial.println("End of 1 Full Scan");
}
