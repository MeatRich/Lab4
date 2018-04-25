#include "find_min_max.h"

#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;
  int size = sizeof(array)/sizeof(array[0]);
  //if (end > size) end = size;
  for (int i = begin; i < end; i++){
      min_max.min = min_max.min < array[i] ? min_max.min : array[i];
      min_max.max = min_max.max > array[i] ? min_max.max : array[i];
  }
  // your code here
  return min_max;
}