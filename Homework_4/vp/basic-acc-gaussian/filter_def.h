#ifndef FILTER_DEF_H_
#define FILTER_DEF_H_

#define CLOCK_PERIOD 10

#define MAX_IMAGE_BUFFER_LENTH 1024
#define THRESHOLD 90

// Gauss mask parameters
const int MASK_X = 3;
const int MASK_Y = 3;
const int DMA_TRANS = 64;

// Gauss Filter inner transport addresses
// Used between blocking_transport() & do_filter()
const int GAUSS_FILTER_R_ADDR = 0x00000000;
const int GAUSS_FILTER_RESULT_ADDR = 0x00000004;

const int GAUSS_FILTER_RS_R_ADDR = 0x00000000;
const int GAUSS_FILTER_RS_W_WIDTH = 0x00000004;
const int GAUSS_FILTER_RS_W_HEIGHT = 0x00000008;
const int GAUSS_FILTER_RS_W_DATA = 0x0000000C;
const int GAUSS_FILTER_RS_RESULT_ADDR = 0x00800000;

union word {
	int sint;
	unsigned int uint;
	unsigned char uc[4];
};

// GAUSS mask
const double mask[MASK_X][MASK_Y] = {
    {0.077847, 0.123317, 0.077847}, {0.123317, 0.195346, 0.123317}, {0.077847, 0.123317, 0.077847}};
#endif
