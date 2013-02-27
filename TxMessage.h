
#ifndef TXMESSAGE_H_
#define TXMESSAGE_H_

#include "arch_types.h"
#include "Handler.h"
#include "RingBuffer.h"
#include "Message.h"

namespace ComStack {

class TxMessage : public Message {

public:

	TxMessage( Handler* );
	virtual ~TxMessage(){}

#ifndef SLIM_FRAME
	TxMessage* create( Message::Type type, Instruction::Id id );
#else
	TxMessage* create();
#endif

	size_t  	send();
	boolean 	add(byte);

	Iterator*	getBuffer();
	void    	accept( size_t );

#ifndef UNITTEST
private:
#endif
	boolean 	insertDLE( byte value );

};

}  // namespace ComStack

#endif /* TXMESSAGE_H_ */

