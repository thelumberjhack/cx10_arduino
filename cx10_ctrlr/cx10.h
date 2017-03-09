#ifndef _CX10_H
#define _CX10_H

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
// #include "iface_nrf24l01.h"


#define PIN_CE  7											// chip enable
#define PIN_CSN 8											// chip select (for SPI)

#define CX10 	0
#define CX10WD 	1
#define CX10A_PACKET_SIZE       19
#define CX10A_PACKET_PERIOD     6000
#define CX10A_SYNC_WORD			0xc710f55

#define CX10WD_PACKET_SIZE      11
#define CX10WD_PACKET_PERIOD    3000
#define CX10WD_SYNC_WORD		0x710f55

extern RF24 radio;
extern uint8_t packet[CX10A_PACKET_SIZE];
extern uint8_t packet_size;

void XN297_init();
uint8_t XN297_ReadPayload(uint8_t* msg, int len);


extern void start_receiver(uint8_t drone);
extern void init(uint8_t drone);
extern void calc_channels(uint8_t drone);
extern void start_receiver(void);
extern void send_packet(uint8_t bind);

#endif
