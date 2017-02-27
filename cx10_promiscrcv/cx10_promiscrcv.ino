/************************************************************
* CX-10 drone RC scanner
* Author: Yannick Formaggio
* Inspired from https://github.com/m-melchior/QC-360-A1/blob/master/src/Arduino/myRF24PromiscuousReceiver/myRF24PromiscuousReceiver.ino
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


// Setup nRF24l01+ radio
RF24 radio(PIN_CE, PIN_CSN);

// print mode is a bit over-done, but will be paying off in future versions,
// when other print modes like printing values and such come in
#define PRINT_MODE_BYTES 0
#define PRINT_MODE_BITS 1
#define PRINT_MODE_COUNT 2

// buffer for reading incoming messages
const uint8_t maxBufferSize = 32;
uint8_t myBuffer[maxBufferSize];
uint8_t bufferSize = 16;

// channel to listen to
uint8_t channel = 75;

// there are two address modes: 0x55 and 0xAA
boolean addressMode = true;

// there are (presently) two print modes: bits and bytes
uint8_t printMode = 0;

// some flags for the state
boolean isRunning = false;
boolean isListening = false;
boolean isScanning = false;


// initialize buffer
void initBuffer() {
  memset(myBuffer, 0, bufferSize);
}


void setup(void) {
  // Use high speed serial
  Serial.begin(250000);
  printf_begin();                  // needed for printDetails() function
  Serial.println(F("nRF24l01+ CX-10 Promiscuous receiver"));

  // Setup and configure RF Radio
  radio.begin();
  radio.setChannel(channel);
  radio.disableCRC();
  radio.setAutoAck(false);
  radio.setRetries(0,0);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setAddressWidth(3);         // CX-10 use 5 bytes addresses

  // Standby mode
  radio.startListening();
  radio.stopListening();

  radio.printDetails();

  Serial.println("Done with setup");
}

// print only zeroes and ones
void printBits() {
  // initialize output string
  String readerStr = "";

  for (int i=0; i < bufferSize; i++) {
    for (int j=0; j<7; j++) {
      readerStr += (((myBuffer[i] << j) & 128)?1:0) + " ";
    }

    // no need for a delimiter at the end of the last bit
    readerStr += (((myBuffer[i] << 7) & 128)?1:0);
  }

  // output of the string
  Serial.println(readerStr);
}

// print the bytes
void printBytes() {
  // loop through the buffer
  for (int i=0; i < bufferSize - 1; i++) {
    Serial.print(myBuffer[i], HEX);
    if (i != bufferSize-2){
      // Don't print delimiter when it is the last byte in the buffer
      Serial.print(":");
    }
  }
  Serial.println("");
}


// toggle between the two addresses 0x55 and 0xAA
void toggleAddress() {
  if(isListening) {
    radio.stopListening();
  }

  if(addressMode) {
    radio.openReadingPipe(0, 0xAA);
    radio.openReadingPipe(1, 0xAA);
  }

  else {
    radio.openReadingPipe(0, 0x55);
    radio.openReadingPipe(1, 0x55);
  }

  addressMode = !addressMode;
  // Print address register mode
  Serial.print("Address Mode set to: ");
  Serial.print(addressMode?0x55:0xAA, HEX);
  Serial.println("");

  if(isListening) {
    radio.startListening();
  }
}

void loop(void) {
  // Are we in running mode?
  if (isRunning) {
    // Are we listening?
    if (!isListening) {
      radio.startListening();
      isListening = true;
    }

    // if anything available and >= -64dBm
    // if (radio.testRPD() && radio.available()) {
    // Tried to remove false positives with this testRPD() func.
    // ?TOFIX: after some packets received it stops receiving any other data.
    if (radio.available()) {
      // read the FIFO
      radio.read(myBuffer, bufferSize);

      // Print it
      switch(printMode) {
        case (PRINT_MODE_BYTES):
          printBytes();
          break;
        case (PRINT_MODE_BITS):
          printBits();
          break;
      }

      // Initialize buffer
      initBuffer();
    }
  }

  else {
    if (isListening) {
      radio.stopListening();
      isListening = false;
    }
  }
  // Getting some user input
  if (Serial.available()) {
    // check the first char
    char inChar = Serial.read();

    if (inChar == 'a') {
      // a toggle address between 0x55 and 0xAA
      toggleAddress();
    }
    else if (inChar == 'b' && Serial.available()){
      // b+ / b-   increase / decrease buffer size
      inChar = Serial.read();
      if (inChar == '+') {
        if (bufferSize < maxBufferSize) {
          bufferSize++;
        }
      }

      else if (inChar == '-') {
        if (bufferSize > 0) {
          bufferSize--;
        }
      }
    }

    else if (inChar == 'p') {
      // p toggle print mode (bits / bytes)
      if (printMode < PRINT_MODE_COUNT) {
        printMode++;
      }
      else {
        printMode = 0;
      }
    }

    else if (inChar == 's') {
      // s start / stop
      isRunning = !isRunning;
      Serial.println(isRunning?"Running...":"Not running.");
    }
  }
}
