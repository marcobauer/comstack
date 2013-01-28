
#include "Message.h"
#include <string.h>

Message::Message() : counter(0), buffer_size(0)
{

}

uint8_t Message::create( const char *data, enum msg_type type )
{
	clearBuffer();
	addBuffer( STX );
	addBuffer( (uint8_t) type );
	buildFrame( data, this->incCounter() );
	addBuffer( ETX );
	addBuffer( '\0' );
}

uint8_t* Message::data()
{
	return &buffer[0];
}

void Message::addBuffer( const char data )
{
	buffer[ buffer_size++ ] = data;
}

void Message::clearBuffer()
{
	buffer_size = 0;
}

uint16_t Message::incCounter()
{
	if( counter == 0xFFFF)
		return 0;

	return counter++;
}

