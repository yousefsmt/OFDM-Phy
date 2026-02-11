#ifndef PHY_SOURCE_QAM_H_
#define PHY_SOURCE_QAM_H_

/*
 * OFDM Physical Layer Simulation
 * Copyright (C) 2026 Yousef
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#define QAM_ORDER 16

#if QAM_ORDER == 16

/* 16-QAM square constellation amplitude levels for I/Q components*/
static const double amp_16qam[4UL] = {-3.00, -1.00, 1.00, 3.00};

/*Number of bits per symbol*/
#define BITS_PER_SYM 4

#elif QAM_ORDER == 64

/* 64-QAM square constellation amplitude levels for I/Q components*/
static const double amp_64qam[6UL] = {-5.00, -3.00, -1.00, 1.00, 3.00, 5.00};

/*Number of bits per symbol*/
#define BITS_PER_SYM 6

#elif QAM_ORDER == 256  

/* 256-QAM square constellation amplitude levels for I/Q components*/
static const double amp_256qam[8UL] = {-7.00, -5.00, -3.00, -1.00, 1.00, 3.00, 5.00, 7.00};

/*Number of bits per symbol*/
#define BITS_PER_SYM 8

#endif // ORDER

/*Calculate logarithm with base 2 from unsigned integer*/
#define LOG2_UINT(x) (uint8_t) log2((double) (x))

/*Calculate 4-bit most significant bit from 8-bit number*/
#define MSB_4(x) ((x) >> 4)

/*Calculate 4-bit least significant bit from 8-bit number*/
#define LSB_4(x) ((x) & 15U)

/*Calculate i-q coordinate from input*/
#define AMP_CALC(x, order) (((x) * 2) + 1 - (order))

/*Calculate gray code from binary*/
// #define GRAY_CODE(x) x ^ (x >> 1)

/*Modulation order*/
// #define M 16

/*Number of bits per symbol*/
// #define BITS_PER_SYM LOG2_UINT(M)

/*Number of symbol per second*/
#define SYMBOL_RATE 2000000

/*Number of seconds on transmission*/
#define SECONDS 1

/*Number of sample per second*/
// #define FS 100000

/*Carrier frequency*/
// #define CARRIER_FREQ 10000

/*Complex number*/
typedef struct
{
    float i;
    float q;
} complex_t;

/**
 * @brief Calculates QAM symbol from bit sequence
 *
 * Give uint8 bit sequence separate each 1 byte to 4 bit then
 * each 4 bit separate to 2 bit fot i-q signal
 * This description for 16-QAM modulation
 *
 * @param bits Input bit sequence each element contain two 4 bit number
 *
 *
 * @return The complex array number
 */
int map_bits_to_complex(const uint8_t* bits, complex_t* symbols);

#endif // !PHY_SOURCE_QAM_H_