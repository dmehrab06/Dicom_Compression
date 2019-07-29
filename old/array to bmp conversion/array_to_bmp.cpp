#include "bitmap_image.hpp"
#include <fstream>

using namespace std;


int main(){

    int length, width;

    ifstream infile ("1.txt");
    infile >> length >> width;




    bitmap_image image(length,width);

    for(int i=0;i<length;i++){

        for(int j=0;j<width;j++){

            int pixelVal;
            infile >> pixelVal;
            image.set_pixel(j,i,pixelVal,pixelVal,pixelVal);
        }
    }

    image.save_image("frame1.bmp");

    return 0;
}
