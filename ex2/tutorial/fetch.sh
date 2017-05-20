#!/bin/bash

IFS=$'\n'

wget --save-cookies cookies.txt --keep-session-cookies --post-data $(cat /home/robin/study/lectures/secrets/moodle) --delete-after https://elearning2.uni-heidelberg.de/login/index.php

pdfs=$(wget --load-cookies cookies.txt -qO- 'https://elearning2.uni-heidelberg.de/course/view.php?id=14332' | pcregrep --buffer-size 10M -o1 '(https:\/\/elearning2\.uni-heidelberg\.de\/mod\/resource\/view\.php\?id=\d*?)"><img src="https:\/\/elearning2\.uni-heidelberg\.de\/theme\/image\.php\/more\/core\/1495103316\/f\/pdf-24" class="iconlarge activityicon" alt=" " role="presentation" \/><span class="instancename">\d*. Übungsblatt')

echo $pdfs

rm *.pdf

for pdf in $pdfs
do
    wget --content-disposition --load-cookies cookies.txt $pdf
done
