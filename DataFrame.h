
#ifndef DATAFRAME_H_
#define DATAFRAME_H_

#include <Arduino.h>

#define STX (uint8_t) 0x02 	// Start of text
#define ETX (uint8_t) 0x03 	// End of text
#define DLE (uint8_t) 0x10	// Data link escape
#define SUB (uint8_t) 0x1A	// Substitute

class DataFrame {

public:
	DataFrame();
	virtual ~DataFrame(){}

	uint8_t buildFrame( const char *data, uint16_t frame_cnt );

private:
	virtual void addBuffer( const char ) = 0;
	void trimDLE( char *, uint8_t );

};

#endif /* DATAFRAME_H_ */
