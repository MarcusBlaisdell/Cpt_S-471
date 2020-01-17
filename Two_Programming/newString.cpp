// stringTest

#include <string.h>
#include <iostream>

using namespace std;

#define DEBUG

void testIota (char * iota, int i)
{
  int j = 0;

  while (*iota != '$')
  {
    cout << j << " not $: " << *iota << endl;
    iota++;
    j++;
  }
  cout << "$?: " << *iota << endl;

  if (i == 0)
  {
    cout << "zero" << endl;
  }
  else
  {
    cout << "not zero" << endl;
  }

  cout << "but I should print regardless" << endl;

} // end testIota

void testNCopy (char *iota_a)
{
  int i = 0;
  char newString[20];
  char *iota_b;
  char tempChar_a, tempChar_b;

  iota_b = iota_a;

  //strcpy (newString, *iota);

  for (i = 0; i < 3; i++)
  {
    *iota_a++;
  }

  for (i = 0; i < 2; i++)
  {
    *iota_b++;
  }

  i = 0;

  while (*iota_a)
  {
    tempChar_a = *iota_a++;
    tempChar_b = *iota_b++;

    cout << "iota_a: " << tempChar_a;
    cout << " - iota_b: " << tempChar_b << endl;

    //newString[i++] = tempChar;

  }
  //newString[i] = '\0';

  //cout << "newString: " << newString << endl;

} // end testNCopy

int main ()
{

  #ifdef DEBUG
  cout << "Debugging is on" << endl;
  #endif
  int i = 0;

  string iota = "abcde$fg";

  testIota (&iota[0], 0);

  testIota (&iota[0], 1);

  testNCopy (&iota[0]);


}
