#include <bits/stdc++.h>

#define MXVAL 1000005
#define MXBIT 65

#define FRMBITSTUFF 1
#define PXLBITSTUFF 1

using namespace std;

void compress_bits(){
	
	ifstream fin("bitstream.txt");
	ofstream myFile("compressed.fddcm", ios::out | ios::binary);
	
	char c;
	unsigned short bucket = 0;
	int sz = (int)(sizeof(bucket))*8;
	int turn = 0;
	int dumped = 0;

	cout<<(int)(sizeof(bucket))<<"\n";

	while(fin>>c){

		int v = c-'0';
		bucket = (bucket<<1)|v;
		turn++;

		if(turn==sz){

			myFile.write(reinterpret_cast<const char *>(&bucket), sizeof(bucket));
			//cout<<bucket<<"\n";
			dumped++;
 			turn = 0;
 			bucket = 0;
		}

	}

	if(turn){

		while(turn<sz){

			bucket = (bucket<<1)|0;
			turn++;
		}

		myFile.write(reinterpret_cast<const char *>(&bucket), sizeof(bucket));
		//cout<<bucket<<"\n";
		dumped++;
	}
	
	cout<<dumped<<"\n";
	fin.close();
	myFile.close();
}

int main(){
	
	compress_bits();
	return 0;

}
