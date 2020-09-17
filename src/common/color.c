#include "color.h"

unsigned int
Pyuv422torgb241(unsigned char * input_ptr, unsigned char * output_ptr, unsigned int image_width, unsigned int image_height)
{
	unsigned int i, size;
	unsigned char Y, Y1, U, V;
	unsigned char *buff = input_ptr;
	unsigned char *output_pt = output_ptr;
	size = image_width * image_height /2;
	for (i = size; i > 0; i--) {
		/* bgr instead rgb ?? */
		Y = buff[0] ;
		U = buff[1] ;
		Y1 = buff[2];
		V = buff[3];
		buff += 4;
		*output_pt++ = R_FROMYV(Y,V);
		*output_pt++ = G_FROMYUV(Y,U,V); //b
		*output_pt++ = B_FROMYU(Y,U); //v
			
		*output_pt++ = R_FROMYV(Y1,V);
		*output_pt++ = G_FROMYUV(Y1,U,V); //b
		*output_pt++ = B_FROMYU(Y1,U); //v
	}
	
	return 2;
} 
