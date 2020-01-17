/////////////////////////////////////////////////////
//
// Marcus Blaisdell
// CptS 471
// Programming Assignment 2
// March 30, 2019
// Professor Kalyanaraman
//
//////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <chrono>
#include "header.h"

using namespace chrono;

// readString function

void readFile (string fileName, string *dataName, string *theString)
{
  string line;
  int i = 1;
  //cout << "readFile called" << endl;

  ifstream inputFile (fileName);

    // first line should be information, but verify it

  getline (inputFile, line);

  if (line[0] == '>')
  {
    while (line[i] != ' ' && line[i])
    {
      *dataName += (line[i]);

      i++;

    } // end while loop to get data name

    //getline (inputFile, line);

    while (getline (inputFile, line))
    {
      theString->append (line);

    } // end read the data in

  } // end if data line

} // end function readString


  // findPath function:

void findPath ()
{

} // end findPath function




// caseINH function
// the NodeHop-insert function

void caseINH (string s)
{

  //cout << "\t\t*** caseINH function called ***" << endl;

  // get the number of children:

  int i = u->child.size ();

  for (int j = 0; j < i; j++)
  {
    // the suffix link lets us skip
    // characters to evaluate:

    int k = u->edgeLabel.length ();

    if (u->child[j]->edgeLabel[k] == s[k])
    {
        // if we found a path, follow it
        // as far as we can:
        // get length of matching child edgeLabel:

      while (u->child[j]->edgeLabel[k] == s[k])
      {
        k++;
      } // end follow path

      // we are now at the location where we need to
      // insert our new node:
      // first, create new internal node,
      // textLabel = u->child[j]->textLabel.erase (k, (length - k))
      // and a new leaf node
      // textLabel = u->textLabel.erase (0, k)
      //
      // insert-in-order, the new leaf node
      // and existing node (u->child[j])
      // as children of new internal node
      //
      // update existing node parent to
      // new internal node,
      // update existing node textLabel to textLabel.erase (0, k)
      // update existing pointer to u->child to
      // new internal node: u->child[j] = new Internal node
      //
      // set u = new leaf node


      aNode * newInternalNode = new aNode;

      newInternalNode->nodeID = internalID++;
      //struct node * SL;
      newInternalNode->parent = u;
      newInternalNode->edgeLabel = s;
      newInternalNode->edgeLabel.erase(k, (newInternalNode->edgeLabel.length () - k) );
      //vector <struct node * > child;
      newInternalNode->stringDepth = newInternalNode->edgeLabel.length () + u->stringDepth;

      aNode * newLeafNode = new aNode;

      newLeafNode->nodeID = leafID++;
      newLeafNode->parent = newInternalNode;
      newLeafNode->edgeLabel = s;
      newLeafNode->edgeLabel.erase (0, k);
      newLeafNode->stringDepth = newLeafNode->edgeLabel.length () + newInternalNode->stringDepth;

        // update existing node:
      u->child[j]->parent = newInternalNode;
      u->child[j]->edgeLabel.erase (0, k);

      // insert new leaf node and existing node
      // as children of new internal node
      // insert in order:

      if (newLeafNode->edgeLabel == "$" || (newLeafNode->edgeLabel[0] < u->child[j]->edgeLabel[0]) )
      {
        newInternalNode->child.push_back (newLeafNode);
        newInternalNode->child.push_back (u->child[j]);
      } // end if newLeaf is lexicographically lower than existing node
      else
      {
        newInternalNode->child.push_back (u->child[j]);
        newInternalNode->child.push_back (newLeafNode);
      } // end, else existing node is lexicographically lower than leaf

        // now, update existing child pointer to
        // point to the new internal node:

      u->child[j] = newInternalNode;

      u = newLeafNode;

      return;

    } // end if there is a path

  } // end check all children
  //cout << "checked all children, no match" << endl;

  // if we get here, there is no path,
  // create a new leaf node and insert
  // lexicographically

  aNode * newLeafNode = new aNode;

  newLeafNode->nodeID = leafID++;
  newLeafNode->parent = u;
  newLeafNode->edgeLabel = s;
  newLeafNode->stringDepth = s.length () + u->stringDepth;

  //cout << "new leaf node created" << endl;

  vector <aNode *>::iterator it = u->child.begin ();
  int l = 0;

  if (s == "$" || (s[0] < u->child[l]->edgeLabel[0]) )
  {
    u->child.insert (it, newLeafNode);

  } // end insert at beginning
  else
  {
    // iterate to correct position:
    it++;
    l++;
    while ( it != u->child.end ())
    {
      if (u->child[l]->edgeLabel[0] >= s[0])
      {
        u->child.insert (it, newLeafNode);
        break;

      } // end insert before,

      it++;
      l++;

    } // end while
    //cout << "no larger string found, must insert at end" << endl;
    // if we get here, we reached the end of the
    // list without find an insert spot,
    // so we need to insert at the end
    // of the list:

    u->child.push_back (newLeafNode);

  } // end else, insert in order

  u = newLeafNode;


} // end caseINH function

  // NodeHops function:

