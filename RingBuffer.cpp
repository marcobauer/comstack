
#include "RingBuffer.h"
#include "arch_types.h"
#include "defines.h"

using namespace ComStack;

RingBuffer::RingBuffer() : iterator_active(false), iterator_begin(NULL), iterator_end(NULL), iterator_ptr(0), dataload(0), old_dataload(0)
{
	clear();
#if defined(UNITTEST)
	for(int i=0; i<BUFFER_SIZE; i++)
		data[i] = 'x';
#endif
	data[BUFFER_SIZE] = '\0';
}

boolean RingBuffer::push( byte value )
{
	if( (index[head] == index[tail]) && dataload )
		return false;

//	if( dataload == BUFFER_SIZE )

	dataload++;

	data[index[head]] = value;
	index[head] = (index[head] + 1) % BUFFER_SIZE;

	return true;
}

boolean RingBuffer::push( byte val0, byte val1 )
{
	boolean retval = true;
	retval = push(val0);
	retval = push(val1);
	return retval;
}

size_t RingBuffer::pop( byte *buf, size_t buf_size )
{
	int i=0;
	size_t numRead = buf_size;
	byte *data_ptr;
	byte *oldTail = &data[index[tail]];

	if( dataload == 0 )
		return -1;

	//! Ensure, that only this will be read what is really available ;-)
	if( buf_size > dataload )
		numRead = dataload;

	index[tail] = ( index[tail] + numRead ) % BUFFER_SIZE;
	dataload--;

	Iterator* it = iterator( oldTail, &data[index[tail]] );
	while( (data_ptr = it->next()) )
		buf[i++] = *data_ptr;

	if( index[tail] == index[head] )
		clear();

	return numRead;
}

size_t RingBuffer::save()
{
	size_t count = dataload - old_dataload;
	dataload = old_dataload = size();
	index[head_old] = index[head];
	index[tail_old] = index[tail];
	return count;
}

void RingBuffer::restore()
{
	index[head] = index[head_old];
	index[tail] = index[tail_old];
	dataload 	= old_dataload;
}

void RingBuffer::clear()
{
	index[head] = index[head_old] = index[tail] = index[tail_old] = 0;
	dataload = old_dataload = 0;
}

size_t RingBuffer::size()
{
	if( &data[index[tail]] < &data[index[head]] )
		return &data[index[head]] - &data[index[tail]];

	if( &data[index[tail]] > &data[index[head]] )
		return (&data[index[head]] - &data[0]) + (&data[BUFFER_SIZE] - &data[index[tail]]);

	if( (&data[index[tail]] == &data[index[head]]) && ( dataload ) )
		return BUFFER_SIZE;

	return 0;
}

size_t RingBuffer::free()
{
	return ( BUFFER_SIZE - size() );
}

Iterator* RingBuffer::iteratorHead()
{
	return iterator( &data[index[head_old]], &data[index[head]] );
}

Iterator* RingBuffer::iteratorTail()
{
	return iterator( &data[index[tail]], &data[index[head]] );
}

Iterator* RingBuffer::iterator( byte* begin, size_t length )
{
	size_t index_Begin = indexOf(begin);
	iterator( begin, &data[(index_Begin+length)%BUFFER_SIZE] );
	return this;
}

Iterator* RingBuffer::iterator( byte *begin, byte *end )
{
	iterator_ptr = iterator_begin = begin;
	iterator_end = end;
	iterator_active = false;
	return this;
}

size_t RingBuffer::indexOf( byte *ptr )
{
	return ptr - &data[0];
}

byte RingBuffer::valueOf( byte *ptr, size_t offset )
{
	if( (&data[0] > ptr) || (&data[BUFFER_SIZE]<=ptr) || ( offset >= BUFFER_SIZE)  ){
		return 0;
	}
	return *pointer( ptr, offset );
}

size_t RingBuffer::indexOf( byte *ptr, size_t offset )
{
	if( (&data[0] > ptr) || (&data[BUFFER_SIZE]<=ptr) || ( offset >= BUFFER_SIZE)  )
		return 0;

	return ( indexOf(ptr)+offset ) % BUFFER_SIZE;
}

