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
  int dist, visited, steps, dist2;
    //Overwrite < operator for PriorityQueue's Comparison
  bool operator< (const NodeInfo& temp) const 
    { return dist > temp.dist; }
};

void PrintAdjList(char node, map<char, priority_queue<Edge> > AdjList);
void InsertEdge(char nF, char nT, int w,
                map<char, priority_queue<Edge> > &AdjList);
void PrintDijkstra(map<char, NodeInfo> nL, char startNode);
void PrintSRP(map<char, NodeInfo> nL, char startNode, int maxSteps);




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
//~~~~~~~~~~~~~~~~~~~~~~~~~    INT MAIN    ~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

int main(int argc, char** argv){
if(argc != 4){
  cout << "\n!!!!!!!!!!!!!!!!!!! Input Error !!!!!!!!!!!!!!!!!!!\n"
       << "::         Input should be as followed...        ::\n"
       << "::                                               ::\n"
       << ":: \"run <filename> <startnode> <distancelimit>\"  ::\n"
       << "::                                               ::\n"
       << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
  return -1;
  }

else{
  char* File = argv[1];
  char startNode = *argv[2];
  int maxSteps = *argv[3] - '0';
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

//<------------Directed Graph Loading-------------->
    if(GraphType == "D"){
      while(infile >> nodeFrom >> nodeTo >> weight){
        InsertEdge(nodeFrom, nodeTo, weight, AdjList);
        NodeInfoList[nodeFrom].nodeName = nodeFrom;
        NodeInfoList[nodeFrom].dist = 999999999;
        NodeInfoList[nodeFrom].steps = -1;
        NodeInfoList[nodeFrom].dist2 = 999999999;
        NodeInfoList[nodeFrom].visited = 0;
        NodeInfoList[nodeTo].nodeName = nodeTo;
        NodeInfoList[nodeTo].dist = 999999999;
        NodeInfoList[nodeTo].steps = -1;
        NodeInfoList[nodeTo].dist2 = 999999999;
        NodeInfoList[nodeTo].visited = 0;
        }
      } //End Directed

//<-------------UnDirected Graph Loading----------->
    if(GraphType == "UD"){
      while(infile >> nodeFrom >> nodeTo >> weight){
        InsertEdge(nodeFrom, nodeTo, weight, AdjList);
        InsertEdge(nodeTo, nodeFrom, weight, AdjList);
        NodeInfoList[nodeFrom].nodeName = nodeFrom;
        NodeInfoList[nodeFrom].dist = 999999999;
        NodeInfoList[nodeFrom].steps = -1;
        NodeInfoList[nodeFrom].dist2 = 999999999;
        NodeInfoList[nodeFrom].visited = 0;
        NodeInfoList[nodeTo].nodeName = nodeTo;
        NodeInfoList[nodeTo].dist = 999999999;
        NodeInfoList[nodeTo].steps = -1;
        NodeInfoList[nodeTo].dist2 = 999999999;
        NodeInfoList[nodeTo].visited = 0;
        }
      } //End Undirected

//================================================>
//---------------  IMPLEMENTATION ---------------->
//================================================>
        //Check if startNode actually exists
      if(NodeInfoList.find(startNode) == NodeInfoList.end()){
        cout << "ERROR: Start node does not exist!\n";
        cout << "\n!!!!!!!!!!!!!!!!!!! Input Error !!!!!!!!!!!!!!!!!!!\n"
          << "::       Startnode was not found in input.       ::\n"
          << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        return -1;
        }

      NodeQueue.push(NodeInfoList[startNode]);
      NodeInfoList[startNode].dist = 0;
      NodeInfoList[startNode].steps = 0;
      NodeInfoList[startNode].dist2 = 0;        
      priority_queue<Edge> Adjacent;
      char node = startNode;
      int currStep = 0;
      int temp;
      while(!NodeQueue.empty()){
        node = NodeQueue.top().nodeName;
        NodeQueue.pop();

          //Set Visited
        NodeInfoList[node].visited = 1;

          //get all edges in AdjList[node]
        Adjacent = AdjList[node];
        while(!Adjacent.empty()){


//-------------------------------------------------------------------->
//-------------- SHORTEST RELIABLE DIST, LOGIC CHECKING -------------->
//-------------------------------------------------------------------->
            //if steps has not been updated yet and nodeTo !- visited 
            //AND if prev node has been visited
          if(NodeInfoList[Adjacent.top().nodeFrom].steps < maxSteps 
             && NodeInfoList[Adjacent.top().nodeTo].steps == -1
             && NodeInfoList[Adjacent.top().nodeFrom].steps != -1){

              //if nodeFrom not -1 steps AND smaller than nodeTo
            if(NodeInfoList[Adjacent.top().nodeFrom].steps != -1
               && NodeInfoList[Adjacent.top().nodeFrom].steps 
                  < NodeInfoList[Adjacent.top().nodeTo].steps){
              NodeInfoList[Adjacent.top().nodeTo].steps = 
                NodeInfoList[Adjacent.top().nodeFrom].steps + 1;

                //Update dist2 to non shortest, but reliable path
              temp  =  NodeInfoList[Adjacent.top().nodeFrom].dist
                + Adjacent.top().weight;

                //if dist2 has not already been found
              if(temp < NodeInfoList[Adjacent.top().nodeTo].dist2){
                NodeInfoList[Adjacent.top().nodeTo].dist2 = temp;
                }                 

              } //Endif nodeFrom not -1 steps...

            if(NodeInfoList[Adjacent.top().nodeTo].steps == -1){
              NodeInfoList[Adjacent.top().nodeTo].dist2 = 
                NodeInfoList[Adjacent.top().nodeFrom].dist
                + Adjacent.top().weight;
              }
            }

          if(NodeInfoList[Adjacent.top().nodeTo].steps == -1 
               && currStep < maxSteps){
            NodeInfoList[Adjacent.top().nodeTo].steps = currStep + 1;
            }

//-------------------------------------------------------------------->
//------- END OF MAJOR SHORTEST RELIABLE DIST, LOGIC CHECKING -------->
//-------------------------------------------------------------------->


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

                //if within maxSteps boundary and Shorter distance
              if(currStep < maxSteps 
                   && temp < NodeInfoList[Adjacent.top().nodeTo].dist2){
                NodeInfoList[Adjacent.top().nodeTo].dist2 = temp;
                }
              }
            Adjacent.pop();
            }//Endelse
          } //Endwhile Adjacent not empty

        currStep = currStep++;
        } //Endwhile NodeQueue not empty

      PrintDijkstra(NodeInfoList, startNode);
      PrintSRP(NodeInfoList, startNode, maxSteps);


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

void PrintSRP(map<char, NodeInfo> nL, char startNode, int maxSteps){
  cout << "\nShortest Reliable Paths Algorithm\nSource: " << startNode
       << "\n";
  int dist;
  typedef map<char, NodeInfo>::const_iterator MapIterator;
  for (MapIterator iter = nL.begin(); iter != nL.end(); iter++){
    if(iter->second.dist2 == 999999999){
      cout << "NODE " << iter->first << ": Unreachable\n";
      }
    else{
      cout << "NODE " << iter->first << ": " << iter->second.dist2 
           << "\n";
      }
    }
  cout <<"End Shortest Reliable Paths Algorithm\n\n";
}
