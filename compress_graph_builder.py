from __future__ import print_function
import os

infile = "/media/dmehrab06/Workplace/ms_thesis/bayzid sir/dicomthesis/anew/dicom_work/allframes/"
outfile = "/media/dmehrab06/Workplace/ms_thesis/bayzid sir/dicomthesis/anew/dicom_work/graph.txt"

of = open(outfile,"w")

for root, dirs, files in os.walk(infile):
    
    for fx in files:
		if fx.endswith(".txt"):
			idx = 0
			
			for i in fx:
				if i.isdigit():
					idx = idx*10+int(i)
		
		for fy in files:
			if fy.endswith(".txt"):
				idy = 0
				
				for j in fy:
					if j.isdigit():
						idy = idy*10+int(j)
				
				if idx>idy:
					f1 = open(os.path.join(root,fx))
					f2 = open(os.path.join(root,fy))
					
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
								same = same + 1
							else:
								diff = diff + 1
					
					print(str(idx)+' '+str(idy)+' '+str(diff),file = of)



