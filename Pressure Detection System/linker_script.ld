/* linker script for cortex m3*/

MEMORY
{
	falsh(RX) : ORIGIN = 0X08000000, LENGTH = 128K
	sram(RWX) : ORIGIN = 0X20000000, LENGTH = 20K
}
SECTIONS
{
	.text : {
         *(.vectors*)
         *(.text*)
	} >flash
	.data : { *(.data*)} > flash
	.bss : {*(.bss*)} > sram
}