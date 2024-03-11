#include "maths_tools.h"

namespace utils {
int factorial(int n) {
  if (n == 0)
	return 1;
  int factorial = 1;
  for (int i = 2; i <= n; i++)
	factorial = factorial * i;
  return factorial;
}

int nCr(int n, int r) {
  return factorial(n) / (factorial(r) * factorial(n - r));
}
}