from __future__ import print_function
import pydicom
import os

infile = "/media/dmehrab06/Workplace/ms_thesis/bayzid sir/dicomthesis/anew/dicom_work/allframes/"
outfile = "/media/dmehrab06/Workplace/ms_thesis/bayzid sir/dicomthesis/anew/dicom_work/graph.txt"

file_number = 0;
of = open(outfile,"w")

for root, dirs, files in os.walk(infile):
    for file in files:
		if file.endswith(".txt"):
			file_number_1 = 0
			for i in file:
				if i.isdigit():
					file_number_1 = file_number_1*10+int(i)
		for file2 in files:
			if file2.endswith(".txt"):
				file_number_2 = 0
				for i2 in file2:
					if i2.isdigit():
						file_number_2 = file_number_2*10+int(i2)
				if file_number_1>file_number_2:
					f1 = open(os.path.join(root,file))
					f2 = open(os.path.join(root,file2))
					r1, c1 = map(int, f1.readline().split())
					r2, c2 = map(int, f2.readline().split())
					if ((r1!=r2) or (c1!=c2)):
						print('wrong')
						continue
					t1 = []
					t2 = []
					diff = 0
					same = 0
					for i in range(r1):
						#print(str(i))
						lines_1 = f1.readlines()
						lines_2 = f2.readlines()
						for line in lines_1:
							t1.append((line.split(" ")))
						for line in lines_2:
							t2.append((line.split(" ")))
					for i in range(r1):
						for j in range(c1):
							#print(str(i)+' '+str(j))
							val1 = int(t1[i][j])
							val2 = int(t2[i][j])
							if val1==val2:
								same = same+1
							else:
								diff = diff + abs(val1-val2)
					print(str(file_number_1)+' '+str(file_number_2)+' '+str(diff),file = of)