void NodeHops (string beta, aNode * u_prime, string s, aNode * uPtr)
{
    // take SL(u') to v':

  u = u_prime->SL;

    // take correct path out of v':

  int i = u->child.size ();

  for (int j = 0; j < i; j++)
  {
    if (u->child[j]->edgeLabel[0] == beta[0])
    {
        // once we find the right path, check it's length,
        // if it is greater than beta, then v doesn't exist,
        // we will use findPath and add V
        //
        // if it is less than beta, we don't know if it
        // exists or not but we can safely hop to the child
        // and re-evaluate once we get there
        //
        // if child edgeLabel is equal to beta, then
        // v exists and we can safely hop to the child

      if (beta.length () >= u->child[j]->edgeLabel.length () )
      {
        u = u->child[j];
        break;
      } // end if edgeLabel less than, equal to beta size (v exists)
      else
      {
        caseINH (s);
        return;

      } // end edgeLabel greater than beta size (v doesn't exist)

    } // end find correct child

  } // end iterate through all children

  beta.erase (0, (u->edgeLabel.length () ) );

  if (beta.length () > 0)
  {
    NodeHops (beta, u, s, uPtr);

  } // end recurse until v is found
  else
  {
    // we are now at v:

    // update u suffix link:
    // do not update if it will
    // point to a child

    if (u->parent != uPtr)
    {
      uPtr->SL = u;
    } // end only update not child


    // and insert suffix s:
    u = uPtr;
    caseINH (s);

  } // end found v

} // end NodeHops function

  // caseIA function

void caseIA (string s)
{
  // SL(u) is known,
  // u is the root:

  //cout << "\t\t*** caseIA function called ***" << endl;

  // go to v
  // I am using u as the current position,
  // so in this case, u is v:

  u = u->SL;


  // get the number of children:

  int i = u->child.size ();

  for (int j = 0; j < i; j++)
  {
    // the suffix link lets us skip
    // characters to evaluate:

    int k = u->edgeLabel.length ();

    if (u->child[j]->edgeLabel[k] == s[k])
    {
        // if we found a path, follow it
        // as far as we can:

      while (u->child[j]->edgeLabel[k] == s[k])
      {
        k++;
      } // end follow path

      // we are now at the location where we need to
      // insert our new node:
      // first, create new internal node,
      // textLabel = u->child[j]->textLabel.erase (k, (length - k))
      // and a new leaf node
      // textLabel = u->textLabel.erase (0, k)
      //
      // insert-in-order, the new leaf node
      // and existing node (u->child[j])
      // as children of new internal node
      //
      // update existing node parent to
      // new internal node,
      // update existing node textLabel to textLabel.erase (0, k)
      // update existing pointer to u->child to
      // new internal node: u->child[j] = new Internal node
      //
      // set u = new leaf node


      aNode * newInternalNode = new aNode;

      newInternalNode->nodeID = internalID++;
      //struct node * SL;
      newInternalNode->parent = u;
      newInternalNode->edgeLabel = s;
      newInternalNode->edgeLabel.erase(k, (newInternalNode->edgeLabel.length () - k) );
      //vector <struct node * > child;
      newInternalNode->stringDepth = newInternalNode->edgeLabel.length () + u->stringDepth;

      aNode * newLeafNode = new aNode;

      newLeafNode->nodeID = leafID++;
      newLeafNode->parent = newInternalNode;
      newLeafNode->edgeLabel = s;
      newLeafNode->edgeLabel.erase (0, k);
      newLeafNode->stringDepth = newLeafNode->edgeLabel.length () + newInternalNode->stringDepth;

        // update existing node:
      u->child[j]->parent = newInternalNode;
      u->child[j]->edgeLabel.erase (0, k);

      // insert new leaf node and existing node
      // as children of new internal node
      // insert in order:

      if (newLeafNode->edgeLabel == "$" || (newLeafNode->edgeLabel[0] < u->child[j]->edgeLabel[0]) )
      {
        newInternalNode->child.push_back (newLeafNode);
        newInternalNode->child.push_back (u->child[j]);
      } // end if newLeaf is lexicographically lower than existing node
      else
      {
        newInternalNode->child.push_back (u->child[j]);
        newInternalNode->child.push_back (newLeafNode);
      } // end, else existing node is lexicographically lower than leaf

        // now, update existing child pointer to
        // point to the new internal node:

      u->child[j] = newInternalNode;

      u = newLeafNode;

      return;

    } // end if there is a path

  } // end check all children
  //cout << "checked all children, no match" << endl;

  // if we get here, there is no path,
  // create a new leaf node and insert
  // lexicographically

  aNode * newLeafNode = new aNode;

  newLeafNode->nodeID = leafID++;
  newLeafNode->parent = u;
  newLeafNode->edgeLabel = s;
  newLeafNode->stringDepth = s.length () + u->stringDepth;

  //cout << "new leaf node created" << endl;

  vector <aNode *>::iterator it = u->child.begin ();
  int l = 0;

  if (s == "$" || (s[0] < u->child[l]->edgeLabel[0]) )
  {
    u->child.insert (it, newLeafNode);

  } // end insert at beginning
  else
  {
    // iterate to correct position:
    it++;
    l++;
    while ( it != u->child.end ())
    {
      if (u->child[l]->edgeLabel[0] >= s[0])
      {
        u->child.insert (it, newLeafNode);
        break;

      } // end insert before,

      it++;
      l++;

    } // end while
    //cout << "no larger string found, must insert at end" << endl;
    // if we get here, we reached the end of the
    // list without find an insert spot,
    // so we need to insert at the end
    // of the list:

    u->child.push_back (newLeafNode);

  } // end else, insert in order

  u = newLeafNode;



} // end caseIA function

  // caseIB function

