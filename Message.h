
#ifndef DATAFRAME_H_
#define DATAFRAME_H_

#include "DataBuffer.h"

#define STX (uint8_t) 0x02 	// Start of text
#define ETX (uint8_t) 0x03 	// End of text
#define DLE (uint8_t) 0x10	// Data link escape

#define MSG_DATA_MAX 50
#define MSG_SEND_DATA_MAX 112

class Message {

public:

	enum Type {
		request 		= 0x01, // Request
		response		= 0x02,	// Response
		acknowledge 	= 0x03, // Acknowledge
		neg_acknowledge	= 0x04,	// Negative Acknowledge
		event			= 0x05	// Event
	};

	enum Result{
		failed = 0x01,
		passed = 0x02
	};

	typedef struct{
		byte 	content[MSG_DATA_MAX];
		byte	size;
		byte	id;
		Message::Type type;
	} Data;

	typedef struct{
		byte 	content[MSG_SEND_DATA_MAX];
		byte	size;
		size_t	status;
	} Payload;

	Message();
	virtual ~Message(){}
	Message::Result enqueueTx( Message::Data *  );
	boolean dequeueRx( Message::Data * );

protected:
	boolean dequeueTx( Message::Payload * );
	void enqueueRx( Message::Payload * );

private:

	enum CounterTyp {
		transmit	= 0,
		receive		= 1,
		error		= 2,
		counter_num	= 3
	};

	void pushDLE( byte );
	void removeDLE( uint8_t *, uint8_t );

	uint16_t incCounter(Message::CounterTyp);
	uint16_t counter[counter_num];

	DataBuffer txBuffer, rxBuffer;

};

#endif /* DATAFRAME_H_ */
