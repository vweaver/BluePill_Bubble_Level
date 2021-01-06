/*
 * utils.c
 *
 *  Created on: Jan 4, 2021
 *      Author: mint
 */

#include "main.h"

/**
  * @brief Constrain an int8_t value such that min <= x <= max
  * @param x: Value to constrain
  * @retval int8_t
  */
int8_t constrain_i8(int8_t x, int8_t min, int8_t max)
{
    if(x < min) {
        return min;
    }
    else if(max < x) {
        return max;
    }
    else
        return x;
}

/**
  * @brief Constrain an int16_t value such that min <= x <= max
  * @param x: Value to constrain
  * @retval int16_t
  */
int16_t constrain_i16(int16_t x, int16_t min, int16_t max)
{
    if(x < min) {
        return min;
    }
    else if(max < x) {
        return max;
    }
    else
        return x;
}

/**
  * @brief Map an int16_t value from the in range to the out range
  * @param x: Value to map
  * @param in_min: min value in
  * @param in_max: max value in
  * @param out_min: min value out
  * @param out_max: max value out
  * @note  Values are not bounded by the in or out range.
  * @retval int16_t
  */
int16_t map_i16(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
