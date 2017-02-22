## uartSerial
UART universal library for ATmel Microcontroller

## Synopsis

This is simple universal library for UART Serial communication using Atmel Microcontroller. This code is written in C and compatible with Atmel Studio 6. it using most common protocol in UART Serial, feel free to edit the code when you needed

## Code Example

Using the code is very simple. Just create the struct using uartInit function and pass the address of UART register you want (UBRR, UCSR and UDR) and you are good to go.

```C
//create default serial port with no configuration at serial port 0
SerialPort serial = uartInit(&UBRR0L, &UBRR0H, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0);

//create default serial port with default config and baud rate 19200 bps at serial port 1
SerialPort serial1 = uartInit(&UBRR1L, &UBRR1H, &UCSR1A, &UCSR1B, &UCSR1C, &UDR1);
uartStandardInit(&serial1, 19200);

//send char
uartSendChar(&serial, 'a');

//send string
uartPrint(&serial, "Hello World");

//get char
char character = uartGetChar(&serial);

//get string
char[100] string;
int read = uartScan(&serial, &string, 100);

//flush UDR
uartFlush(&serial);
```
## Motivation

This is my personal library to use serial pin for Atmel Microcontroller. I think its a good thing if I share it for someone who need it
