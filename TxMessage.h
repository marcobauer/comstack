
#ifndef TXMESSAGE_H_
#define TXMESSAGE_H_

#include "arch_types.h"
#include "abstract/Handler.h"
#include "RingBuffer.h"
#include "Message.h"

namespace ComStack {

class TxMessage : public Message {

public:

	TxMessage( Handler* );
	virtual ~TxMessage(){}

	TxMessage* 	create( Message::Type, Instruction::Id );
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

