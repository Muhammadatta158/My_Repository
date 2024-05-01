#define DDRA     (0x3A)
#define PORTA    (0x3B)
#define PINA     (0x39)

#define DDRB     (0x37)
#define PORTB    (0x38)
#define PINB     (0x36)

//SPI Registers
#define SPDR     (0x2F)
#define SPSR     (0x2C)
#define SPCR     (0x2D)

//SPSR Pins
#define SPI2X        0
#define WCOL         6
#define SPIF         7

//SPCR Pins
#define SPR0         0
#define SPR1         1
#define CPHA         2
#define CPOL         3
#define MSTR         4
#define DORD         5
#define SPE          6
#define SPIE         7


//MCU Pins
#define SS           4
#define MOSI         5
#define MISO         6
#define SCK          7