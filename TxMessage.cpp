#include "TxMessage.h"
#include "checksum.h"
#include "defines.h"

using namespace ComStack;

TxMessage::TxMessage( Handler* cb ) : Message(cb)
{
}

TxMessage* TxMessage::create( Message::Type type, Instruction::Id id )
{
	byte seqCnt = incSeqCounter(type);
	this->contentSize = 0;
	this->clear_type  = type;

	// At least, free space of MSG_FRAME_SIZE is required
	if( ringBuffer.free() < MSG_FRAME_SIZE )
	{
		error(Error::buffer_tx_full);
		return NULL;
	}

	if( (byte) id > (0xFF-DLE))
	{
		error(Error::msg_invalid_id);
		return NULL;
	}

	ringBuffer.save();
	ringBuffer.push( DCTL );
	this->message_begin = ringBuffer.pointer(RingBuffer::head, 0 );
	ringBuffer.push( SMSG );
	ringBuffer.push( type + DLE );
	ringBuffer.push( id + DLE );
	ringBuffer.push( seqCnt );

	return this;
}

size_t TxMessage::send()
{
	boolean result;

	if( !message_begin ){
		error( Error::msg_invalid );
		return 0;
	}

	uint16_t data_crc = calcCRC16( ringBuffer.iteratorHead() );
	result = ringBuffer.push( DCTL, ECNT );
	result = insertDLE( (byte)( (data_crc >> 8) & 0xFF ) );
	result = insertDLE( (byte)( (data_crc & 0xFF) ) );
	result = ringBuffer.push( DCTL, EMSG );

	if( !result )
		error(Error::buffer_tx_full);

	if(ringBuffer.size() > BUFFER_OVERLOAD )
		handler->warn(Warning::buffer_tx_overload);

	this->message_begin = NULL;
	return ringBuffer.save();
}


Iterator* TxMessage::getBuffer()
{
	if(ringBuffer.size() == 0)
		return NULL;

	return ringBuffer.iteratorTail();
}


void TxMessage::accept( size_t value )
{
	ringBuffer.remove( value );
}

boolean TxMessage::add( byte value )
{

	if( !message_begin )
		return false;

	if( !insertDLE( value ) )
	{
		error(Error::buffer_tx_full);
		return false;
	}

	contentSize++;
	return true;
}

boolean TxMessage::insertDLE( byte value )
{
	boolean result = true;
	switch( value )
	{
		case SMSG:
			result = ringBuffer.push( DLE, SMSG );
			break;

		case EMSG:
			result = ringBuffer.push( DLE, EMSG );
			break;

		case ECNT:
			result = ringBuffer.push( DLE, ECNT );
			break;

		case DLE:
			result = ringBuffer.push( DLE, DLE );
			break;

		default:
			result = ringBuffer.push( value);
			break;
	}
	return result;
}
