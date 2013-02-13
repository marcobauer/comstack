
#include "SerialStack.h"

SerialStack::SerialStack() : pending_send(false)
{}

void SerialStack::process()
{
	thread_read();
	thread_write();

	if( dequeueRx( &rxMsgData ) ){

		switch(rxMsgData.type)
		{
			case Message::request:
				handle_request( &rxMsgData );
				break;

			case Message::response:
				handle_response( &rxMsgData );
				break;

			case Message::event:
				handle_event( &rxMsgData );
				break;

			default:
				//! handle error
				break;
		}
	}
}

void SerialStack::thread_read()
{
	/*!
	 * 												Process received data
	 ********************************************************************/
	if( data_available() )
	{
		while ( data_available() )
		{
			payload.content[payload.size++] = data_read();
			if( payload.size == MSG_DATA_MAX )
				break;
		}

		enqueueRx( &payload );
	}
}

void SerialStack::thread_write()
{
	/*!
	 * 												Process transmit data
	 ********************************************************************/
	if( !pending_send )
	{
		if( dequeueTx( &payload ) )
		{
			payload.status = data_write( &payload );

			if( payload.status == payload.size )
			{
				pending_send = false;
				payload.status = 0;
			}else
				pending_send = true;
		}
	}else
	{

	}
}
