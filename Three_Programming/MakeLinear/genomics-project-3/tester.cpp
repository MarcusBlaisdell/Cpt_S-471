#include <iostream>
#include <string>
#include <vector>

using namespace std;

void myFunction (string *s, int i, int * r)
{
  s->push_back('$');

  cout << "*s: " << *s << endl;
  cout << "(*s)[0]: " << (*s)[0] << endl;

  cout << "i: " << i << "   *r: " << *r << endl;
  *r += 2;
  cout << "i: " << i << "   *r: " << *r << endl;

} // end myFunction

void mySecond (vector <int> * A)
{
  cout << "(*A)[0]: " << (*A)[0] << endl;

} // end function mySecond

void testArray (int A[])
{
  A[2] = 3;
  A[5] = 7;

} // end testArray

int main ()
{
  int i = 0, r = 1;
  vector <int> A;

  string myString = "my_string";

  myFunction (&myString, i, &r);

  for (int j = 5; j < 7; j++)
  {
    cout << "j: " << j << endl;
    A.push_back(j);

  } // end test for loop

  mySecond (&A);

  int B[8];

  for (i = 0; i < 8; i++)
  {
    cout << "i: " << i << endl;
    B[i] = -1;
  }

  for (i = 0; i < 8; i++)
  {
    cout << "B[i]: " << B[i] << endl;

  }

  testArray (B);

  for (i = 0; i < 8; i++)
  {
    cout << "B[i]: " << B[i] << endl;

  }

}