void caseIB (string s)
{
  // SL(u) is known,
  // u is the root:

  //cout << "\t\t*** caseIB function called ***" << endl;

  // 1) check if we have a child
  // that begins with the same
  // character as the suffix
  // we are adding:

  // get the number of children:

  int i = u->child.size ();

  for (int j = 0; j < i; j++)
  {
    int k = 0;

    if (u->child[j]->edgeLabel[k] == s[k])
    {
        // if we found a path, follow it
        // as far as we can:

      while (u->child[j]->edgeLabel[k] == s[k])
      {
        k++;
      } // end follow path

      // we are now at the location where we need to
      // insert our new node:
      // first, create new internal node,
      // textLabel = u->child[j]->textLabel.erase (k, (length - k))
      // and a new leaf node
      // textLabel = u->textLabel.erase (0, k)
      //
      // insert-in-order, the new leaf node
      // and existing node (u->child[j])
      // as children of new internal node
      //
      // update existing node parent to
      // new internal node,
      // update existing node textLabel to textLabel.erase (0, k)
      // update existing pointer to u->child to
      // new internal node: u->child[j] = new Internal node
      //
      // set u = new leaf node


      aNode * newInternalNode = new aNode;

      newInternalNode->nodeID = internalID++;
      //struct node * SL;
      newInternalNode->parent = u;
      newInternalNode->edgeLabel = s;
      newInternalNode->edgeLabel.erase(k, (newInternalNode->edgeLabel.length () - k) );
      //vector <struct node * > child;
      newInternalNode->stringDepth = newInternalNode->edgeLabel.length () + u->stringDepth;

      aNode * newLeafNode = new aNode;

      newLeafNode->nodeID = leafID++;
      newLeafNode->parent = newInternalNode;
      newLeafNode->edgeLabel = s;
      newLeafNode->edgeLabel.erase (0, k);
      newLeafNode->stringDepth = newLeafNode->edgeLabel.length () + newInternalNode->stringDepth;

        // update existing node:
      u->child[j]->parent = newInternalNode;
      u->child[j]->edgeLabel.erase (0, k);

      // insert new leaf node and existing node
      // as children of new internal node
      // insert in order:

      if (newLeafNode->edgeLabel == "$" || (newLeafNode->edgeLabel[0] < u->child[j]->edgeLabel[0]) )
      {
        newInternalNode->child.push_back (newLeafNode);
        newInternalNode->child.push_back (u->child[j]);
      } // end if newLeaf is lexicographically lower than existing node
      else
      {
        newInternalNode->child.push_back (u->child[j]);
        newInternalNode->child.push_back (newLeafNode);
      } // end, else existing node is lexicographically lower than leaf

        // now, update existing child pointer to
        // point to the new internal node:

      u->child[j] = newInternalNode;

      u = newLeafNode;

      return;

    } // end if there is a path

  } // end check all children
  //cout << "checked all children, no match" << endl;

  // if we get here, there is no path,
  // create a new leaf node and insert
  // lexicographically

  aNode * newLeafNode = new aNode;

  newLeafNode->nodeID = leafID++;
  newLeafNode->parent = u;
  newLeafNode->edgeLabel = s;
  newLeafNode->stringDepth = s.length () + u->stringDepth;

  //cout << "new leaf node created" << endl;

  vector <aNode *>::iterator it = u->child.begin ();
  int l = 0;

  if (s == "$" || (s[0] < u->child[l]->edgeLabel[0]) )
  {
    u->child.insert (it, newLeafNode);
  } // end insert at beginning
  else
  {
    // iterate to correct position:
    it++;
    l++;
    while ( it != u->child.end ())
    {
      if (u->child[l]->edgeLabel[0] >= s[0])
      {
        u->child.insert (it, newLeafNode);
        break;
      } // end insert before,

      it++;
      l++;

    } // end while
    //cout << "no larger string found, must insert at end" << endl;
    // if we get here, we reached the end of the
    // list without find an insert spot,
    // so we need to insert at the end
    // of the list:

    u->child.push_back (newLeafNode);

  } // end else, insert in order

  u = newLeafNode;

  //cout << "end of caseIB" << endl;
} // end caseIB function

  // caseIIA function

