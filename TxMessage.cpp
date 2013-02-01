
#include "TxMessage.h"
#include "arch_types.h"

TxMessage::TxMessage() : counter(0)
{

}

uint8_t TxMessage::create( const uint8_t *data, MsgType type )
{
//	clearBuffer();
	add( STX );
	add( (uint8_t) type );
	buildFrame( data, this->incCounter() );
	add( ETX );
	add( '\0' );
}

uint8_t* TxMessage::data()
{
	return (uint8_t*) 0;//&buffer[0];
}

uint16_t TxMessage::incCounter()
{
	if( counter == 0xFFFF)
		return 0;

	return counter++;
}

