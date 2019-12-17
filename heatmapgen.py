import sys

import numpy as np
import numpy.random
import matplotlib.pyplot as plt
import matplotlib.colors
from matplotlib.colors import LinearSegmentedColormap
#sys.path.insert(0, '.')
#import seaborn as sns

def inputNumber(message):
  while True:
    try:
       userInput = int(input(message))
    except ValueError:
       print("You did not enter an integer. Try again.")
       continue
    else:
       return userInput
       break

###################################################################
# Configurables:                                                  #
# use this section to change varables related to image generation #
###################################################################
# dimension of image in inches
#img_width  = 8
#img_height = 10
# tick labels along the axes of the heat map- numbers represent
# labels skipped. i.e. 5 = 0, 5, 10, 15 etc
x_labels = 1
y_labels = 1
###################################################################

#to run: python heatmapgen.py input.txt output.filetype
#filetypes can be .jpeg, .png, .svg, .gif

if len(sys.argv) != 7:
    print('Usage: python heatmapgen.py input.txt output.filetype img_width img_height objList featList')
    print('Acceptable filetypes are be .jpeg, .png, .svg, .gif')
    quit()

#Generate image size in inches.
plt.rcParams['figure.figsize'] = (sys.argv[3], sys.argv[4])

#axis labels
toRemove=['k', '*******'];
objList = open(sys.argv[5]).readlines();
nObjList=[];
for i in range(len(objList)):
    objList[i]=objList[i].strip('\n');
for line in objList:
    if not any(badWord in line for badWord in toRemove):
        nObjList.append(line);
ftList = open(sys.argv[6]).readlines();
ftList[0]=ftList[0].strip('\n');
ftList = ftList[0].split(' ');

#heatmap generation. don't mess with this.
path = str(sys.argv[1])
print ('loading...')
df = np.loadtxt(path)
#dfs = np.split(df, 2);
x = len(df)
y = len(df[0])

objLocs=np.arange(x);
ftLocs=np.arange(y);


# color choice
colChoice = input("Color or grayscale? c/g: ");
if colChoice == 'c':
	color = 'cividis';
if colChoice == 'g':
	color = 'Greys';

print("Generate full heatmap (f), heatmap split by cluster (c) or subsection of heatmap (s)?")
drawChoice = input("Choose f, c, or s: ")

if drawChoice == "f":
    print ('generating...')
    plt.pcolormesh(df, cmap=color, vmin=-1, vmax=1)
    plt.colorbar(orientation="horizontal");
    plt.yticks(objLocs, nObjList);
    plt.xticks(ftLocs, ftList);
    #image drawing to file.
    print ('saving...')
    plt.savefig(str(sys.argv[2]))
    print('done!')

###### split section ######
if drawChoice == "c":

    splitLocs = open(sys.argv[5]).readlines();
    for i in range(len(splitLocs)):
        splitLocs[i]=splitLocs[i].strip('\n');
        splitLocs[i]=splitLocs[i].strip(' ');
    splitLocs=splitLocs[1:];
    splitDex = [i for i, e in enumerate(splitLocs) if "*******" in e];
    # print(f"splitDex: {splitDex}")
    # print(len(splitLocs))

    # Generate list of Clusters
    # splitChoice = input("Seperate graphs by cluster? y/n: ")
    # if splitChoice == 'y':
    for i in range(len(splitDex)):
        try:
                clusterObjNames=splitLocs[splitDex[i]+1:splitDex[i+1]]
                print(clusterObjNames);
                print(df[splitDex[i]+1-(i+1):splitDex[i+1]-(i+1)])

        except:
                clusterObjNames=splitLocs[splitDex[i]+1:]
                print(clusterObjNames);
                print(df[splitDex[i]+1-(i+1):,:])

    for i in range(len(splitDex)):
        plt.subplot(len(splitDex),1, i+1);
        try:
            plt.pcolormesh(df[splitDex[i]+1-(i+1):splitDex[i+1]-(i+1), :], cmap=color, vmin=-1, vmax=1)
            plt.yticks(np.arange(len(splitLocs[splitDex[i]+1:splitDex[i+1]])), splitLocs[splitDex[i]+1:splitDex[i+1]]);
            plt.xticks(ftLocs, ftList);
        except:
            plt.pcolormesh(df[splitDex[i]+1-(i+1):, :], cmap=color, vmin=-1, vmax=1)
            plt.yticks(np.arange(len(splitLocs[splitDex[i]+1:])), splitLocs[splitDex[i]+1:]);
            plt.xticks(ftLocs, ftList);

    plt.colorbar(orientation="horizontal");
    print ('saving...')
    plt.savefig(str(sys.argv[2]))
    print('done!')

    ##########
if drawChoice == "s":

# cropChoice = input("Select section? y/n: ")
#
# if cropChoice == "y":
    startY = inputNumber("Start Object: ");
    endY   = inputNumber("End Object  : ");
    startX = inputNumber("Start Feature: ");
    endX   = inputNumber("End Feature  : ");

    df = df[int(startY):int(endY), int(startX):int(endX)];
    print(df);

    plt.pcolormesh(df, cmap=color, vmin=-1, vmax=1)
    plt.colorbar(orientation="horizontal");
    plt.yticks(np.arange(len(nObjList[startY:endY])), nObjList[startY:endY]);
    plt.xticks(np.arange(len(ftList[startX:endX])), ftList[startX:endX]);
    #image drawing to file.
    print ('saving...')
    plt.savefig(str(sys.argv[2]))
    print("done!")

else:
    print("Incorrect choice, please choose f, c, or s.")
