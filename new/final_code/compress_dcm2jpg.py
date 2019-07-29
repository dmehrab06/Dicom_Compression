from __future__ import print_function
import pydicom
import os

infile = "dataset/"
outfile = "allframes/"

outfileidx = 0
r = 0
c = 0

for root, dirs, files in os.walk(infile):
    for file in files:
		if file.endswith(".dcm"):

			outfileidx = outfileidx + 1
			f_name = os.path.join(root,file)
			print(file)

			content = pydicom.dcmread(f_name)
			#print(content)
			row = content.pixel_array.shape[0]
			col = content.pixel_array[0].shape[0]
			r = row
			c = col
			
			f = open(outfile+str(outfileidx)+".txt","w")

			print(str(row),end=' ',file=f)
			print(str(col),file=f)

			for i in range(row):
				for j in range(col):
					
					p = str(content.pixel_array[i][j])
					print(p,end=' ',file=f)
				
				print('',file=f)

totf = open("dimension.txt","w")
print(outfileidx,end = ' ',file = totf)
print(r,end = ' ',file = totf)
print(c,file = totf)
