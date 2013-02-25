
#include "TestMessageHandler.h"

void TestMessageHandler::lock_unlock()
{
//	msgHandler.incCounter();
//	msgHandler.incCounter();
//	msgHandler.incCounter();
//	msgHandler.incCounter();
//
//	TxMessage *message = msgHandler.newMessage(Message::request, 0x44);
//
//	for( int i=0; i< 5; i++ )
//		CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
//
//	CPPUNIT_ASSERT( message->getSize() == 5 );
//	CPPUNIT_ASSERT( message->send() == ComStack::passed );
//	CPPUNIT_ASSERT( msgHandler.counter == 5 );
//
//	//###################################################################################
//
//	message = msgHandler.newMessage(Message::request, 0x44);
//	for( int i=0; i< 4; i++ )
//		CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
//
//	CPPUNIT_ASSERT( message->add( DLE )  == ComStack::passed );
//	CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
//	CPPUNIT_ASSERT( message->add( SMSG ) == ComStack::passed );
//	CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
//	CPPUNIT_ASSERT( message->add( EMSG ) == ComStack::passed );
//	CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
//	CPPUNIT_ASSERT( message->getSize() == 10 );
//	CPPUNIT_ASSERT( message->send() == ComStack::passed );
//
//
//	//###################################################################################
//
//	message = msgHandler.newMessage(Message::request, 0x44);
//
//	for( int i=0; i< 15; i++ )
//		CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
//
//
//	CPPUNIT_ASSERT( message->getSize() == 15 );
//	CPPUNIT_ASSERT( message->send() == ComStack::buffer_full );
//
//
//	//###################################################################################
//	RingBuffer *buffer = msgHandler.getBuffer( Buffer::transmit );
//
//	uint16_t size = buffer->size();
//	boolean retval;
//	for(int i=0; i< 25; i++ )
//	{	buffer->pop(retval);
//		CPPUNIT_ASSERT( retval == true );
//	}
//
//	buffer->print();
//	CPPUNIT_ASSERT( buffer->size() == (size-25) );
//
//	message = msgHandler.newMessage(Message::request, 0x44);
//	for( int i=0; i< 10; i++ )
//		CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
//
//	CPPUNIT_ASSERT( message->getSize() == 10 );
//	CPPUNIT_ASSERT( message->send() == ComStack::passed );

}

//void TestMessageHandler::enqueueRx()
//{
////	MessageHandlerImpl msgHandler;
////	msgHandler.incCounter();
////	msgHandler.incCounter();
////	msgHandler.incCounter();
////	msgHandler.incCounter();
////
////	RingBuffer 	*bufferRx 	= msgHandler.getBuffer(Buffer::receive);
////	RingBuffer 	*bufferTx 	= msgHandler.getBuffer(Buffer::transmit);
////	TxMessage 	*message 	= msgHandler.newMessage(Message::request, 0x44);
////
////	message->add( 0xAA );
////	message->add( 0xAA );
////	message->add( 0xAA );
////	message->add( 0xAA );
////	message->send();
////	bufferTx->print();
////
////	BufferIterator *iterator = bufferTx->getIterator();
////
////	byte *data;
////	while((data = iterator->next()))
////		bufferRx->push( *data );
////
////	bufferRx->print();
////	bufferRx->save();
////
////	//####################################
////
////	message = msgHandler.newMessage(Message::request, 0x55);
////
////	message->add( 0xAA );
////	message->add( SMSG );
////	message->add( 0xAA );
////	message->add( DLE );
////	message->add( 0xAA );
////	message->add( EMSG );
////	message->send();
////	bufferTx->print();
//}
//
//void TestMessageHandler::dequeueTx()
//{
////	MessageHandlerImpl msgHandler;
////	RingBuffer *buffer = msgHandler.getBuffer(Buffer::transmit);
////	msgHandler.incCounter();
////	msgHandler.incCounter();
////	msgHandler.incCounter();
////	msgHandler.incCounter();
////
////	TxMessage *message = msgHandler.newMessage(Message::request, 0x44);
////
////	for( int i=0; i< 5; i++ )
////		CPPUNIT_ASSERT( message->add( 0x88 ) == ComStack::passed );
////
////	CPPUNIT_ASSERT( message->send() == ComStack::passed );
////
////	buffer->print();
//}
//
//void TestMessageHandler::dequeueRx()
//{
//
//}
