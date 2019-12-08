/*
Student Name:
Student Number:
Project Number: 4
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "HelpStudents.h"

class Graph{
public:
    int numberOfVertices; // No. of verticess
    vector< pair<int, int> > *adjacencyList;
    vector<bool> visited;
    vector<int> parents;
    vector<int> numberOfVerticesToGo;
    vector<long long int> pathDistance;
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> edgeSize;
    Graph(int numberOfVertices) {
        this->numberOfVertices = numberOfVertices+1;
        adjacencyList = new vector< pair<int, int> >[numberOfVertices+1];
        for(int i=0;i<= numberOfVertices+1;i++){
            visited.push_back(false);
            parents.push_back(-1);
            numberOfVerticesToGo.push_back((-1));
            pathDistance.push_back(-1);
        }

    }
    void addEdge(int u, int v, int w) {
        adjacencyList[u].push_back(make_pair(v, w));
        adjacencyList[v].push_back(make_pair(u, w));
    }
    void deleteEdge(int u, int v){
        for(int i=0;i<adjacencyList[v].size();i++){
            if(adjacencyList[v][i].first==u){
                adjacencyList[v].erase(adjacencyList[v].begin()+i);
            }
        }
        for(int i=0;i<adjacencyList[u].size();i++){
            if(adjacencyList[u][i].first==v){
                adjacencyList[u].erase(adjacencyList[u].begin()+i);
            }
        }
    }

};
using namespace std;
Graph *g;
int final;
int start;
HelpStudents::HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways) {
    // IMPLEMENT ME!
  g=new Graph(N);
  for(pair<pair<int,int>, int> temp:ways){
      g->addEdge(temp.first.first,temp.first.second,temp.second);
      g->edgeSize.push(make_pair(temp.second,make_pair(temp.first.first,temp.first.second)));
  }
  final=K;
}
long long int HelpStudents::firstStudent()    {
    // IMPLEMENT ME!
    priority_queue<pair<long long int,int>,vector<pair<long long int,int>>,greater<pair<long long int,int>>> que;
    g->pathDistance[1]=0;
    que.push(make_pair(g->pathDistance[1],1));
    while(!que.empty()){
        int temp= que.top().second;
        que.pop();
        for(int i=0;i<g->adjacencyList[temp].size();i++){
            int temp2=g->adjacencyList[temp][i].first;
            long long int weight =g->adjacencyList[temp][i].second;

                if(g->pathDistance[temp2]==-1){
                    g->pathDistance[temp2]=weight+g->pathDistance[temp];
                    que.push(make_pair(g->pathDistance[temp2],temp2));
                }
                else {
                    if (weight + g->pathDistance[temp] < g->pathDistance[temp2]){
                        g->pathDistance[temp2] = weight + g->pathDistance[temp];
                        que.push(make_pair(g->pathDistance[temp2],temp2));
                    }
            }


        }
}
    return g->pathDistance[final];
}
long long int HelpStudents::secondStudent() {
    // IMPLEMENT ME!
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pque;
    pque.push(make_pair(0,1));
    while(!pque.empty()){
        int temp= pque.top().second;
        pque.pop();
        g->visited[temp]=true;
        for(int i=0;i<g->adjacencyList[temp].size();i++){
            int temp2=g->adjacencyList[temp][i].first;
            int weight=g->adjacencyList[temp][i].second;
            if(!g->visited[temp2]){
                if(g->pathDistance[temp2]==-1){
                    g->parents[temp2]=temp;
                    g->pathDistance[temp2]=weight;
                    pque.push(make_pair(g->pathDistance[temp2],temp2));
                }
                else if(g->pathDistance[temp2]>weight){
                    g->parents[temp2]=temp;
                    g->pathDistance[temp2]=weight;
                    pque.push(make_pair(g->pathDistance[temp2],temp2));                }
            }
        }
    }
    int ret=final;
    int largest=-1;
    while(ret!=1){
        int start=g->parents[ret];
        int end=ret;
        for(int i=0;i<g->adjacencyList[start].size();i++){
            if(g->adjacencyList[start][i].first==end){
                if(largest<g->adjacencyList[start][i].second)
                    largest=g->adjacencyList[start][i].second;
            }
        }
        ret=g->parents[ret];
    }
    return largest;
}
long long int HelpStudents::thirdStudent() {
    // IMPLEMENT ME!
    vector<int> v;
    v.push_back(1);
    g->numberOfVerticesToGo[1]=0;
    while(!v.empty()){
        int temp= v[0];
        v.erase(v.begin());
        g->visited[temp]=true;
        for(int i=0;i<g->adjacencyList[temp].size();i++){
            int temp2=g->adjacencyList[temp][i].first;
            if(!g->visited[temp2]){
                g->visited[temp2]=true;
                g->numberOfVerticesToGo[temp2]=g->numberOfVerticesToGo[temp]+1;
                v.push_back(temp2);
            }
        }
    }
    return g->numberOfVerticesToGo[final];
}
long long int HelpStudents::fourthStudent() {
    // IMPLEMENT ME!
    vector<int> v;
    v.push_back(1);
    long long int total=0;
    while(!v.empty()){
        int temp= v[0];
        v.erase(v.begin());
        g->visited[temp]=true;
        if(g->adjacencyList[temp].size()==0)
            break;
        int smallest=g->adjacencyList[temp][0].second;
        int mintemp=g->adjacencyList[temp][0].first;
        for(int i=1;i<g->adjacencyList[temp].size();i++){
            int temp2=g->adjacencyList[temp][i].first;
            int weight=g->adjacencyList[temp][i].second;
            if(smallest>weight){
                    smallest=weight;
                    mintemp=temp2;

            }
            else if(smallest==weight){
                if(mintemp>temp2){
                    smallest=weight;
                    mintemp=temp2;
                }
            }
        }
        g->deleteEdge(temp,mintemp);
        total+=smallest;
        v.push_back(mintemp);
        if(mintemp==final){
            return total;
        }
    }
    return -1;
}
long long int HelpStudents::fifthStudent() {
    // IMPLEMENT ME!
       vector<int> v;
    v.push_back(1);
    g->pathDistance[1]=0;
    g->numberOfVerticesToGo[1]=0;
    while(!v.empty()){
        int temp=v.front();
        v.erase(v.begin());
        int smallest=g->adjacencyList[temp][0].second;
        int mintemp=g->adjacencyList[temp][0].first;
        for(int i=0;i<g->adjacencyList[temp].size();i++){
            int temp2=g->adjacencyList[temp][i].first;
            int weight=g->adjacencyList[temp][i].second;
            if(smallest>weight){
                smallest=weight;
                mintemp=temp2;
            }
        }
        for(int i=0;i<g->adjacencyList[temp].size();i++){
            int temp2=g->adjacencyList[temp][i].first;
            int weight=g->adjacencyList[temp][i].second;
            if(g->numberOfVerticesToGo[temp]==0){
                if(weight==smallest){
                    if(g->pathDistance[temp2]>g->pathDistance[temp]+weight||g->pathDistance[temp2]==-1){
                        g->numberOfVerticesToGo[temp2]=g->numberOfVerticesToGo[temp]+1;
                        g->pathDistance[temp2]=g->pathDistance[temp]+weight;
                        v.push_back(temp2);
                    }
                }
                else if(weight<2*smallest){
                    if(g->pathDistance[temp2]>g->pathDistance[temp]+weight||g->pathDistance[temp2]==-1){
                        g->numberOfVerticesToGo[temp2]=g->numberOfVerticesToGo[temp]+1;
                        g->pathDistance[temp2]=g->pathDistance[temp]+weight;
                        v.push_back(temp2);
                    }
                }
                else{
                    if(g->pathDistance[temp2]>g->pathDistance[temp]+weight||g->pathDistance[temp2]==-1){
                        g->numberOfVerticesToGo[temp2]=0;
                        g->pathDistance[temp2]=g->pathDistance[temp]+2*smallest;
                        v.push_back(temp2);
                    }
                }
            }
            else if(g->numberOfVerticesToGo[temp]==1){
                if(g->pathDistance[temp2]>g->pathDistance[temp]+weight||g->pathDistance[temp2]==-1){
                    g->numberOfVerticesToGo[temp2]=g->numberOfVerticesToGo[temp]+1;
                    g->pathDistance[temp2]=g->pathDistance[temp]+weight;
                    v.push_back(temp2);
                }
            }
            else{
                if(g->pathDistance[temp2]>g->pathDistance[temp]||g->pathDistance[temp2]==-1){
                    g->pathDistance[temp2]=g->pathDistance[temp];
                    g->numberOfVerticesToGo[temp2]=0;
                    v.push_back(temp2);
                }
            }
        }
    }
    return g->pathDistance[final];
}



// YOU CAN ADD YOUR HELPER FUNCTIONS
