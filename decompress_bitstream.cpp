#include <bits/stdc++.h>

using namespace std;

vector < int > bit_class_frames;
vector < int > bit_class_pixels;

int FRMBITSTUFF,PXLBITSTUFF;

void load_bit_classes(){
    
    ifstream fin("flag_bit_info.txt");

    fin>>FRMBITSTUFF;

    for(int i = 0; i<(1<<FRMBITSTUFF); ++i){

        int bt;
        fin>>bt;
        bit_class_frames.push_back(bt);

    }

    fin>>PXLBITSTUFF;

    for(int i = 0; i<(1<<PXLBITSTUFF); ++i){

        int bt;
        fin>>bt;
        bit_class_pixels.push_back(bt);
        
    }

    fin.close();
}

void decode(){

    ifstream fin("decompressed_bitstream.txt");

    ifstream fin2("llsize.txt");

    int read_req; fin2>>read_req; fin2.close();

    int read = 0;

    ofstream fout("decompressed_infodump.txt");

    while(read<read_req){

        if(read%1000==0)cout<<"current read: "<<read<<"\n";

        if(read%2==0){

            //frame read needed
            int bitflag = 0;

            for(int i = 1; i<=FRMBITSTUFF; ++i){

                char bt;
                fin>>bt;
                bitflag = (bitflag<<1)|(bt-'0');

            }

            int read_next = bit_class_frames[bitflag];

            int frame_no = 0;

            for(int i = 1; i<=read_next; ++i){

                char bt;
                fin>>bt;
                frame_no = (frame_no<<1)|(bt-'0');
            }

            fout<<frame_no<<"\n";

        }
        else{

            //pixel read needed
            int bitflag = 0;

            for(int i = 1; i<=PXLBITSTUFF; ++i){

                char bt;
                fin>>bt;
                bitflag = (bitflag<<1)|(bt-'0');

            }

            int read_next = bit_class_pixels[bitflag];

            int pixel_val = 0;

            for(int i = 1; i<=read_next; ++i){

                char bt;
                fin>>bt;
                pixel_val = (pixel_val<<1)|(bt-'0');
            }

            fout<<pixel_val<<"\n";

        }

        read++;

    }

    fin.close();
    fout.close();

}

int main(){
    load_bit_classes();
    decode();
    return 0;
}