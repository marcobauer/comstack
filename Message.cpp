#include "Message.h"
#include "checksum.h"
#include "defines.h"

using namespace ComStack;

Message::Message( Handler* cb ) : handler(cb), message_begin(NULL), contentSize(0), clear_type(Message::undef_type)
{
	for( int i= 0; i< Message::num_of_msg_type; i++ )
		seqCounter[i] = 0xFF;
}

void Message::error( Error::Type error_id )
{
	if( !message_begin )// it is already
		return;

	ringBuffer.restore();
	this->message_begin = NULL;
	decSeqCounter( clear_type );
	handler->error( error_id );
}

byte Message::incSeqCounter( Message::Type type )
{
	if( seqCounter[type]++ == 0xFF)
		seqCounter[type] = MSG_DLE_OFFSET ;

	return seqCounter[type];
}

void Message::decSeqCounter( Message::Type type )
{
	if( seqCounter[type] == MSG_DLE_OFFSET )
		seqCounter[type] = 0xFF;
	else
		seqCounter[type]--;
}

Iterator* Message::getContent()
{
	if( this->message_begin == NULL )
		return 0;

	return ringBuffer.iterator( &message_begin[MSG_POS_CONTENT], this->contentSize );
}

size_t 	Message::getContentSize()
{
	if(! this->message_begin )
		return 0;

	return contentSize;
}

byte Message::getSeqCounter()
{
	if(! this->message_begin )
		return 0;

	return ringBuffer.valueOf( this->message_begin , MSG_POS_SCNT ) - MSG_DLE_OFFSET;
}

Instruction::Id Message::getInstructionId()
{
	if(! this->message_begin )
		return Instruction::undef_id;

	return (Instruction::Id) (ringBuffer.valueOf( this->message_begin , MSG_POS_ID ) - DLE);
}

Message::Type Message::getType()
{
	if(! this->message_begin )
		return Message::undef_type;

	return (Message::Type) (ringBuffer.valueOf( this->message_begin , MSG_POS_TYPE ) - DLE);
}

#ifdef UNITTEST

boolean Message::pop(byte &value)
{
	if( ringBuffer.pop( &value, 1 ) == -1)
		return false;

	return true;
}

#endif