void caseIIA (string s)
{
  // SL(u) is not known,
  // u' is the not the root:

  //cout << "\t\t*** caseIIA function called ***" << endl;

  // Store pointer to u
  // so we can use it
  // to update the suffix link

  aNode * uPtr = u;

  // move to u': u->parent:
  // which should have a suffix link

  u = u->parent;

  if (u->SL != NULL)
  {
    // go to v
    // I am using u as the current position,
    // so in this case, u is v:

    u = u->SL;


    // get the number of children:

    int i = u->child.size ();

    for (int j = 0; j < i; j++)
    {
      // the suffix link lets us skip
      // characters to evaluate:

      int k = u->edgeLabel.length ();

      if (u->child[j]->edgeLabel[k] == s[k])
      {
          // if we found a path, follow it
          // as far as we can:

        while (u->child[j]->edgeLabel[k] == s[k])
        {
          k++;
        } // end follow path

        // we are now at the location where we need to
        // insert our new node:
        // first, create new internal node,
        // textLabel = u->child[j]->textLabel.erase (k, (length - k))
        // and a new leaf node
        // textLabel = u->textLabel.erase (0, k)
        //
        // insert-in-order, the new leaf node
        // and existing node (u->child[j])
        // as children of new internal node
        //
        // update existing node parent to
        // new internal node,
        // update existing node textLabel to textLabel.erase (0, k)
        // update existing pointer to u->child to
        // new internal node: u->child[j] = new Internal node
        //
        // set u = new leaf node


        aNode * newInternalNode = new aNode;

        newInternalNode->nodeID = internalID++;
        //struct node * SL;
        newInternalNode->parent = u;
        newInternalNode->edgeLabel = s;
        newInternalNode->edgeLabel.erase(k, (newInternalNode->edgeLabel.length () - k) );
        //vector <struct node * > child;
        newInternalNode->stringDepth = newInternalNode->edgeLabel.length () + u->stringDepth;

        aNode * newLeafNode = new aNode;

        newLeafNode->nodeID = leafID++;
        newLeafNode->parent = newInternalNode;
        newLeafNode->edgeLabel = s;
        newLeafNode->edgeLabel.erase (0, k);
        newLeafNode->stringDepth = newLeafNode->edgeLabel.length () + newInternalNode->stringDepth;

          // update existing node:
        u->child[j]->parent = newInternalNode;
        u->child[j]->edgeLabel.erase (0, k);

        // insert new leaf node and existing node
        // as children of new internal node
        // insert in order:

        if (newLeafNode->edgeLabel == "$" || (newLeafNode->edgeLabel[0] < u->child[j]->edgeLabel[0]) )
        {
          newInternalNode->child.push_back (newLeafNode);
          newInternalNode->child.push_back (u->child[j]);
        } // end if newLeaf is lexicographically lower than existing node
        else
        {
          newInternalNode->child.push_back (u->child[j]);
          newInternalNode->child.push_back (newLeafNode);
        } // end, else existing node is lexicographically lower than leaf

          // now, update existing child pointer to
          // point to the new internal node:

        u->child[j] = newInternalNode;
        // update suffix link:
        // do not update if link
        // is a child of uPtr:
        if (newInternalNode->parent != uPtr)
        {
          uPtr->SL = newInternalNode;
        } // end update if not child


        u = newLeafNode;

        return;

      } // end if there is a path

    } // end check all children
    //cout << "checked all children, no match" << endl;

    // if we get here, there is no path,
    // create a new leaf node and insert
    // lexicographically

    aNode * newLeafNode = new aNode;

    newLeafNode->nodeID = leafID++;
    newLeafNode->parent = u;
    newLeafNode->edgeLabel = s;
    newLeafNode->stringDepth = s.length () + u->stringDepth;

    //cout << "new leaf node created" << endl;

    vector <aNode *>::iterator it = u->child.begin ();
    int l = 0;

    if (s == "$" || (s[0] < u->child[l]->edgeLabel[0]) )
    {
      u->child.insert (it, newLeafNode);
      if (u->parent != uPtr)
      {
        uPtr->SL = u;
      } // end only update if not child

    } // end insert at beginning
    else
    {
      // iterate to correct position:
      it++;
      l++;
      while ( it != u->child.end ())
      {
        if (u->child[l]->edgeLabel[0] >= s[0])
        {
          u->child.insert (it, newLeafNode);
          if (u->parent != uPtr)
          {
            uPtr->SL = u;
          }

          break;
        } // end insert before,

        it++;
        l++;

      } // end while
      //cout << "no larger string found, must insert at end" << endl;
      // if we get here, we reached the end of the
      // list without find an insert spot,
      // so we need to insert at the end
      // of the list:

      u->child.push_back (newLeafNode);
      if (u->parent != uPtr)
      {
        uPtr->SL = u;
      } // end only update if not child


    } // end else, insert in order

    u = newLeafNode;


  } // end if suffix link is known

} // end caseIIA function

  // caseIIB function

