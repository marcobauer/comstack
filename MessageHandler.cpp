#include "MessageHandler.h"
#include "arch_types.h"

using namespace ComStack;

MessageHandler::MessageHandler() : messageRx( this ), messageTx( this )
{}

#ifndef SLIM_FRAME

TxMessage* MessageHandler::newMessage( Message::Type type, Instruction::Id id )
{
	return messageTx.create( type, id );
}

#else

TxMessage* MessageHandler::newMessage()
{
	return messageTx.create();
}

#endif

void MessageHandler::threadRead()
{
	/*!
	 * 												Process received data
	 ********************************************************************/
	if( data_available() )
	{
		while ( data_available() )
		{
			if( !messageRx.add( data_read() ) )
				break;
		}

		RxMessage *msgRx = messageRx.getMessage();

		if( msgRx )
		{
#ifdef SLIM_FRAME

			rxMsgCallback( msgRx );

#else
			switch( msgRx->getType() )
			{
				case Message::request:
					request( msgRx );
					msgRx->accept();
					break;

				case Message::response:
					response( msgRx );
					msgRx->accept();
					break;

				case Message::event:
					event( msgRx );
					msgRx->accept();
					break;

				default:
					break;
			}
#endif

		}
	}
}

void MessageHandler::threadWrite()
{
	/*!
	 * 												Process transmit data
	 ********************************************************************/
	Iterator *iterator = messageTx.getBuffer();

	if( iterator ){
		byte *data;
		while( ( data = iterator->next() ))
		{
			data_write( *data );
			messageTx.accept(1);
		}
	}
}
