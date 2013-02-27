
#ifndef DEFINES_H_
#define DEFINES_H_

#include "common.h"

#define BUFFER_OVERLOAD 	(uint8_t) (BUFFER_SIZE * 0.9)

#define DLE  				(uint8_t) 0x10		// Data link escape
#define DCTL  				(uint8_t) 0xFF		// Data Control
#define SMSG 				(uint8_t) 0x01 		// Start of Message
#define EMSG 				(uint8_t) 0x00 		// End of Message

#ifndef SLIM_FRAME

#define ECNT				(uint8_t) 0x02 		// End of Content
#define MSG_DLE_OFFSET		(uint8_t) (DLE+1)
#define MSG_POS_TYPE 		(uint8_t) 1
#define MSG_POS_ID 			(uint8_t) 2
#define MSG_POS_SCNT 		(uint8_t) 3
#define MSG_POS_CONTENT 	(uint8_t) 4
#define MSG_FRAME_SIZE 		(uint8_t) 11

#else

#define MSG_FRAME_SIZE 		(uint8_t) 4
#define MSG_POS_CONTENT 	(uint8_t) 1

#endif

#endif /* COMMON_H_ */
