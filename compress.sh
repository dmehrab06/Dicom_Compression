mkdir allframes
python compress_dcm2jpg.py
echo "finished extracting pixels" 
python compress_graph_builder.py
echo "graph built"
g++ -std=c++14 compress_mst.cpp -o compress_mst
./compress_mst <graph.txt >mstout.txt
echo "mst formed"
g++ -std=c++14 compress_dump.cpp -o compress_dump
./compress_dump >infodump.txt 
wc -l infodump.txt >llsize.txt
echo "frames represented by their differences"
g++ -std=c++14 compress_bit.cpp -o compress_bit
./compress_bit
echo "frames represented as bits"
g++ -std=c++14 compress_to_fddcm.cpp -o compress_to_fddcm
./compress_to_fddcm
rm compress_to_fddcm
rm compress_bit
rm compress_dump
rm compress_mst
#rm -r allframes/*.txt
rm graph.txt
rm infodump.txt
rm bitstream.txt
echo "compression complete"