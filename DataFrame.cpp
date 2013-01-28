
#include "DataFrame.h"
#include "checksum.h"

#include <string.h>

#define HEAD_SIZE	  5

DataFrame::DataFrame()
{
}

uint8_t DataFrame::buildFrame ( const char *data, uint16_t frame_cnt  )
{
	char buffer[ 128 + HEAD_SIZE ];
	uint8_t size;

	uint8_t  data_len = snprintf( &buffer[HEAD_SIZE], 128, "%s", data );
	uint16_t data_crc = checksumCRC16( (uint8_t*) &buffer[HEAD_SIZE],  (uint8_t*) &buffer[ HEAD_SIZE + data_len -1 ] );

	buffer[0] = (uint8_t)( frame_cnt & 0xFF00 );
	buffer[1] = (uint8_t)( frame_cnt & 0x00FF );
	buffer[2] = (uint8_t)( data_crc  & 0xFF00 );
	buffer[3] = (uint8_t)( data_crc  & 0x00FF );
	buffer[4] = (uint8_t)( data_len );

	trimDLE( &buffer[0], data_len + HEAD_SIZE );

	return size;
}

void DataFrame::trimDLE( char *buffer, uint8_t size)
{
	for(int i=0; i< size; i++ )
	{
		switch( buffer[i] )
		{
			case '\0':
				addBuffer(SUB);
				break;
			case STX:
				addBuffer(DLE);
				addBuffer(STX);
				break;

			case ETX:
				addBuffer(DLE);
				addBuffer(ETX);
				break;

			case DLE:
				addBuffer(DLE);
				addBuffer(DLE);
				break;

			case SUB:
				addBuffer(DLE);
				addBuffer(SUB);
				break;

			default:
				addBuffer(buffer[i]);
				break;

		} // end of switch (character substitution)
	} // end of for loop (buffer iteration)
}
