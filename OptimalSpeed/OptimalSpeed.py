import matplotlib.pyplot as plt
import csv
import numpy as np
from statistics import *
# open the file in universal line ending mode 
with open('Clean1600.csv', 'rU') as infile:
  # read the file as a dictionary for each row ({header : value})
  reader = csv.DictReader(infile)
  data = {}
  for row in reader:
    for header, value in row.items():
      try:
        data[header].append(value)
      except KeyError:
        data[header] = [value]

# extract the variables you want
Distance = data['Dist']
X = data['X']
Y = data['Y']
Z = data['Z']

#print(type(Distance), type(Z))
#print(Distance)
#print(Z)

X = list(map(float, X))
meanX=mean(X)
stdevX=stdev(X)
print(meanX, stdevX)

Y = list(map(float, Y))
meanY=mean(Y)
stdevY=stdev(Y)
print(meanY, stdevY)

Z = list(map(float, Z))
meanZ=mean(Z)
stdevZ=stdev(Z)
print(meanZ, stdevZ)
z=1

Xnorm=[]
for i in X:
    ZScoreval=abs(abs(i-meanX)-z*stdevX)
    if(ZScoreval<=stdevX):
        ZScoreval=0
    else:
        ZScoreval=ZScoreval*3
    Xnorm.append(ZScoreval)

Ynorm=[]
for i in Y:
    ZScoreval=abs(abs(i-meanY)-z*stdevY)
    if(ZScoreval<=stdevY):
        ZScoreval=0
    else:
        ZScoreval=ZScoreval*3
    Ynorm.append(ZScoreval)

Znorm=[]
for i in Z:
    ZScoreval=abs(abs(i-meanZ)-z*stdevZ)
    if(ZScoreval<=stdevZ):
        ZScoreval=0
    else:
        ZScoreval=ZScoreval*3
    Znorm.append(ZScoreval)
    #print(i)
	
#print(Znorm)
#print(type(Z[0]))
#print(mean(Z))
plt.plot(Distance, Xnorm, linewidth=1.0)
plt.plot(Distance, Ynorm, linewidth=1.0)
plt.plot(Distance, Znorm, linewidth=1.0)
plt.title("Epic Chart")
plt.xlabel('Distance')
plt.ylabel('Z Axis')
#plt.subplot(221)
#plt.legend()
plt.show()