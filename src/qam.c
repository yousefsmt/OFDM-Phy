#include "qam.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

int map_bits_to_complex(const uint8_t* bits, complex_t* symbols)
{
    if (symbols && bits)
    {
        uint8_t msb_four_bit = 0;
        uint8_t lsb_four_bit = 0;

        for (size_t i = 0; i < SYMBOL_RATE*SECONDS/2; i++)
        {
            for (size_t k = 0; k < BITS_PER_SYM / 2; k++)
            {
                switch (k)
                {
                    case 0:
                        msb_four_bit = MSB_4(bits[i]) >> 2u;
                        msb_four_bit ^= msb_four_bit >> 1;
                        lsb_four_bit = MSB_4(bits[i]) & 3u;
                        lsb_four_bit ^= lsb_four_bit >> 1;
                        symbols[i << 1].i =  NORM_SYMBOL(amp_16qam[msb_four_bit]);
                        symbols[i << 1].q = -NORM_SYMBOL(amp_16qam[lsb_four_bit]);
                        break; 
                    case 1:
                        msb_four_bit = LSB_4(bits[i]) >> 2u;
                        msb_four_bit ^= msb_four_bit >> 1;
                        lsb_four_bit = LSB_4(bits[i]) & 3u;
                        lsb_four_bit ^= lsb_four_bit >> 1;
                        symbols[(i << 1) + 1].i =  NORM_SYMBOL(amp_16qam[msb_four_bit]);
                        symbols[(i << 1) + 1].q = -NORM_SYMBOL(amp_16qam[lsb_four_bit]);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        fprintf(stderr, "cannot malloc complex array\n");
        return -1;
    }

    return 0;
}