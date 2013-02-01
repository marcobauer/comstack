
#ifndef DATAFRAME_H_
#define DATAFRAME_H_

#include "DataBuffer.h"

#define STX (uint8_t) 0x02 	// Start of text
#define ETX (uint8_t) 0x03 	// End of text
#define DLE (uint8_t) 0x10	// Data link escape
#define SUB (uint8_t) 0x1A	// Substitute

class DataFrame : public DataBuffer {

public:

	enum MsgType {
		request 	= 0x01, // Request Message
		response	= 0x02,	// Response Message
		acknowledge = 0x03, // Acknowledge Message
		event		= 0x04	// Event Message
	};

	DataFrame();
	virtual ~DataFrame(){}
	uint8_t buildFrame( const uint8_t *data, uint16_t frame_cnt );

private:
	void addDLE( uint8_t *, uint8_t );
	void removeDLE( uint8_t *, uint8_t );

};

#endif /* DATAFRAME_H_ */
