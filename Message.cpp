
#include "Message.h"
#include "checksum.h"

#include "arch_types.h"

Message::Message()
{}

Message::Result Message::enqueueTx( Message::Data *msg  )
{
	txBuffer.push( STX );
	txBuffer.push( (byte) msg->type );

	uint16_t data_crc = checksumCRC16( &msg->content[0],  &msg->content[ msg->size-1 ] );
	uint16_t data_cnt = incCounter(Message::transmit);

	pushDLE( (byte)( data_cnt & 0xFF00 ) );
	pushDLE( (byte)( data_cnt & 0x00FF ) );
	pushDLE( (byte)( data_crc & 0xFF00 ) );
	pushDLE( (byte)( data_crc & 0x00FF ) );
	pushDLE( msg->size );
	pushDLE( msg->id );

	for( size_t i=0; i< msg->size; i++)
		pushDLE( msg->content[i] );

	txBuffer.push( ETX );

	return Message::passed;
}

void Message::enqueueRx( Message::Payload* msg )
{
	for(int i=0; i< msg->size; i++)
		rxBuffer.push(msg->content[i]);

}

boolean Message::dequeueTx( Message::Payload * )
{
	return true;
}

boolean Message::dequeueRx( Message::Data * )
{
	return true;
}

uint16_t Message::incCounter( Message::CounterTyp type)
{
	if( counter[type] == 0xFFFF)
		return 0;

	return counter[type]++;
}

void Message::pushDLE( byte data )
{
	switch( data )
	{
		case STX:
			txBuffer.push(DLE);
			txBuffer.push(STX);
			break;

		case ETX:
			txBuffer.push(DLE);
			txBuffer.push(ETX);
			break;

		case DLE:
			txBuffer.push(DLE);
			txBuffer.push(DLE);
			break;

		default:
			txBuffer.push( data );
			break;

	} // end of switch (character substitution)

}
