#include <bits/stdc++.h>

using namespace std;

vector< vector < vector<int> > >img;
vector < int > deg;
vector < vector <int> >g;
vector < int > par;
vector < int > level_order_tree;

int frame,row,column;

void init_memory(){

	ifstream fin("dimension.txt");

	fin>>frame>>row>>column; fin.close();

	for(int i = 0; i<frame+1; ++i){

		vector< vector<int> > mat;
		img.push_back(mat);

		for(int j = 0; j<row+1; ++j){

			vector<int>line;
			img[i].push_back(line);

			for(int k = 0; k<column+1; ++k){

				img[i][j].push_back(-1);

			}
		}
	}

	for(int i = 0; i<frame+1; ++i){
		
		std::vector<int> line;
		g.push_back(line);
		deg.push_back(0);
		par.push_back(-1);
	
	}
}

int find_root(){

	ifstream fin("mstout.txt");

	int u,v,w;

	while(fin>>u>>v>>w){

		g[u].push_back(v); deg[u]++;
		g[v].push_back(u); deg[v]++;
	}

	int mxnode = -1, mxdeg = -1;

	for(int i = 1; i<=frame; ++i){

		if(deg[i]>mxdeg){

			mxdeg = deg[i];
			mxnode = i;
		}

	}

	fin.close();

	return mxnode;
}

void load_tree_level(int src){

	queue<int>bfsq;

	bfsq.push(src);

	while(!bfsq.empty()){

		int cur_frame = bfsq.front();

		bfsq.pop();

		level_order_tree.push_back(cur_frame);

		for(int v: g[cur_frame]){

			if(v!=par[cur_frame]){
				bfsq.push(v);
			}
		}
	}
}

void dfs(int u, int p){


	cout<<"dfs in "<<u<<"\n";
	par[u] = p;

	for(int v: g[u])
		if(p!=v)
			dfs(v,u);	

}

void fill_bfs(int ro, int col){

	for(int cur_frame: level_order_tree){
		if(img[cur_frame][ro][col]==-1){
			img[cur_frame][ro][col] = img[par[cur_frame]][ro][col];
		}
	}

}

void fill_frame(int ro, int col, vector<int>&info){

	for(int i = 0; i<(int)info.size(); i+=2){

		int fr = info[i];
		int val = info[i+1];

		img[fr][ro][col] = val;
	}

}

void traverse_list(int srcframe){

	ifstream fin("decompressed_infodump.txt");

	int content; fin>>content;

	for(int i = 1; i<=row; ++i){

		cout<<i<<"\n";

		for(int j = 1; j<=column; ++j){

			//cout<<i<<" "<<j<<"\n";

			vector<int>ll_info;

			ll_info.push_back(srcframe);

			int curturn = 1;

			while(fin>>content){

				if(curturn%2==0 && content==srcframe)break;

				ll_info.push_back(content);

				curturn++;

			}

			fill_frame(i,j,ll_info);
			fill_bfs(i,j);

		}

	}

	fin.close();
}

char* file_name(int num){
	
	char* buf = new char[100];
	char dir[] = "decompressed_allframes/";
	char ext[] = ".txt";

	sprintf(buf,"%s%d%s",dir,num,ext);
	
	return buf;
}

void make_jpgs(){

	for(int i = 1; i <= frame; ++i){

		char* fname = file_name(i);

		ofstream fout(fname);

		fout<<row<<" "<<column<<"\n";
		
		for(int r = 1; r<=row; ++r){

			for(int c = 1; c<=column; ++c){

				fout<<img[i][r][c]<<" ";
			}

			fout<<"\n";

		}

		fout.close();
	}

}

int main(){
	
	init_memory();
	int root = find_root();
	dfs(root,-1);
	load_tree_level(root);

	traverse_list(root);

	make_jpgs();

	return 0;

}
