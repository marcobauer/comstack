
#ifndef SERIALPROTOCOL_H_
#define SERIALPROTOCOL_H_

#include "Message.h"
#include "arch_types.h"

class SerialStack : public Message {

public:
	SerialStack();
	virtual ~SerialStack(){}

	void process();

private:
	void thread_read();
	void thread_write();

	Message::Data rxMsgData;
	Message::Payload payload;
	boolean	pending_send;

	virtual byte 	data_read() = 0;
	virtual size_t 	data_write( Message::Payload * ) = 0;
	virtual boolean data_available() = 0;

	virtual void handle_response( Message::Data * ) = 0;
	virtual	void handle_request( Message::Data * ) = 0;
	virtual	void handle_event( Message::Data * ) = 0;

};

#endif /* SERIALPROTOCOL_H_ */
