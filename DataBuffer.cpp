
#include "DataBuffer.h"
#include "arch_types.h"

DataBuffer::DataBuffer() : read_index(0), write_index(0), write_ahead(false)
{

#if defined(UNITTEST)
	for(int i=0; i<BUFFER_SIZE; i++)
		data[i] = 'x';
#endif

	data[BUFFER_SIZE] = '\0';
}

DataBuffer::Result DataBuffer::add( uint8_t value )
{
	if( size() == BUFFER_SIZE )
	{
		reset();
		return DataBuffer::overflow;

	} else if( write_index == BUFFER_SIZE )
	{
		write_index = 0;
	}

	data[ write_index++ ] = value;

	updateAHead();

	return DataBuffer::successful;
}

DataBuffer::Result DataBuffer::get( uint8_t *buf, size_t buf_size )
{
//	printf("read_index:%d | write_index:%d | size: %d | ahead:%d \n", read_index, write_index, size(), write_ahead );

	if( size() == 0 ){
		buf[0] ='\0';
		return DataBuffer::empty;
	}

	//! @note Buffer is bordered by a termination symbol; If we reach the border the return value is less than size
	uint16_t num = snprintf( (char*) buf, buf_size+1, "%s", &data[read_index] );

	if( num >= buf_size )
	{
		//! Increment of read_index
		read_index += buf_size;

		//! Check, whether we read to much bytes
		if( (read_index > write_index) && write_ahead )
		{
			num =  read_index - write_index;
			read_index = write_index;
			buf[buf_size-num] = '\0';
		}

	} else {
		read_index = buf_size - num;

		//! Check, whether we read to much bytes
		if( read_index > write_index )
			read_index = write_index;

		snprintf( (char*) &buf[num], read_index+1, "%s", &data[0] );
	}

	//! If write_index equal read_index than we can reset the buffer
	if( write_index == read_index )
	{
		reset();
	} else if( read_index == BUFFER_SIZE )
	{
		read_index = 0;
	}

	updateAHead();

	return DataBuffer::successful;
}

void DataBuffer::reset()
{
	updateAHead();
	write_index = 0;
	read_index  = 0;
}

uint16_t DataBuffer::size()
{
	if( write_ahead )
		return  write_index-read_index;
	else
		return ( (write_index == 0) && (read_index == 0) ?  0 : ((BUFFER_SIZE-read_index )+write_index) );
}

void DataBuffer::updateAHead()
{
	if( write_index <= read_index )
		write_ahead = false;
	else
		write_ahead = true;
}

#if defined(UNITTEST)

void DataBuffer::print(){
	uint8_t value;
	uint16_t lsize = size();
	uint16_t temp = read_index + lsize - BUFFER_SIZE;

//	printf("\nA:%d ; R:%d ; W:%d ; temp:%d", write_ahead, read_index , write_index, temp );
	printf("\n[");
	for(int i=0; i<BUFFER_SIZE; i++){

		if( write_ahead )
		{
			if((i >= read_index) && ( i < write_index ) )
				value = data[i];
			else
				value ='_';

		}else
		{
			if( lsize > 0 )
			{
				if( ((i>=temp) && (i<read_index)) )
					value ='_';
				else
					value = data[i];

			} else
			{
				value ='_';
			}
		}

		if(i<(BUFFER_SIZE-1))
			printf("%c|", value);
		else
			printf("%c", value);

	}
	printf("]\n");
	printf(" ");

	for(int i=0; i<BUFFER_SIZE; i++){

		if( i == read_index ){
			if( i== write_index )
				printf("# ");
			else
				printf("R ");
		} else if (i == write_index) {
			printf("W ");
		} else {
			printf("  ");
		}
	}

	printf("\n");
}

#endif
