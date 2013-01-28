
#include "SerialStack.h"
#include <string.h>
#include <Arduino.h>

SerialStack::SerialStack( ) : timestamp( millis() ), uptime( 0 )
{

}

void SerialStack::alive()
{
	char buf[30];

    if( (millis() - this->timestamp) >= 5000) {
    	this->timestamp = millis();
    	this->uptime += 5;
    	snprintf( &buf[0], 128, "Uptime:%d", this->uptime );
    	this->send( &buf[0] );
    }
}

boolean SerialStack::send( char *data )
{
	uint8_t size = sendMessage.create( data, Message::event );
	this->transmit( sendMessage.data() );
	return true;
}
