#pragma once

#include <cstddef>

namespace bytetrack
{
    int lapjv_internal(const size_t n, double *cost[], int *x, int *y);
}