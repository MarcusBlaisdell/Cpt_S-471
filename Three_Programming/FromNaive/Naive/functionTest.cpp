#include "functionTestB.h"

int main ()
{
  int a = 1;
  int b = 3;
  int c;

  c = testFunctionOne (a, b);

  cout << "c: " << c << endl;

  c = testFunctionTwo (c, b);

  cout << "c: " << c << endl;

}
