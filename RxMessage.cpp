#include "RxMessage.h"
#include "checksum.h"
#include "defines.h"

using namespace ComStack;

RxMessage::RxMessage( Handler* cb ) : Message(cb), message_end(NULL)
{
}

void RxMessage::accept()
{
	ringBuffer.remove( message_end );
}

boolean RxMessage::add( byte value )
{
	if( ringBuffer.push(value) )
	{
		ringBuffer.save();
		if( ringBuffer.free() == 0 )
			return false;

		if(ringBuffer.size() > BUFFER_OVERLOAD )
			handler->warn(Warning::buffer_rx_overload);
	}

	contentSize++;
	return true;
}

RxMessage* RxMessage::getMessage()
{
#ifndef SLIM_FRAME
	byte *cnt_end, *crc_begin, *crc_end;
	size_t offset2=0;
#endif

	Iterator *it;
	size_t offset=0, offset3=0;

	if(ringBuffer.size() == 0)
		return NULL;

	if( !(it = ringBuffer.iteratorTail()) )
		return NULL;

	this->message_begin = find( it, offset, SMSG );
//	printf("SMSG-Index: %02d - Offset: %02d \n", ringBuffer.indexOf(this->message_begin), offset );

#ifndef SLIM_FRAME
	crc_begin = it->prev();
#endif

	if( (this->message_begin == NULL) && (ringBuffer.free() == 0) )
	{	// No start symbol is present but the buffer is full
		// It seem that the buffer is corrupted
		error(Error::msg_rx_no_start);
		ringBuffer.clear();

		return NULL;
	}

#ifndef SLIM_FRAME
	cnt_end = find( it, offset2, ECNT );
//	printf("ECNT-Index: %02d - Offset: %02d\n", ringBuffer.indexOf(cnt_end), offset2 );
	crc_end = it->prev();
	if( (cnt_end == NULL) && (ringBuffer.free() == 0) )
	{
		// No content end symbol present but the buffer is full
		ringBuffer.clear();
		error(Error::msg_rx_no_data);
		return NULL;
	}
#endif

	message_end = find( it, offset3, EMSG );
//	printf("EMSG-Index: %02d - Offset: %02d\n", ringBuffer.indexOf(message_end), offset3 );

	if( (message_end == NULL) && (ringBuffer.free() == 0) )
	{	// No end symbol present but the buffer is full
		ringBuffer.clear();
		error(Error::msg_rx_no_end);
		return NULL;
	}

	// Remove the none sense stuff in front of the message
	if( offset > 1 ){
		handler->warn(Warning::buffer_rx_cleanup);
		ringBuffer.remove(offset-1); // decrement by 1; Remove everything in front of the start symbol
	}
#ifndef SLIM_FRAME
	ringBuffer.trim( cnt_end, message_end, DLE );

	uint16_t crcValue = (uint16_t) (( (uint16_t)( ringBuffer.valueOf(cnt_end,1) << 8) & 0xFF00 ) | ( ringBuffer.valueOf(cnt_end,2) & 0x00FF ) );
	if( ! compCRC16( ringBuffer.iterator( crc_begin, crc_end ), crcValue ) )
	{
		handler->error( ComStack::Error::msg_crc_error );
		return NULL;
	}

	this->contentSize = ringBuffer.trim( message_begin, crc_end, DLE ) - MSG_POS_CONTENT;
#else
	this->contentSize = ringBuffer.trim( message_begin, message_end, DLE ) - MSG_POS_CONTENT;
#endif

	if( this->contentSize == 0 )
		return NULL;

	return this;
}

byte* RxMessage::find( Iterator *it, size_t &offset, byte symbol )
{
	byte *data_ptr, *data_prev;
	do{

		data_ptr = ringBuffer.find( it, symbol, offset );

		if(data_ptr)
		{
//			printf("Found : %02d \n", ringBuffer.indexOf(data_ptr) );

			if( (offset == 0) && ((data_prev = it->prev()) == NULL) )
			{
				return data_ptr;
			}else
			{
				if( (data_prev = it->prev()) != NULL ){
					if( *data_prev != DLE )
						return data_ptr;

				}
			}
			offset++;
		}

	}while( data_ptr );

	return data_ptr;
}

//#ifdef UNITTEST
//
//boolean RxMessage::pop(byte &value)
//{
//	if( ringBuffer.pop( &value, 1 ) == -1)
//		return false;
//
//	return true;
//}
//
//#endif
