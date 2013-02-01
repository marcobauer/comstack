
#include "DataFrame.h"
#include "checksum.h"

#include "arch_types.h"

#define HEAD_SIZE	  5

DataFrame::DataFrame()
{
}

uint8_t DataFrame::buildFrame ( const uint8_t *data, uint16_t frame_cnt  )
{
	uint8_t buf[ 128 + HEAD_SIZE ];
	uint8_t size;

	uint8_t  data_len = (uint8_t) snprintf( (char*) &buf[HEAD_SIZE], 128, "%s", data );
	uint16_t data_crc = checksumCRC16( (uint8_t*) &buf[HEAD_SIZE],  (uint8_t*) &buf[ HEAD_SIZE + data_len -1 ] );

	buf[0] = (uint8_t)( frame_cnt & 0xFF00 );
	buf[1] = (uint8_t)( frame_cnt & 0x00FF );
	buf[2] = (uint8_t)( data_crc  & 0xFF00 );
	buf[3] = (uint8_t)( data_crc  & 0x00FF );
	buf[4] = (uint8_t)( data_len );

	addDLE( &buf[0], data_len + HEAD_SIZE );

	return size;
}

void DataFrame::addDLE( uint8_t *buf, uint8_t size)
{
	for(int i=0; i< size; i++ )
	{
		switch( buf[i] )
		{
			case '\0':
				add(SUB);
				break;
			case STX:
				add(DLE);
				add(STX);
				break;

			case ETX:
				add(DLE);
				add(ETX);
				break;

			case DLE:
				add(DLE);
				add(DLE);
				break;

			case SUB:
				add(DLE);
				add(SUB);
				break;

			default:
				add(buf[i]);
				break;

		} // end of switch (character substitution)
	} // end of for loop (buffer iteration)
}
