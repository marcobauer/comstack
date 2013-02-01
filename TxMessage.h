
#ifndef TX_MESSAGE_H_
#define TX_MESSAGE_H_

#include "arch_types.h"
#include "DataFrame.h"

class TxMessage : public DataFrame {

public:

	TxMessage();
	uint8_t create( const uint8_t *, MsgType type );
	uint8_t* data();
//	uint16_t getCounter ();

private:
		uint16_t incCounter();
		uint16_t counter;
};

#endif /* TX_MESSAGE_H_ */
