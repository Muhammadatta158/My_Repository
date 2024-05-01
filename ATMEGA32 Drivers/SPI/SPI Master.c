#include <avr/io.h>
#include <util/delay.h>

#define F_CPU    1000000UL

void Mastr_Init(void)
{
	DDRB |= (1<<SS) | (1<<MOSI) | (1<<SCK);
	DDRB &= ~(1<<MISO);
	//Set Master mode
	SPCR|= (1<<MSTR) | (1<<SPR0) | (1<<SPE);
}

unsigned char Master_Transmit(unsigned char data)
{
	SPDR = data;
	//SPIF flag is set when the transmission is done
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void main()
{
	unsigned char data=0;
	DDRA = 0xFF;
	Master_Init();
	for(data=0; data<=255; data++)
	{
		_delay_ms(1000);
		PORTA = Master_Transmit(data);
	}
}