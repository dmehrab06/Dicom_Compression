python dcm2jpg.py 
#echo 'start'
python graph_builder.py
#echo 'end'
g++ mst.cpp -o mst
./mst <graph.txt >mstout.txt
g++ -std=c++14 compress_dump.cpp -o compress_dump
./compress_dump >infodump.txt 