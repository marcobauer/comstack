
#ifndef ARCH_TYPES_H_
#define ARCH_TYPES_H_

#if defined(ARDUINO)

#include <string.h>
#include <Arduino.h>
#include <HardwareSerial.h>

#else

typedef signed char 			int8_t;
typedef unsigned char 			uint8_t;
typedef signed int 				int16_t;
typedef unsigned int 			uint16_t;
typedef signed long int 		int32_t;
typedef unsigned long int 		uint32_t;
typedef signed long long int 	int64_t;
typedef unsigned long long int 	uint64_t;
typedef uint16_t 				size_t;
typedef uint8_t 				boolean;
typedef uint8_t	 				byte;

#include <stdio.h>
#include <string.h>

#endif

#include "common.h"

#endif /* ARCH_TYPES_H_ */
