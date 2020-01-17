#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

//#define DEBUG
#define NAIVE

typedef struct node
{
  int label[2];
  int j;
  vector <struct node *> children;

} aNode;

string theString = "This is a string";

void testFunction (aNode * theNode)
{
  int i = 0;
  vector <aNode *>::iterator it = theNode->children.begin();

  while (it != theNode->children.end () )
  {

    if (theNode->children[i]->j == 33)
    //if (it->j == 33)
    {
      cout << "found it" << endl;
    }
    else
    {
      cout << "not it" << endl;
    }

    it++;
    i++;
  }

} // end testFunction function

int main ()
{
  // create a vector of pointers

  aNode * node_1 = new aNode;
  aNode * node_2 = new aNode;
  aNode * node_3 = new aNode;

  node_1->label[0] = 11;
  node_1->label[1] = 12;
  node_1->j = 13;

  node_2->label[0] = 21;
  node_2->label[1] = 22;
  node_2->j = 23;

  node_3->label[0] = 31;
  node_3->label[1] = 32;
  node_3->j = 33;


  node_1->children.push_back (node_2);
  node_1->children.push_back (node_2);

  testFunction (node_1);

  #ifdef NAIVE
  cout << "naive is set" << endl;
  #ifdef DEBUG
  cout << "debug is set" << endl;
  #endif
  #else
  cout << "naive is not set" << endl;
  #endif

  string myString = "mississippi$";

  cout << "This should print \"issi\"" << endl;
  int i = 1;
  while (i != 5)
  {
    cout << myString[i++];
  } // end print specific characters
  cout << endl;

  i = 0;
  while (myString[i])
  {
    cout << myString[i++];
  } // end print specific characters
  cout << endl;
  cout << "i = " << i << endl;
  cout << "myString[i]:" << myString[i] << ":" << endl;

  cout << "myString.length(): " << myString.length() << endl;
  cout << "myString.size(): " << myString.size() << endl;

  // populate the vector:
} // end main
