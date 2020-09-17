#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#define CLIP(color) (unsigned char)(((color)>0xFF)?0xff:(((color)<0)?0:(color)))
static int *LutYr = NULL;
static int *LutYg = NULL;;
static int *LutYb = NULL;;
static int *LutVr = NULL;;
static int *LutVrY = NULL;;
static int *LutUb = NULL;;
static int *LutUbY = NULL;;
static int *LutRv = NULL;
static int *LutGu = NULL;
static int *LutGv = NULL;
static int *LutBu = NULL;

#if 0
#define RGB24_TO_Y(r,g,b) LutYr[(r)] + LutYg[(g)] + LutYb[(b)]
#define YR_TO_V(r,y) LutVr[(r)] + LutVrY[(y)]
#define YB_TO_U(b,y) LutUb[(b)] + LutUbY[(y)]

#define R_FROMYV(y,v)  CLIP((y) + LutRv[(v)])
#define G_FROMYUV(y,u,v) CLIP((y) + LutGu[(u)] + LutGv[(v)])
#define B_FROMYU(y,u) CLIP((y) + LutBu[(u)])
#endif

unsigned char
RGB24_TO_Y(unsigned char r, unsigned char g, unsigned char b)
{
return (LutYr[(r)] + LutYg[(g)] + LutYb[(b)]);
}
unsigned char
YR_TO_V(unsigned char r, unsigned char y)
{
return (LutVr[(r)] + LutVrY[(y)]);
}
unsigned char
YB_TO_U(unsigned char b, unsigned char y)
{
return (LutUb[(b)] + LutUbY[(y)]);
}
unsigned char
R_FROMYV(unsigned char y, unsigned char v)
{
return CLIP((y) + LutRv[(v)]);
}
unsigned char
G_FROMYUV(unsigned char y, unsigned char u, unsigned char v)
{
return CLIP((y) + LutGu[(u)] + LutGv[(v)]);
}
unsigned char
B_FROMYU(unsigned char y, unsigned char u)
{
return CLIP((y) + LutBu[(u)]);
}

unsigned int
Pyuv422torgb241(unsigned char * input_ptr, unsigned char * output_ptr, unsigned int image_width, unsigned int image_height);
 
