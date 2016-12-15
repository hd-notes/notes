#!/bin/bash

wget --save-cookies cookies.txt --keep-session-cookies --post-data $(cat /home/robin/study/lectures/secrets/theo) --delete-after https://uebungen.physik.uni-heidelberg.de/uebungen/login.php
pdfs=$(wget --load-cookies cookies.txt -qO- 'https://uebungen.physik.uni-heidelberg.de/uebungen/liste.php?vorl=683' | grep -o 'uebungen/download/.*pdf')

for pdf in $pdfs 
do
    grep UB0.pdf <<< $pdf > /dev/null && continue;
    num=$(grep -o UB.*pdf <<< $pdf | sed 's/UB//g' | sed 's/\.pdf//g')
    wget --load-cookies cookies.txt -O UB$num.pdf "https://uebungen.physik.uni-heidelberg.de/$pdf"
done
