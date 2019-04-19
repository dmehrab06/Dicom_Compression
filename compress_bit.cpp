#include <bits/stdc++.h>

#define MXVAL 1000005
#define MXBIT 65

#define FRMBITSTUFF 1
#define PXLBITSTUFF 1

using namespace std;

int bits_needed[MXVAL];
int bit_frequency_frame[MXBIT];
int bit_frequency_pixel[MXBIT];

vector < int > allcontents;
vector < int > bit_class_frames;
vector < int > bit_class_pixels;


void set_bit_classes(int frmxbit, int pxmxbit){
	cout<<frmxbit<<" "<<pxmxbit<<"\n";
	bit_class_frames.push_back(frmxbit/2);
	bit_class_frames.push_back(frmxbit);
	bit_class_pixels.push_back(pxmxbit/2);
	bit_class_pixels.push_back(pxmxbit);
}

void set_bit_classes_2(int frmxbit, int pxmxbit){
	cout<<frmxbit<<" "<<pxmxbit<<"\n";
	
	for(int i = 1; i<=frmxbit; ++i)bit_frequency_frame[i]+=bit_frequency_frame[i-1];
	for(int i = 1; i<=pxmxbit; ++i)bit_frequency_pixel[i]+=bit_frequency_pixel[i-1];

	int halffrmmxbit,halfpxmxbit;

	for(int i = 1; i<=frmxbit; ++i)
		if(bit_frequency_frame[i]>=bit_frequency_frame[frmxbit]/2){
			halffrmmxbit = i;
			break;
		}
	
	for(int i = 1; i<=pxmxbit; ++i)
		if(bit_frequency_pixel[i]>=bit_frequency_pixel[pxmxbit]/2){
			halfpxmxbit = i;
			break;
		}

	cout<<halffrmmxbit<<" "<<halfpxmxbit<<"\n";

	bit_class_frames.push_back(halffrmmxbit);
	bit_class_frames.push_back(frmxbit);
	bit_class_pixels.push_back(halfpxmxbit);
	bit_class_pixels.push_back(pxmxbit);
}

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

			frmxbit = max(frmxbit,bits_needed[a]);
			bit_frequency_frame[bits_needed[a]]++;

		}
		else{

			pxmxbit = max(pxmxbit,bits_needed[a]);
			bit_frequency_pixel[bits_needed[a]]++;
		}

		turn++;
	}

	set_bit_classes_2(frmxbit,pxmxbit);
}

void printbits(int val, int bits, ofstream &ff){
    string conv = "";

    for(int i = 1; i<=bits; ++i){
        conv.push_back(val%2+'0');
        val = val/2;
    }

    reverse(conv.begin(),conv.end());
    ff<<conv;
}

void dumpbits(){
    ofstream fout("bitstream.txt");
    int turn = 0;

    for(int a: allcontents){

        if(turn%2==0){

            int mnbit = bits_needed[a];
            int flagbit = (int)(lower_bound(bit_class_frames.begin(),bit_class_frames.end(),mnbit)-bit_class_frames.begin());
            int bit_req = bit_class_frames[flagbit];
            printbits(flagbit,FRMBITSTUFF,fout);
            printbits(a,bit_req,fout);

        }
        else{

            int mnbit = bits_needed[a];
            int flagbit = (int)(lower_bound(bit_class_pixels.begin(),bit_class_pixels.end(),mnbit)-bit_class_pixels.begin());
            int bit_req = bit_class_pixels[flagbit];
            printbits(flagbit,PXLBITSTUFF,fout);
            printbits(a,bit_req,fout);

        }

        turn++;
    }

    fout.close();
}

void flag_bit_dump(){

	ofstream fout("flag_bit_info.txt");

	fout<<FRMBITSTUFF<<"\n";

	for(auto a: bit_class_frames)fout<<a<<"\n";

	fout<<PXLBITSTUFF<<"\n";

	for(auto a: bit_class_pixels)fout<<a<<"\n";

	fout.close();

}

int main(){
	find_bits_needed();
	load();
	calc_bit_info();
	dumpbits();
	flag_bit_dump();
}
