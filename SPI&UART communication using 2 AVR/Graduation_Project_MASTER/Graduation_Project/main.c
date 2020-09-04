/*
 * Graduation_Project.c
 *
 * Created: 6/26/2020 3:25:48 PM
 * Author : Eyad Ahmed
 */ 
 #define F_CPU	16000000
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <avr/interrupt.h>
#define SS_DISABLE()		PORTC|=(1<<0)
#define SS_ENABLE()			PORTC&=~(1<<0)
void UART_init(void);
unsigned char UART_recieve(void);
void SPI_MASTER_INIT(void);
void spi_transfer(unsigned char senddata);
unsigned char Rec=0;
int main(void)
{	
	LCD_Init();
	UART_init();
	SPI_MASTER_INIT();
	

	
    while (1) 
    {	
		Rec=UART_recieve();
		switch(Rec)
		{
				case 'a':
					LCD_Command(0x80);
					LCD_String("lamp one is on");
					SS_ENABLE();
					spi_transfer('a');
					SS_DISABLE();
					break;
				case 'b':
					LCD_Command(0x80);
					LCD_String("lamp two is on");
					SS_ENABLE();
					spi_transfer('b');
					SS_DISABLE();
					break;
				case 'c':
					LCD_Command(0x80);
					LCD_String("lamp three is on");
					SS_ENABLE();
					spi_transfer('c');
					SS_DISABLE();
					break;
				case 'd':
					LCD_Command(0x80);
					LCD_String("lamp four is on");
					SS_ENABLE();
					spi_transfer('d');
					SS_DISABLE();
					break;
				case 'e':
					LCD_Command(0x80);
					LCD_String("Washing machine on");
					SS_ENABLE();
					spi_transfer('e');
					SS_DISABLE();
					break;
				case 'f':
					LCD_Command(0x80);
					LCD_String("lamp one is off");
					SS_ENABLE();
					spi_transfer('f');
					SS_DISABLE();
					break;
				case 'g':
					LCD_Command(0x80);
					LCD_String("lamp two is off");
					SS_ENABLE();
					spi_transfer('g');
					SS_DISABLE();
					break;
				case 'h':
					LCD_Command(0x80);
					LCD_String("lamp three is off");
					SS_ENABLE();
					spi_transfer('h');
					SS_DISABLE();
					break;
				case 'i':
					LCD_Command(0x80);
					LCD_String("lamp four is off");
					SS_ENABLE();
					spi_transfer('i');
					SS_DISABLE();
					break;
				case 'j':
					LCD_Command(0x80);
					LCD_String("washing machine off");
					SS_ENABLE();
					spi_transfer('j');
					SS_DISABLE();
					break;
		}//switch case
	}//while 1
}//main function
void UART_init(void)
{	
	UBRRL=103;	// Baud rate =9600
	UCSRC|=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);	//8-Bit , 1 stop bit
	UCSRB =(1<<RXEN)|(1<<TXEN);		//Enable RX and TX
}
unsigned char UART_recieve(void)
{
	while (!(UCSRA&(1<<UDRE)));
	return UDR;
}
void SPI_MASTER_INIT(void)
{
	DDRB|=(1<<5)|(1<<7);
	DDRB&=~(1<<6);
	DDRC|=(1<<0);
	SPCR|=(1<<MSTR)|(1<<SPR0)|(1<<SPE);
	sei();
}
void spi_transfer(unsigned char senddata)
{
	SPDR=senddata;
	while(!(SPSR&(1<<SPIF)));
}