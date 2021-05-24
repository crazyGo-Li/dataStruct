#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bit.h"

int bit_get(const unsigned char *bits, int pos)
{
    unsigned char mask;
    int i;

    mask = 0x80;

    for(i = 0; i < (pos % 8); i++)
        mask = mask >> 1;

    return (((mask & bits[(int)(pos / 8)]) == mask) ? 1 : 0);
}

void bit_set(unsigned char *bits, int pos, int state)
{
    unsigned char mask;
    int i;
    mask = 0x80;
    for(i = 0; i < (pos % 8); i ++)
        mask = mask >> 1;

    if(state)
    {
        /* 置1的时候，目标位或1，其他或0，保持不变 */
        bits[pos / 8] = bits[pos / 8] | mask;
    }
    else
    {
        /* 置0的时候，目标位与0，其他与1，保持不变 */
        bits[pos / 8] = bits[pos / 8] & (-mask);
    }
    return;
}

/* 将bits1和bist2中的size数据做异或操作 */
void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(bit_get(bits1, i) != bit_get(bits2, i))
        {
            bit_set(bitsx, i, 1);
        }
        else
        {
            bit_set(bitsx, i, 0);
        }
    }
    return;
}

/* 整个数据向左轮转count位 */
void bit_rot_left(unsigned char *bits, int size, int count)
{
    int fbit,
        lbit,
        i,
        j;

    if(size > 0)
    {
        for(j = 0; j < count; j++)
        {
            for(i = 0; i <= ((size - 1) / 8); i++)
            {
                /* 先拿到最左侧的一位因为会被轮转丢失了 */
                lbit = bit_get(&bits[i], 0);
                if(i == 0)
                {
                    fbit = lbit;
                }
                else
                {
                    bit_set(&bits[i - 1], 7, lbit);
                }
                bits[i] = bits[i] << 1;
            }
            bit_set(bits, size - 1, fbit);
        }
    }
    return;
}
