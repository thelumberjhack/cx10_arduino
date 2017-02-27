/************************************************************
* CX-10 drone RC scanner
* Author: Chi Zhang
* Refered to Yannick's CX-10 Promiscuous receiver and
* https://github.com/m-melchior/QC-360-A1/blob/master/src/Arduino/myRF24Scanner/myRF24Scanner.ino
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

// some flags for the state
boolean isRunning = false;
boolean isListening = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf_begin();                  // needed for printDetails() function
  Serial.println(F("nRF24l01+ CX-10 Scanner"));

  // Setup and configure RF Radio
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MIN);

  // Standby mode
  radio.startListening();
  radio.stopListening();

  radio.printDetails();

  Serial.println("Done with setup");
}

void scan_channels(void){
  int rep_counter = numReps;

  while  (rep_counter--){
    //number of repetitions of each full scan
    int i = num_channels;
    while (i--) {
      //scan over defined channels
      radio.setChannel(i);
      radio.startListening();
      delayMicroseconds(500);

      if (radio.testRPD()) {
        // Test if signals over -64dB on current signal
        flags[i]++;
      }
      radio.stopListening();
    }
  }
}

void loop() {
  if (isRunning){
    scan_channels();
  }

  // Getting some user input
  if (Serial.available()) {
    // check the first char
    char inChar = Serial.read();

    if (inChar == 's') {
      // 's' to start scanning the channels looking for data
      isRunning = !isRunning;
      Serial.println(isRunning?"Running...":"Not running.");
    }

    else if (inChar == 'p') {
      // p toggle print results
      if (!isRunning) {
        for (int k = 0; k < num_channels; k++) {
          //output channels and its number of apperance
          if((flags[k] >= 20)){
            Serial.println(String(k) + ": " + String(flags[k]));
          }
        }
      }
      else {
        Serial.println("Please stop scanning before printing results.");
      }
    }
  }
}
