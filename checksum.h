
#ifndef CHECKSUM_H_
#define CHECKSUM_H_

#include "arch_types.h"
#include "abstract/Iterator.h"

uint16_t calcCRC16( Iterator* );
boolean  compCRC16( Iterator*, uint16_t value );

#endif /* CHECKSUM_H_ */