void caseIIB (string s)
{
  // SL(u) is not known,
  // u' is the root:

  //cout << "\t\t*** caseIIB function called ***" << endl;

  // Store pointer to u
  // so we can use it
  // to update the suffix link

  aNode * uPtr = u;

  // move to u': u->parent:
  // which should have a suffix link

  u = u->parent;


  // get the number of children:

  int i = u->child.size ();

  for (int j = 0; j < i; j++)
  {
    int k = 0;

    if (u->child[j]->edgeLabel[k] == s[k])
    {


      // we are now at the location where we need to
      // insert our new node:
      // first, create new internal node,
      // textLabel = u->child[j]->textLabel.erase (k, (length - k))
      // and a new leaf node
      // textLabel = u->textLabel.erase (0, k)
      //
      // insert-in-order, the new leaf node
      // and existing node (u->child[j])
      // as children of new internal node
      //
      // update existing node parent to
      // new internal node,
      // update existing node textLabel to textLabel.erase (0, k)
      // update existing pointer to u->child to
      // new internal node: u->child[j] = new Internal node
      //
      // set u = new leaf node


      aNode * newInternalNode = new aNode;

      newInternalNode->nodeID = internalID++;
      //struct node * SL;
      newInternalNode->parent = u;
      newInternalNode->edgeLabel = s;
      newInternalNode->edgeLabel.erase(k, (newInternalNode->edgeLabel.length () - k) );
      //vector <struct node * > child;
      newInternalNode->stringDepth = newInternalNode->edgeLabel.length () + u->stringDepth;

      aNode * newLeafNode = new aNode;

      newLeafNode->nodeID = leafID++;
      newLeafNode->parent = newInternalNode;
      newLeafNode->edgeLabel = s;
      newLeafNode->edgeLabel.erase (0, k);
      newLeafNode->stringDepth = newLeafNode->edgeLabel.length () + newInternalNode->stringDepth;

        // update existing node:
      u->child[j]->parent = newInternalNode;
      u->child[j]->edgeLabel.erase (0, k);

      // insert new leaf node and existing node
      // as children of new internal node
      // insert in order:

      if (newLeafNode->edgeLabel == "$" || (newLeafNode->edgeLabel[0] < u->child[j]->edgeLabel[0]) )
      {
        newInternalNode->child.push_back (newLeafNode);
        newInternalNode->child.push_back (u->child[j]);
      } // end if newLeaf is lexicographically lower than existing node
      else
      {
        newInternalNode->child.push_back (u->child[j]);
        newInternalNode->child.push_back (newLeafNode);
      } // end, else existing node is lexicographically lower than leaf

        // now, update existing child pointer to
        // point to the new internal node:

      u->child[j] = newInternalNode;
      if (newInternalNode->parent != uPtr)
      {
        uPtr->SL = newInternalNode;
      } // end only update if not child


      u = newLeafNode;

      return;

    } // end if there is a path

  } // end check all children
  //cout << "checked all children, no match" << endl;

  // if we get here, there is no path,
  // create a new leaf node and insert
  // lexicographically

  aNode * newLeafNode = new aNode;

  newLeafNode->nodeID = leafID++;
  newLeafNode->parent = u;
  newLeafNode->edgeLabel = s;
  newLeafNode->stringDepth = s.length () + u->stringDepth;

  //cout << "new leaf node created" << endl;

  vector <aNode *>::iterator it = u->child.begin ();
  int l = 0;

  if (s == "$" || (s[0] < u->child[l]->edgeLabel[0]) )
  {
    u->child.insert (it, newLeafNode);
    if (u->parent != uPtr)
    {
      uPtr->SL = u;
    } // end only update if not child

  } // end insert at beginning
  else
  {
    // iterate to correct position:
    it++;
    l++;
    while ( it != u->child.end ())
    {
      if (u->child[l]->edgeLabel[0] >= s[0])
      {
        u->child.insert (it, newLeafNode);
        if (u->parent != uPtr)
        {
          uPtr->SL = u;
        } // end only update if not parent

        break;
      } // end insert before,

      it++;
      l++;

    } // end while
    //cout << "no larger string found, must insert at end" << endl;
    // if we get here, we reached the end of the
    // list without find an insert spot,
    // so we need to insert at the end
    // of the list:

    u->child.push_back (newLeafNode);
    if (u->parent != uPtr)
    {
      uPtr->SL = u;
    } // end only update if not child


  } // end else, insert in order

  u = newLeafNode;


} // end caseIIB function

