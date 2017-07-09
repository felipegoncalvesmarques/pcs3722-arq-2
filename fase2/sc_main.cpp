// All systemc modules should include systemc.h header file
#include "systemc.h"
#include <assert.h>
#include <stdint.h>
#include "jpec.h"
#include "jpec_enc_block_dct.cpp"
#define ERROR 0.001

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {

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
    block[i] = i;
  }
  sc_start(1, SC_NS);
  for (int i = 0; i < BLOCK_SIZE; i++) {
    assert(dct_block[i].read() - 0.1 < ERROR && 0.1 -  dct_block[i].read() < ERROR);
  }

  width = 3;
  height = 4;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] = 0;
  }
  sc_start(1, SC_NS);
  for (int i = 0; i < BLOCK_SIZE; i++) {
    assert(dct_block[i].read() - 0.1 < ERROR && 0.1 -  dct_block[i].read() < ERROR);
  }

  return(0);
}