byte* RingBuffer::pointer( RingBuffer::PtrName ptrName, size_t offset )
{
	return &data[ ( index[ptrName] + offset) % BUFFER_SIZE ];
}

byte* RingBuffer::pointer( byte* ptr, size_t offset )
{
	return &data[ (indexOf(ptr) + offset) % BUFFER_SIZE ];
}

void RingBuffer::remove( byte* ptr )
{
	index[tail] = indexOf( ptr, 1 );

	if( index[tail] == index[head] )
		clear();
}

void RingBuffer::remove( size_t cnt )
{
	if( cnt >= size() )
		clear();
	else
		index[tail] = ( index[tail] + cnt ) % BUFFER_SIZE;

	if( index[tail] == index[head] )
		clear();
}

byte* RingBuffer::reset()
{
	iterator_ptr = iterator_begin;
	iterator_active = false;
	return iterator_begin;
}

byte* RingBuffer::next()
{
	if(!iterator_active)
	{
		iterator_active = true;
		return iterator_ptr;
	}

	if( iterator_ptr == &data[BUFFER_SIZE-1] )
		iterator_ptr = &data[0];
	else
		iterator_ptr++;

	if( (iterator_ptr == iterator_end) || (iterator_ptr == iterator_begin) )
		return NULL;
	else
		return iterator_ptr;
}

byte* RingBuffer::prev()
{
	byte *iterator_prev = iterator_ptr;

	if( iterator_ptr == iterator_begin )
		return NULL;

	if( iterator_prev == &data[0] )
		iterator_prev = &data[BUFFER_SIZE-1];
	else
		iterator_prev--;

	return iterator_prev;
}

size_t RingBuffer::trim( byte *start, byte *end, byte symbol )
{
	size_t newSize=0;
	byte *data_ptr;
	Iterator *it;

	if( (start == NULL) || (end == 0) )
		return 0;

	size_t index_start 	= indexOf(start);
	it = iterator( start, end );

	while( (data_ptr = it->next()) ){

		if(*data_ptr == symbol)
			data_ptr = it->next();

		data[(index_start+newSize)%BUFFER_SIZE] = *data_ptr;
		newSize++;
	}

	return newSize;
}


byte* RingBuffer::find( Iterator *it, byte value, size_t &offset )
{
	byte *data_next;
	while( ( data_next = it->next() ) )
	{
		if( *data_next == value )
		{
			return data_next;
		}else
		{
			offset++;
		}
	}

	return NULL;
}

/***************************************************************************************************
 ************************** 	Utility functions for unit testing	  ******************************/

#if defined(UNITTEST)

void RingBuffer::print(){
	uint8_t value;
	uint16_t temp = index[tail] + size() - BUFFER_SIZE;

	printf("\n ");
	for(int i= 0; i< BUFFER_SIZE; i++)
	{
		printf("%02d", i );
		if( i < (BUFFER_SIZE-1) )
			printf(" ");
	}
	printf("\n");

	printf("[");
	for(int i=0; i<BUFFER_SIZE; i++){

		if( &data[index[head]] > &data[index[tail]] )
		{
			if((i >= index[tail]) && ( i < index[head] ) )
				value = data[i];
			else
				value ='_';

		}else
		{
			if( size() > 0 )
			{
				if( ((i>=temp) && (i<index[tail])) )
					value ='_';
				else
					value = data[i];

			} else
			{
				value ='_';
			}
		}

		if(i<(BUFFER_SIZE-1))
		{
			value == '_' ? printf("__|") : printf("%02X|", value);
		} else
		{
			value == '_' ? printf("__") : printf("%02X", value);
		}

	}
	printf("]\n");
	printf(" ");

	for(int i=0; i<BUFFER_SIZE; i++){

		if( i == index[tail] ){
			if( i== index[head] )
				printf("#  ");
			else
				printf("T  ");
		} else if (i == index[head]) {
			printf("H  ");
		} else {
			printf("   ");
		}
	}

	printf("\n");
}

#endif
