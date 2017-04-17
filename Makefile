rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
tex_files = $(call rwildcard, , *.tex)
pdf_files = $(tex_files:.tex=.pdf)
pdf_files_continous = $(tex_files:.tex=.pdfc)
clean_files = $(tex_files:.tex=.does_not_exist)

.PHONY : FORCE_MAKE

%.does_not_exist: %.tex
	latexmk --pdf -cd -c -pdflatex="xelatex -8bit %O %S" $<	

%.pdf: %.tex FORCE_MAKE
#	latexmk -xelatex -cd --silent --shell-escape -pdflatex="xelatex -8bit %O %S" $<	
	latexmk --pdf -cd --shell-escape -pdflatex="xelatex -8bit %O %S" $<	
#	latexmk -xelatex -cd -c -pdflatex="xelatex -8bit %O %S" $<	

all: $(pdf_files)

%.pdfc: %.tex
	latexmk --pdf -cd --interaction=nonstopmode -pvc --shell-escape -pdflatex="xelatex -8bit %O %S" $<	

continuous: $(pdf_files_continous)

.PHONY: clean clobber
clean: $(clean_files)
	find . -mindepth 2 -maxdepth 2 -name '*.pdf' -delete

clobber: $(clean_files)
