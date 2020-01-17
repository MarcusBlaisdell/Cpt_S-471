#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

typedef struct node
{
  int label[2];
  int j;
  vector <struct node *> children;

} aNode;

string theString = "This is a string";

void testFunction (aNode * theNode)
{
  vector <aNode *>::iterator it = theNode->children.begin();

  while (it != theNode->children.end () )
  {
  
    if (it->j == 33)
    {
      cout << "found it" << endl;
    }
    else
    {
      cout << "not it" << endl;
    }

    it++;
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

  // populate the vector:
} // end main
