
#ifndef RXMESSAGE_H_
#define RXMESSAGE_H_

#include "arch_types.h"
#include "Message.h"

namespace ComStack {

class RxMessage : public Message {

public:
	RxMessage( Handler* );
	virtual ~RxMessage(){}

	RxMessage* 	getMessage();
	void 		accept();

	boolean 	add(byte);

#ifndef UNITTEST
private:
#endif

	byte* find( Iterator *, size_t &, byte );
	byte* message_end;

};

}  // namespace ComStack

#endif /* RXMESSAGE_H_ */

