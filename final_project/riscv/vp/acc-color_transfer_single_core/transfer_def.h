#ifndef COLOR_TRANSFER_DEF_H_
#define COLOR_TRANSFER_DEF_H_

#define CLOCK_PERIOD 10

#define MAX_IMAGE_BUFFER_LENTH 1024
#define THRESHOLD 90

const int DMA_TRANS = 64;

// Color transfer transport addresses
// Used between blocking_transport() & do_filter()
const int COLORTRANSFER_P1_ADDR = 0x00000000;
const int COLORTRANSFER_P1_RESULT_ADDR = 0x00000004;

// const int GAUSS_FILTER_RS_R_ADDR = 0x00000000;
// const int GAUSS_FILTER_RS_W_WIDTH = 0x00000004;
// const int GAUSS_FILTER_RS_W_HEIGHT = 0x00000008;
// const int GAUSS_FILTER_RS_W_DATA = 0x0000000C;
// const int GAUSS_FILTER_RS_RESULT_ADDR = 0x00800000;

union word {
	float flt;
	int sint;
	unsigned int uint;
	unsigned char uc[4];
};

#endif
