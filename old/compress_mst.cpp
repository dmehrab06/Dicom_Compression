#include <bits/stdc++.h>

using namespace std;

vector< pair<long long int, pair<int,int> > >alledg;
vector<int>rep;
set<int>vertex;

int processfile(){
	int u,v; long long w;
	while(cin>>u>>v>>w){
		vertex.insert(u);
		vertex.insert(v);
		pair<long long, pair<int,int> >pp = make_pair(w,make_pair(u,v));
		alledg.push_back(pp);
	}
	sort(alledg.begin(),alledg.end());
	return (int)vertex.size();
}

void init(int n){
	for(int i = 0; i<n+3; ++i){
		rep.push_back(i);
	}
}

int findrep(int u){
	if(rep[u]==u)return u;
	int v = findrep(rep[u]);
	return rep[u] = v;
}

bool __union(int u, int v){
	int pu = findrep(u);
	int pv = findrep(v);
	if(pu!=pv){
		rep[pu] = pv;
		return true;
	}
	return false;
}

void kruskal(int n){
	int taken = 0;
	for(int i = 0; i<(int)alledg.size(); ++i){
		pair<long long, pair<int,int> >pp = alledg[i];
		long long w = pp.first;
		int u = pp.second.first;
		int v = pp.second.second;
		if(__union(u,v)){
			taken++;
			cout<<u<<" "<<v<<" "<<w<<"\n";
			if(taken==(n-1)){
				break;
			}
		}
	}
}

void solve(){
	int n = processfile();
	init(n);
	kruskal(n);
}

int main(){
	solve();
	return 0;
}