// All systemc modules should include systemc.h header file
#include "systemc.h"
#include <assert.h>
#include <stdint.h>
#include "jpec.h"
#include "jpec_enc_block_zz.cpp"
#define ERROR 0.001

// Quant
// -461 22 1 0 1 0 0 1
// -57 -20 3 1 -1 0 0 -1
// 30 -4 -9 -2 0 0 0 0
// -8 18 4 0 0 0 0 1
// 0 -10 1 1 0 0 0 0
// 0 2 -2 -1 0 0 0 0
// 0 0 1 0 -1 0 0 0
// 0 0 0 0 1 0 0 0

// ZZ
// -461 22 -57 30 -20 1 0 3
// -4 -8 0 18 -9 1 1 0
// -1 -2 4 -10 0 0 2 1
// 0 0 0 0 1 0 0 0
// 1 -2 0 0 0 1 -1 0
// 0 0 -1 0 0 0 0 0
// 0 0 -1 0 0 1 0 0
// 0 1 0 0 0 0 0 0

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {


  int quant_in[64] = {
    -461, 22, 1, 0, 1, 0, 0, 1,
    -57, -20, 3, 1, -1, 0, 0, -1,
    30, -4, -9, -2, 0, 0, 0, 0,
    -8, 18, 4, 0, 0, 0, 0, 1,
    0, -10, 1, 1, 0, 0, 0, 0,
    0, 2, -2, -1, 0, 0, 0, 0,
    0, 0, 1, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0
  };

  int expected_zz[64] = {
    -461, 22, -57, 30, -20, 1, 0, 3,
    -4, -8, 0, 18, -9, 1, 1, 0,
    -1, -2, 4, -10, 0, 0, 2, 1,
    0, 0, 0, 0, 1, 0, 0, 0,
    1, -2, 0, 0, 0, 1, -1, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0
  };

  sc_signal<int> quant[BLOCK_SIZE];
  sc_signal<int> zz_block[BLOCK_SIZE];
  sc_signal<int> len;

  jpec_enc_block_zz zz("zz");

  for (int i = 0; i < BLOCK_SIZE; i++) {
    zz.quant[i](quant[i]);
    zz.zz_block[i](zz_block[i]);
  }
  zz.len(len);
  sc_start();

  for (int i = 0; i < BLOCK_SIZE; i++) {
    quant[i] = quant_in[i];
  }
  sc_start(1, SC_NS);
  for (int i = 0; i < BLOCK_SIZE; i++) {
    cout << zz_block[i].read() << " and " << expected_zz[i] << '\n';
    assert(zz_block[i].read() == expected_zz[i] && expected_zz[i] == zz_block[i].read());
  }

  return(0);
}
