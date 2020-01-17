// findPath function:

int findPath (aNode * u, string s)
{
  int index = 0;
  int i = 0, j = 0, k = 0;

    // check if s is empty:

  if (s.length() == 0)
  {
    return -1;
  } // end if s is empty, return -1

  i = u->child.size();

  // look for a child that begins with our character:
  for (j = 0; j < i; j++)
  {
    if (u->child[j]->edgeLabel[k] == s[k])
    {
      //cout << "match" << endl;
      // find the index of the last matching character:

      while (u->child[j]->edgeLabel[k] == s[k])
      {
        k++;

      } // end keep moving forward while we have matches

      return k - 1;

    } // end if we find a match

  } // end look for a child that begins with character

  //cout << "no match" << endl;

  return -1;
} // end findPath function

==

// caseLong function
// the special case insert

void caseLong (string s)
{

  //cout << "\t\t*** caseLong function called ***" << endl;

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

        // get length of matching child edgeLabel:

      int l = u->child[j]->edgeLabel.length ();

      //while (u->child[j]->edgeLabel[k] == s[k])
      for (k = 0; k < l; k++)
      {
        if (u->child[j]->edgeLabel[k] != s[k])
        {
          break;
        } // end only iterate while we have matches

        //k++;
      } // end follow path

        // if we get to the next node,
        // shorten our string by the edgeLabel
        // we just traversed,
        // and call special caseLong:

      if (l == k)
      {
        u = u->child[j];
        caseLong (s.erase (0,l));
        return;
      } // end if we made it to the next node

      /*
      while (u->child[j]->edgeLabel[k] == s[k])
      {
        k++;
      } // end follow path
      */

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

  return;

} // end caseLong function


// if we found a path, follow it
// as far as we can:
// if the edge label is shorter than
// the string we are evaluating,
// and we match all the way up to
// an internal node, we need to
// be able to continue our search
// beyond the internal node:

// get length of matching child edgeLabel:

int l = u->child[j]->edgeLabel.length ();

//while (u->child[j]->edgeLabel[k] == s[k])
for (k = 0; k < l; k++)
{
if (u->child[j]->edgeLabel[k] != s[k])
{
  break;
} // end only iterate while we have matches

//k++;
} // end follow path

// if we get to the next node,
// shorten our string by the edgeLabel
// we just traversed,
// and call special caseINH:

if (l == k)
{
caseLong (s.erase (0,l));
return;
} // end if we made it to the next node


// but, if l is not equal to k,
// we broke out of the for loop
// so we are at an insertion point:
