#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;


struct Edge{
  char nodeFrom, nodeTo;
  int weight;
    //Overwrite < operator for PriorityQueue's Comparison
  bool operator< (const Edge& temp) const 
    { return weight > temp.weight; }
};

struct NodeInfo{
  char nodeName;
  int dist;
  int visited;
    //Overwrite < operator for PriorityQueue's Comparison
  bool operator< (const NodeInfo& temp) const 
    { return dist > temp.dist; }
};

void PrintAdjList(char node, map<char, priority_queue<Edge> > AdjList);
void InsertEdge(char nF, char nT, int w,
                map<char, priority_queue<Edge> > &AdjList);
void PrintDijkstra(map<char, NodeInfo> nL, char startNode);




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
//~~~~~~~~~~~~~~~~~~~~~~~~~    INT MAIN    ~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

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
  char startNode = *argv[2];
  ifstream infile;
  infile.open(File);
  if(infile.is_open()){

      //Ignore the first line.
    infile.ignore(256, '\n');

    string GraphType;
    char nodeFrom, nodeTo;
    int weight;
    priority_queue<NodeInfo>NodeQueue;
    map<char, priority_queue<Edge> > AdjList;
    map<char, NodeInfo> NodeInfoList;

    infile >> GraphType;

//=======================================================>
//------------Directed Graph Implementation-------------->
//=======================================================>
    if(GraphType == "D"){
      while(infile >> nodeFrom >> nodeTo >> weight){
        InsertEdge(nodeFrom, nodeTo, weight, AdjList);
        NodeInfoList[nodeFrom].nodeName = nodeFrom;
        NodeInfoList[nodeFrom].dist = 999999999;
        NodeInfoList[nodeFrom].visited = 0;
        NodeInfoList[nodeTo].nodeName = nodeTo;
        NodeInfoList[nodeTo].dist = 999999999;
        NodeInfoList[nodeTo].visited = 0;
        }

      NodeQueue.push(NodeInfoList[startNode]);
      NodeInfoList[startNode].dist = 0;      
      priority_queue<Edge> Adjacent;
      char node = startNode;
      while(!NodeQueue.empty()){
        node = NodeQueue.top().nodeName;
        NodeQueue.pop();

          //Set Visited
        NodeInfoList[node].visited = 1;

          //Set Distance of all non visited if new dist is smaller
        int temp;
          //get all edges in AdjList[node]
        Adjacent = AdjList[node];
        while(!Adjacent.empty()){
            //POP if visited
          if(NodeInfoList[Adjacent.top().nodeTo].visited == 1){
            Adjacent.pop();
            }
          else{
            NodeQueue.push(NodeInfoList[Adjacent.top().nodeTo]);
            temp = NodeInfoList[Adjacent.top().nodeFrom].dist 
                   + Adjacent.top().weight;
              //if Smaller Distance, Then update it.
            if(NodeInfoList[Adjacent.top().nodeTo].dist > temp){
              NodeInfoList[Adjacent.top().nodeTo].dist = temp;
              }
            Adjacent.pop();
            }//Endelse
          } //Endwhile Adjacent not empty
        } //Endwhile NodeQueue not empty

      PrintDijkstra(NodeInfoList, startNode);

      } //End if (Directed Graph Implementation)




//=======================================================>
//-------------UnDirected Graph Implementation----------->
//=======================================================>
    else if(GraphType == "UD"){
      while(infile >> nodeFrom >> nodeTo >> weight){
        InsertEdge(nodeFrom, nodeTo, weight, AdjList);
        InsertEdge(nodeTo, nodeFrom, weight, AdjList);
        NodeInfoList[nodeFrom].nodeName = nodeFrom;
        NodeInfoList[nodeFrom].dist = 999999999;
        NodeInfoList[nodeFrom].visited = 0;
        NodeInfoList[nodeTo].nodeName = nodeTo;
        NodeInfoList[nodeTo].dist = 999999999;
        NodeInfoList[nodeTo].visited = 0;
        }

      NodeQueue.push(NodeInfoList[startNode]);
      NodeInfoList[startNode].dist = 0;      
      priority_queue<Edge> Adjacent;
      char node = startNode;
      while(!NodeQueue.empty()){
        node = NodeQueue.top().nodeName;
        NodeQueue.pop();

          //Set Visited
        NodeInfoList[node].visited = 1;

          //Set Distance of all non visited if new dist is smaller
        int temp;
          //get all edges in AdjList[node]
        Adjacent = AdjList[node];
        while(!Adjacent.empty()){
            //POP if visited
          if(NodeInfoList[Adjacent.top().nodeTo].visited == 1){
            Adjacent.pop();
            }
          else{
            NodeQueue.push(NodeInfoList[Adjacent.top().nodeTo]);
            temp = NodeInfoList[Adjacent.top().nodeFrom].dist 
                   + Adjacent.top().weight;
              //if Smaller Distance, Then update it.
            if(NodeInfoList[Adjacent.top().nodeTo].dist > temp){
              NodeInfoList[Adjacent.top().nodeTo].dist = temp;
              }
            Adjacent.pop();
            }//Endelse
          } //Endwhile Adjacent not empty
        } //Endwhile NodeQueue not empty

      PrintDijkstra(NodeInfoList, startNode);

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









//??????????????????????????????????????????????????????????
//??????????????    HELPER FUNCTIONS    ????????????????????
//??????????????????????????????????????????????????????????

void PrintAdjList(char node, map<char, priority_queue<Edge> > AdjList){
  while (!AdjList[node].empty()){
    cout << "\n~~~~~~~~~~~~~~~~~~\nNode " << node 
         << " has: " << AdjList[node].top().nodeTo
         << "\nEdge Weight: " << AdjList[node].top().weight << "\n";
    AdjList[node].pop();
    }
}

void InsertEdge(char nF, char nT, int w,
                map<char, priority_queue<Edge> > &AdjList){
  Edge edge;
  edge.nodeFrom = nF;
  edge.nodeTo = nT;
  edge.weight = w;
  AdjList[nF].push(edge);
}

void PrintDijkstra(map<char, NodeInfo> nL, char startNode){
  cout << "\nDijkstra\nSource: " << startNode
       << "\n";
  int dist;
  typedef map<char, NodeInfo>::const_iterator MapIterator;
  for (MapIterator iter = nL.begin(); iter != nL.end(); iter++){
    if(iter->second.dist == 999999999){
      cout << "NODE " << iter->first << ": Unreachable\n";
      }
    else{
      cout << "NODE " << iter->first << ": " << iter->second.dist 
           << "\n";
      }
    }
  cout <<"End Dijkstra\n\n";
}

