//
// Created by mwypych on 02.02.17.
//
#include "Factorial.h"

int Factorial(int value) {
  if (value>=13 || value<=-13)
    return 0;
  if (value==0)
    return 1;
  if (value>=0)
    return Factorial(value - 1)*value;
  return Factorial(value + 1)*value;
}
