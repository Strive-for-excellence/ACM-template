// ipsc 2003 G [hackenbush] (c) misof
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <vector>
#include <list>
#define min(x,y) ((x)<(y))?(x):(y)

int Cases,N,M;
vector< list<int> > G,G2;
vector<int> GV;
vector<int> visited,from,time_disc,time_up;
int DFStime;

void DFS_Visit(int v){
  int edges_to_parent=0;
  visited[v]=1; time_disc[v]=time_up[v]=++DFStime;
  for (list<int>::iterator start=G[v].begin();start!=G[v].end();start++) {
    if (!visited[*start]) { from[*start]=v; DFS_Visit(*start); time_up[v]=min(time_up[v],time_up[*start]); }
    else {
      if ((*start)!=from[v]) { time_up[v]=min(time_up[v],time_disc[*start]); }
      else { 
        if (edges_to_parent) { time_up[v]=min(time_up[v],time_disc[*start]); } 
        edges_to_parent++; 
      }
    }
  }
}

void FindBridges(void){
  time_disc.clear(); time_up.clear(); visited.clear(); from.clear();
  visited.resize(N+3,0); time_disc.resize(N+3,0); time_up.resize(N+3,0); from.resize(N+3,0);
  from[1]=1; DFStime=0;
  DFS_Visit(1);
}

int IsBridge(int v_lo, int v_high) { 
  if (v_high!=from[v_lo]) return 0;
  return ( time_disc[v_lo]==time_up[v_lo] ); 
}

void ContractGraph(void){
  vector<int> color(N+3,0);
  int colors=1;
  color[1]=1;

  list<int> Q;
  Q.clear(); Q.push_back(1); 
  while (!Q.empty()) { 
    int where=Q.front(); Q.pop_front(); 
    for (list<int>::iterator it=G[where].begin(); it!=G[where].end(); it++) if (!color[*it]) {
      if (IsBridge(*it,where)) color[*it]=++colors; else color[*it]=color[where];
      visited[*it]=1; Q.push_back(*it);
    }
  }
  
  G2.clear(); G2.resize(N+3);
  for (int i=1;i<=N;i++) 
    for (list<int>::iterator it=G[i].begin(); it!=G[i].end(); it++) 
      G2[color[i]].push_back(color[*it]);
}

int GrundyValue(int v){
  int loops=0,gv=0;
 
  if (GV[v]!=-1) return GV[v]; GV[v]=1000000000;
 
  for (list<int>::iterator start=G2[v].begin(); start!=G2[v].end(); start++) {
    if ((*start)==v) loops++; else if (GV[*start]!=1000000000) gv^=(1+GrundyValue(*start)); 
  }
  loops/=2; if (loops%2) gv^=1;
  return GV[v]=gv;
}

int main(void){
  int v1,v2;
 
  cin >> Cases;
  while (Cases--) {
    // read graph dimensions
    cin >> N >> M;
    // read the graph
    G.clear(); G.resize(N+3);
    for (int i=0;i<M;i++) { cin >> v1 >> v2; G[v1].push_back(v2); G[v2].push_back(v1); }
    // collapse all circuits in the graph
    FindBridges();
    ContractGraph();
    // compute the SG value
    GV.clear(); for (int i=0;i<=N;i++) GV.push_back(-1);
    int result=GrundyValue(1);
    // if (result) cout << "Alice\n"; else cout << "Bob\n"; // cout << result << "\n";
    cout << result << "\n";
  }
  return 0;
}
