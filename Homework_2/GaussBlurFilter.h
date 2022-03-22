#ifndef GAUSS_FILTER_H_
#define GAUSS_FILTER_H_
#include <systemc>
using namespace sc_core;

#include <tlm>
#include <tlm_utils/simple_target_socket.h>

#include "filter_def.h"

class GaussBlurFilter : public sc_module
{
public:
  tlm_utils::simple_target_socket<GaussBlurFilter> t_skt;

  sc_fifo<unsigned char> i_r;
  sc_fifo<unsigned char> i_g;
  sc_fifo<unsigned char> i_b;
  sc_fifo<double> or_result;
  sc_fifo<double> og_result;
  sc_fifo<double> ob_result;

  SC_HAS_PROCESS(GaussBlurFilter);
  GaussBlurFilter(sc_module_name n);
  ~GaussBlurFilter();

private:
  void do_filter();
  double r_val;
  double g_val;
  double b_val;
  unsigned int base_offset;
  void blocking_transport(tlm::tlm_generic_payload &payload,
                          sc_core::sc_time &delay);
};
#endif
