/*
 * Graduation_PROJECT_SLAVE.c
 *
 * Created: 7/1/2020 9:51:03 AM
 * Author : Eyad Ahmed
 */ 
 #define F_CPU	16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
char SPI_RETURN(void);
void SPI_SLAVE_INIT(void);
int main(void)
{	//Output pins select
	DDRC|=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	SPI_SLAVE_INIT();
	unsigned char recieved;
	while (1)
	{	
		recieved=SPI_RETURN();
		switch(recieved)
		{
		case 'a':
			PORTC|=(1<<0);	//Led 0 room 1 is on
			break;
		case 'b':
			PORTC|=(1<<1);	//Led 1 room 1 is on
			break;
		case 'c':
			PORTC|=(1<<2);		//Led 0 room 2 is on
			break;
		case 'd':
			PORTC|=(1<<3);		//Led 0 room 3 is on
			break;
		case 'e':
			PORTC|=(1<<4)|(1<<6);	//Washing machine is on
			PORTC&=~(1<<5);
			break;
		case 'f':
			PORTC&=~(1<<0);	//Led 0 room 1 is off
			break;
		case 'g':
			PORTC&=~(1<<1);	//Led 1 room 1 is off
			break;
		case 'h':
			PORTC&=~(1<<2);		//Led 0 room 2 is off
			break;
		case 'i':
			PORTC&=~(1<<3);		//Led 0 room 3 is off
			break;
		case 'j':
			PORTC|=(1<<4);	//Washing machine is off
			PORTC&=~(1<<5);
			PORTC&=~(1<<6);
			break;
		}
		
	}
}

void SPI_SLAVE_INIT(void)
{
	DDRB|=(1<<7);
	DDRB&=~(1<<5);
	DDRB&=~(1<<6);
	DDRB&=~(1<<8);
	SPCR|=(1<<SPE);//(1<<SPR0)|
	//sei();
}
char SPI_RETURN(void)
{
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

