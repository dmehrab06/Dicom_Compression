#include <bits/stdc++.h>

using namespace std;

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value){
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
void printbit(const T& value, int bitsz, ofstream& outfile){

	string conv = "";

	int mask = 1;

	for (int i = 0; i < bitsz; ++i)
	{
		char cur = (value&mask)?'1':'0';
		conv.push_back(cur);
		mask = mask<<1;
	}

	reverse(conv.begin(),conv.end());
	outfile<<conv;

}

int main(){

	ifstream myFile("compressed.fddcm", ios::in | ios::binary);
    ofstream bitFile("decompressed_bitstream.txt");

    while(myFile.peek()!=EOF){
    	
    	unsigned short p;
    	binary_read(myFile,p);
    	printbit(p,(int)(sizeof(p))*8,bitFile);
    	
    	//cout<<p<<"\n";
    }

    myFile.close();
    bitFile.close();

    return 0;
}