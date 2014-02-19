#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

int FindHopLocation(const vector<int>, vector<int>::iterator&, int);
bool Finished(int, int, string&);


int main(int argc, char** argv)
{
    //Command Line Arg[1] = Filename. Assuming Correct user input.
  ifstream inFile;
  inFile.open(argv[1]);
  
  int v, location, hop, end;
  string output;
  stringstream ss;
  vector<int> masterList;

    //Read in v until EOF [Load masterList]
  while(inFile >> v)
  {
    masterList.push_back(v);
  }
  
    //Initialize Values
  location = 0;
  end = masterList.size();
  vector<int>::iterator iter = masterList.begin();

  
    //First box visited  
    ss.str("");
    ss << location;
    output.append(ss.str());
    output.append(", ");	

  //Traverse and Find Hops!
  while(!Finished(*iter, end, output))
  {
    hop = FindHopLocation(masterList, iter, end);
      //if it cannot finish End Program
	if (hop == 0)
	{
	  cout << "failure";
	  return 0;
	}
    location = hop + location;
    end = end - hop;

    ss.str("");
    ss << location;
    output.append(ss.str());
    output.append(", ");	

  }
  
  cout << output;
  return 0;
}




  //Finds next "hopping" spot
int FindHopLocation
  (const vector<int> mList, vector<int>::iterator& iter, int end)
{
    //end is size of subset
    //subLocation is next jumping spot
    //difference is end - (i+1) - value
  int subLocation, difference, range;
  vector<int>::iterator it = iter;
  subLocation = 0;
  range = *iter;  //times to loop
  difference = end; //largest possible number that a difference needs to be

    //Whatever has SMALLEST difference
  for (int i = 1; i <= range; i++)
  {
    it = ++it;
	
      //current subLocation has smaller difference
    if(difference > (end - i - *it))
    {
      difference = end - i - *it;
	  subLocation = i;
	  
	    //current subLocation's value can reach end
      if(difference <= 0)
      {
        iter = it;
        return subLocation;
      }

      iter = it;
    }
  } 

  return subLocation; //this is how many hops you will increment your location by
}


bool Finished(int hops, int end, string& output)
{
    //return true if end is reachable with hops, otherwise false
  if(end - hops > 0) return false;
  else
  {
    output.append("out"); 
    return true;
  }
}
