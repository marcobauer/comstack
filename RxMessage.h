
#ifndef RX_MESSAGE_H_
#define RX_MESSAGE_H_

#include "arch_types.h"
#include "DataFrame.h"

class RxMessage : public DataFrame {

public:

	RxMessage();
	uint8_t collect( const uint8_t *, uint8_t size );
	uint16_t getCounter();

private:
		uint16_t incCounter();
		uint16_t counter;
};

#endif /* RX_MESSAGE_H_ */
