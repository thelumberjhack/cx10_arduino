#include "cx10.h"


// void init(uint8_t drone) {
//         txid[0] = 0;
//         txid[1] = 0;
//         txid[2] = 0;
//         txid[3] = 0;
//         rf_chans[0] = 0x03;
//         rf_chans[1] = 0x16;
//         rf_chans[2] = 0x2D;
//         rf_chans[3] = 0x40;
//         if (!drone){
//         	packet_size = CX10A_PACKET_SIZE;
//         }

//         else {
//         	packet_size = CX10WD_PACKET_SIZE;
//         }

//         for (uint8_t i = 0; i < 4; i++)
//                 packet[5 + i] = 0xFF; // clear aircraft id
//         packet[9] = 0;
// 		radio.begin();

//         NRF24L01_Initialize();
//         NRF24L01_SetTxRxMode(TX_EN);
//         XN297_SetTXAddr(rx_address, 5);
//         XN297_SetRXAddr(rx_address, 5);

//         radio.flush_tx();
//         radio.flush_rx();

//         radio.write_register(STATUS, 0x70);
//         radio.write_register(EN_AA, 0x00);
//         radio.write_register(EN_RXADDR, 0x01);
//         radio.write_register(RX_PW_P0, packet_size);
//         radio.write_register(RF_CH, RF_BIND_CHANNEL);
//         radio.write_register(RF_SETUP, 0x07);
//         NRF24L01_SetBitrate(0); //1M
//         NRF24L01_SetPower(3);
//         // this sequence necessary for module from stock tx
//         radio.read_register(FEATURE);
//         radio.toggle_features();
//         radio.read_register(FEATURE);
//         radio.write_register(DYNPD, 0x00);       // Disable dynamic payload length on all pipes
//         radio.write_register(FEATURE, 0x00);     // Set feature bits on

//         NRF24L01_SetTxRxMode(TXRX_OFF);
//         NRF24L01_SetTxRxMode(RX_EN);
//         XN297_Configure(BV(EN_CRC) | BV(CRCO) | BV(PWR_UP) | BV(PRIM_RX));
// }


// void start_receiver(void){
// 	if (radio.available()){
// 		XN297_ReadPayload(packet, packet_size);
// 		int i = 0;

// 		while (i < packet_size) {
// 			printf("%02X ", (int)packet[i]);
// 			i++;
// 		}
// 		printf("\r\n");
// 	}
// }
