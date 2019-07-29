mkdir allframes
python compress_dcm2jpg.py
g++ -std=c++14 convertToFasta.cpp -o convertToFasta
./convertToFasta
echo "fasta created"
rm convertToFasta
python3 msa2.py