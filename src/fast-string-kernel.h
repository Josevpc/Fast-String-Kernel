#include "suffix_tree.h"

#define MAX(x, y) \
      ({ __typeof__ (x) _x = (x); \
      __typeof__ (y) _y = (y); \
      _x > _y ? _x : _y; })

#define MIN(x, y) \
      ({ __typeof__ (x) _x = (x); \
      __typeof__ (y) _y = (y); \
      _x < _y ? _x : _y; })

double FAST_STRING_KERNEL(char *x, char *y, char *weight, float aux);