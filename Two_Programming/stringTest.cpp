// stringTest

#include <string.h>
#include <iostream>
#include <list>
#include <vector>
#include <time.h>
#include <chrono>
#include <typeinfo>

using namespace std;
using namespace chrono;

typedef struct testStruct
{
  int ID;
  string Label;
  vector <struct testStruct *> Stuff;

} TestStruct;

void printString (string *dataName)
{
  cout << "dataName in function: " << *dataName << endl;
  dataName->append (" This");
}

int main (int argc, char * argv[])
{
  //auto begin = chrono::high_resolution_clock::now();
  auto startTime = steady_clock::now();

  //time_t startTime, endTime;
  //time (&startTime);
  string dataName = "test";
  string testOne = "testOne";
  string alpha = "abcde";
  string beta = alpha;
  string gamma = alpha;
  string delta = "abcfg";
  string epsilon = "abcde";
  string iota = "abcde$";
  int i = 0, j = 0, k = 0;

  cout << alpha.erase (2,1) << endl;
  cout << beta << endl;
  cout << "testOne: " << testOne << endl;
  gamma.erase(2, (gamma.length () - 2));
  cout << "gamma: " << gamma << endl;
  i = 0;
  while (epsilon[i] == delta[i])
  {
    i++;
  }
  string zeta  = delta;
  delta.erase (i, (delta.length () ) );
  //zeta.erase (0, (zeta.length () - (i - 1) ) );
  zeta.erase (0, i );
  cout << "epsilon: " << epsilon << endl;
  cout << "delta: " << delta << endl;
  cout << "zeta: " << zeta << endl;
  if (zeta == "fg")
  {
    cout << "valid" << endl;
  }
  else
  {
    cout << "invalid: " << endl;
  }
  // remove first character from a string
  testOne.erase (0,2);
  cout << "testOne.erase (0,2): " << testOne << endl;
  string testThree = testOne;
  testThree.pop_back ();
  cout << "testOne.pop_back: " << testThree << endl;

  //TestStruct myTest1, myTest2, myTest3;
  /*
  TestStruct * myTest1 = (TestStruct * ) malloc (sizeof (TestStruct) );
  TestStruct * myTest2 = (TestStruct * ) malloc (sizeof (TestStruct) );
  TestStruct * myTest3 = (TestStruct * ) malloc (sizeof (TestStruct) );
  */
  TestStruct * myTest1 = new TestStruct;
  TestStruct * myTest2 = new TestStruct;
  TestStruct * myTest3 = new TestStruct;

  myTest1->ID = 0;
  myTest1->Label = "Zero";

  myTest2->ID = 1;
  myTest2->Label = "One";

  myTest3->ID = 2;
  myTest3->Label = "Two";

  myTest1->Stuff.push_back (myTest2);
  myTest1->Stuff.push_back (myTest3);
  cout << "myTest1->Stuff[0]->ID: " << myTest1->Stuff[0]->ID << endl;
  cout << "myTest1->Stuff[1]->ID: " << myTest1->Stuff[1]->ID << endl;

  /*
  for (vector <TestStruct *>::iterator it = myTest1->Stuff.begin (); it != myTest1->Stuff.end (); it++)
  {
    cout << "here" << endl;
    cout << "ID: " << (*it)->ID << endl;
    cout << "Label: " << (*it)->Label << endl;
  }
  */

  //printString (&dataName);

  //cout << "dataName out of function: " << dataName << endl;

  vector <string> testInsert;
  string val1 = "first";
  string val2 = "second";
  string val3 = "third";

  testInsert.push_back (val1);
  testInsert.push_back (val3);

  for (vector <string>::iterator it = testInsert.begin(); it != testInsert.end(); it++)
  {
    cout << "it[0][0]: " << it[0][0] << endl;
  }

  for (vector <string>::iterator it = testInsert.begin(); it != testInsert.end(); it++)
  {
    //cout << "it[0][0]: " << it[0][0] << endl;
    //cout << "val2[0]: " << val2[0] << endl;
    if (it[0][0] > val2[0])
    {
      testInsert.insert (it, val2);
      cout << "it[0][0] here" << endl;
      break;
    }

  }


  for (vector <string>::iterator it = testInsert.begin(); it != testInsert.end(); it++)
  {
    cout << "testInsert: (*it): " << (*it) << endl;
  }

  for (vector <TestStruct *>::iterator it = myTest1->Stuff.begin(); it != myTest1->Stuff.end(); it++)
  {
    cout << "myTest1: (*it)->ID: " << (*it)->ID << endl;
  }

  //time (&endTime);


  for (i = 0; i < 32; i++)
  {
    //for (j = 0; j< 32000; j++)
    //{
      //k++;
    //}
  }

  auto endTime = steady_clock::now();
  cout << "time: " << duration_cast<microseconds>(endTime - startTime).count() << " us" << endl;


  //auto end = chrono::high_resolution_clock::now();
  //auto dur = end - begin;
  //auto ms = std::chrono::duration_cast<chrono::milliseconds> (dur).count();
  //cout << "ms: " << ms << endl;

  string printFlag = "-p";

  if ((argc > 1) && (argv[1] == printFlag))
  {
    cout << "printFlag read" << endl;
  }

  i = 0;

  while (iota[i] != '$')
  {
    cout << "not $: " << iota[i] << endl;
    i++;
  }
  cout << "$?: " << iota[i] << endl;

  string substrTest = "String";

  cout << "substrTest: " << substrTest << endl;
  substrTest = substrTest.substr(2);
  cout << "substrTest: " << substrTest << endl;

}
