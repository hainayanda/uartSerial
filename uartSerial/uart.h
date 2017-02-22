/*
* uart.h
*
* Created: 6/9/2015 11:46:39 PM
* Author: Nayanda Haberty <nayanda1@outlook.com>
*/


#ifndef UART_H_
#define UART_H_
#define __DELAY_BACKWARD_COMPATIBLE__
#endif /* PCSERIAL_H_ */

#ifndef boolean
#define boolean unsigned char
#endif

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define RX_ENABLE 4
#define TX_ENABLE 3
#define U_STOP_BIT 3

#ifndef UCSZ0
#define UCSZ0 1
#define UCSZ1 2
#endif

#define RX_FLAG 7
#define UDR_READY 5

typedef struct SerialPort{
	volatile uint8_t *ubrrL;
	volatile uint8_t *ubrrH;
	volatile uint8_t *ucsrA;
	volatile uint8_t *ucsrB;
	volatile uint8_t *ucsrC;
	volatile uint8_t *udr;
	unsigned long timeOut;
} SerialPort;

/**
 * \brief 
 * 
 * \param ubrrL
 * \param ubrrH
 * \param ucsrA
 * \param ucsrB
 * \param ucsrC
 * \param udr
 * 
 * \return SerialPort
 */
SerialPort uartInit(uint8_t *ubrrL, uint8_t *ubrrH, uint8_t *ucsrA, uint8_t *ucsrB, uint8_t *ucsrC, uint8_t *udr);

/**
 * \brief 
 * 
 * \param port
 * \param baud
 * 
 * \return void
 */
void uartStandardInit(SerialPort *port, unsigned int baud);

/**
 * \brief 
 * 
 * \param port
 * 
 * \return void
 */
void uartClose(SerialPort *port);

/**
 * \brief 
 * 
 * \param port
 * \param string
 * 
 * \return void
 */
void uartPrint(SerialPort *port, const char *string);

/**
 * \brief 
 * 
 * \param port
 * \param string
 * \param length
 * 
 * \return void
 */
unsigned int uartScan(SerialPort *port, char *string, unsigned int length);

/**
 * \brief 
 * 
 * \param port
 * 
 * \return boolean
 */
boolean uartAvailable(SerialPort *port);

/**
 * \brief 
 * 
 * \param port
 * 
 * \return boolean
 */
boolean uartTimeout(SerialPort *port);

/**
 * \brief 
 * 
 * \param port
 * 
 * \return char
 */
char uartReadChar(SerialPort *port);

/**
 * \brief 
 * 
 * \param port
 * \param character
 * 
 * \return void
 */
void uartSendChar(SerialPort *port, const char character);

/**
 * \brief 
 * 
 * \param port
 * 
 * \return void
 */
void uartFlush(SerialPort *port);

/**
 * \brief 
 * 
 * \param ubrrL
 * \param ubrrH
 * 
 * \return unsigned long
 */
unsigned long uartCalculateTimeOut(uint8_t ubrrL, uint8_t ubrrH);