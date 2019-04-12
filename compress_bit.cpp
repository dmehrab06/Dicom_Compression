#include <bits/stdc++.h>

#define MXVAL 1000005
#define MXBIT 65

using namespace std;

int bits_needed[MXVAL];
int bit_frequency_frame[MXBIT];
int bit_frequency_pixel[MXBIT];

vector < int > allcontents;

void find_bits_needed(){

	bits_needed[0] = 1;
	bits_needed[1] = 1;

	for(int i = 2; i<MXVAL; ++i) bits_needed[i] = bits_needed[i/2]+1;

}

void load(){
	
	ifstream fin("infodump.txt");

	int val;

	while(fin>>val){
		allcontents.push_back(val);
	}

	fin.close();
}

void calc_bit_info(){
	
	int frmxbit = 0, pxmxbit = 0;

	int turn = 0;

	for(int a: allcontents){

		if(turn%2==0){

			frmxbit = max(frmxbit,a);	
			bit_frequency_frame[bits_needed[a]]++;
        
		}
		else{

			pxmxbit = max(pxmxbit,a);
			bit_frequency_pixel[bits_needed[a]]++;	
		} 

		turn++;
	} 
}

int main(){
	find_bits_needed();
	load();
	calc_bit_info();
}