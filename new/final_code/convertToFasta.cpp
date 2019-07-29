#include <bits/stdc++.h>
#define PIXELBIT 16

using namespace std;

char* file_name(int num){
	
	char* buf = new char[100];
	char dir[] = "allframes/";
	char ext[] = ".txt";

	sprintf(buf,"%s%d%s",dir,num,ext);
	
	return buf;
}

pair<int, pair<int,int> > getframe(){
	
	ifstream dim("dimension.txt");
	
	int f,r,c;
	dim>>f>>r>>c;

	return make_pair(f,make_pair(r,c));
}

void WriteBit(int val, ofstream &fout){

	string ss = "";
	
	for(int i = 0; i<PIXELBIT; ++i){
		int bb = val%2;
		ss.push_back(bb+'0');
		val/=2;
	}

	reverse(ss.begin(),ss.end());

	for(int i = 0; i<PIXELBIT; i+=2){

		char c1 = ss[i];
		char c2 = ss[i+1];

		if(c1==c2){

			if(c1=='0')fout<<"A";
			else fout<<"T";
		}

		else{
			if(c1=='0')fout<<"C";
			else fout<<"G";
		}

	}
}

void writeToFasta(int frame, ofstream &fout){

	for(int i = 1; i<=frame; ++i){

		ifstream fin(file_name(i));
		int row,col;
		fin>>row>>col;

		fout<<">Frame "<<i<<"\n";

		for(int rr = 1; rr<=row; ++rr){
			for(int cc = 1; cc<=col; ++cc){
				int val;
				fin>>val;
				WriteBit(val,fout);
			}
		}

		fout<<"\n";

		fin.close();
	}

}

int main(){
	
	ofstream fdcm("indcm.fasta");

	pair<int, pair<int,int> >dcminfo = getframe();
	writeToFasta(dcminfo.first,fdcm);

	fdcm.close();
}