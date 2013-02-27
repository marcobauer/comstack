
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "arch_types.h"
#include "Handler.h"
#include "RingBuffer.h"

namespace ComStack {

class Message {

public:
	Message( Handler* );
	virtual ~Message(){}

#ifndef SLIM_FRAME

	enum Type{
		undef_type		= (0x00),
		request 		= (0x01), 	// Request
		response		= (0x02), 	// Response
		acknowledge 	= (0x03), 	// Acknowledge
		neg_acknowledge	= (0x04), 	// Negative Acknowledge
		event			= (0x05),	// Event
		num_of_msg_type = (0x06)
	};

#endif

public:

#ifndef SLIM_FRAME

	Instruction::Id 	getInstructionId();
	Message::Type 		getType();
	byte 				getSeqCounter();
	byte 				getSeqCounter( Message::Type type ){ return seqCounter[type]; }

#endif

	size_t 				getContentSize();
	Iterator*			getContent();


#ifdef UNITTEST
	boolean pop(byte &);
#endif

#ifndef UNITTEST
protected:
#endif

	void			error( Error::Type );

#ifndef SLIM_FRAME
	byte 			seqCounter[Message::num_of_msg_type];
	byte 			incSeqCounter( Message::Type );
	void			decSeqCounter( Message::Type );
	Message::Type 	clear_type;
#endif

	size_t 			contentSize;
	byte        	*message_begin;

	Handler* 		handler;
	RingBuffer 		ringBuffer;
};

}  // namespace ComStack

#endif /* MESSAGE_H_ */

