#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

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
    char Node1, Node2;
    int Weight;
    priority_queue<int, std::vector<int>,  std::greater<int> >Queue;
    infile >> GraphType;

//!!!!!!!!!!!!!!!!!!!!!!!!
//IMPLEMENT THIS MEOWW~!!!
//!!!!!!!!!!!!!!!!!!!!!!!!
      //Directed Graph Implementation
    if(GraphType == "D"){
      while(infile >> Node1 >> Node2 >> Weight){
/*        cout << "Node1: " << Node1 
             << "\nNode2: " << Node2
             << "\nWeight: " << Weight
             << "\n~~~~~~~~~~~~~~~~~\n\n";*/
        Queue.push(Weight);
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
      while(infile >> Node1 >> Node2 >> Weight){
        cout << "Node1: " << Node1 
             << "\nNode2: " << Node2
             << "\nWeight: " << Weight
             << "\n~~~~~~~~~~~~~~~~~\n\n";
        }
      } //End if (UnDirected Graph Implementation)

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
