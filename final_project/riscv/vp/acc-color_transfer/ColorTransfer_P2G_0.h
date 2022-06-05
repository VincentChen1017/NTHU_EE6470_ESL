#ifndef COLOR_TRANSFER_P2G_0_H_
#define COLOR_TRANSFER_P2G_0_H_
#include <cmath>
#include <iomanip>
#include <systemc>
using namespace sc_core;

#include <tlm_utils/simple_target_socket.h>

#include <tlm>

#include "transfer_def.h"

struct COLORTRANSFER_P2G_0 : public sc_module {
	tlm_utils::simple_target_socket<COLORTRANSFER_P2G_0> tsock;

	sc_fifo<unsigned char> x, y, z;
	sc_fifo<double> og_result;

	SC_HAS_PROCESS(COLORTRANSFER_P2G_0);

	COLORTRANSFER_P2G_0(sc_module_name n) : sc_module(n), tsock("t_skt"), base_offset(0) {
		tsock.register_b_transport(this, &COLORTRANSFER_P2G_0::blocking_transport);
		SC_THREAD(do_transformation);
	}

	~COLORTRANSFER_P2G_0() {}

	double g;
	unsigned int base_offset;
	word data;
	void do_transformation() {
		{ wait(CLOCK_PERIOD, SC_NS); }
		while (true) {
			g = 0;
			wait(CLOCK_PERIOD, SC_NS);
			for (int i = 0; i < 3; i++) {
				x.read();
				y.read();
				z.read();
				data.uc[0] = x.read();
				data.uc[1] = y.read();
				data.uc[2] = z.read();
				data.uc[3] = 0;
				wait(CLOCK_PERIOD, SC_NS);
				if (i == 0)
					g += (sqrt(3) / 3) * log10(data.flt);
				else if (i == 1)
					g += (sqrt(6) / 6) * log10(data.flt);
				else
					g += (-sqrt(2) / 2) * log10(data.flt);
				wait(CLOCK_PERIOD, SC_NS);
			}

			g = pow(10, g);
			og_result.write(g);
		}
	}

	void blocking_transport(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay) {
		wait(delay);
		// unsigned char *mask_ptr = payload.get_byte_enable_ptr();
		// auto len = payload.get_data_length();
		tlm::tlm_command cmd = payload.get_command();
		sc_dt::uint64 addr = payload.get_address();
		unsigned char *data_ptr = payload.get_data_ptr();

		addr -= base_offset;

		// cout << (int)data_ptr[0] << endl;
		// cout << (int)data_ptr[1] << endl;
		// cout << (int)data_ptr[2] << endl;
		word buffer;
		switch (cmd) {
			case tlm::TLM_READ_COMMAND:
				// cout << "READ" << endl;
				switch (addr) {
					case COLORTRANSFER_P2G_0_RESULT_ADDR:
						buffer.sint = og_result.read();
						break;
					default:
						std::cerr << "READ Error! COLORTRANSFER_P2G_0::blocking_transport: address 0x"
						          << std::setfill('0') << std::setw(8) << std::hex << addr << std::dec
						          << " is not valid" << std::endl;
				}
				data_ptr[0] = buffer.uc[0];
				data_ptr[1] = 0;
				data_ptr[2] = 0;
				data_ptr[3] = 0;
				break;
			case tlm::TLM_WRITE_COMMAND:
				// cout << "WRITE" << endl;
				switch (addr) {
					case COLORTRANSFER_P2G_0_R_ADDR:
						x.write(data_ptr[0]);
						y.write(data_ptr[1]);
						z.write(data_ptr[2]);
						break;
					default:
						std::cerr << "WRITE Error! COLORTRANSFER_P2G_0::blocking_transport: address 0x"
						          << std::setfill('0') << std::setw(8) << std::hex << addr << std::dec
						          << " is not valid" << std::endl;
				}
				break;
			case tlm::TLM_IGNORE_COMMAND:
				payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
				return;
			default:
				payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
				return;
		}
		payload.set_response_status(tlm::TLM_OK_RESPONSE);  // Always OK
	}
};
#endif
