#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct node{
  char id;
  int dist;
  int visited;
    //Overwrite < operator for PriorityQueue's Comparison
  bool operator< (const node& temp) const 
    { return visited > temp.visited; }
};

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
    char n1, n2;
    int w;
    priority_queue<int, std::vector<int>,  std::greater<int> >Queue;
    priority_queue<node>NodeQueue;
    vector<char> Nodes1, Nodes2;
    vector<int> Weights;
    infile >> GraphType;

//!!!!!!!!!!!!!!!!!!!!!!!!
//IMPLEMENT THIS MEOWW~!!!
//!!!!!!!!!!!!!!!!!!!!!!!!
      //Directed Graph Implementation
    if(GraphType == "D"){
      while(infile >> n1 >> n2 >> w){
          //Parallel Vectors (Node1, Node2, Weight)
        Nodes1.push_back(n1);
        Nodes2.push_back(n2);
        Weights.push_back(w);


	

/*        cout << "Node1: " << Node1 
             << "\nNode2: " << Node2
             << "\nWeight: " << Weight
             << "\n~~~~~~~~~~~~~~~~~\n\n";*/
        Queue.push(w);
//NodeQueue.push(//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
//NodeQueue.push(//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
//NodeQueue.push(//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
//NodeQueue.push(//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
        }
      while (!Queue.empty()){
          cout << "\n~~~~~~~~~~~~~~~~~~\nQueue has: "
               << Queue.top();
          Queue.pop();
        }







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
