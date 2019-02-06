#include <bits/stdc++.h>
#define FRAMES 33
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

void dump_again(int tot_frame, int r, int c, int mnn, int mxx){

	//load all the pixel info in code memory
	for(int i = 1; i<=tot_frame; ++i){
		char* fname = file_name(i);
		ofstream fout(fname);
		fout<<r<<" "<<c<<"\n";
		for(int j = 1; j<=r; ++j){
			for(int k = 1; k<=c; ++k){
				int curval = img[i][j][k];
				double vv = 255.0*((double)(curval-mnn))/((double)(mxx-mnn));
				int normval = round(vv);
				fout<<normval<<" ";
			}
			fout<<"\n";
		}
		fout.close();
	}
}

void process(int tot_frame){
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
	int mnn = 1000000; int mxx = 0;
	for(int i = 1; i<=tot_frame; ++i){
		char* fname = file_name(i);
		ifstream fin(fname);
		int r, c;
		fin>>r>>c;
		for(int j = 1; j<=r; ++j){
			for(int k = 1; k<=c; ++k){
				fin>>img[i][j][k];
				mxx = max(mxx,img[i][j][k]);
				mnn = min(mnn,img[i][j][k]);
			}
		}
		fin.close();
	}
	ofstream fout("maxmin.txt");
	fout<<mxx<<" "<<mnn<<"\n";
	dump_again(tot_frame,r,c,mnn,mxx);
}  

int main(){
	process(FRAMES);
	return 0;
}