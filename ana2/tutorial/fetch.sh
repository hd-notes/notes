#!/bin/bash
for i in `seq 1 15`;
do
	wget -O Uebungsblatt_$i.pdf http://www.biostruct.uni-hd.de/pdffileAnalysis2/Uebungsblatt_$i.pdf
done  
find . -size 0 -delete
