#include <bits/stdc++.h>

using namespace std;

vector< vector < vector <int> > >img;

vector< int > deg;

vector< int > par;

vector< vector<int> >g;

int root = 0;

void dfs(int src, int p){
	par[src] = p;
	for(int u: g[src]){
		if(u==p)continue;
		dfs(u,src);
	}
}

void load_location(string s, char* c){
	for(int i = 0; i<(int)s.size();++i){
		c[i] = s[i];
	}
	c[(int)s.size()] = '\0';
}

char* file_name(int num){
	string s = "";
	while(num){
		s.push_back(num%10+'0');
		num/=10;
	}
	reverse(s.begin(),s.end()); s+=".txt";
	char* c = new char[100];
	load_location("allframes/",c);
	for(int i = 0; i<s.size(); ++i){
		c[10+i] = s[i];
	}
	c[10+(int)s.size()] = '\0';
	return c;
}

pair<int,int> load(int tot_frame){
	//finding pixel dimension
	ifstream fin("allframes/1.txt");
	int r,c;
	fin>>r>>c;
	fin.close();
	
	for(int i = 0; i<tot_frame+2; ++i){
		vector< vector<int> >mat;
		img.push_back(mat);
		for(int j = 0; j<r+2; ++j){
			vector< int >line;
			img[i].push_back(line);
			for(int k = 0; k<c+2; ++k){
				img[i][j].push_back(0);
			}
		}
	}

	//load all the pixel info in code memory
	for(int i = 1; i<=tot_frame; ++i){
		char* fname = file_name(i);
		ifstream fin(fname);
		int r, c;
		fin>>r>>c;
		for(int j = 1; j<=r; ++j){
			for(int k = 1; k<=c; ++k){
				fin>>img[i][j][k];
			}
		}
		fin.close();
	}

	for(int i = 1; i< tot_frame+3; ++i){
		std::vector<int> line;
		g.push_back(line);
		deg.push_back(0);
		par.push_back(-1);
	}

	ifstream finmst("mstout.txt");
	for(int i = 1; i<tot_frame; ++i){
		int u,v,w;
		finmst>>u>>v>>w;
		g[u].push_back(v);
		g[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	finmst.close();
	//finding the root
	int mxnode = -1, mxdeg = -1;
	for(int i = 1; i<=tot_frame; ++i){
		int d = deg[i];
		if(d>mxdeg){
			mxdeg = d;
			mxnode = i;
		}
	}

	//finding reference for each frame
	dfs(mxnode,-1);

	root = mxnode;

	return make_pair(r,c);
}  

typedef struct ss{
	int frameno;
	int val;
	struct ss * next;
	struct ss* prev;
	struct ss* last;
	ss(int _f = 0, int _d = 0){
		frameno = _f;
		val = _d;
		next = NULL;
		prev = NULL;
		last = this;
	}
}node;

vector< vector< node* > >compressor;

void init_cmp(int r, int c){
	for(int i = 1; i<=r; ++i){
		vector< node* >line;
		compressor.push_back(line);
		for(int j = 1; j<=c; ++j){
			node* h = new node();
			compressor[i-1].push_back(h);
		}
	}
}

int profit = 0;

void construct(int r, int c, int src){
	queue<int>fq;
	fq.push(src);
	node* head = compressor[r-1][c-1];
	node* cn = head;
	while(!fq.empty()){
		int curframe = fq.front(); int temp = curframe;
		set<int>pars;
		while(par[temp]!=-1){
			pars.insert(par[temp]);
			temp = par[temp];
		}
		fq.pop();
		for(int u: g[curframe]){
			if(u==par[curframe]){
				continue;
			}
			fq.push(u);
		}
		int curpixelval = img[curframe][r][c];
		node* curpack = new node(curframe,curpixelval);
		node* ll = head->last;
		int has = 0;
		while(ll!=head){
			int thisframe = ll->frameno;
			if(pars.find(thisframe)!=pars.end()){
				if(ll->val==curpixelval){
					//ager reference er sathe value mile, eta r store korbo na
					has = 1;
					break;
				}
				else{
					//ager reference er sathe value mile na, store kora jabe na
					break;
				}
			}
			ll = ll->prev;
		}
		if(has){
			profit++;
			//printf("saved something\n");
			continue;
		}
		else{
			cn->next = curpack;
			curpack->prev = cn;
			head->last = curpack;
			cn = curpack;
		}
	}
	return;
}

int get_list_size(int r, int c){
	node* head = compressor[r-1][c-1];
	int size = 0;
	while(head){
		head = head->next;
		size++;
	}
	return size;
}

int main(){
	pair<int,int>rc = load(33);
	for(int j = 499; j<=512; ++j){
		for(int i = 1; i<=33; ++i){
			if(img[i][512][j]!=0){
				printf("boka\n");
			}
		}
	}
	return 0;
}