int printDFS (aNode *, int, int);
int printPOT (aNode *, int);

  // insertNode function

void insertNode (string * theData)
{

    // 1) go to u:

  u = u->parent;

    // remove first character from our string:

  string tempString;
  tempString = *theData;
  tempString.erase (0, 1);
  *theData = tempString;

  // uncomment to print a random node
  /*
  if (tempString.length () == 776)
  {
    printDFS (u, 0, 0);
  }
  */

  //cout << "tempString: " << tempString << endl;

    // check if string is now empty,
    // if string is empty, we have completed
    // the suffix tree

  if (theData->length () == 0)
  {
    cout << "string is empty" << endl;
    return;
  } // end if we have completed the tree

  // If the string is not yet empty,
  // continue adding suffixes:
  // determine which of the four cases
  // we have and add the new suffix appropriately:

  else
  {
    if (u->SL == NULL)
    {
      if (u->parent->edgeLabel == "")
      {
          // Case IIB
        caseIIB (*theData);

      } // end is Case IIB
      else
      {
          // Case IIA
        caseIIA (*theData);

      } // end is Case IIA

    } // end if Case II

      // else, SL is not null, it is known:

    else
    {
      if (u->edgeLabel == "")
      {
          // Case IB
        caseIB (*theData);

      } // end is Case IB
      else
      {
          // Case IA
        caseIA (*theData);
      } // end is Case IA

    } // end if Case I

  } // end we have more suffix'es to add


} // end insertNode function


// build a suffix tree:

