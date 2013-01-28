
#ifndef SERIALPROTOCOL_H_
#define SERIALPROTOCOL_H_

#include "Message.h"

class SerialStack {

public:
	SerialStack();
	virtual ~SerialStack(){}

	void alive();
	boolean send( char *data );

private:
	virtual uint16_t transmit( uint8_t * ) = 0;
	virtual uint16_t receive( uint8_t * )  = 0;

	Message 	sendMessage;

	unsigned long uptime, timestamp;
};

#endif /* SERIALPROTOCOL_H_ */
