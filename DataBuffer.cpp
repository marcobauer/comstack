
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

size_t DataBuffer::push( byte value )
{
	if( size() == BUFFER_SIZE )
	{
		clear();
		return -1;

	} else if( write_index == BUFFER_SIZE )
	{
		write_index = 0;
	}

	data[ write_index++ ] = value;

	updateAHead();

	return 1;
}

size_t DataBuffer::pop( byte *buf, size_t buf_size )
{
	size_t curr_size = size();
	size_t numRead = buf_size;

//	printf("read_index:%d | write_index:%d | size: %d | ahead:%d \n", read_index, write_index, curr_size, write_ahead );

	if( curr_size == 0 ){
		buf[0] ='\0';
		return -1;
	}

	//! Ensure, that only this will be read what is really available ;-)
	if( buf_size > curr_size )
		numRead = curr_size;

	//! If we reach the end of the buffer than we have to read from the beginning. So that#s idea of a ring buffer ;-)
	if( (numRead + read_index) <= BUFFER_SIZE  )
	{
		memcpy((char*) &buf[0], &data[read_index], numRead );
		read_index += numRead;
	}else
	{
		size_t tmp = (BUFFER_SIZE - read_index);
		memcpy((char*) &buf[0], &data[read_index], tmp );
		memcpy((char*) &buf[tmp], &data[0], numRead - tmp );
		read_index = (numRead-tmp);
//		printf("read_index:%d | write_index:%d | tmp:%d \n", read_index, write_index, tmp );
	}

	//! If write_index equal read_index than we can reset the buffer
	if( write_index == read_index )
	{
		clear();
	} else if( read_index == BUFFER_SIZE )
	{
		read_index = 0;
	}

	updateAHead();

	return numRead;
}

void DataBuffer::clear()
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
