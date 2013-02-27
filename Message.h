
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

	enum Type{
		undef_type		= (0x00),
		request 		= (0x01), 	// Request
		response		= (0x02), 	// Response
		acknowledge 	= (0x03), 	// Acknowledge
		neg_acknowledge	= (0x04), 	// Negative Acknowledge
		event			= (0x05),	// Event
		num_of_msg_type = (0x06)
	};

public:

	Instruction::Id 	getInstructionId();
	Message::Type 		getType();
	byte 				getSeqCounter();
	size_t 				getContentSize();
	Iterator*			getContent();
	byte 				getSeqCounter( Message::Type type ){ return seqCounter[type]; }

#ifdef UNITTEST
	boolean pop(byte &);
#endif

#ifndef UNITTEST
protected:
#endif

	void			error( Error::Type );

	byte 			seqCounter[Message::num_of_msg_type];
	byte 			incSeqCounter( Message::Type );
	void			decSeqCounter( Message::Type );

	size_t 			contentSize;
	byte        	*message_begin;
	Message::Type 	clear_type;
	Handler* 		handler;
	RingBuffer 		ringBuffer;
};

}  // namespace ComStack

#endif /* MESSAGE_H_ */

