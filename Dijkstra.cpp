#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct Edge{
  char nodeTo;
  int dist;
  int visited;
    //Overwrite < operator for PriorityQueue's Comparison
  bool operator< (const Edge& temp) const 
    { return dist > temp.dist; }
};



void PrintNodeList(char node, map<char, priority_queue<Edge> > NodeList);
void InsertEdge(char nF, char nT, int d, int v,
                map<char, priority_queue<Edge> > &NodeList);



int main(int argc, char** argv){
if(argc > 4 | argc < 2){
  cout << "\n!!!!!!!!!!!!!!!!!!! Input Error !!!!!!!!!!!!!!!!!!!\n"
       << "::         Input should be as followed...        ::\n"
       << "::                                               ::\n"
       << "::         \"run <filename> <startnode>\"          ::\n"
       << "::                      or                       ::\n"
       << ":: \"run <filename> <startnode> <distancelimit>\"  ::\n"
       << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
  return -1;
  }

else{
  char* File = argv[1];
  ifstream infile;
  infile.open(File);
  if(infile.is_open()){

      //Ignore the first line.
    infile.ignore(256, '\n');

    string GraphType;
    char nodeFrom, nodeTo;
    int Distance;
    priority_queue<Edge>EdgeQueue;
    map<char, priority_queue<Edge> > NodeList;
    infile >> GraphType;

      //Directed Graph Implementation
    if(GraphType == "D"){
      while(infile >> nodeFrom >> nodeTo >> Distance){
        InsertEdge(nodeFrom, nodeTo, Distance, 0, NodeList );
        }


  PrintNodeList ('A', NodeList);
  PrintNodeList ('B', NodeList);
  PrintNodeList ('C', NodeList);
  PrintNodeList ('E', NodeList);




      } //End if (Directed Graph Implementation)

//!!!!!!!!!!!!!!!!!!!!!!!!
//IMPLEMENT THIS LATORRRRR
//!!!!!!!!!!!!!!!!!!!!!!!!
      //UnDirected Graph Implementation
    else if(GraphType == "UD"){
/*      while(infile >> Node1 >> Node2 >> Weight){
        cout << "Node1: " << Node1 
             << "\nNode2: " << Node2
             << "\nWeight: " << Weight
             << "\n~~~~~~~~~~~~~~~~~\n\n";
        }
*/      } //End if (UnDirected Graph Implementation)

    else //Bad GraphType
      cout << "\n!!!!!!!!! Error in File !!!!!!!!!\n"
           << ":: GraphType must be either... ::\n"
           << "::        D for Directed       ::\n"
           << "::      UD for UnDirected      ::"
           << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";

    } //End if (File open)
  else{
    cout << "\n!!!!!!!!!!!!ERROR!!!!!!!!!!!!\n"
         << "::    File did not open.   ::\n"
         << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    return -1;
    } //End else (File did not open)
  } //End else (Correct argc)
} //End int main




//HELPER FUNCTIONS

void PrintNodeList(char node, map<char, priority_queue<Edge> > NodeList){
  while (!NodeList[node].empty()){
    cout << "\n~~~~~~~~~~~~~~~~~~\nNode " << node 
         << " has: " << NodeList[node].top().nodeTo
         << "\nDist: " << NodeList[node].top().dist << "\n";
    NodeList[node].pop();
    }
}

void InsertEdge(char nF, char nT, int d, int v,
                map<char, priority_queue<Edge> > &NodeList){
  Edge edge;
  edge.nodeTo = nT;
  edge.dist = d;
  edge.visited = v;
  NodeList[nF].push(edge);
}
