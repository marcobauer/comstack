
#include "TestMessageImpl.h"

#define MSG_FRAME_SIZE 		11
#define SMSG 				(uint8_t) 0x02 		// Start of Message
#define ECNT				(uint8_t) 0x01 		// End of Content
#define EMSG 				(uint8_t) 0x00 		// End of Message
#define DLE  				(uint8_t) 0x10	// Data link escape

void TestMessageImpl::counter()
{
	printf("\n-------------------------------------------------- Testcase: counter \n");
	TxMessage message( &messageHandler );
	TxMessage *txMsg;

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 0 );
	message.error(Error::buffer_tx_full);

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 0 );
	CPPUNIT_ASSERT( txMsg->send() );

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 1 );
	CPPUNIT_ASSERT( txMsg->send() );

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 2 );
	message.error(Error::buffer_tx_full);

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 2 );
	CPPUNIT_ASSERT( txMsg->send() );

	// Manipulation of private member
	message.seqCounter[Message::request] = 0xFE;
	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == (0xFF - (DLE+1) ) );
	message.error(Error::buffer_tx_full);

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == (0xFF - (DLE+1) ) );
	CPPUNIT_ASSERT( txMsg->send() );

	popMessage(message, MSG_FRAME_SIZE );

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 0 );
	message.error(Error::buffer_tx_full);

	CPPUNIT_ASSERT( message.create( Message::request, Instruction::adc0 ) );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 0 );
	CPPUNIT_ASSERT( txMsg->send() );

	popMessage(message, MSG_FRAME_SIZE );

	txMsg = message.create( Message::request, Instruction::adc0 );
	CPPUNIT_ASSERT( txMsg != NULL );
	CPPUNIT_ASSERT( txMsg->getSeqCounter() == 1 );
	CPPUNIT_ASSERT( txMsg->send() );
}

void TestMessageImpl::msgOverflow()
{
//	printf("\n-------------------------------------------------- Testcase: message overflow\n");
//	byte value;
//	size_t msgSize;
//	TxMessage message( &messageHandler );
//
//	msgSize = pushMessage( message, Message::request,  	Package::adc0, 0, 10 );
//	popMessage( message, BUFFER_SIZE );
//	msgSize = pushMessage( message, Message::request,  	Package::adc0, 1, 15 );
//	msgSize = pushMessage( message, Message::response, 	Package::adc0, 0, 20 );
//	popMessage( message, 20 );
//	msgSize = pushMessage( message, Message::event, 	Package::adc0, 0, 0 );
//	msgSize = pushMessage( message, Message::request, 	Package::adc0, 2, 6 );
//	popMessage( message, BUFFER_SIZE );
}

void TestMessageImpl::msgError()
{
//	printf("\n-------------------------------------------------- Testcase: message error\n");
//	MessageImpl message( &messageHandler, Message::transmit);
//
//	pushMessage( message, Message::request,  	Message::adc0, 0, 28 );
//
//	pushErrorContent( message, Message::response ,  7 );
//	pushErrorContent( message, Message::response ,  7 );
//	pushMessage( message, Message::response,  	Message::adc0, 0, 0 );
//
//	pushErrorHead( message, Message::request );
//	popMessage( message, 10 );
//
//	pushErrorTail(message, Message::request, 9 );
//	pushErrorTail(message, Message::request, 8 );
//	pushErrorTail(message, Message::request, 7 );
//
//	pushMessage( message, Message::request, Message::adc1, 1, 6 );
//	popMessage(message, 15 );
//	pushErrorContent( message, Message::request, 12  );
//	pushErrorTail(message, Message::request, 11 );
//	pushErrorTail(message, Message::request, 10 );
//	pushErrorTail(message, Message::request, 9 );
//	pushMessage( message, Message::request, Message::adc1, 2, 8 );
//
//	pushErrorHead( message, Message::request );
}

void TestMessageImpl::findMessage()
{
	printf("\n-------------------------------------------------- Testcase: findMessage \n");
	byte value;
	RxMessage messageRX( &messageHandler );
	TxMessage messageTX( &messageHandler );

	//################################################################################### push 5 > Tx	(0)
	writeTx( messageTX, Message::request, 	Instruction::adc0, 5, 0x88 );
	//################################################################################### push 8 > Tx	(1)
	writeTx( messageTX, Message::response, 	Instruction::led2, 8, EMSG);

	//################################################################################### Copy TX > RX
	copyTx2Rx( messageTX, messageRX );

	//################################################################################### push 10 > Tx	(2)
	writeTx( messageTX, Message::response, 	Instruction::led2, 10, 0x88 );

	//################################################################################### read (0)
	readRx( messageRX, Message::request, 	Instruction::adc0, 0, 5, 0x88 );

	//################################################################################### Copy TX > RX
	copyTx2Rx( messageTX, messageRX );
	//################################################################################### read (1)
	readRx( messageRX, Message::response, 	Instruction::led2, 0, 8, EMSG );

	//################################################################################### push 1 > Tx	(3)
	writeTx( messageTX, Message::request, 	Instruction::port0, 1, 0x88 );
	//################################################################################### push 2 > Tx	(4)
	writeTx( messageTX, Message::response, 	Instruction::port1, 2, DLE);
	//################################################################################### Copy TX > RX
	copyTx2Rx( messageTX, messageRX );

	//################################################################################### Corrupt (2)
	messageRX.pop(value);
	messageRX.pop(value);

	//################################################################################### read (3)
	readRx( messageRX, Message::request, 	Instruction::port0, 1, 1, 0x88 );
	//################################################################################### read (3)
	readRx( messageRX, Message::response, 	Instruction::port1, 2, 2, DLE );

}

