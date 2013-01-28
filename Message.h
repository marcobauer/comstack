
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <Arduino.h>
#include "DataFrame.h"

class Message : public DataFrame {

public:

	enum msg_type {
		request 	= 0x01, // Request Message
		response	= 0x02,	// Response Message
		acknowledge = 0x03, // Acknowledge Message
		event		= 0x04	// Event Message
	};

	Message();
	uint8_t create( const char *, enum msg_type type );

	uint8_t* data();
	uint16_t getCounter ();

private:
		void addBuffer( const char );
		void clearBuffer();

		uint8_t buffer[256];
		uint8_t buffer_size;


		uint16_t incCounter();
		uint16_t counter;
};

#endif /* MESSAGE_H_ */
