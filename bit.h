#ifndef __BIT_H__
#define __BIT_H__

int bit_get(const unsigned char *bits, int pos);
void bit_set(unsigned char *bits, int pos, int state);
void bit_xor(const unsigned char *bits1, const unsigned char *bits2, const unsigned char *bitsx, int size);
void bit_rot_lefg(unsigned char *bits, int size, int count);

#endif
