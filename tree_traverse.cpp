#include <bits/stdc++.h>
#define N 33
using namespace std;

vector< vector<int> >g;

vector< vector<int> >deep;

int depth[N+2];
int deg[N+2];

void init(){
	for(int i = 1; i<N+4; ++i){
		std::vector<int> line;
		g.push_back(line);
		deep.push_back(line);
	}
}

int main(){
	init();
	for(int i = 1; i<=N; ++i){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		g[u].push_back(v);
		g[v].push_back(u);
		deg[u]++; deg[v]++;
	}
	int mxnode = 6;
	queue<int>bq;
	bq.push(mxnode); depth[mxnode] = 1;
	while(!bq.empty()){
		int v = bq.front();
		bq.pop();
		for(int u: g[v]){
			if(!depth[u]){
				depth[u] = depth[v]+1;
				bq.push(u);
			}
		}
	}
	for(int i = 1; i<=N; ++i){
		deep[depth[i]].push_back(i);
	}
	for(int i = 1; i<=N; ++i){
		cout<<"at depth "<<i<<": ";
		for(int node: deep[i]){
			cout<<node<<" ";
		}
		cout<<"\n";
	}
	return 0;
}