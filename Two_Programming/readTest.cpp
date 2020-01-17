#include <iostream>
#include <fstream>

using namespace std;

// global variable

string theData;

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


void printData ()
{
  int i = 0;

  while (theData[i] != '$')
  {
    cout << ":" << theData[i++] << ":" << endl;
  } // end print one character at a time

} // end printData function


int main (int argc, char * argv[])
{
  string fileName;
  string dataName;
  int stringSize;

    // If no input file was provided,
    // prompt user for one:

  if (argc == 1)
  {
    // prompt user for input file:
    cout << "Enter an input file name: " << endl;
    cin >> fileName;
    cout << "> " << fileName << endl;

  } // end if no argument provided, ask for a file name

  else
  {
    fileName = argv[1];

  } // end if there is an argument, assume it is the input file name

    // read the data from the file:

  readFile (fileName, &dataName, &theData);

    // append terminating symbol to string:

  theData += '$';
  stringSize = theData.length ();
  cout << "stringSize: " << stringSize << endl;

  printData ();

} // end main function
