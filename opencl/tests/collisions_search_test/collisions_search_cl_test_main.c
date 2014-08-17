#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "collisions_search_cl_test.h"

int main(int argc, char *argv[])
{
  int num_bodies;
  int num_threads_tree_kernel;
  int num_threads_tree_gravity_kernel;
  int num_threads_tree_sort_kernel;
  int num_threads_force_gravity_kernel;
  int num_threads_collisions_search_kernel;
  int num_threads_collisions_resolve_kernel;

  if (argc != 8){
    num_bodies = 32768;
    num_threads_tree_gravity_kernel = 128;
    num_threads_tree_kernel = 128;
    num_threads_tree_sort_kernel = 128;
    num_threads_force_gravity_kernel = 128;
    num_threads_collisions_search_kernel = 128;
    num_threads_collisions_resolve_kernel = 128;
  }

  else{
    num_bodies = atoi(argv[1]);
    num_threads_tree_kernel = atoi(argv[2]);
    num_threads_tree_gravity_kernel = atoi(argv[3]);
    num_threads_tree_sort_kernel = atoi(argv[4]);
    num_threads_force_gravity_kernel = atoi(argv[5]);
    num_threads_collisions_search_kernel = atoi(argv[6]);
    num_threads_collisions_resolve_kernel = atoi(argv[7]);
  }

  collisions_search_cl_test(num_bodies, num_threads_tree_kernel, num_threads_tree_gravity_kernel,num_threads_tree_sort_kernel, num_threads_force_gravity_kernel, num_threads_collisions_search_kernel, num_threads_collisions_resolve_kernel);
  return 0;
}