//size_t TestMessageImpl::pushMessage( MessageImpl &message, Message::Type type, Package::Id id, byte seqcount, size_t data_size )
//{
//	size_t msgSize;
//	size_t old_size = message.ringBuffer.size();
//
//	printf("\nPush >>>  %02d | size : %02d\n", data_size + MSG_FRAME_SIZE, old_size );
//	TxMessage* txMsg = message.create( type, id);
//	CPPUNIT_ASSERT( txMsg != NULL );
//	message.ringBuffer.print();
//	CPPUNIT_ASSERT( txMsg->getId() == id );
//	CPPUNIT_ASSERT( txMsg->getSeqCounter() == seqcount );
//	CPPUNIT_ASSERT( txMsg->getType() == type );
//
//	for( int i=0; i< data_size; i++ )
//		CPPUNIT_ASSERT( txMsg->add( 0x88 ) );
//
//	msgSize = txMsg->send();
//	message.ringBuffer.print();
//	printf("msgSize= %d | size(%d)", msgSize, message.ringBuffer.size());
//	CPPUNIT_ASSERT( msgSize >= (data_size + MSG_FRAME_SIZE) );
//	CPPUNIT_ASSERT( message.ringBuffer.size() >= ( old_size + data_size + MSG_FRAME_SIZE) );
//	return msgSize;
//}
//
void TestMessageImpl::popMessage( Message &message, size_t data_size )
{
	byte value;
	size_t old_size = message.ringBuffer.size();

//	printf("Pop  <<<  %02d | old-size : %02d ", data_size, old_size );
	for(int i=0; i<data_size; i++ )
		CPPUNIT_ASSERT( message.pop(value) == true );

	CPPUNIT_ASSERT( message.ringBuffer.size() == ( old_size - data_size) );
//	printf(">> new-size : %02d\n", message.ringBuffer.size() );
}
//
//void TestMessageImpl::pushErrorHead( MessageImpl &message, Message::Type type )
//{
//	TxMessage* txMsg = message.create( type, Message::port0 );
//	CPPUNIT_ASSERT( txMsg == NULL );
//}
//
//void TestMessageImpl::pushErrorTail( MessageImpl &message, Message::Type type, size_t size )
//{
//	TxMessage* txMsg = message.create( type, Message::port0 );
//	CPPUNIT_ASSERT( txMsg != NULL );
//	for( int i=0; i< size; i++ )
//	{
//		CPPUNIT_ASSERT( txMsg->add( 0x88 ) );
//	}
//	message.ringBuffer.print();
//	CPPUNIT_ASSERT( txMsg->send() == 0 );
//}
//
//void TestMessageImpl::pushErrorContent( MessageImpl &message, Message::Type type, size_t error_pos )
//{
//	printf("\nPush >>>  error pos : %d\n", error_pos );
//	TxMessage* txMsg = message.create( type, Message::port0 );
//	CPPUNIT_ASSERT( txMsg != NULL );
//
//	for( int i=0; i< error_pos+2; i++ )
//	{
//		if( i < (error_pos-1) )
//			CPPUNIT_ASSERT( txMsg->add( 0x88 ) );
//		else
//			CPPUNIT_ASSERT( txMsg->add( 0x88 ) == false );
//	}
//}

void TestMessageImpl::copyTx2Rx( TxMessage &messageTx, RxMessage &messageRx )
{
	byte value;
	while( messageTx.pop(value) )
		messageRx.add( value );
}

void TestMessageImpl::readRx( RxMessage &message, Message::Type type, Instruction::Id id, byte seqCnt, size_t contentSize, byte value )
{
	byte *data_ptr;
	printf("Read:  %02x ; Count: %d ; Id: %d\n", value, contentSize, id );
	RxMessage *rxMsg = message.getMessage();
	CPPUNIT_ASSERT( rxMsg != NULL );
	CPPUNIT_ASSERT( rxMsg->getContentSize() == contentSize );
	CPPUNIT_ASSERT( rxMsg->getInstructionId() == id );
	CPPUNIT_ASSERT( rxMsg->getType() == type );
	CPPUNIT_ASSERT( rxMsg->getSeqCounter() == seqCnt );
	Iterator *iter = rxMsg->getContent();
	CPPUNIT_ASSERT( iter != NULL );

	while( (data_ptr = iter->next()) )
		CPPUNIT_ASSERT( *data_ptr == value );

	rxMsg->accept();
}

void TestMessageImpl::writeTx( TxMessage &message, Message::Type type, Instruction::Id id, size_t contentSize, byte value )
{
	TxMessage * txMsg = message.create( type, id );
	printf("Write: %02x ; Count: %d ; Id: %d\n", value, contentSize, id );

	for( int i=0; i< contentSize; i++ )
		CPPUNIT_ASSERT( txMsg->add( value ) );

	CPPUNIT_ASSERT( txMsg->send() > 0  );
}
