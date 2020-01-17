bool findPath (aNode * u, int i, int len)
{
  #ifdef DEBUG1
  cout << "\t*** findPath called ***" << endl;
  cout << "v->nodeID: " << v->nodeID;
  cout << " - i: " << i << " - len: " << len << endl;
  #endif

  int j = 0, k = 0, l = 0, childNum = 0;;
  int found = 0;
  bool pathFound;
  int m = i + len;

    // only run if there is a character to evaluate:
  if (theString[i])
  {
    if (curPtr->child.size() == 0)
    {
      return false;

    } // end if no children, return false
    else
    {
      l = curPtr->child.size ();

      for (k = 0; k < l; k++)
      {
        if (theString[curPtr->child[k]->edgeLabel[0]] == theString[i])
        {
          found = 1;
          cout << "found = 1 - child: " << k << endl;
          childNum = k;
          break;
        } // end if we found a path

        k++;
      } // end look for child

      // if we iterated though the children and
      // did not find one that begins with our character,
      // return false:

      if (found == 0)
      {
        cout << "found == 0" << endl;
        return false;
      } // return false if no path found
      else
      {
        while (i <= m && theString[curPtr->child[childNum]->edgeLabel[0] + j])
        {
          #ifdef DEBUG1
          cout << "theString[" << i << "]: " << theString[i];
          cout << "  -  theString[u->child[childNum]->edgeLabel[0] + " << j;
          cout << "]]: " << theString[curPtr->child[childNum]->edgeLabel[0] + j] << endl;
          #endif

          if (theString[i] == theString[curPtr->child[childNum]->edgeLabel[0] + j])
          {

            i++;
            j++;
          } // end continue evaluating while matches
          else
          {
            #ifdef DEBUG1
            cout << "\t************* mismatch *****************" << endl;
            cout << "theString[" << i << "]: " << theString[i];
            cout << "  -  theString[curPtr->child[childNum]->edgeLabel[0] + " << j;
            cout << "]]: " << theString[curPtr->child[childNum]->edgeLabel[0] + j] << endl;
            #endif
            return false;
          } // end return false if mismatch

        } // end while to evaluate the string

      } // end else, evaluate the child

    } // end look for path in child list

    u = curPtr->child[k];

    pathFound = findPath (u, i, len - j);

  } // end if there is a character to evaluate

  return pathFound;

} // end findPath function

==
