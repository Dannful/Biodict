#ifndef BIODICT_CALCULATIONS_H
#define BIODICT_CALCULATIONS_H

/**
 * Returns min if value is lower than min
 * or max if value is higher than max
 * @param value the value to be coerced
 * @param min the minimum value
 * @param max the max value
 * @return the coerced value
 */
float coerce_in(float value, float min, float max);

/**
 * Returns the lowest value out of
 * two integers
 * @param a the first integer
 * @param b the second integer
 * @return the lowest value
 */
float min(float a, float b);

/**
 * Returns the highest value out of
 * two integers
 * @param a the first integer
 * @param b the second integer
 * @return the highest value
 */
float max(float a, float b);

#endif
