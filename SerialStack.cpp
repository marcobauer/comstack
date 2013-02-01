
#include "SerialStack.h"
#include "arch_types.h"

SerialStack::SerialStack( )
{}

boolean SerialStack::transmit( uint8_t *data )
{
	uint8_t size = txMessage.create( data, TxMessage::event );
	this->writeData( txMessage.data() );
	return true;
}

void SerialStack::receive( uint8_t *data, uint8_t size )
{




	for(int i=0; i< size; i++){
//		rxMessage
	}

//	for(int i =0 ; i< size; i++){
//		receiveMessage.collect( data[i] );
//	}


}

