
#ifndef HANDLER_H_
#define HANDLER_H_

#include "arch_types.h"

namespace ComStack {

class RxMessage;

class Handler {

public:
	virtual ~Handler(){};

#ifndef SLIM_FRAME

	virtual void response( RxMessage * ) = 0;
	virtual	void request( RxMessage * ) = 0;
	virtual	void event( RxMessage * ) = 0;

#else
	virtual void rxMsgCallback( RxMessage * ) = 0;
#endif

	virtual	void error( Error::Type ) = 0;
	virtual	void warn( Warning::Type ) = 0;

};

}  // namespace ComStack

#endif // HANDLER_H_
