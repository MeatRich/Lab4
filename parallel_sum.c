#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <getopt.h>

#include "utils.h"
#include "sum.h"

int main(int argc, char **argv) {
    
  uint32_t threads_num = 0;
  uint32_t array_size = 0;
  uint32_t seed = 0;
  
   while (true) {
                int current_optind = optind ? optind : 1;

                static struct option options[] = {
                    { "seed", required_argument, 0, 0 },
                    { "array_size", required_argument, 0, 0 },
                    { "tnum", required_argument, 0, 0 },
                    { 0, 0, 0, 0 } };

                int option_index = 0;
                int c = getopt_long(argc, argv, "f", options, &option_index);

                if (c == -1) break;

                switch (c) {
                case 0:
                        switch (option_index) {
                        case 0:
                                seed = atoi(optarg);
                                printf("seed = %d\n", seed);
                                break;
                        case 1:
                                array_size = atoi(optarg);
                                printf("array_size = %d\n", array_size);
                                break;
                        case 2:
                                threads_num = atoi(optarg);
                                printf("number of threads = %d\n", threads_num);
                                break;

                        defalut:
                                printf("Index %d is out of options\n", option_index);
                        }
                        break;

                default:
                        printf("getopt returned character code 0%o?\n", c);
                }
        }
  
  pthread_t threads[threads_num];

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  
  struct SumArgs args[threads_num];
  int interval = array_size / threads_num;
  for(int i = 0; i < threads_num; i++)
  {
      args[i].begin = interval * i;
      args[i].end = i == threads_num - 1 ? array_size : interval * (i + 1);
      args[i].array = array;
  }

  struct timeval start_time;
  gettimeofday(&start_time, NULL);
  
  for (uint32_t i = 0; i < threads_num; i++) {
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;
  
  free(array);
  printf("Total: %d\n", total_sum);
  printf("Elapsed time: %fms\n", elapsed_time);
  
  return 0;
}
