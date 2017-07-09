// All systemc modules should include systemc.h header file
#include "systemc.h"
#include <assert.h>
#include <stdint.h>
#include "jpec.h"
#include "jpec_enc_block_dct.cpp"
#define ERROR 0.001

// BLOCK
// 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0
// 74 74 0 69 66 65 0 0
// 74 71 71 68 66 63 63 59

// DCT
// -913.607   22.057 -9.517 19.645 8.625 -6.707 -5.664 -14.229
// -143.906 -26.915  11.225 -23.173 -10.115 7.748 6.675 16.613
// 110.917 15.482 -5.276 10.896 4.572 -3.128 -3.117 -7.271
// -66.633 -0.638 -2.389 4.919 2.561 -2.803 -1.465 -4.740
// 23.375 -12.795 9.190 -18.954 -8.875 8.019 5.529 15.350
// 7.792 20.532 -12.846 26.498 12.235 -10.728 -7.709 -20.954
// -20.643 -20.262 12.133 -25.029 -11.500 9.975 7.276 19.627
// 15.726 12.414 -7.304 15.069 6.909 -5.966 -4.379 -11.775

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {
  uint16_t block_in[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    74, 74, 0, 69, 66, 65, 0, 0,
    74, 71, 71, 68, 66, 63, 63, 59
  };
  float expected_dct_block[64] = {
    -913.607,   22.057, -9.517, 19.645, 8.625, -6.707, -5.664, -14.229,
    -143.906, -26.915,  11.225, -23.173, -10.115, 7.748, 6.675, 16.613,
    110.917, 15.482, -5.276, 10.896, 4.572, -3.128, -3.117, -7.271,
    -66.633, -0.638, -2.389, 4.919, 2.561, -2.803, -1.465, -4.740,
    23.375, -12.795, 9.190, -18.954, -8.875, 8.019, 5.529, 15.350,
    7.792, 20.532, -12.846, 26.498, 12.235, -10.728, -7.709, -20.954,
    -20.643, -20.262, 12.133, -25.029, -11.500, 9.975, 7.276, 19.627,
    15.726, 12.414, -7.304, 15.069, 6.909, -5.966, -4.379, -11.775
  };
  sc_signal<uint8_t> block[BLOCK_SIZE];
  sc_signal<uint8_t> width, height;
  sc_signal<float> dct_block[BLOCK_SIZE];

  jpec_enc_block_dct dct("dtc");
  dct.height(height);
  dct.width(width);

  for (int i = 0; i < BLOCK_SIZE; i++) {
    dct.block[i](block[i]);
    dct.dct_block[i](dct_block[i]);
  }
  sc_start();

  width = 8;
  height = 8;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = block_in[i];
  }
  sc_start(1, SC_NS);
  for (int i = 0; i < BLOCK_SIZE; i++) {
    cout << dct_block[i].read() << " and " << expected_dct_block[i] << '\n';
    assert(dct_block[i].read() - expected_dct_block[i] < ERROR && expected_dct_block[i] -  dct_block[i].read() < ERROR);
  }

  return(0);
}
