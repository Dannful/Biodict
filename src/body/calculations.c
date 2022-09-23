#include "functions/calculations.h"

float coerce_in(float value, float min, float max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

float min(float a, float b) {
    if (a > b)
        return a;
    return b;
}

float max(float a, float b) {
    if (a < b)
        return a;
    return b;
}
