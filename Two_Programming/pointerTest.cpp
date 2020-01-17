// pointer test

#include <iostream>
#include <string.h>

using namespace std;

void printString (string * a)
{
  cout << ": " << (*a)[1] << endl;
}

int main ()
{
  string a = "test";

  cout << "a[0]: " << a[0] << endl;
  printString (&a);
}
