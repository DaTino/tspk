import sys;
import csv;

if len(sys.argv) != 2:
    print('Usage: file name required');
    quit();

dataFileName=sys.argv[1];
dataFileName=dataFileName[:len(dataFileName)-4];

file = open(sys.argv[1],"r");
li = [line.strip()[:].split() for line in file]
file.close();

data=li;

try:
    float(li[0][1]);
    featuresList=[]
    for i in range(len(li[0])):
        featuresList.append(f"{i}")
    with open(f"{dataFileName}FeaturesList.txt", "w") as f:
        writer = csv.writer(f, delimiter=' ');
        writer.writerows(featuresList);
except:
    featuresList=li[:1]
    with open(f"{dataFileName}FeaturesList.txt", "w") as f:
        writer = csv.writer(f, delimiter=' ');
        writer.writerows(featuresList);

    li=li[1:]
try:
    float(li[1][0]);
    objectList=[]
    for i in range(len(li)):
        featuresList.append(f"{i}")
    with open(f"{dataFileName}ObjectList.txt", "w") as f:
        writer = csv.writer(f, delimiter=' ');
        writer.writerows(objectList);
except:
    data=[li[i][1:] for i in range(len(li))];

    objectList=[li[i][0:1] for i in range(len(li))];
    with open(f"{dataFileName}ObjectList.txt", "w") as f:
        writer = csv.writer(f, delimiter=' ');
        writer.writerows(objectList);

with open(f"{dataFileName}Headerless.txt", "w", newline="") as f:
    writer = csv.writer(f, delimiter=' ');
    writer.writerows(data)