aNode * buildSFTree (string *theData)
{
    // create a timer:
    auto startTime = steady_clock::now ();

    // get the length of string:
    // lowercase n will be the size of the string,
    // uppercase N will be the number of nodes,
    // N = internal nodes + leaf nodes

  int n = theData->length();

    // To follow with the numbering convention
    // specified in lecture,
    // We will number leaf nodes up from 1:
    // to track internal nodes as distinguishable
    // from leaf nodes by nodeID,
    // We will number internal nodes up from n + 1:

  leafID = 1;
  internalID = n + 1;

    // create the root node:

  aNode * root = new aNode;

    // root node is a special case that has it's
    // suffix-link point to itself:

  root->SL = root;

    // set root's variables:

    // int nodeID;
    // struct node * SL;
    // struct node * parent;
    // string edgeLabel;
    // vector <struct node * > child;
    // int stringDepth;

  root->nodeID = internalID++;
  // root->SL is already NULL,
  root->parent = root;
  root->edgeLabel = "";
  // root->child starts out empty
  root->stringDepth = 0;

    // create the initial leaf node:

  aNode * newNode = new aNode;

  newNode->nodeID = leafID++;
  // newNode->SL is NULL
  newNode->parent = root;
  newNode->edgeLabel = *theData;
  // newNode child list is empty
  newNode->stringDepth = theData->length();

  root->child.push_back (newNode);

  u = newNode;

    // now, create the remainder of the tree
    // using a while loop that removes the
    // first character from the string on
    // each iteration until the string is
    // empty:

  while (theData->length() > 0)
  {
    insertNode (theData);

  } // end insert until our string is empty

  auto endTime = steady_clock::now();
  cout << "Time to build Suffix Tree: ";
  cout << duration_cast<microseconds>(endTime - startTime).count () << " us\n" << endl;

  return root;

} // end buildSFTree function

  // printDFS function
  // print the tree using
  // depth-first-search

int printDFS (aNode * u, int count, int ifFirst)
{
  int i = 0, j = 0;

    // handle root node:
    // ifFirst flag is used to only do this the
    // very first time the function is called,
    // and to not repeat it on the recursive calls

  if (u->edgeLabel == "" && ifFirst == 0)
  {
    //cout << u->nodeID << " : " << u->stringDepth << endl;
    cout << u->nodeID << " : " << u->stringDepth << " * ";
    count++;
  } // end if we are at root, print that


  i = u->child.size ();

    // if no children, just print the edge label

  if (i == 0)
  {
    // Do nothing

  } // end just print edge label
  else
  {
    for (j = 0; j < i; j++)
    {
      //cout << u->child[j]->nodeID << " : " << u->child[j]->edgeLabel << endl;
      //cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << endl;
      cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << " * ";
      count++;
      //cout << "count: " << count << endl;
        // only print 10 elements per line
        // if we just printed the 10th element,
        // print newline, reset count to 0

      if (count == 10)
      {
        cout << endl;
        count = 0;
      } // end only print 10 elements per line

      if (u->child[j]->child.size () > 0)
      {
        count = printDFS (u->child[j], count, 1);

      } // end if node has children, recursively print them

    } // end print out all children

  } // end else, print all children

  return count;

} // end printDFS

// printPOT function
// print the tree using
// post-order traversal

int printPOT (aNode * u, int count)
{
  int i = u->child.size();
  int j = 0;

    // if there are children,
    // iterate though them one at a time,
    // start with left-most,
    // end with right-most

  if (i > 0)
  {
    for (j = 0; j < i; j++)
    {
      if (u->child[j]->child.size () > 0)
      {
        count = printPOT (u->child[j], count);

      } // end if there are more children, iterate through them
      else
      {
        cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << " * ";
        count++;

          // if the count reaches 10,
          // print newline, reset count

        if (count == 10)
        {
          cout << endl;
          count = 0;

        } // end if count reaches 10, reset it

      } // end print leaf

    } // end iterate through all children

      // after printing children, print root node:

    cout << u->nodeID << " : " << u->stringDepth << " * ";
    count++;
      // if the count reaches 10,
      // print newline, reset count

    if (count == 10)
    {
      cout << endl;
      count = 0;

    } // end if count reaches 10, reset it

  } // end if there are children, iterate through them
  else
  {
    cout << u->nodeID << " : " << u->stringDepth << " * ";
    count++;
      // if the count reaches 10,
      // print newline, reset count

    if (count == 10)
    {
      cout << endl;
      count = 0;

    } // end if count reaches 10, reset it

  } // end if no children, we are at a leaf node

  return count;

} // end printPOT


// printBWT function
// print only the
// leaf nodes of the tree

