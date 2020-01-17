//////////////////////////////////////////////////////
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
#include "HW1_Functions.h"


int main (int argc, char * argv[])
{
  string fileName;
  string dataName;
  //string theData;
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
