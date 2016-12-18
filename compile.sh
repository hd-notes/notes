#!/bin/bash

files=$(find . -type f -name '*.org')

configfile=$(realpath emacs_config.el)

for file in $files 
do 
	grep TITLE $file > /dev/null || continue
    emacs $file --batch -l $configfile -f org-latex-export-to-latex --kill
done

make