void printBWT (aNode * u, string * s)
{
  int i = 0, j = 0, k = 0;

  i = u->child.size ();

    // if no children, it is a leaf node,
    // print the index and the corresponding
    // character in the original string

  if (i == 0)
  {
    // do nothing

  } // end just print edge label
  else
  {
    for (j = 0; j < i; j++)
    {
      //cout << u->child[j]->nodeID << " : " << u->child[j]->edgeLabel << endl;
      //cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << endl;
      if (u->child[j]->child.size() == 0)
      {
        k = (u->child[j]->nodeID) - 2;
        if (k < 0)
        {
          cout << (*s)[s->length () - 1] << endl;
        }
        else
        {
          cout << (*s)[k] << endl;
        }


      }

      if (u->child[j]->child.size () > 0)
      {
        printBWT (u->child[j], s);

      } // end if node has children, recursively print them

    } // end print out all children

} // end else, print all children

} // end printBWT


// getStats function
// iterate through the tree
// and gather statistical data

// forward declaration:
void getStatsHelper (aNode *, int);

void getStats (aNode * u)
{
  getStatsHelper (u, 0);

  cout << "\n\nStatistics:\n" << endl;
  cout << "numInternalNodes: " << numInternalNodes << endl;
  cout << "numLeaves: " << numLeaves << endl;
  totalNodes += numInternalNodes + numLeaves;
  cout << "totalNodes: " << totalNodes << endl;
  cout << "tree size: " << sizeof (u) * totalNodes << endl;
  cout << "average string-depth of internal nodes: " << depthSum / float (numInternalNodes) << endl;
  cout << "string-depth of deepest internal node: " << deepest << endl;
  cout << "\n" << endl;

} // end getStats function

  // getStatsHelper function

void getStatsHelper (aNode * u, int ifFirst)
{
  int i = 0, j = 0;
  int theDepth;

    // handle root node:
    // ifFirst flag is used to only do this the
    // very first time the function is called,
    // and to not repeat it on the recursive calls

  if (u->edgeLabel == "" && ifFirst == 0)
  {
    numInternalNodes++;

  } // end if we are at root, print that


  i = u->child.size ();

    // if no children, just print the edge label

  if (i == 0)
  {
    // Do nothing

  } // end just print edge label
  else
  {
    for (j = 0; j < i; j++)
    {
      if (u->child[j]->nodeID < stringSize + 1)
      {
        numLeaves++;
      } // end it is a leaf
      else
      {
        theDepth = u->child[j]->stringDepth;
        depthSum += theDepth;
        numInternalNodes++;

        if (theDepth > deepest)
        {
          deepest = theDepth;

        } // end update deepest
      } // end else it is internal

      if (u->child[j]->child.size () > 0)
      {
        getStatsHelper (u->child[j], 1);

      } // end if node has children, recursively print them

    } // end print out all children

  } // end else, print all children

} // end getStatsHelper

int main (int argc, char * argv[])
{
  string fileName;
  string dataName;
  string theData;
  string dataCopy;
  string theAlphabet;
  aNode * root;

    // If no input file was provided,
    // prompt user for one:

  if (argc == 1)
  {
    // prompt user for input file:
    cout << "Enter an input file name: " << endl;
    cin >> fileName;
    cout << "> " << fileName << endl;

  } // end if no argument provided, ask for a file name

  else if (argc == 2)
  {
    // prompt user for input file:
    cout << "Enter an alphabet file name: " << endl;
    cin >> theAlphabet;
    cout << "> " << theAlphabet << endl;

  } // end if no alphabet provided, prompt for one

  else
  {
    fileName = argv[1];
    theAlphabet = argv[2];

  } // end if there is an argument, assume it is the input file name

    // read the data from the file:

  readFile (fileName, &dataName, &theData);

    // append terminating symbol to string:

  theData += '$';
  dataCopy = theData;
  stringSize = theData.length ();

    // create the tree and
    // return a pointer to the root node:

  root = buildSFTree (&theData);

  // only print the tree if a flag is set:
  // -DFS will print the DFS tree,
  // -BWT will print the BWT tree

  if (argc == 4)
  {

    if (strcmp(argv[3], "-DFS") == 0)
    {
      int count = printDFS (root, 0, 0);
      cout << endl;

    } // end printDFS if flagged

    else if (strcmp(argv[3], "-BWT") == 0)
    {
      printBWT (root, &dataCopy);
    } // end printBWT if flagged

    else if (strcmp(argv[3], "-POT") == 0)
    {
      int count = printPOT (root, 0);

    } // end printPOT if flagged

  } // end if 4 args

  getStats (root);


} // end main function
