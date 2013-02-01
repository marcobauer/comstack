
#ifndef SERIALPROTOCOL_H_
#define SERIALPROTOCOL_H_

#include "TxMessage.h"
#include "RxMessage.h"

class SerialStack {

public:
	SerialStack();
	virtual ~SerialStack(){}

	boolean transmit( uint8_t *data );

protected:
	void receive( uint8_t *data, uint8_t size );

private:
	virtual uint16_t writeData( uint8_t * ) = 0;

	TxMessage txMessage;
	RxMessage rxMessage;
};

#endif /* SERIALPROTOCOL_H_ */
