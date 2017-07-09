#include "systemc.h"
#include "jpec.h"
#include <stdint.h>

const float coeff[7] = {
	0.49039, 0.46194, 0.41573, 0.35355,
	0.27779, 0.19134, 0.09755
};

// Hello_world is module name
SC_MODULE (jpec_enc_block_dct) {

  sc_in<uint8_t> block[BLOCK_SIZE];
  sc_in<uint8_t> width, height;
  sc_out<float> dct_block[BLOCK_SIZE];

  float tmp[BLOCK_SIZE];

  SC_CTOR (jpec_enc_block_dct) {
    SC_METHOD(inc_func);
    sensitive << width << height;
    for (int i = 0; i < BLOCK_SIZE; i++) {
      sensitive << block[i];
    }
  }

  void inc_func() {
    #define TRANSLATE(col, row) (row < height.read() ? row : height.read() - 1) * width.read() + (col < width.read() ? col : width.read() - 1)
    #define JPEC_BLOCK(col, row) block[TRANSLATE(col, row)].read()
      float tmp[64];
      for (int row = 0; row < 8; row++) {
        /* NOTE: the shift by 256 allows resampling from [0 255] to [–128 127] */
        float s0 = (float) (JPEC_BLOCK(0, row) + JPEC_BLOCK(7, row) - 256);
        float s1 = (float) (JPEC_BLOCK(1, row) + JPEC_BLOCK(6, row) - 256);
        float s2 = (float) (JPEC_BLOCK(2, row) + JPEC_BLOCK(5, row) - 256);
        float s3 = (float) (JPEC_BLOCK(3, row) + JPEC_BLOCK(4, row) - 256);

        float d0 = (float) (JPEC_BLOCK(0, row) - JPEC_BLOCK(7, row));
        float d1 = (float) (JPEC_BLOCK(1, row) - JPEC_BLOCK(6, row));
        float d2 = (float) (JPEC_BLOCK(2, row) - JPEC_BLOCK(5, row));
        float d3 = (float) (JPEC_BLOCK(3, row) - JPEC_BLOCK(4, row));

        tmp[8 * row]     = coeff[3]*(s0+s1+s2+s3);
        tmp[8 * row + 1] = coeff[0]*d0+coeff[2]*d1+coeff[4]*d2+coeff[6]*d3;
        tmp[8 * row + 2] = coeff[1]*(s0-s3)+coeff[5]*(s1-s2);
        tmp[8 * row + 3] = coeff[2]*d0-coeff[6]*d1-coeff[0]*d2-coeff[4]*d3;
        tmp[8 * row + 4] = coeff[3]*(s0-s1-s2+s3);
        tmp[8 * row + 5] = coeff[4]*d0-coeff[0]*d1+coeff[6]*d2+coeff[2]*d3;
        tmp[8 * row + 6] = coeff[5]*(s0-s3)+coeff[1]*(s2-s1);
        tmp[8 * row + 7] = coeff[6]*d0-coeff[4]*d1+coeff[2]*d2-coeff[0]*d3;
      }

      for (int col = 0; col < 8; col++) {
        float s0 = tmp[     col] + tmp[56 + col];
        float s1 = tmp[ 8 + col] + tmp[48 + col];
        float s2 = tmp[16 + col] + tmp[40 + col];
        float s3 = tmp[24 + col] + tmp[32 + col];

        float d0 = tmp[     col] - tmp[56 + col];
        float d1 = tmp[ 8 + col] - tmp[48 + col];
        float d2 = tmp[16 + col] - tmp[40 + col];
        float d3 = tmp[24 + col] - tmp[32 + col];

        dct_block[     col].write(coeff[3]*(s0+s1+s2+s3));
        dct_block[ 8 + col].write(coeff[0]*d0+coeff[2]*d1+coeff[4]*d2+coeff[6]*d3);
        dct_block[16 + col].write(coeff[1]*(s0-s3)+coeff[5]*(s1-s2));
        dct_block[24 + col].write(coeff[2]*d0-coeff[6]*d1-coeff[0]*d2-coeff[4]*d3);
        dct_block[32 + col].write(coeff[3]*(s0-s1-s2+s3));
        dct_block[40 + col].write(coeff[4]*d0-coeff[0]*d1+coeff[6]*d2+coeff[2]*d3);
        dct_block[48 + col].write(coeff[5]*(s0-s3)+coeff[1]*(s2-s1));
        dct_block[56 + col].write(coeff[6]*d0-coeff[4]*d1+coeff[2]*d2-coeff[0]*d3);
      }
    #undef TRANSLATE
    #undef JPEC_BLOCK
  }
};

