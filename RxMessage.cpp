
#include "RxMessage.h"

RxMessage::RxMessage() : counter(0)
{

}

uint8_t RxMessage::collect( const uint8_t *data, uint8_t size )
{

}

//uint8_t* RxMessage::data()
//{
//	return &buffer[0];
//}

uint16_t RxMessage::incCounter()
{
	if( counter == 0xFFFF)
		return 0;

	return counter++;
}

