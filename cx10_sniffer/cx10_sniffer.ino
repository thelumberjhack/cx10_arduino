#include "printf.h"
#include "cx10.h"


RF24 radio(PIN_CE, PIN_CSN);

// Some flags to track the states
boolean isRunning = false;
boolean isListening = false;

uint8_t ctrl_channels[4] = {-1, -1, -1, -1};
uint32_t txid = 0x00000000;

void setup(void) {
	Serial.begin(115200);
	printf_begin();
	Serial.println("CX-10 (A/WD) Sniffer/Decoder");

	// Initialize receiver
	init(CX10WD);
	radio.printDetails();

	delayMicroseconds(500);
}


void calc_channels(void) {
	uint32_t offset = (txid >> 24) & 3;
	for (int i = 0; i < 4; i++) {
		ctrl_channels[i] = (0x46 + i*2 + offset);
	}
}


void get_txid(void) {
	txid = (uint32_t)packet[1] << 24 |
      (uint32_t)packet[2] << 16 |
      (uint32_t)packet[3] << 8  |
      (uint32_t)packet[4];
}


void start_receiver(void){
	if (radio.available()){
		XN297_ReadPayload(packet, packet_size);
		int i = 0;
		printf("Packet data: ");
		while (i < packet_size) {
			printf("%02X ", (int)packet[i]);
			i++;
		}
		get_txid();
		calc_channels();
		printf("\nCTRL Channels: ");
		for (int i = 0; i < 4; i++) {
			printf("%02X ", ctrl_channels[i]);
		}
		printf("\n");
	}
}



void loop(void) {
	start_receiver();
}
