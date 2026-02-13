#ifndef PHY_SOURCE_OFDM_H_
#define PHY_SOURCE_OFDM_H_

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

#include <stdio.h>

typedef struct
{
    int  number_of_subcarriers;
    char *output_signal;
}ofdm_config;

#endif // !PHY_SOURCE_OFDM_H_