import bz2
import sys
import os
file = "input.fasta_mafft"
compressionLevel=9
tarbz2contents1 = bz2.compress(open(file, 'rb').read(), compressionLevel)
zipfile=file+'zip'
z= open(zipfile,'wb')
z.write(tarbz2contents1)

z.close()
print(os.path.getsize(zipfile))