#include <avr/io.h>
#include <util/delay.h>

#define F_CPU    1000000UL

void Slave_init(void)
{
	DDRB |= (1<<MISO);
	DDRB &= ~(1<<MOSI) & ~(1<<SS) & ~(1<<SCK);
	//Set Slave mode
	SPCR |= (1<<SPE);
}

unsigned char Slave_Recieve(unsigned char data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
void main()
{
	unsigned char data=0;
	DDRA = 0xFF;
	Master_Init();
	for(data=255; data>=0; data--)
	{
		PORTA = Slave_Recieve(data);
	}
}