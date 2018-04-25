#include <stdint.h> 
#include <stdio.h> 
#include <stdlib.h> 

struct SumArgs {
  int *array;
  int begin;
  int end;
};

int Sum(const struct SumArgs *args) {
  int sum = 0;
  // TODO: your code here 
  int begin = args->begin;
  int end = args->end;
  for (int i = begin; i < end; i++)
  {
      sum += args->array[i];
  }
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}