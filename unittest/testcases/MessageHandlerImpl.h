
#ifndef MESSAGEHANDLER_IMPL_H_
#define MESSAGEHANDLER_IMPL_H_

#include "arch_types.h"
#include <MessageHandler.h>

using namespace ComStack;

class MessageHandlerImpl : public MessageHandler
{

public:


private:
	byte 	data_read(){ return 0xAA;}
	size_t  data_write( byte data ){}
	size_t 	data_write( byte *, byte ){}
	boolean data_available(){ return true; }

	void response( RxMessage *msg ){}
	void request( RxMessage *msg ){}
	void event( RxMessage *msg ){}
	void error( Error::Type type )
	{
		switch (type)
		{
			case Error::buffer_tx_full:
				printf("Error >>>>> Buffer transmit full \n");
				break;

			case Error::buffer_rx_full:
				printf("Error >>>>> Buffer receive full \n");
				break;


			case Error::msg_invalid:
				printf("Error >>>>> Message invalid \n");
				break;

			case Error::msg_crc_error:
				printf("Error >>>>> Message CRC error \n");
				break;

			case Error::msg_seq_error:
				printf("Error >>>>> Message Seq-Counter error \n");
				break;

			case Error::msg_rx_no_start:
				printf("Error >>>>> Buffer corruption missing start symbol \n");
				break;

			case Error::msg_rx_no_data:
						printf("Error >>>>> Buffer corruption missing content end symbol \n");
						break;

			case Error::msg_rx_no_end:
					printf("Error >>>>> Buffer corruption missing end symbol \n");
					break;



			default:
				break;
		}
	}

	void warn( Warning::Type type )
	{
		switch (type)
		{
			case Warning::buffer_rx_cleanup:
				printf("Error >>>>> Buffer receive cleaning performed\n");
				break;

			case Warning::buffer_rx_overload:
				printf("Error >>>>> Buffer receive 90 percent load\n");
				break;

			case Warning::buffer_tx_overload:
				printf("Error >>>>> Buffer transmit 90 percent load\n");
				break;

			default:
				break;
		}
	}
};

#endif /* MESSAGEHANDLER_IMPL_H_ */
