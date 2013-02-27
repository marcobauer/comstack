#ifndef MSGHANDLER_H_
#define MSGHANDLER_H_

#include "TxMessage.h"
#include "RxMessage.h"

#include "Handler.h"

namespace ComStack {

class MessageHandler : public Handler {

public:
	MessageHandler();
	virtual ~MessageHandler(){}

	TxMessage* 	newMessage( Message::Type, Instruction::Id );

	void threadRead();
	void threadWrite();

#ifndef UNITTEST
private:
#endif

	virtual byte 	data_read() = 0;
	virtual size_t  data_write( byte ) = 0;
	virtual size_t 	data_write( byte *, byte ) = 0;
	virtual boolean data_available() = 0;

	RxMessage messageRx;
	TxMessage messageTx;
};

}  // namespace ComStack

#endif /* MSGHANDLER_H_ */




