g++ -std=c++14 decompress_fddcm.cpp -o decompress_fddcm
./decompress_fddcm
g++ -std=c++14 decompress_bitstream.cpp -o decompress_bitstream
./decompress_bitstream
mkdir decompressed_allframes
g++ -std=c++14 decompress_infodump.cpp -o decompress_infodump
./decompress_infodump
rm decompress_infodump
rm decompress_bitstream
rm decompress_fddcm
rm decompressed_bitstream.txt
rm decompressed_infodump.txt