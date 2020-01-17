// HW3_Functions.h

#include "header.h"

/* This function finds a branch from a given node that starts with a given char
 * Inputs: 	u = the node to search for the branch
 *			c = the character that the branch starts at
 * Return index of the branch in u's children
 * If the branch does not exist, return -1
 */
int find_branch(aNode *u, char c)
{
	int i = 0;

  vector<aNode*>::iterator it;

	for (it = (u->child).begin(); it < (u->child).end(); it++)
	{
		if (theData[(*it)->edgeLabel[0]] == c)
		{
			return i;
		}
		i++;
	}

	return -1;
}

  // DFS_PrepareST function

void DFS_PrepareST (aNode * T, int A[], int *nextIndex)
{

    // if NULL, return

  if (T == NULL)
  {
    return;

  } // end return if NULL

    // if leaf:

  if (T->child.size() == 0)
  {
    A[*nextIndex] = T->nodeID;

    if (T->stringDepth >= xi)
    {
      T->start_index = *nextIndex;
      T->end_index = *nextIndex;

      *nextIndex++;

      return;

    } // end if >= xi

  } // end if leaf node

  else
  {
    for (int i = 0; i < T->child.size(); i++)
    {
      DFS_PrepareST (T->child[i], A, nextIndex);
    } // end iterate through all children

  } // end else, internal node

  if (T->stringDepth >= xi)
  {
    aNode * u_left = T->child[0];
    aNode * u_right = T->child[T->child.size() - 1];

    T->start_index = u_left->start_index;
    T->end_index = u_right->end_index;

  } // end if T->stringDepth >= xi

} // end DFS_PrepareST function

// PrepareST function
// prepare the suffix tree:

int PrepareST (aNode * u, int count, int ifFirst)
{
  int i = 0;
  int nextIndex = 0;

  int A[theData.size() + 1];

  for (i = 0; i < theData.size() + 1; i++)
  {
    A[i] = -1;
  } // end initialize A

  DFS_PrepareST (u, A, &nextIndex);

} // end PrepareST function

void miniFindPath (aNode * T, string ri, int *read_ptr, aNode * u, int * r)
{
	int e = find_branch (T, ri[0]);
	int cur_edgelabel[2];

	if (e != 0)
	{
		int i = 0;

		cur_edgelabel[0] = T->child[e]->edgeLabel[0];
    cur_edgelabel[1] = T->child[e]->edgeLabel[1];

		while ((ri[*read_ptr] == theData[cur_edgelabel[0] + i]) && (i < cur_edgelabel[1] ) )

		{
			*read_ptr++;
			i++;

		} // end while

		if (i == cur_edgelabel[1] )
		{
			miniFindPath (T->child[e], ri, read_ptr, u, r);

		} // end if i == cur_edgelabel.length ()
		else
		{
			u = T->child[e];
			*r = i;

		} // end else

	} // end if e != 0

} // end miniFindPath

vector <int> * FindLoc (aNode * T, string ri, aNode * u, int xi, vector <int> * A, vector <int> * Li)
{

	int read_ptr = 0, r = 0, longestSoFar = 0;
	int start_i = 0;
	int end_i = 0;

	node * deepestNode;


	while (read_ptr < ri.length() )
	{
		miniFindPath (T, ri, &read_ptr, u, &r);

		if (r == 0)
		{
			// do nothing
		} // end if r == 0
		else if (r > 0)
		{
			read_ptr -= r;

		} // end else if r > 0

		if ((u->stringDepth >= xi) && (u->stringDepth > longestSoFar) )
		{
			deepestNode = u;
		} // end if depth >= xi and > longestSoFar

			// step 4, if suffix links work:

		T = u->SL;

		/*
			// step 4, if using Naive:

		int alphaPrime = u->depth - 1;

		while (u->parent->id != "")
		{
			u = u->parent;
		} // end move to root

		T = u;

		read_ptr -= alphaPrime;

		*/

	} // end while

	start_i = deepestNode->start_index;
	end_i = deepestNode->end_index;

	for (int i = start_i; i < end_i + 1; i++)
	{
		Li->push_back ((*A)[i]);

	} // end add all possible leaf nodes to Li

} // end FindLoc function
/////
