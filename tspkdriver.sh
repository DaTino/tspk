#!/bin/bash

#check usage
ARGC=$#
if [[ ARGC -lt  3 ]]; then
  echo "Usage: ./tspkdriver data.txt output.txt numClusters"
  exit
fi

#get concorde path from config
CONFIG="tspk_config.txt"
CONCORDE_PATH=$(cat "$CONFIG")

#set variables from usage
DATA=$1
OUTPUT=$2
NCLUST=$3

size_w=8
size_h=10

#preprocess data to remove headers, if there are any
#generates file called headerlessData.txt for later use
python3 preprocess.py $DATA
HLDATA="${DATA%.*}Headerless.txt"
#NOBJS=$(wc -l < "./headerlessData.txt")
NOBJS=$(wc -l < "${HLDATA}")
#NENTRIES=$(wc -w < "headerlessData.txt")
NENTRIES=$(wc -w < "${HLDATA}")
NFEAT=$(($NENTRIES / $NOBJS))
OBJLIST="${DATA%.*}ObjectList.txt"
FTLIST="${DATA%.*}FeaturesList.txt"


#output name of heat map and file type
echo "Enter a name for your heatmap: "
read HEATMAP
echo "Enter a filetype [png, jpg, svg]: "
read EXT
HMFILE="${HEATMAP%.*}.${EXT##.*}"

#temporary file to hold concorde output
TOHM="./toHM.txt"
TOHM2="./toHM2.txt"
TOHMNAME="./toHMname.txt"
rm -f $TOHM
touch $TOHM
touch $TOHM2
touch $TOHMNAME

echo "Converting data to .tsp..."
OUT="$(./conv $HLDATA $OUTPUT $NCLUST $NOBJS $NFEAT)"
echo "Conversion complete."
echo "Solving with Concorde..."
OUT="$($CONCORDE_PATH $OUTPUT)"
echo "Solving complete."
TOUR="${OUTPUT%.*}.sol"
OUT="$(./order1 $TOUR $HLDATA $TOHM $NCLUST $NOBJS $NFEAT)"
OUT2="$(./order2 $TOUR $HLDATA $TOHM2 $NCLUST $NOBJS $NFEAT)"
OUTNAME="$(./orderNames $TOUR $OBJLIST $TOHMNAME $NCLUST $NOBJS)"
echo "Generating heatmap"
python3 ./heatmapgen.py $TOHM $HMFILE $size_w $size_h $TOHMNAME $FTLIST

#cleanup
FNAME="${DATA%.*}"
rm -f "${FNAME}.mas" "${FNAME}.pul" "${FNAME}.sav" "${FNAME}.sol" "${FNAME}.tsp"
