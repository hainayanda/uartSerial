/*
* uart.c
*
* Created: 6/9/2015 11:44:27 PM
* Author: Nayanda Haberty <nayanda1@outlook.com>
*/

#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>

SerialPort uartInit(uint8_t *ubrrL, uint8_t *ubrrH, uint8_t *ucsrA, uint8_t *ucsrB, uint8_t *ucsrC, uint8_t *udr){
	SerialPort port;
	port.ubrrL = ubrrL;
	port.ubrrH = ubrrH;
	port.ucsrA = ucsrA;
	port.ucsrB = ucsrB;
	port.ucsrC = ucsrC;
	port.udr = udr;
	port.timeOut = uartCalculateTimeOut(*ubrrL, *ubrrH);
	return port;
}

void uartStandardInit(SerialPort *port, unsigned int baud){
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	*(port->ubrrH) = ubrr >> 7;
	*(port->ubrrL) = ubrr;
	*(port->ucsrB) = ((1 << RX_ENABLE) | (1 << TX_ENABLE));			 //enable TX0 and RX0
	*(port->ucsrC) = ((1 << U_STOP_BIT) | (1 << UCSZ0) | (1 << UCSZ1)); // set 8 bit data and 2 bit stop bit
	port->timeOut = uartCalculateTimeOut(*(port->ubrrL), *(port->ubrrH));
}

void uartClose(SerialPort *port){
	*(port->ucsrB) = 0x00;
}

char uartReadChar(SerialPort *port){
	if(uartTimeout(port)){
		return 0x00;
	}
	return *(port->udr);
}

void uartSendChar(SerialPort *port, const char character){
	while (!(*(port->ucsrA) & (1 << UDR_READY)))
	;
	*(port->udr) = character;
}

void uartPrint(SerialPort *port, const char *string){
	while (*string != 0x00){
		uartSendChar(port, *string);
		string++;
	}
}

unsigned int uartScan(SerialPort *port, char *str, unsigned int length){
	unsigned int i = 0, timeout = 0;
	while (!timeout && i < length){
		*str = uartReadChar(port);
		timeout = uartTimeout(port);
		str++;
		i++;
	}
	return i;
}

boolean uartAvailable(SerialPort *port){
	return (*(port->ucsrA) & (1 << RX_FLAG));
}

boolean uartTimeout(SerialPort *port){
	int time = 0;
	while (!uartAvailable(port) && time < 100){
		_delay_us(port->timeOut);
		time++;
	}
	return (time > 1000);
}

void uartFlush(SerialPort *port){
	char dummy;
	while (*(port->ucsrA) & (1<<RX_FLAG)) dummy = *(port->udr);
	return;
}

unsigned long uartCalculateTimeOut(uint8_t ubrrL, uint8_t ubrrH){
	unsigned int ubrr = ubrrL;
	ubrr = ubrr | (ubrrH >> 7);
	unsigned long baud = ((F_CPU / 16) / (ubrr + 1));
	return (1000000UL / baud);
}