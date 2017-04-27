#!/bin/bash

wget --save-cookies cookies.txt --keep-session-cookies --post-data $(cat /home/robin/study/lectures/secrets/moodle) --delete-after https://elearning2.uni-heidelberg.de/login/index.php
match='<a class="" onclick="" href=".*?"><img src="https://elearning2.uni-heidelberg.de/theme/image.php/more/core/1480334238/f/pdf-24" class="iconlarge activityicon" alt=" " role="presentation"><span class="instancename">Blatt .*?<span class="accesshide "> Datei</span></span></a>'
pdfs=$(wget --load-cookies cookies.txt -qO- 'https://elearning2.uni-heidelberg.de/course/view.php?id=12813' | grep -Po '(?<=(href="))https://elearning2.uni-heidelberg.de/mod/resource/view.php.*?(?=")(?=.*?>Blatt .*?<)')

rm *.pdf

for pdf in $pdfs
do
    wget --content-disposition --load-cookies cookies.txt $pdf
done

rm HinweiseZurUebungV4.pdf
rm MusterloesungBlatt01.pdf
