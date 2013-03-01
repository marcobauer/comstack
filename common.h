
#ifndef COMMON_H_
#define COMMON_H_

#include "config.h"

namespace ComStack {

	namespace Error {

		enum Type {
			buffer_rx_full	= (0x00),
			buffer_tx_full	= (0x01),
			msg_rx_no_start	= (0x02),
			msg_rx_no_end	= (0x03),
			msg_rx_no_data	= (0x04),
			msg_crc_error	= (0x05),
			msg_seq_error	= (0x06),
			msg_invalid		= (0x07),
			msg_invalid_id	= (0x08),
			missing_role	= (0x09)
		};
	};

	namespace Warning {
		enum Type {
			buffer_tx_overload	= (0x00),
			buffer_rx_overload	= (0x01),
			buffer_rx_cleanup	= (0x02)
		};
	};

	namespace Instruction {

		enum Id {
			undef_id		= (0x00),
			adc0  			= (0x01),
			adc1			= (0x02),
			adc2			= (0x03),
			adc3			= (0x04),
			port0			= (0x05),
			port1			= (0x06),
			port2			= (0x07),
			port3			= (0x08),
			led0			= (0x09),
			led1			= (0x10),
			led2			= (0x11),
			led3			= (0x12),
			uptime			= (0x13),
			startup			= (0x14),
			num_of_id		= (0x15)
		};

	}  // namespace Instruction

};


#endif /* COMMON_H_ */
