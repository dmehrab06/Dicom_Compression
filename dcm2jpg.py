from __future__ import print_function
import pydicom
import os

infile = "/media/dmehrab06/Workplace/ms_thesis/bayzid sir/dicomthesis/anew/dicom_work/dataset/"
outfile = "/media/dmehrab06/Workplace/ms_thesis/bayzid sir/dicomthesis/anew/dicom_work/allframes/"

file_number = 0;

for root, dirs, files in os.walk(infile):
    for file in files:
		if file.endswith(".dcm"):
			file_number = file_number + 1
			f_name = os.path.join(root,file)
			print(file)
			ds = pydicom.read_file(f_name)
			f = open(outfile+str(file_number)+".txt","w")
			sz = ds.pixel_array.shape[0]
			print(str(sz),end=' ',file=f)
			r = ds.pixel_array.shape[1]
			print(str(r),file=f)
			for i in range(ds.pixel_array.shape[0]):
				for j in range(ds.pixel_array[0].shape[0]):
					p = str(ds.pixel_array[i][j])
					print(p,end=' ',file=f)
				print('',file=f)
