/*
 * utils.h
 *
 *  Created on: Jan 4, 2021
 *      Author: mint
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

int8_t constrain_i8(int8_t x, int8_t min, int8_t max);
int16_t constrain_i16(int16_t x, int16_t min, int16_t max);

int16_t map_i16(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max);

#endif /* INC_UTILS_H_ */
