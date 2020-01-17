// general c code testing:

#include <iostream>

using namespace std;

int main ()
{
  int i = 0, j = 9;

  for (i = 0; i < 10; i++)
  {
    if (i == j)
    {
      break;
    } // end if

  } // end for

  cout << "i: " << i << endl;

}
