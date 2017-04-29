#!/bin/bash
pdfs=$(wget -qO- https://typo.iwr.uni-heidelberg.de/groups/mobocon/teaching/numerik-0-ss17/ | grep -o 'href=".*blatt.*pdf"')
rm *.pdf

for pdf in $pdfs
do
	wget --content-disposition "https://typo.iwr.uni-heidelberg.de/$(sed 's/href="//g; s/"//g' <<< $pdf)"
done  
find . -size 0 -delete
