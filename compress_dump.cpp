#include <bits/stdc++.h>
using namespace std;

vector< vector < vector <int> > >img;

vector< int > deg;

vector< int > par;

vector< vector<int> >g;

vector< set<int> > ancestors;

int root = 0;

void dfs(int src, int p){
	
	par[src] = p;
	
	for(int u: g[src]){
		
		if(u==p)continue;
		
		dfs(u,src);
	}
}

void set_ancestors(int tot_frame){

	for(int i = 1; i<=tot_frame+3; ++i){

		set<int>line;
		ancestors.push_back(line);

	}

	for(int i = 1; i<=tot_frame; ++i){

		int temp = i;
		
		while(par[temp]!=-1){
			
			ancestors[i].insert(par[temp]);
			temp = par[temp];

		}

	}

}

char* file_name(int num){
	
	char* buf = new char[100];
	char dir[] = "allframes/";
	char ext[] = ".txt";

	sprintf(buf,"%s%d%s",dir,num,ext);
	
	return buf;
}

void makegraph(int tot_frame){
	
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

		g[u].push_back(v); g[v].push_back(u);
		deg[u]++; deg[v]++;
	
	}

	finmst.close();	
}

int find_root(int tot_frame){
	
	int mxnode = -1, mxdeg = -1;
	
	for(int i = 1; i<=tot_frame; ++i){
		
		int d = deg[i];
		
		if(d>mxdeg){
			mxdeg = d;
			mxnode = i;
		}
	}

	return mxnode;
}

pair<int,int> load(int tot_frame){
	//finding pixel dimension
	ifstream fin("allframes/1.txt");
	int r,c;
	fin>>r>>c;
	fin.close();
	
	//initializing img memory
	for(int i = 0; i<tot_frame+2; ++i){
		
		vector< vector<int> >mat;
		img.push_back(mat);
		
		for(int j = 0; j<r+2; ++j){
			
			vector< int >line;
			img[i].push_back(line);
			
			for(int k = 0; k<c+2; ++k) img[i][j].push_back(0);
			
		}
	}

	//load all the pixel info in code memory
	for(int i = 1; i<=tot_frame; ++i){
		
		char* fname = file_name(i);
		//printf("%s\n",fname);	
		ifstream fin(fname);
		int r, c;
		fin>>r>>c;
		
		for(int j = 1; j<=r; ++j) for(int k = 1; k<=c; ++k) fin>>img[i][j][k];

		fin.close();
	}
	
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

void init_compressor(int r, int c){
	
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
	node* curnode = head;
	
	while(!fq.empty()){
		
		int curframe = fq.front(); fq.pop();

		for(int u: g[curframe])if(u!=par[curframe])fq.push(u);
		
		int curpixelval = img[curframe][r][c];
		node* packet = new node(curframe,curpixelval);
		node* ll = head->last;
		int match = 0;

		while(ll!=head){
			
			int thisframe = ll->frameno;

			if(ancestors[curframe].find(thisframe)!=ancestors[curframe].end()){
				
				if(ll->val==curpixelval) match = 1;
					
				break;
				
			}

			ll = ll->prev;
		}
		
		if(match){
			
			profit++;
			//printf("saved something\n");
			continue;
		}

		else{ //add another node.. memory consumption
			
			curnode->next = packet;
			packet->prev = curnode;
			head->last = packet;
			curnode = packet;
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

void print_list(int r, int c){
	node* head = compressor[r-1][c-1];
	int first = 0;
	while(head){
		if(first) printf(",");
		printf(" (%d-%d)",head->frameno, head->val);
		head = head->next;
		first = 1;
	}
	printf("\n");
	return;
}

void dump_contents(int totframe){
	
    int r = compressor.size();
    int c = compressor[0].size();
    
    
    for(int i = 0;i<r;++i){
        
        for(int j = 0;j<c;++j){
            
            node *cur = compressor[i][j];
            
            while(cur->next){
                
                cur = cur->next;
                
                int fr = cur->frameno; int px = cur->val;

                if(fr==0)continue;
                
                printf("%d\n",fr);
                printf("%d\n",px);
            }
        }
    }
    
}

void outputinfile(int totframe){
    
    ofstream myFile ("compressed.bin", ios::out | ios::binary);
    
    int r = compressor.size();
    int c = compressor[0].size();
    
    myFile.write(reinterpret_cast<const char *>(&totframe), sizeof(totframe));
    myFile.write(reinterpret_cast<const char *>(&r), sizeof(r));
    myFile.write(reinterpret_cast<const char *>(&c), sizeof(c));
    
    myFile.close();
}

void make_frame_ll(int ro, int col, int root){
	for(int i = 1; i<=ro; ++i){
		//cout<<i<<"\n";
		for(int j = 1; j<=col; ++j){
			//cout<<i<<" "<<j<<"\n";
			construct(i,j,root);
		}
	}
}

void print_supplements( pair<int,int>rc ){
	int tot_size = 0;
	for(int i = 1; i<=rc.first; ++i){
		for(int j = 1; j<=rc.second; ++j){
			//cout<<i<<" "<<j<<" ";
			int sz = get_list_size(i,j);
			//cout<<"size: "<<sz<<"\n";
			tot_size+=sz;
		}
	}	
	cout<<tot_size<<"\n\n\n";
	
	cout<<"printing compressed information\n";
	for(int i = 1; i<=rc.first; ++i){
		for(int j = 1; j<=rc.second; ++j){
			cout<<i<<" "<<j<<" list: ";
			print_list(i,j);
		}
	}
	cout<<profit<<"\n";
}

int main(){

	ifstream fin("totalframe.txt");
	int FRAMES; fin>>FRAMES; fin.close();

	pair<int,int>rc = load(FRAMES);

	makegraph(FRAMES);

	int root = find_root(FRAMES);
	//printf("%d\n",root);

	dfs(root,-1);
	set_ancestors(FRAMES);

	init_compressor(rc.first,rc.second);
	
	make_frame_ll(rc.first,rc.second,root);

	//print_supplements(rc);
	
	dump_contents(FRAMES);

	//outputinfile(FRAMES);
	return 0;
}