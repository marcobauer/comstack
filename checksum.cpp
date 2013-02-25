#include "checksum.h"

#define CRC16 0x8005

uint16_t calcCRC16( Iterator *iterator )
{
	byte *data;
	uint16_t out = 0;
	int bits_read = 0, bit_flag;

	/* Sanity check: */
	if( iterator == NULL )
		return 0;
//	printf("CRC calc...\n");
	data = iterator->next();
//	printf("%02x|", *data );
	while( data )
	{
		bit_flag = out >> 15;

		/* Get next bit: */
		out <<= 1;
		out |= (*data >> (7 - bits_read)) & 1;

		/* Increment bit counter: */
		bits_read++;
		if (bits_read > 7) {
			bits_read = 0;
//			printf("%02x|", *data );
			data = iterator->next();

		}

		/* Cycle check: */
		if (bit_flag)
			out ^= CRC16;
	}
//	printf("\n");
	return out;
}

boolean compCRC16( Iterator* iterator, uint16_t value )
{
	return  ( value == (0xFFFF & calcCRC16(iterator)) ) ? true : false;
}



